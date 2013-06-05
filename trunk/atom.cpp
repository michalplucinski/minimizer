#include <atom.hpp>
#include <point.hpp>
#include <cstdlib>
#include <ctime>
#include <matrix3.hpp>
#include <minexcept.hpp>
#include <iostream>
#define debug(x) std::cout << __LINE__ << ' ' << x << std::endl; std::cout.flush();

Atom::Atom (Parameters *info)
{
   pos.setAll(0);
   cellInfo = info;
   for (int i=0; i<sNeighbourCount; i++)
   {
      neighbours[i] = this;
   }
   neighbourCount = 0;
}

Atom::Atom(const Point& target, int index, Parameters* info)
{
   cellInfo = info;
   setPos(target);
   atomIndex = index;
   for (int i=0; i<sNeighbourCount; i++)
   {
      neighbours[i] = this;
   }
   neighbourCount = 0;
}
      
void Atom::copy (const Atom& target)
{  
   cellInfo = target.cellInfo;
   for (int i=0; i<sNeighbourCount; i++)
   {
      if (target.neighbours[i] == &target) 
      {
          neighbours[i] = this;
      }
      else 
      {
          neighbours[i] = target.neighbours[i];
      }
   }
   pos = target.pos;
   atomIndex = target.atomIndex;
   neighbourCount = target.neighbourCount;
}

Atom::Atom (const Atom & target)
{
   copy (target);
}

void Atom::clearNeighbours()
{
   for (int i=0; i<sNeighbourCount; i++)
   {
      delNeighbour(i);
   }
   neighbourCount = 0;
}

void Atom::setPos(const Point & coord)
{
   pos = coord.changeBasis(cellInfo->dim());
}

void Atom::setNeighbour(Atom * pTarget)
{
   for (int i=0; i<sNeighbourCount; i++)
   {
      if (neighbours[i] == pTarget)
      {
         break;
      }
      if (neighbours[i] == this)
      {
         neighbours[i] = pTarget;
         pTarget->setNeighbour(this);
         neighbourCount += 1;
         break;
      }
   }
}

void Atom::setParam (Parameters *info)
{
   cellInfo = info;
}

Atom * Atom::getNeighbour(int num) const
{
   return neighbours[num];
}

void Atom::delNeighbour(int num)
{
   int i;

   for(i=0;i<sNeighbourCount;i++)
   {
      if (neighbours[num]->neighbours[i] == this)
      {
         neighbours[num]->neighbours[i] = neighbours[num];
      }
   }
   if (neighbours[num] != this)
      neighbourCount -= 1;
   
   neighbours[num] = this;
}

void Atom::delRandNeighbour()
{
   srand ( time(NULL) );
   delNeighbour(rand() % neighbourCount);
}

double Atom::getPos(char dimen) const
{
   Point posXYZ = pos.xyzBasis(cellInfo->dim());
   switch (dimen)
   {
      case 'x':
         return posXYZ.x();
      case 'y':
         return posXYZ.y();
      case 'z':
         return posXYZ.z();
      default:
         throw BadIndex();
   }
}

double Atom::getPos(int i) const
{
   Point posXYZ = pos.xyzBasis(cellInfo->dim());
   return posXYZ.coord(i);
}

Point Atom::getPos() const
{
   return pos.xyzBasis(cellInfo->dim());
}

void Atom::setIndex(int num)
{
   atomIndex = num;
}

int Atom::getIndex() const
{
   return atomIndex;
}

int Atom::getNeighbourIndex(int num) const
{
   return neighbours[num]->atomIndex;
}
