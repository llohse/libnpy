#!/usr/bin/python3

import numpy
from pathlib import Path
import sys

outdir = Path(sys.argv[1] if len(sys.argv) > 1 else "data")
outdir.mkdir(exist_ok=True)

data_categories = {
  "matrix": [ [1, 2, 3], [4, 5, 6], ],
  "empty":  [ [], [], ],
  "scalar": 42,
}

dtypes = ['f4', 'f8', 
          'i1', 'i2', 'i4', 'i8',
          'u1', 'u2', 'u4', 'u8',
          'c8', 'c16', ]

for d in dtypes:
  for data_name, data in data_categories.items():
    a = numpy.array(data, numpy.dtype(d))
    numpy.save(outdir / f"{data_name}_{d}.npy", a)
    numpy.save(outdir / f"{data_name}_{d}_t.npy", a.T)

booldata = [ [False, True, False], [True, False, True], ]
a = numpy.array(booldata, numpy.dtype(bool))
numpy.save(outdir / "bool.npy", a)
numpy.save(outdir / "bool_t.npy", a.T)
