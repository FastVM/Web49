#!/usr/bin/env python3

import matplotlib.pyplot as plt
import os
import subprocess
import time
import argparse
import colorsys

cur = os.path.dirname(os.path.realpath(__file__))

os.chdir('test/bench')

parser = argparse.ArgumentParser(
    prog='bench',
    description='Benchmark Wasm Engines',
)

parser.add_argument('--runs', '-r', type=int, help='number of benchmark runs', default=1)
parser.add_argument('--engine', '-e', type=str, action='append', default=[])
parser.add_argument('--test', '-t', type=str, action='append', default=[])
parser.add_argument('--compiler', '-c', type=str, default='emcc')
parser.add_argument('--opt', '-O', type=str, default='2')

args = parser.parse_args()

runs = args.runs
engines = args.engine
emcc = args.compiler
optlevel = args.opt

if len(engines) == 0:
    engines = ['wasm3', os.path.join(cur, 'bin/miniwasm')]

if len(args.test) == 0: 
    tests = {
        'nop': {
            'runs': 100,
            'args': [],
            'memory': 256,
        },
        'coremark': {
            'runs': 1,
            'args': ['3000'],
            'memory': 256,
        },
        'fib_f32': {
            'runs': 1,
            'args': ['40'],
            'memory': 256,
        },
        'fib_i32': {
            'runs': 1,
            'args': ['40'],
            'memory': 256,
        },
        'fib_f64': {
            'runs': 1,
            'args': ['40'],
            'memory': 256,
        },
        'fib_i64': {
            'runs': 1,
            'args': ['40'],
            'memory': 256,
        },
        'binary-trees': {
            'runs': 1,
            'args': ['16'],
            'memory': 2**12,
        },
        'fannkuch-redux': {
            'runs': 1,
            'args': ['10'],
            'memory': 256,
        },
        'mandelbrot-simd': {
            'runs': 1,
            'args': ['2000'],
            'memory': 256,
        },
        'mandelbrot': {
            'runs': 1,
            'args': ['2000'],
            'memory': 256,
        },
        'nbody': {
            'runs': 1,
            'args': ['2000000'],
            'memory': 256,
        },
        # 'trap': {
        #     'runs': 10,
        #     'args': [],
        #     'memory': 256,
        # },
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
        build = subprocess.call([*emcc.split(' '), '-Xlinker', f'--initial-memory={tests[test]["memory"] * (2 ** 16)}', f"-O{optlevel}", test + '.c', '-o', test + '.wasm'])
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

        keys = [key.replace(cur, '.') for key in keys]

        for i,key in enumerate(keys):
            rgb = colorsys.hsv_to_rgb(i / (len(keys) * (5/4)), 0.4, 0.9)

            ax.bar(key, values[i], color=(*rgb, 1.0))

        ax.set_ylabel('time taken in seconds')
        ax.set_xlabel('wasm engine')

        ax.set_title(' '.join([test, *tests[test]['args']]))
        fig.savefig(test + '.png')
