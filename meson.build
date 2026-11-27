project('libnpy',
    'cpp',
    version : '1.0.1',
    license : 'MIT',
    default_options : ['cpp_std=c++14', 'warning_level=3']
)

libnpy_dep = declare_dependency(
    include_directories : include_directories('include')
)

if not meson.is_subproject()
    install_headers('include/npy.hpp')

    import('pkgconfig').generate(
        name : 'libnpy',
        description : 'C++ header for reading and writing NumPy .npy files',
        install_dir : join_paths(get_option('datadir'), 'pkgconfig')
    )
endif

if get_option('tests')
    subdir('tests')
endif
