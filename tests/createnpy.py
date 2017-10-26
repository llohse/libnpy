#!/usr/bin/python3

import numpy

data = [ [1, 2, 3], [4, 5, 6], ]

dtypes = ['f4', 'f8', 
          'i1', 'i2', 'i4', 'i8',
          'u1', 'u2', 'u4', 'u8',
          'c8', 'c16', ]

for d in dtypes:
  a = numpy.array(data, numpy.dtype(d))
  numpy.save('data/' + d + ".npy", a)

booldata = [ [False, True, False], [True, False, True], ]
a = numpy.array(booldata, numpy.dtype(bool))
numpy.save('data/' + 'bool' + ".npy", a)
