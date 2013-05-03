#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
   private:
      double * mElements;
      int width, height;
   protected:
      void copy (const Matrix&);
   public:
      Matrix ();
      Matrix (const Matrix& other) { mElements = new double [0]; copy(other); }
      Matrix (int, int);
      Matrix (int, int, double);
      Matrix (const double [], int, int);
      Matrix (double*, int, int);
      ~Matrix ();
      double get (int, int) const;
      int columns() const {return width;}
      int rows() const {return height;}
      void set (int, int, double);
      void setAll (double);
      Matrix operator* (const Matrix&) const;
      Matrix operator* (double) const;
      Matrix operator+ (const Matrix&) const;
      Matrix operator- (const Matrix&) const;
      Matrix& operator= (const Matrix& other) { copy(other); return *this; }
      Matrix& operator+= (const Matrix& other) { *this = other + *this; return *this; }
};

#endif
