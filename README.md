# libnpy

libnpy is a simple C++ library for reading and writing of numpy's [.npy files](https://docs.scipy.org/doc/numpy/neps/npy-format.html).

Refer to [format.py](https://github.com/numpy/numpy/blob/master/numpy/lib/format.py) for a detailed description of the .npy format.

This libraries primary purpose is *writing* numerical data easily and efficiently into the .npy format.
It also allows *reading* .npy files, although only a very limited subset of data types are supported.

## Features
 - Writing C++ vectors (std::vector<T>) to .npy files
 - Reading (some) simple .npy files into C++ vectors

## Supported data types and mapping
 Only *scalar* *numeric* data types are supported. There is no natural way to represent more complex objects and parsing the header becomes tremendously more complex.
 Supported types:
 - unsigned integer
 - signed integer
 - floating point
 - complex floating point (std::complex<float>, ...)

## Usage
libnpy is a header only library. You only need to download `npy.hpp` into your include path. Neither special compiler flags nor a specific build system are required.

Optional: If you use meson, you can use the provided `meson.build` file to declare the dependency on libnpy.

Reading data:
```c++
#include "npy.hpp"
#include <vector>
#include <string>

int main() {
  std::vector<unsigned long> shape {};
  bool fortran_order;
  std::vector<double> data;
  
  const std::string path {"data.npy"};
  npy::LoadArrayFromNumpy(path, shape, fortran_order, data);
}

```

Writing data:
```c++
#include "npy.hpp"
#include <vector>
#include <string>

int main() {
  const std::vector<long unsigned> shape{2, 3};
  const bool fortran_order{false};
  const std::string path{"out.npy"};

  const std::vector<double> data1{1, 2, 3, 4, 5, 6};
  npy::SaveArrayAsNumpy(path, fortran_order, shape.size(), shape.data(), data1);
}

```

See `test/` for further examples.
C++11 is required. If you use g++, use `-std=c++11`.

## Tests
The tests can be build with `meson>=0.55` and depend on catch2.
```
cd tests
meson setup builddir
meson test -Cbuilddir
```


## Known limitations
1. Only a few data types are supported.

2. The numpy header is a literal Python dictionary and the Python syntax is very permissive. libnpy's parser was only tested with numpy's implemenation of the .npy format.

## Contributing
Feel free to send me a pull request, open an issue, or contact me directly.

## License
The project is licensed under the [MIT](LICENSE) license
