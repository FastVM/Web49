import json
import os

os.chdir('main/runtime')

with open('raylib.json') as f:
    src = json.load(f)

with open('rlruntime.c', 'w') as outfile:
    print(f'#include "rlruntime.h"', file=outfile)
    print('#include <raylib.h>', file=outfile)
    print('#include <raymath.h>', file=outfile)
    print('#include <rlgl.h>', file=outfile)
    names = []
    for func in src['functions']:
        fname = func['name']
        fret = func['returnType']
        fparams = func['params'] if 'params' in func else []
        bad = False
        if fret[-1] == '*':
            print('// returns ptr: %s' % fname, file=outfile)
            bad = True
        for arg in fparams:
            argtype = arg['type']
            if argtype == '...':
                print('// is variadic: %s' % fname, file=outfile)
                bad = True
            if argtype.endswith('Callback'):
                print('// is callback: %s' % fname, file=outfile)
                bad = True
        if bad:
            continue
        names.append(fname)
        print('static web49_interp_data_t web49_main_runtime_%s(web49_interp_t interp) {' % fname, file=outfile)
        print('  web49_interp_data_t ret;', file=outfile)
        offset = 0
        if fret == 'void':
            print('  %s(' % fname, file=outfile)
        elif fret == 'bool':
            print('  ret.i32_s = (int32_t) %s(' % fname, file=outfile);
        elif fret == 'int':
            print('  ret.i32_s = (int32_t) %s(' % fname, file=outfile);
        elif fret == 'unsigned int':
            print('  ret.i32_u = (uint32_t) %s(' % fname, file=outfile);
        elif fret[0].upper() == fret[0]:
            print(f'  *({fret} *) &interp.memory[interp.locals[0].i32_s] = {fname}(', file=outfile);
        else:
            print('  %s(' % fname, file=outfile)
        for argnum, arg in enumerate(fparams):
            argtype = arg['type']
            if argtype[-1] == '*':
                print(f'    ({argtype}) &interp.memory[interp.locals[{argnum+offset}].i32_s]', end='', file=outfile)
            elif argtype[0].upper() == argtype[0] or argtype[0:2] == 'rl':
                print(f'    *({argtype} *) &interp.memory[interp.locals[{argnum+offset}].i32_s]', end='', file=outfile)
            else:
                print(f'    ({argtype}) interp.locals[{argnum+offset}].i32_s', end='', file=outfile)
            if argnum + 1 != len(fparams):
                print(',', file=outfile)
            else:
                print('', file=outfile)
        print('  );', file=outfile)
        print('  return ret;', file=outfile)
        print('}', file=outfile)
    print('web49_env_func_t web49_main_import_raylib(const char *name) {', file=outfile)
    for fname in names:
        print('  if (!strcmp(name, "%s")) {' % fname, file=outfile)
        print('    return &web49_main_runtime_%s;' % fname, file=outfile)
        print('  }', file=outfile)
    print('  return NULL;', file=outfile)
    print('}', file=outfile)