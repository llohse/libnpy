project('libnpy',
    'cpp',
    version : '1.0.1',
    license : 'MIT'
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
