#include <matrix.hpp>

#ifndef POINT_H
#define POINT_H

class Point: public Matrix
{
   public:
      Point () {Matrix(3,1);}
      Point (double n) {Matrix(3,1,n);}
      Point (double, double, double);
      Point (const Point& other) {copy(other);}
      double dot (const Point&) const;
      Point cross (const Point&) const;
//      Point operator* (double n) const {return (*this * n);}
//      Point operator+ (const Point& other) const {return (*this + other);}
//      Point operator- (const Point& other) const {return (*this - other);}
      Point& operator= (const Point& other) { copy(other); return *this; }
      bool operator== (const Point&) const;
      double x () const {return get(0,0);}
      double y () const {return get(1,0);}
      double z () const {return get(2,0);}
      double coord (int i) const {return get(i,0);}
      void x (double n) {set(0,0,n);}
      void y (double n) {set(1,0,n);}
      void z (double n) {set(2,0,n);}
      void setCoord (double n, int i) {set(i,0,n);}
      double quadrance () const;
      double distance () const;
      double scalarProj (const Point&) const;
//      Point rotate (double, const Point&) const;
      Point normalize () const;
};

//Point operator*(double d, Point & p) { return p*d; }

#endif
