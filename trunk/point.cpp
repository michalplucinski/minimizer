#include <point.hpp>
#include <cmath>

void Point::copy(const Point & other)
{
   mX = other.mX;
   mY = other.mY;
   mZ = other.mZ;
}

Point::Point()
{
   mX = 0;
   mY = 0;
   mZ = 0;
}

Point::Point(double x, double y, double z)
{
   mX = x;
   mY = y;
   mZ = z;
}

//dot product
double Point::operator* (const Point & other) const
{
   return mX * other.mX + mY * other.mY + mZ * other.mZ;
}

//scalar product
Point Point::operator* (double num) const
{
   Point product(mX * num, mY * num, mZ * num);
   return product;
}

Point Point::operator+ (const Point & other) const
{
   Point sum(mX + other.mX, mY + other.mY, mZ + other.mZ);
   return sum;
}

Point& Point::operator+= (const Point & other)
{
   mX += other.mX;
   mY += other.mY;
   mZ += other.mZ;
   return *this; 
}

Point Point::operator- (const Point & other) const
{
   Point diff(mX - other.mX, mY - other.mY, mZ - other.mZ);
   return diff;
}

bool Point::operator== (const Point & other) const
{
   return mX == other.mX && mY == other.mY && mZ == other.mZ;
}

double Point::coord(int n) const
{
   switch (n)
   {
      case 0:
         return mX;
      case 1:
         return mY;
      case 2:
         return mZ;
      default:
         return mX;
   }
}

double Point::quadrance() const
{
   return mX*mX + mY*mY + mZ*mZ;
}

double Point::distance() const
{
   return pow( quadrance(), .5);
}

//Scalar projection of this onto other
double Point::scalarProj (const Point & other) const
{
   return ((*this)*other)/other.distance();
}

void Point::setCoord(double val, int n)
{
   switch (n)
   {
      case 0:
         mX = val;
      case 1:
         mY = val;
      case 2:
         mZ = val;
      default:   
         mX = val;
   }
}

//Cross product
Point Point::cross (const Point& other) const
{
   Point product;
   product.mX = mY*other.mZ - mZ*other.mY;
   product.mY = mZ*other.mX - mX*other.mZ;
   product.mZ = mX*other.mY - mY*other.mX;
   return product;
}

Point Point::normalize () const
{
   Point unit(mX/distance(), mY/distance(), mZ/distance);
   return unit;
}

Point Point::rotate (double theta, const Point & axis) const
{
   Point rot( (*this)*cos(theta) );
   axis = axis.normalize();
   rot += ( axis.cross(*this) ) * sin(theta);
   rot += ( axis * ( (axis*(*this)) * (1-cos(theta)) ) );
   return rot; 
}
