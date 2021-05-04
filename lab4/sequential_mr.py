#!/usr/bin/env python
"""mapper.py"""

import sys
import time
from pathlib import Path

words_dict = {}

time_start = time.time()
# source: https://stackoverflow.com/questions/10377998/how-can-i-iterate-over-files-in-a-given-directory
pathlist = Path('.').glob('*.txt')
for path in pathlist:
    # because path is object not string
    path_in_str = str(path)
    # input comes from STDIN (standard input)
    with open(path_in_str, 'r', encoding='utf-8', errors='ignore') as file_object:
        file_lines = file_object.readlines()
        for line in file_lines:
            # remove leading and trailing whitespace
            line = line.strip()
            # split the line into words
            words = line.split()
            # increase counters
            for word in words:
                if word in words_dict:
                    words_dict[word] += 1
                else:
                    words_dict[word] = 1

time_end = time.time()
print("Time execution {time_execution} [s]". format(time_execution=time_end - time_start))