#include <matrix.hpp>
#include <exception>
#include <minexcept.hpp>

void Matrix::copy (const Matrix& other)
{
   width = other.width;
   height = other.height;
   for (int i=0; i<height; i++)
   {
      for (int j=0; j<width; j++)
      {
         set(i,j, other.get(i,j) );
      }
   }
}

Matrix::Matrix ()
{
   width = 3;
   height = 3;
   mElements = new double [width*height];
   setAll(0);
}

Matrix::Matrix (int h, int w)
{
   width = w;
   height = h;
   mElements = new double [width*height];
   setAll(0);
}

Matrix::Matrix (int h, int w, double n)
{
   width = w;
   height = h;
   mElements = new double [width*height];
   setAll(n);
}

Matrix::Matrix (const double other[], int h, int w)
{
   width = w;
   height = h;
   mElements = new double [width*height];
   for (int i=0; i<h; i++)
   {
      for (int j=0; j<w; j++)
      {
         set(i, j, other[i*w+j]);
      }
   }
}

Matrix::Matrix (double * other, int h, int w)
{
   width = w;
   height = h;
   mElements = new double [width*height];
   for (int i=0; i<h; i++)
   {
      for (int j=0; j<w; j++)
      {
         set(i, j, other[i*w+j]);
      }
   }
}

Matrix::~Matrix ()
{
   delete[] mElements;
}

double Matrix::get (int i, int j) const
{
   if (i >= height || j >= width)
   {
      throw BadIndex();
   }

   return mElements[i*width + j];
}

#include <iostream>
void Matrix::set (int i, int j, double n)
{
   if (i >= height || j >= width)
   {
      throw BadIndex();
   }
   std::cout << 'h' << std::endl;
   mElements[i*width + j] = n;
}

void Matrix::setAll (double n)
{
   for (int i=0; i<height; i++)
   {
      for (int j=0; j<width; j++)
      {
         set(i, j, n);
      }
   }
}

Matrix Matrix::operator+ (const Matrix& other) const
{
   if (width != other.width || height != other.height)
   {
      throw BadOperator();
   }

   Matrix sum(width, height);

   for (int i=0; i<height; i++)
   {
      for (int j=0; j<width; j++)
      {
         sum.set(i,j, get(i,j) + other.get(i,j) );
      }
   }
   return sum;
}

Matrix Matrix::operator- (const Matrix& other) const
{
   if (width != other.width || height != other.height)
   {
      throw BadOperator();
   }

   Matrix diff(width, height);

   for (int i=0; i<height; i++)
   {
      for (int j=0; j<width; j++)
      {
         diff.set(i,j, get(i,j) - other.get(i,j) );
      }
   }
   return diff;
}

Matrix Matrix::operator* (double n) const
{
   Matrix product(width, height);

   for (int i=0; i<height; i++)
   {
      for (int j=0; j<width; j++)
      {
         product.set(i,j, get(i,j) * n );
      }
   }
   return product;
}

Matrix Matrix::operator* (const Matrix& other) const
{
   if (width != other.height)
   {
      throw BadOperator();
   }

   Matrix product(height, other.width);
   double element;

   for (int i=0; i<height; i++)
   {
      for (int j=0; j<other.width; j++)
      {
         element = 0;
         for (int k=0; k<width; k++)
         {
            element += (get(i,k) * other.get(k,j));
         }
         product.set(i,j, element);
      }
   }
   return product;
}
