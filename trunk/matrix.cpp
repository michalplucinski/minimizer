#include <matrix.hpp>
#include <exception>
#include <minexcept.hpp>
#include <iostream>

void Matrix::copy (const Matrix& other)
{
   width = other.width;
   height = other.height;
   delete[] mElements;
   mElements = new double [width*height];
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
   width = 0;
   height = 0;
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
   //std::cout << h << ' ' << w << std::endl;
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
      std::cout << i << ' ' << j << std::endl;
      std::cout << height << ' ' << width << std::endl;
      throw BadIndex();
   }

   return mElements[i*width + j];
}

void Matrix::set (int i, int j, double n)
{
   if (i >= height || j >= width)
   {
      std::cout << i <<  ' ' << height << ' ' << j << ' ' << width << ' ' << n << std::endl;
      throw BadIndex();
   }
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

   Matrix sum(height, width);

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

   Matrix diff(height, width);

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
   Matrix product(height, width);
   
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

Matrix Matrix::getCol(int n) const
{
   Matrix column(height, 1);
   
   for (int i=0; i<height; i++)
      column.set( i,0, get(i,n) );
   
   return column;
}

