datafiles = ['bool.npy', 'bool_t.npy']
foreach dtype : ['f4', 'f8', 'i1', 'i2', 'i4', 'i8', 'u1', 'u2', 'u4', 'u8', 'c8', 'c16']
    foreach category : ['matrix', 'empty', 'scalar']
        stem = category + '_' + dtype
        datafiles += [stem + '.npy', stem + '_t.npy']
    endforeach
endforeach

gen_data = custom_target('gen-data',
                         input : '../createnpy.py',
                         output : datafiles,
                         command : [python, '@INPUT@', '@OUTDIR@'])
