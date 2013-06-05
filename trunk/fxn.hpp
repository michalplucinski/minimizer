#ifndef FXN_H
#define FXN_H

#include <matrix.hpp>
#include <matrix3.hpp>
#include <vector>
#include <point.hpp>
#include <atom.hpp>
#include <cmath>

class Atom;

//All info needed about the function
class Parameters
{
   private:
      int mpnt; //number of points
      int mvar; //number of variables, must always be 3*pnt
      int mcxn; //number of connections per atom
      Matrix3 mdim; //matrix of the cell vectors
      Point mlen; //The length of each cell vector
      double mdist; //Optimal bond distance
      std::vector<int> mpairs; //List of bonds
      double mk; //Elastic constant, k
      void copy (const Parameters&);
   public:
      Parameters ();
      Parameters (const Parameters& other) {copy(other);}
      int pnt () const {return mpnt;}
      int var () const {return mvar;}
      int cxn () const {return mcxn;}
      double dist () const {return mdist;}
      Point len () const {return mlen;}
      const std::vector<int>& pairs () {return mpairs;}
      Point dim (int n) const {return mdim.getPoint(n);}
      const Matrix3& dim () const {return mdim;}
      double volume() const {return fabs( mdim.tripleProduct() );}
      double k () const {return mk;}
      
      void k (double n) {mk = n;}
      void pnt (int n) {mpnt = n; mvar = n*3;}
      void cxn (int n) {mcxn = n;}
      void dist (double n) {mdist = n;}
      void setDim (Point pt, int n) {mdim.setPoint(pt,n); mlen.setCoord(pt.distance(), n);}
      void setDim (const Matrix3&);
      void genBondList (std::vector<Atom>&);

      Parameters& operator= (const Parameters& other) {copy(other); return *this;}
      void strain (const Point&);
      void strain (const Point&, const Point&);
      void strain (const Matrix3&);
      
      Point getRealDiff (Point&, Point&); //Returns the distance between atoms bonded across cell boundaries
      Point checkPeriodBound (Point&); //Shifts a point back into the cell if the optimization moves it outside
};

double optimizer (std::vector<Point>&, Parameters&, double, double);

#endif
