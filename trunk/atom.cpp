#include <atom.hpp>
#include <point.hpp>
#include <cstdlib>
#include <ctime>

Atom::Atom ()
{
   for (int i=0; i<sNeighbourCount; i++)
   {
      neighbours[i] = this;
   }
   neighbourCount = 0;
}

Atom::Atom (Point & target, int index)
{
   setPos(target);
   atomIndex = index;
   for (int i=0; i<sNeighbourCount; i++)
   {
      neighbours[i] = this;
   }
   neighbourCount = 0;
}

Atom::Atom (const Atom & target)
{
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

void Atom::clearNeighbours()
{
   for (int i=0; i<sNeighbourCount; i++)
   {
      delNeighbour(i);
   }
   neighbourCount = 0;
}

void Atom::setPos(double val, char dimen)
{
   switch (dimen)
   {
      case 'x':
         pos.x(val);
         break;
      case 'y':
         pos.y(val);
         break;
      case 'z':
         pos.z(val);
         break;
   }     
}

void Atom::setPos(Point & coord)
{
   pos = coord;
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

Atom * Atom::getNeighbour(int num)
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

double Atom::getPos(char dimen)
{
   switch (dimen)
   {
      case 'x':
         return pos.x();
      case 'y':
         return pos.y();
      case 'z':
         return pos.z();
      default:
         return pos.x();
   }
}

const Point& Atom::getPos()
{
   return pos;
}

void Atom::setIndex(int num)
{
   atomIndex = num;
}

int Atom::getIndex()
{
   return atomIndex;
}

int Atom::getNeighbourIndex(int num)
{
   return neighbours[num]->atomIndex;
}
