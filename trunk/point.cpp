#include <point.hpp>
#include <cmath>

Point::Point (double x, double y, double z) 
{
   double xyz[3];
   xyz[0] = x;
   xyz[1] = y;
   xyz[2] = z;
   Matrix(xyz, 3,1); 
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

/*Point Point::rotate (double theta, const Point & axis) const
{
   Point rot( (*this)*cos(theta) );
   axis = axis.normalize();
   rot += ( axis.cross(*this) ) * sin(theta);
   rot += ( axis * ( (axis.dot(*this)) * (1-cos(theta)) ) );
   return rot; 
}*/
