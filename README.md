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
libnpy is a single-header library for C++14 or later. Use `#include <npy.hpp>` with any of these options.

- **Copy the header.** Put `include/npy.hpp` on your project's include path.
- **Vendor libnpy in a CMake project.** Place the checkout under `external/libnpy/` and add this line after defining your target (here, `app`).

  ```cmake
  target_include_directories(app PRIVATE external/libnpy/include)
  ```

- **Install with Meson.** Run `meson setup build` and `meson install -C build`. Consumers can use `pkg-config --cflags libnpy` or Meson's `dependency('libnpy')`. For a custom prefix, pass `--prefix=/your/prefix` at setup and add `/your/prefix/share/pkgconfig` to `PKG_CONFIG_PATH`.
- **Use a Meson subproject.** Place the checkout in `subprojects/libnpy/` and use `dependency('libnpy', fallback: ['libnpy', 'libnpy_dep'])` in your target's `dependencies`.
- **Use an installed copy from CMake.** With pkg-config available, add the following after defining your target (here, `app`).

  ```cmake
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(LIBNPY REQUIRED IMPORTED_TARGET libnpy)
  target_link_libraries(app PRIVATE PkgConfig::LIBNPY)
  target_compile_features(app PRIVATE cxx_std_14) # C++14 or later
  ```

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
  npy::write_npy(path, d);
}

```

This will involve an additional copy of the data, which might be undesireable for larger data. The copy can be avoided by using `npy::npy_data_ptr` as follows.

```c++
#include "npy.hpp"
#include <vector>
#include <string>

int main() {
  const std::vector<double> data{1, 2, 3, 4, 5, 6};

  npy::npy_data_ptr<double> d;
  d.data_ptr = data.data();
  d.shape = {2, 3};
  d.fortran_order = false; // optional

  const std::string path{"out.npy"};
  npy::write_npy(path, d);
}

```

See `tests/` for further examples.

## Tests
The optional tests require Meson 0.55 or later, Python 3 with NumPy, and Catch2 v2. Meson can fetch Catch2 if needed. Run these commands from the repository root.

```sh
meson setup build -Dtests=true
meson test -C build
```

## Known limitations
1. Only a few data types are supported.

2. The numpy header is a literal Python dictionary and the Python syntax is very permissive. libnpy's parser was only tested with numpy's implemenation of the .npy format.

## Contributing
Feel free to send me a pull request, open an issue, or contact me directly.

The code is formatted with clang-format.
Please test your changes by running the tests and static analysis.
With the test build configured and clang-tidy installed, run

```sh
ninja -C build clang-tidy
```

## License
The project is licensed under the [MIT](LICENSE) license
