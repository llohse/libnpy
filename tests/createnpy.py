#!/usr/bin/python3

import numpy

data = [ [1, 2, 3], [4, 5, 6], ]

ar = numpy.array(data, numpy.dtype('double'))
numpy.save("double.npy", ar)

ar2 = numpy.array(data, numpy.dtype('int'))
numpy.save("int.npy", ar2)

ar3 = numpy.array(data, numpy.dtype('u1'))
numpy.save("u1.npy", ar3)
