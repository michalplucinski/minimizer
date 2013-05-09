#ifndef POINT_H
#define POINT_H

#include <matrix.hpp>

class Matrix3;

class Point: public Matrix
{
   public:
      Point () : Matrix(3,1) {}
      Point (double n) : Matrix(3,1,n) {}
      Point (double, double, double);
      Point (const Point& other) : Matrix(3,1) {copy(other);}
      Point (const Matrix&);
      
      double dot (const Point&) const;
      Point cross (const Point&) const;
      Point operator* (double n) const {Point product( Matrix::operator* (n)); return product;}
      Point operator+ (const Point& other) const {Point sum (Matrix::operator+(other)); return sum;}
      Point operator- (const Point& other) const {Point diff (Matrix::operator-(other)); return diff;}
      Point& operator= (const Point& other) { return *static_cast<Point*> (&Matrix::operator=(other)) ; }
      Point& operator+= (const Point& other) { return *static_cast<Point*> (&Matrix::operator+=(other)) ; }
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
      Point normalize () const;
      Point rotate (double, const Point&) const;
      Point changeBasis (const Matrix3&) const;
      Point xyzBasis (const Matrix3&) const;
};

#endif
