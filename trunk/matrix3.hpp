#ifndef MATRIX3_H
#define MATRIX3_H

#include <matrix.hpp>
#include <cstring>
#include <point.hpp>

class Matrix3: public Matrix
{
   public:
      Matrix3 () : Matrix(3,3) {}
      Matrix3 (double n) : Matrix(3,3,n) {}
      Matrix3 (const Matrix3& other) : Matrix(3,3) {copy(other);}
      Matrix3 (const Point&, const Point&, const Point&);
      Matrix3 (const Matrix&);
      
      Matrix3 operator* (double n) const {Matrix3 product( Matrix::operator* (n)); return product;}
      Matrix3 operator* (const Matrix3& other) const {Matrix3 product( Matrix::operator* (other)); return product;}
      Point operator* (const Point& other) const {Point product( Matrix::operator* (other)); return product;}
      Matrix3 operator+ (const Matrix3& other) const {Matrix3 sum (Matrix::operator+(other)); return sum;}
      Matrix3 operator- (const Matrix3& other) const {Matrix3 diff (Matrix::operator-(other)); return diff;}
      Matrix3& operator= (const Matrix3& other) { return *static_cast<Matrix3*> (&Matrix::operator=(other)) ; }
      Matrix3& operator+= (const Matrix3& other) { return *static_cast<Matrix3*> (&Matrix::operator+=(other)) ; }
      Matrix3& operator*= (const Matrix3& other) { return *static_cast<Matrix3*> (&Matrix::operator*=(other)) ; }
      
      Point getPoint (int n) const {Point column (getCol(n)); return column;}
      Point operator[] (size_t n) {return getPoint(n);}
      double tripleProduct() const;
      
      void setPoint (const Point&, int);
      void setDiag (const Point&);
};

#endif
