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
      Matrix (const Matrix& other) { copy(other); }
      Matrix (int, int);
      Matrix (int, int, double);
      Matrix (const double [], int, int);
      Matrix (double*, int, int);
      ~Matrix ();
      double get (int, int) const;
      void set (int, int, double);
      void setAll (double);
      virtual Matrix operator* (const Matrix&) const;
      virtual Matrix operator* (double) const;
      virtual Matrix operator+ (const Matrix&) const;
      virtual Matrix operator- (const Matrix&) const;
      virtual Matrix& operator= (const Matrix& other) { copy(other); return *this; }
      virtual Matrix& operator+= (const Matrix& other) { *this = other + *this; return *this; }
};

#endif
