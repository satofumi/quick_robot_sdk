#!/usr/bin/env python

import sys


file = sys.argv[1]
for line in open(file):
    values = line[:-1].split(' ')
    print int(values[0]) - int(values[1])
