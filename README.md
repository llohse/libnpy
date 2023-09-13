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

The API has changed in the last release. The old C-style API is still available, but might get removed in the future.

### Reading data:
```c++
#include "npy.hpp"
#include <vector>
#include <string>

int main() {
  
  const std::string path {"data.npy"};
  npy::npy_data d = npy::read_npy<double>(path);

  std::vector<double> data = d.data;
  std::vector<unsigned long> shape = d.shape;
  bool fortran_order = d.fortran_order;
}

```

### Writing data:
```c++
#include "npy.hpp"
#include <vector>
#include <string>

int main() {
  const std::vector<double> data{1, 2, 3, 4, 5, 6};

  npy::npy_data d;
  d.data = data;
  d.shape = {2, 3};
  d.fortran_order = false; // optional

  const std::string path{"out.npy"};
  write_npy(path, d);
}

```

This will involve an additional copy of the data, which might be undesireable for larger data. The copy can be avoided by using `npy::npy_data_ptr` as follows.

```c++
#include "npy.hpp"
#include <vector>
#include <string>

int main() {
  const std::vector<double> data{1, 2, 3, 4, 5, 6};

  npy::npy_data_ptr d;
  d.data_ptr = data.data();
  d.shape = {2, 3};
  d.fortran_order = false; // optional

  const std::string path{"out.npy"};
  write_npy(path, d);
}

```

See `test/` for further examples.
C++14 is required.

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

The code is formatted with clang-format.
Please test your changes by running the tests and static analysis.
Meson automatically builds a target for clang-tidy: 
```
cd tests
meson setup builddir
ninja -C builddir clang-tidy
```

## License
The project is licensed under the [MIT](LICENSE) license
