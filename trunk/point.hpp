#ifndef POINT_H
#define POINT_H

class Point
{
   private:
      double mX,mY,mZ;
      void copy(const Point&);
   public:
      Point ();
      Point (double, double, double);
      Point (const Point& other) {copy(other);}
      double operator* (const Point&) const;
      Point operator* (double) const;
      Point cross (const Point&) const;
      Point operator+ (const Point&) const;
      Point operator- (const Point&) const;
      Point& operator= (const Point& other) { copy(other); return *this; }
      Point& operator+= (const Point&);
      bool operator== (const Point&) const;
      double x () const {return mX;}
      double y () const {return mY;}
      double z () const {return mZ;}
      double coord (int) const;
      void x (double n) {mX = n;}
      void y (double n) {mY = n;}
      void z (double n) {mZ = n;}
      void setCoord (double, int);
      void set (double a, double b, double c) {mX = a; mY = b; mZ = c;}
      void setAll (double n) {mX = n; mY = n; mZ = n;}
      double quadrance () const;
      double distance () const;
      double scalarProj (const Point&) const;
      Point rotate (const Point&, const Point&) const;
      Point normalize () const;
};

//Point operator*(double d, Point & p) { return p*d; }

#endif
