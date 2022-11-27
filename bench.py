#!/usr/bin/env python3

import matplotlib.pyplot as plt
import os
import subprocess
import time
import argparse

os.chdir('test/bench')

parser = argparse.ArgumentParser(
    prog='bench',
    description='Benchmark Wasm Engines',
)

parser.add_argument('--runs', '-r', type=int, help='number of benchmark runs', default=1)
parser.add_argument('--engine', '-e', type=str, action='append', default=[])
parser.add_argument('--test', '-t', type=str, action='append', default=[])

args = parser.parse_args()

runs = args.runs
engines = args.engine

if len(engines) == 0:
    engines = ['wasm3', 'miniwasm', 'wasmtime', 'wasmer']

if len(args.test) == 0: 
    tests = {
        'fibf': {
            'runs': 1,
            'args': ['35'],
        },
        'coremark': {
            'runs': 1,
            'args': ['3000'],
        },
        'nop': {
            'runs': 1,
            'args': [],
        },
        'binary-trees': {
            'runs': 1,
            'args': ['16'],
        },
        'fannkuch-redux': {
            'runs': 1,
            'args': ['10'],
        },
        'fasta': {
            'runs': 1,
            'args': ['5000000'],
        },
        'mandelbrot-simd': {
            'runs': 1,
            'args': ['2000'],
        },
        'mandelbrot': {
            'runs': 1,
            'args': ['2000'],
        },
        'nbody': {
            'runs': 1,
            'args': ['10000000'],
        },
        'fib': {
            'runs': 1,
            'args': ['40'],
        },
    }
else:
    tests = {}
    for test in args.test:
        [name, *args1] = test.split(':')
        split = name.split('+')
        if len(split) == 1:
            n = 1
        else:
            name = split[0]
            n = int(split[1])
        
        tests[name] = {
            'args': args1,
            'runs': n,
        }

testdata = {}
for i in range(1, runs+1):
    print('RUN: #' + str(i))
    for test in tests.keys():
        print('  TEST: ' + test)
        build = subprocess.call(['emcc', '-sPURE_WASI=1', '-sWASM=1', '-O3', test + '.c', '-o', test + '.wasm'])
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
