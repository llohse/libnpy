project('libnpy-tests', 'cpp',
        default_options : ['cpp_std=c++14', 'warning_level=3'])

pymod = import('python')
python = pymod.find_installation('python3', required : true)


catch2_dep = dependency('catch2', required : false)
if not catch2_dep.found()
  catch2_proj = subproject('catch2')
  catch2_dep = catch2_proj.get_variable('catch2_dep')
endif

datafiles = [ 
'bool.npy',
'empty_c16.npy',
'empty_c16_t.npy',
'empty_c8.npy',
'empty_c8_t.npy',
'empty_f4.npy',
'empty_f4_t.npy',
'empty_f8.npy',
'empty_f8_t.npy',
'empty_i1.npy',
'empty_i1_t.npy',
'empty_i2.npy',
'empty_i2_t.npy',
'empty_i4.npy',
'empty_i4_t.npy',
'empty_i8.npy',
'empty_i8_t.npy',
'empty_u1.npy',
'empty_u1_t.npy',
'empty_u2.npy',
'empty_u2_t.npy',
'empty_u4.npy',
'empty_u4_t.npy',
'empty_u8.npy',
'empty_u8_t.npy',
'matrix_c16.npy',
'matrix_c16_t.npy',
'matrix_c8.npy',
'matrix_c8_t.npy',
'matrix_f4.npy',
'matrix_f4_t.npy',
'matrix_f8.npy',
'matrix_f8_t.npy',
'matrix_i1.npy',
'matrix_i1_t.npy',
'matrix_i2.npy',
'matrix_i2_t.npy',
'matrix_i4.npy',
'matrix_i4_t.npy',
'matrix_i8.npy',
'matrix_i8_t.npy',
'matrix_u1.npy',
'matrix_u1_t.npy',
'matrix_u2.npy',
'matrix_u2_t.npy',
'matrix_u4.npy',
'matrix_u4_t.npy',
'matrix_u8.npy',
'matrix_u8_t.npy',
'scalar_c16.npy',
'scalar_c16_t.npy',
'scalar_c8.npy',
'scalar_c8_t.npy',
'scalar_f4.npy',
'scalar_f4_t.npy',
'scalar_f8.npy',
'scalar_f8_t.npy',
'scalar_i1.npy',
'scalar_i1_t.npy',
'scalar_i2.npy',
'scalar_i2_t.npy',
'scalar_i4.npy',
'scalar_i4_t.npy',
'scalar_i8.npy',
'scalar_i8_t.npy',
'scalar_u1.npy',
'scalar_u1_t.npy',
'scalar_u2.npy',
'scalar_u2_t.npy',
'scalar_u4.npy',
'scalar_u4_t.npy',
'scalar_u8.npy',
'scalar_u8_t.npy', ]

gen_data = custom_target('gen-data',
                         input : 'createnpy.py',
			 output : datafiles,
			 command : [python, '@INPUT@'])

libnpy_inc = include_directories('../include')
#libnpy_dep = declare_dependency(include_directories : libnpy_inc)

src = ['test-read.cpp', '../include/npy.hpp']
exe = executable('test-read', sources : src, include_directories : libnpy_inc, dependencies : catch2_dep)

test('test read', exe, depends : gen_data)
