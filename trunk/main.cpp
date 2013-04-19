#include <iostream>
#include <fstream>

#include <vector>
#include <string>

#include <cmath>
#include <cstdlib>

#include <atom.hpp>
#include <point.hpp>
#include <fxn.hpp>

#define debug(x) cout << __LINE__ << ' ' << x << endl; cout.flush();

using namespace std;

void readAtoms(vector<Atom>&, string, Parameters&);
void multiplyCell(vector<Atom>&, Point&, Parameters&, Parameters&);
void connectAtoms(vector<Atom>&, int, Parameters&);
void outputAtoms(vector<Atom>&, string, Parameters&, double);

int mod(int, int); 

double energy (vector<Atom>&, Parameters&, double, double, double);

int main (int argc, char* argv[])
{
   string inputFile = argv[1];
   vector<Atom> atomList;
   Parameters param, unitCellParam, strainParam;
   
   int exBond = atoi(argv[2]);
   int cellFactor = atoi(argv[3]);
   Point cellMultiply(cellFactor, cellFactor, cellFactor);

   readAtoms(atomList, inputFile, unitCellParam);
   multiplyCell(atomList, cellMultiply, unitCellParam, param);
   connectAtoms(atomList, exBond, param);
  // param.dist = 0;
  
   //defines parameters for optimization 
   double potential;
   double stepSize = .01;
   double tolerance = 1e-2;
   double expectedEnergy = 0;
   Point strainFactor(1,1,1);

   //Shifts Atoms off Minimum
//   double num = atomList[2].getPos('x');
//   atomList[2].setPos( num+.1, 'x');
   
//   potential = energy(atomList, param, stepSize, tolerance, expectedEnergy);
//   cout << potential << endl;
   
   for (double i=1; i<1.1; i+=.01)
   {
      strainParam = param;
      strainFactor.setAll(i);
      strainParam.strain(strainFactor);
      potential = energy(atomList, strainParam, stepSize, tolerance, expectedEnergy);
      cout << strainFactor.x() << ' ' << potential << endl;
   }
   for (double i=1; i>.9; i-=.01)
   {
      strainParam = param;
      strainFactor.setAll(i);
      strainParam.strain(strainFactor);
      potential = energy(atomList, strainParam, stepSize, tolerance, expectedEnergy);
      cout << strainFactor.x() << ' ' << potential << endl;
   }
      strainParam = param;
            strainFactor.setAll(.9);
      strainParam.strain(strainFactor);
      potential = energy(atomList, strainParam, stepSize, tolerance, expectedEnergy);
      cout << strainFactor.x() << ' ' << potential << endl;
      strainParam = param;
            strainFactor.setAll(1.3);
      strainParam.strain(strainFactor);
      potential = energy(atomList, strainParam, stepSize, tolerance, expectedEnergy);
      cout << strainFactor.x() << ' ' << potential << endl;
      strainParam = param;
            strainFactor.setAll(1.6);
      strainParam.strain(strainFactor);
      potential = energy(atomList, strainParam, stepSize, tolerance, expectedEnergy);
      cout << strainFactor.x() << ' ' << potential << endl;
   outputAtoms(atomList, inputFile, strainParam, potential);

   return 0;
}

double energy (vector<Atom>& atomList, Parameters& param, double stepSize, double tolerance, double expect)
{
   double potential;
   int i;

   vector<Point> positions(param.pnt());
   for (i=0; i<param.pnt(); i++)
      positions[i] = atomList[i].getPos();

   param.genBondList(atomList);
   
   potential = optimizer(positions, param, stepSize, tolerance, expect);
   for (i=0; i<param.pnt(); i++)
   {
      atomList[i].setPos(positions[i]);
   }

   return potential;
}

int mod(int x, int m) 
{
   return (x%m + m)%m;
}

void readAtoms(vector<Atom> & atoms, string fileName, Parameters & p)
{
   string buffer;
   fstream file (fileName.c_str(), fstream::in | fstream::out);
   double x,y,z;
   int i,n;
   Point tmp;
   Atom newAtom;

   file >> buffer >> buffer;
   for (i=0;i<3;i++)
   {
      file >> x >> y >> z;
      tmp.x(x);
      tmp.y(y);
      tmp.z(z);
      p.dim(tmp, i);
   }
   
   file >> buffer >> n >> buffer;
   p.pnt(n);
   for (i=0;i<p.pnt();i++)
   {
      file >> n >> x >> y >> z;
      tmp.x(x);
      tmp.y(y);
      tmp.z(z);
      newAtom.setPos(tmp);
      newAtom.setIndex(i);
      atoms.push_back(newAtom);
   }
   file.close();
}

//Assumes atom connections will be generated afterwards
void multiplyCell(vector<Atom> & atoms, Point & n, Parameters & op, Parameters & np)
{
   int i,j,k,m;
   unsigned int index;
   Atom newAtom;
   
   np = op;
   np.pnt( op.pnt() * (n.x() * n.y() * n.z()) );
   
   for (i=0;i<3;i++)
      np.dim(op.dim(i)*n.coord(i), i);

   for (i=0;i<n.x();i++)
   {
      for (j=0;j<n.y();j++)
      {
         for (k=0;k<n.z();k++)
         {
            for (m=0;m<op.pnt();m++)
            {
               Point pos;
               pos = atoms[m].getPos();
               index = m + k*op.pnt() + j*n.z()*op.pnt() + i*n.y()*n.z()*op.pnt();
               pos = (op.dim(0)*i) + pos;
               pos = (op.dim(1)*j) + pos;
               pos = (op.dim(2)*k) + pos;
               if (index < atoms.size())
               {
                  atoms[index].setPos( pos );
                  atoms[index].setIndex(index);
                  atoms[index].clearNeighbours();
               }
               else
               {
                  newAtom.setPos(pos);
                  newAtom.setIndex(index);
                  atoms.push_back(newAtom);
               }
            }
         }
      }
   }
}

void connectAtoms(vector<Atom> & atoms, int target, Parameters & p)
{
   int size = atoms.size();
   Point a,b;
   int nBond = 0;
   p.cxn(0);
   double cellDist;
   double epsilon = 1e-8;

   p.dist( abs( (atoms[0].getPos() - atoms[target].getPos()).distance() ) );
   
   for (int i=0; i<size; i++)
   {
      for (int j=0; j<size; j++)
      {
         if (i == j)
            continue;
         a = atoms[i].getPos();
         b = atoms[j].getPos();
         cellDist = abs( (p.getRealDiff(a,b)).distance());
         if ( abs(cellDist - p.dist()) < epsilon)
         {
            atoms[i].setNeighbour(&atoms[j]);
            nBond++;
         }
      }
      if (nBond > p.cxn())
         p.cxn(nBond);
      nBond = 0;
   }
}

void outputAtoms(vector<Atom> & atoms, string fileName, Parameters & p, double potential)
{
   int i;
   fstream file ( (fileName.append(".out")).c_str(), fstream::in | fstream::out | fstream::trunc);
   
   file << "CRYSTAL\n" << "PRIMVEC\n";
   
   for (i=0;i<3;i++)
      file << (p.dim(i)).x() << " " << (p.dim(i)).y() << " " << (p.dim(i)).z() << "\n";

   file << "PRIMCOORD\n" << p.pnt() << " 1\n";
   
   for (i=0;i<p.pnt();i++)
   {
      file << "6 " << atoms[i].getPos('x') << " " << atoms[i].getPos('y') << " " << atoms[i].getPos('z') 
      << ' ' << atoms[i].getNeighbourIndex(0) << ' ' <<atoms[i].getNeighbourIndex(1) << ' '
      << atoms[i].getNeighbourIndex(2) << ' ' <<atoms[i].getNeighbourIndex(3) << '\n';
      
//      cout << atoms[i].getPos('x') << " " << atoms[i].getPos('y') << ' ' << atoms[i].getPos('z') << "   ";
   }

   cout  << potential << "\n";
   file.close();
}
