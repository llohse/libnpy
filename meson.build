project('libnpy',
    'cpp',
    version : '1.0.1',
    license : 'MIT'
)

# Allow system-wide installation
libnpy_subdir = 'libnpy'
libnpy_headers = ['include/npy.hpp']
install_headers(libnpy_headers, subdir : libnpy_subdir)

# Allow auto-configuration with pkg-config
pkg = import('pkgconfig')
pkg.generate(
  name : meson.project_name(),
  subdirs : [libnpy_subdir],
  description : 'A lightweight library for reading and writing NumPy-compatible .npy files',
  )

# Make this library usable as a Meson subproject
libnpy_dep = declare_dependency(
    include_directories : include_directories('include')
)
