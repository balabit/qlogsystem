#!/usr/bin/env python3

import sys
import math

ID_BITS = 32 #bit

# Max values
MAJOR = 16
MINOR = 32
BUILD = 32

VERSION_SHIFT = 0
MAJOR_SHIFT = 0
MINOR_SHIFT = 0

def calculate_shifts():
  global MAJOR, MINOR, BUILD, ID_BITS
  global VERSION_SHIFT, MAJOR_SHIFT, MINOR_SHIFT

  needed_bits = []

  needed_bits.append(math.log(MAJOR, 2))
  needed_bits.append(math.log(MINOR, 2))
  needed_bits.append(math.log(BUILD, 2))

  version_bits = sum(needed_bits)

  if ID_BITS <= version_bits:
    print('ERROR Wrong settings, ID_BITS are too low')
    exit(-1)

  VERSION_SHIFT = 2 ** (ID_BITS - version_bits)
  MINOR_SHIFT = 2 ** needed_bits[2]
  MAJOR_SHIFT = 2 ** (needed_bits[2] + needed_bits[1])

def main():
  if len(sys.argv) != 2:
    print('Usage %s ID' % sys.argv[0])
    exit(1)

  calculate_shifts()
  global VERSION_SHIFT, MAJOR_SHIFT, MINOR_SHIFT

  _id = int(sys.argv[1])
  _prefix_part = _id / VERSION_SHIFT

  major = _prefix_part / MAJOR_SHIFT + 1
  _prefix_part = _prefix_part % MAJOR_SHIFT

  minor = _prefix_part / MINOR_SHIFT
  _prefix_part = _prefix_part % MINOR_SHIFT

  build = _prefix_part

  print('%d.%d.%d' % (major, minor, build))

if __name__ == '__main__':
  main()
