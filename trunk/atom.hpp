#ifndef ATOM_H
#define ATOM_H

#include <point.hpp>
#include <matrix3.hpp>

class Atom
{
   private:
      int atomIndex;
      Point pos; //position relative to posBasis
      static const int sNeighbourCount=4;
      Atom *neighbours[sNeighbourCount];
      int neighbourCount;
      void copy(const Atom&);
      Matrix3 posBasis; //vectors defining cell Atom is found in
   public:
      Atom();
      Atom(const Matrix3&);
      Atom(const Point&, int);
      Atom(const Point&, int, const Matrix3&);
      Atom(const Atom&);

//      void setPos(double, char);
      void setPos(const Point&);
      void setNeighbour(Atom*);
      void delNeighbour(int);
      void clearNeighbours();
      void delRandNeighbour();
      void setIndex(int);

      double getPos(char) const;
      double getPos(int i) const {return pos.coord(i);}
      Point getPos() const;
      const Point& getRelPos() const {return pos;}
      Atom* getNeighbour(int) const;
      int getIndex() const;
      int getNeighbourIndex(int) const;
      Atom& operator=(const Atom& other) {copy(other); return *this;}
};

#endif
