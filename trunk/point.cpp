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
   double a = basis.getPoint(0).distance();
   double b = basis.getPoint(1).distance();
   double c = basis.getPoint(2).distance();
   double al = basis.getAngle(0);
   double be = basis.getAngle(1);
   double ga = basis.getAngle(2);
   double v = sqrt( 1 -pow(cos(al),2) -pow(cos(be),2) -pow(cos(ga),2) + 2*cos(al)*cos(be)*cos(ga) );
   
   Matrix3 changeOfBasis;
   changeOfBasis.set(0,0, 1/a );
   changeOfBasis.set(0,1, -cos(ga)/a/sin(ga) );
   changeOfBasis.set(0,2, (cos(al) *cos(ga) -cos(be)) /a /v /sin(ga) );
   changeOfBasis.set(1,1, 1 /b /sin(ga) );
   changeOfBasis.set(1,2, (cos(be) *cos(ga) -cos(al)) /b /v /sin(ga) );
   changeOfBasis.set(2,2, sin(ga)/c/v );
   
   basisPt = changeOfBasis*(*this);
   
   return basisPt;
}

Point Point::xyzBasis (const Matrix3& basis) const
{
   Point xyzPt;
   
   double a = basis.getPoint(0).distance();
   double b = basis.getPoint(1).distance();
   double c = basis.getPoint(2).distance();
   double al = basis.getAngle(0);
   double be = basis.getAngle(1);
   double ga = basis.getAngle(2);
   double v = sqrt( 1 -pow(cos(al),2) -pow(cos(be),2) -pow(cos(ga),2) + 2*cos(al)*cos(be)*cos(ga) );

   Matrix3 changeOfBasis;
   changeOfBasis.set(0,0, a );
   changeOfBasis.set(0,1, b *cos(ga) );
   changeOfBasis.set(0,2, c *cos(be) );
   changeOfBasis.set(1,1, b *sin(ga) );
   changeOfBasis.set(1,2, c *(cos(al) -cos(be) *cos(ga)) /sin(ga) );
   changeOfBasis.set(2,2, c *v /sin(ga));
   
   xyzPt = changeOfBasis*(*this);

   return xyzPt;
}

double Point::angle (const Point& other) const
{
   return acos( dot(other)/distance()/other.distance() );
}
