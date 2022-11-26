#!/usr/bin/env python3

import matplotlib.pyplot as plt
import os
import subprocess
import time 

os.chdir('test/bench')

runs = 1
engines = ['miniwasm', 'wasmer', 'wasm3', 'wasmtime']
tests = {
    'nop': {
        'runs': 10,
        'build': [],
        'args': [],
    },
    'binary-trees': {
        'runs': 1,
        'build': [],
        'args': ['16'],
    },
    'fannkuch-redux': {
        'runs': 1,
        'build': [],
        'args': ['10'],
    },
    'fasta': {
        'runs': 1,
        'build': [],
        'args': ['5000000'],
    },
    'mandelbrot-simd': {
        'runs': 1,
        'build': [],
        'args': ['2000'],
    },
    'mandelbrot': {
        'runs': 1,
        'build': [],
        'args': ['2000'],
    },
    'nbody': {
        'runs': 1,
        'build': [],
        'args': ['10000000'],
    },
    'fib': {
        'runs': 1,
        'build': [],
        'args': ['40'],
    },
}

testdata = {}
for i in range(1, runs+1):
    print('RUN: #' + str(i))
    for test in tests.keys():
        print('  TEST: ' + test)
        build = subprocess.call(['emcc', '-sPURE_WASI=1', '-sWASM=1', '-O3', test + '.c', '-o', test + '.wasm', *tests[test]['build']])
        if test not in testdata:
            testdata[test] = {}
        data = testdata[test]
        for engine in engines:
            print('    ENGINE: ' + engine)
            if engine not in data:
                data[engine] = []
            times = data[engine]
            for i in range(tests[test]['runs']):
                start = time.time()
                run = subprocess.call([engine, test + '.wasm', *tests[test]['args']], stdout=subprocess.DEVNULL)
                end = time.time()
                times.append(end - start)

        fig, ax = plt.subplots()
        
        keys = data.keys()
        values = [sum(data[i]) / len(data[i]) for i in keys]

        ax.bar(keys, values, color=(0.2, 0.3, 0.6, 0.8))

        ax.set_ylabel('time taken in seconds')
        ax.set_xlabel('wasm engine')

        ax.set_title(' '.join([test, *tests[test]['args'], ]))
        fig.savefig(test + '.png')
