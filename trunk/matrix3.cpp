#include <matrix3.hpp>
#include <iostream>
#include <minexcept.hpp>
#include <cmath>

Matrix3::Matrix3 (const Point& c1, const Point& c2, const Point& c3) : Matrix(3,3)
{
   int i;
   
   for (i=0; i<3; i++)
      set( i, 0, c1.coord(i) );
   for (i=0; i<3; i++)
      set( i, 1, c2.coord(i) );
   for (i=0; i<3; i++)
      set( i, 2, c3.coord(i) );
}

Matrix3::Matrix3 (const Matrix& other) : Matrix(3,3)
{
   if (other.columns() != 3 || other.rows() != 3)
   {
      std::cout << other.columns() << ' ' << other.rows() << std::endl;
      throw BadOperator();
   }
   copy(other);
}
      
void Matrix3::setPoint (const Point& other, int n)
{
   for (int i=0; i<3; i++)
      set( i,n, other.coord(i) );
}
      
void Matrix3::setDiag (const Point& other)
{
   for (int i=0; i<3; i++)
      Matrix::setDiag( i, other.coord(i) );
}

double Matrix3::tripleProduct() const
{
   return getPoint(0).dot( getPoint(1).cross(getPoint(2)) );
}
