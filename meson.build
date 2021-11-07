project('libnpy', 
        'c++', 
        license: 'MIT'
        )

project_headers = [
  'include/npy.hpp'
]

public_headers = include_directories('include')

project_target = shared_library(
  meson.project_name(),
  [],
  install : true,
  include_directories : public_headers,
)

project_dep = declare_dependency(
  include_directories : public_headers
)
set_variable(meson.project_name() + '_dep', project_dep)

install_headers(project_headers, subdir : meson.project_name())


if not meson.is_subproject()
  subdir('tests')
endif
