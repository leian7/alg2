###############################################################################
# File: generate_random.py
# Author: Annie Lei
# Date created: 02-17-2017
# Description: Generates 10 pairs of random ATCG sequences of lengths 500,
# 1000, 2000, 4000, and 5000, and outputs them to five files to be used as
# input to time main algorithm
###############################################################################

import random
import string

# create five new files for writing
rand_500 = open('rand_500.txt', 'w')
rand_1000 = open('rand_1000.txt', 'w')
rand_2000 = open('rand_2000.txt', 'w')
rand_4000 = open('rand_4000.txt', 'w')
rand_5000 = open('rand_5000.txt', 'w')

for pair in range(0, 10):
    # first sequence of length 500
    rand_500.write(''.join(random.choice('AGTC') for i in range(500)))
    rand_500.write(',')     # separate from next with comma
    # second sequence of length 500
    rand_500.write(''.join(random.choice('AGTC') for i in range(500)))
    rand_500.write('\n')    # done with this pair; move to next line
    
    # etc.
    rand_1000.write(''.join(random.choice('AGTC') for i in range(1000)))
    rand_1000.write(',')
    rand_1000.write(''.join(random.choice('AGTC') for i in range(1000)))
    rand_1000.write('\n')

    rand_2000.write(''.join(random.choice('AGTC') for i in range(2000)))
    rand_2000.write(',')
    rand_2000.write(''.join(random.choice('AGTC') for i in range(2000)))
    rand_2000.write('\n')
    
    rand_4000.write(''.join(random.choice('AGTC') for i in range(4000)))
    rand_4000.write(',')
    rand_4000.write(''.join(random.choice('AGTC') for i in range(4000)))
    rand_4000.write('\n')

    rand_5000.write(''.join(random.choice('AGTC') for i in range(5000)))
    rand_5000.write(',')
    rand_5000.write(''.join(random.choice('AGTC') for i in range(5000)))
    rand_5000.write('\n')

rand_500.close()
rand_1000.close()
rand_2000.close()
rand_4000.close()
rand_5000.close()
