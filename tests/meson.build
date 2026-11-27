python = import('python').find_installation('python3', modules : ['numpy'])
catch2_dep = dependency('catch2', version : '<3')

subdir('data')

read_exe = executable('test-read', 'test-read.cpp',
                      dependencies : [libnpy_dep, catch2_dep])
write_exe = executable('test-write', 'test-write.cpp',
                       dependencies : libnpy_dep)

test('test read', read_exe, workdir : meson.current_build_dir(), depends : gen_data)
test('test write', write_exe, workdir : meson.current_build_dir())
