#!/usr/bin/env python2

''' ID generator script '''

from optparse import OptionParser
import sys
import os
from os.path import join, getsize
import re
import fileinput
import math
import collections

ID_BITS = 32 #bit

# Max values
MAJOR = 16
MINOR = 32
BUILD = 32

# Find log messages, there is a format ID string parameter
log_re_string = r'log_(?P<TYPE>\w+)\((?P<COMPONENT>(\w|::|\->)+)\,(\s|)%(ID)s,(\s|)(?P<MSG>.*)'
# RE for finding log messages with 0 ID
log0_re = re.compile(log_re_string % {'ID': 0})
log_max_re = re.compile(log_re_string % {'ID': '(?P<ID>\d+)'})

matched_logs = []
ids = []

VERSION_SHIFT = 0
MAJOR_SHIFT = 0
MINOR_SHIFT = 0

def get_prefix(version_file):
  ''' Read VERSION file and calculate prefix for IDs '''

  global MAJOR, MINOR, BUILD
  global VERSION_SHIFT, MAJOR_SHIFT, MINOR_SHIFT
  if not os.path.exists(version_file):
    print >>sys.stderr, 'VERSION file doesn\'t exists'
    exit(1)

  f = open(version_file, 'r')
  ver = f.read().strip()
  version_parts = ver.split('.')

  # Remove alphanumeric letters
  version_parts[-1] = re.sub('^(?P<NUM>\d+).*$', '\g<NUM>', version_parts[-1])

  if len(version_parts) == 2:
    version_parts.append('0')

  # Convert string to int
  version_parts = map(int, version_parts)

  # Map MAJOR version 1 -> 0
  version_parts[0] = version_parts[0] - 1

  if version_parts[0] >= MAJOR or version_parts[1] >= MINOR or version_parts[2] >= BUILD:
    print >>sys.stderr, 'ERROR you have reached the limit of the version number! Max is: %d-%d-%d (No the limit is not the sky)' % (MAJOR, MINOR, BUILD), ver
    exit(1)

  ret_val = (version_parts[0] * MAJOR_SHIFT + version_parts[1] * MINOR_SHIFT + version_parts[2]) * VERSION_SHIFT
  print 'Prefix for log IDs:', ret_val
  return ret_val

def filter_code(_file):
  ''' Check for hh or cc files '''

  return re.match(r'.*\.(cc|hh)$', _file) != None

def collect_files(directory):
  ''' Collect files from the given directory, filter with filter_code function '''

  all_file = []
  for root, dirs, files in os.walk(directory):
    # remove the unit test directory as we should not check it for log ID-s
    if "unit" in dirs:
      del dirs[dirs.index("unit")]
      continue

    files = filter(filter_code, files)
    for _file in files:
      all_file.append(os.path.join(root, _file))

  return all_file

def collect_logs(_file, prefix, max_id):
  ''' Collect logs from the given file, and find the max id within this prefix by the given RE '''

  global VERSION_SHIFT
  f = open(_file, 'r')

  for (i, line) in enumerate(f.readlines()):
    # Check for 0 id
    if log0_re.search(line) != None:
      matched_logs.append({'file': _file, 'line_num': i, 'line': line, 'new': ''})

    # Check max id
    search_res = log_max_re.search(line)
    if search_res is not None:
      _id = int(search_res.group('ID'))
      ids.append({'id': _id, 'file': _file, 'line_num': i})
      if (_id != 0) and (_id >= prefix and _id < (prefix + VERSION_SHIFT)) and (max_id < _id):
        max_id = _id

  return max_id

def check_ids(exit_if_zero):
  ''' Find colliding IDs '''

  items = collections.defaultdict(list)
  for i, item in enumerate(ids):
    items[item['id']].append(item)

  # Delete items with 0 ID
  if 0 in items:
    print "0 ID count:", len(items[0])
    del items[0]
    if exit_if_zero:
      exit(1)

  # Collect IDs where count > 1
  duplications = [[_id, data]  for _id, data in items.iteritems()   if len(data) > 1]
  if len(duplications) > 0:
    print >>sys.stderr, "ERROR ID duplications"
    for wrong_id in duplications:
      print "ID: ", wrong_id[0]
      for error in wrong_id[1]:
        print error
    exit(1)

def replace_id(start_id):
  ''' Replace the 0 id with proper one '''

  _id = start_id
  for data in matched_logs:
    #print data['line']
    data['new'] = log0_re.sub('log_\g<TYPE>(\g<COMPONENT>, %#d, \g<MSG>' % (_id), data['line'])
    _id += 1

def replace_log_in_file(data):
  ''' Replace the log in the file '''

  # Read a line and after that redirect the stdout into the file
  for i, line in enumerate(fileinput.input(data['file'], inplace = 1)):
    if i == data['line_num']:
      sys.stdout.write(data['new'])
    else:
      sys.stdout.write(line)

def calculate_shifts():
  ''' Calculate the shifts of the different fields '''

  global MAJOR, MINOR, BUILD, ID_BITS
  global VERSION_SHIFT, MAJOR_SHIFT, MINOR_SHIFT

  needed_bits = []

  needed_bits.append(math.log(MAJOR, 2))
  needed_bits.append(math.log(MINOR, 2))
  needed_bits.append(math.log(BUILD, 2))

  version_bits = sum(needed_bits)

  if ID_BITS <= version_bits:
    print >>sys.stderr, 'ERROR Wrong settings, ID_BITS are too low'
    exit(1)

  VERSION_SHIFT = 2 ** (ID_BITS - version_bits)
  MINOR_SHIFT = 2 ** needed_bits[2]
  MAJOR_SHIFT = 2 ** (needed_bits[2] + needed_bits[1])

def main(directory, check):
  print 'In Main', directory

  calculate_shifts()

  files = collect_files(directory)

  prefix = get_prefix(os.path.join(directory, 'VERSION'))
  max_id = prefix

  for _file in files:
    max_id = collect_logs(_file, prefix, max_id)

  check_ids(check)

  # If not in check mod
  if not check:
    replace_id(max_id + 1)

    for data in matched_logs:
      replace_log_in_file(data)
      print data['line'], data['new']

if __name__ == '__main__':
  parser = OptionParser()
  parser.add_option("-d", "--directory", dest="directory", nargs=1, help="Source directory")
  parser.add_option("-c", "--check", dest="check", action="store_true", default=False, help="Check for colliding IDs")
  (options, args) = parser.parse_args()

  directory = options.directory
  check = options.check

  if directory is None or not os.path.exists(directory):
    print >>sys.stderr, "No directory given or specified directory does'nt exist"
  else:
    main(directory, check)
