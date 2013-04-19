#!/usr/bin/python

from scipy.optimize import fmin_bfgs
from numpy import *
from numpy.random import uniform

def pot(x,d):
    natom = x.size
    cell_length = natom*d
    pot_e = (x[0] - (x[natom-1]-cell_length) - d)*(x[0] - (x[natom-1]-cell_length) - d)
    for ii in range(1,natom):
        pot_e = pot_e + (x[ii]-x[ii-1] - d)*(x[ii]-x[ii-1] - d)
    pot_e = 0.5*pot_e
    return pot_e

def gradpot(x,d):
    natom = x.size
    cell_length = natom*d
    dpot_e = zeros(natom)
    dpot_e[0] = (x[0]-(x[natom-1]-cell_length)-d)-(x[1]-x[0]-d)
    dpot_e[natom-1] = (x[natom-1]-x[natom-2]-d)-(x[0]+cell_length-x[natom-1]-d)
    for ii in range(1,natom-1):
        dpot_e[ii] = (x[ii]-x[ii-1]-d)-(x[ii+1]-x[ii]-d)
    return dpot_e

d = 0.6
x = zeros(100)
for ii in range(0,x.size):
    x[ii] = d*ii + uniform(-0.05,0.05)

xopt = fmin_bfgs(pot,x,args=(d,),gtol=1.0E-8,maxiter=100,fprime=gradpot)

for ii in range(x.size):
    x[ii] = xopt[ii]-xopt[0]

#print xopt
print x
