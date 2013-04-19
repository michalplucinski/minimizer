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

double Point::operator* (const Point & other) const
{
   return mX * other.mX + mY * other.mY + mZ * other.mZ;
}

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
   }
}
