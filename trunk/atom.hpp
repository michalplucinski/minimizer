#ifndef ATOM_H
#define ATOM_H

#include <point.hpp>

class Atom
{
   private:
      int atomIndex;
      Point pos;
      static const int sNeighbourCount=4;
      Atom *neighbours[sNeighbourCount];
      int neighbourCount;
   public:
      Atom();
      Atom(Point&, int);
      Atom(const Atom&);
      void setPos(double, char);
      void setPos(Point&);
      double getPos(char);
      const Point& getPos();
      void setNeighbour(Atom*);
      Atom* getNeighbour(int);
      void delNeighbour(int);
      void clearNeighbours();
      void setIndex(int);
      int getIndex();
      int getNeighbourIndex(int);
      void delRandNeighbour();
};

#endif
