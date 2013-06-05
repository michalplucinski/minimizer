#include <point.hpp>
#include <cmath>
#include <minexcept.hpp>
#include <iostream>
#include <matrix3.hpp>
#define debug(x) std::cout << __LINE__ << ' ' << x << std::endl; std::cout.flush();

Point::Point (double x, double y, double z) : Matrix(3,1)
{
   set(0,0,x);
   set(1,0,y);
   set(2,0,z);
}

Point::Point (const Matrix& other) : Matrix(3,1)
{
   if (other.columns() != 1 || other.rows() != 3)
   {
      std::cout << other.columns() << ' ' << other.rows() << std::endl;
      throw BadOperator();
   }
   copy(other);
}

//dot product
double Point::dot (const Point & other) const
{
   return x() * other.x() + y() * other.y() + z() * other.z();
}

bool Point::operator== (const Point & other) const
{
   return x() == other.x() && y() == other.y() && z() == other.z();
}

double Point::quadrance() const
{
   return x()*x() + y()*y() + z()*z();
}

double Point::distance() const
{
   return pow( quadrance(), .5);
}

//Scalar projection of this onto other
double Point::scalarProj (const Point & other) const
{
   return (dot(other))/other.distance();
}

//Cross product
Point Point::cross (const Point& other) const
{
   Point product;
   product.x( y()*other.z() - z()*other.y() );
   product.y( z()*other.x() - x()*other.z() );
   product.z( x()*other.y() - y()*other.x() );
   return product;
}

Point Point::normalize () const
{
   Point unit;
   unit.x(x() / distance());
   unit.y(y() / distance());
   unit.z(z() / distance());
   return unit;
}

Point Point::rotate (double theta, const Point & axis) const
{
   Point rot( (*this)*cos(theta) );
   Point normalAxis(axis.normalize());
   rot += ( axis.cross(*this) ) * sin(theta);
   rot += ( axis * ( (axis.dot(*this)) * (1-cos(theta)) ) );
   return rot; 
}

Point Point::changeBasis (const Matrix3& basis) const
{
   Point basisPt;

   for (int i=0; i<3; i++)
   {
      basisPt.setCoord( scalarProj(basis.getPoint(i))/basis.getPoint(i).distance(), i);
   }
   
   return basisPt;
}

Point Point::xyzBasis (const Matrix3& basis) const
{
   Point xyzPt;

   for (int i=0; i<3; i++)
      xyzPt += basis.getPoint(i)*coord(i);
   
   return xyzPt;
}
