#include <assert.h>
#include <fxn.hpp>
#include <iostream>

int main ()
{
   Point a(5.05524,0,0);
   Point b(2.52762, 4.37796, 0);
   Point c(2.52762, 1.45932, 4.12758);

   Parameters dimensions;
   dimensions.setDim(a,0);
   dimensions.setDim(b,1);
   dimensions.setDim(c,2);

   a = Point(4.42333, 2.55381, 1.80582);
   b = Point(0.631905, 0.36483, 0.257974);

   assert(
}

