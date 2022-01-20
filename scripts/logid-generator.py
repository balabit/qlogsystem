#!/usr/bin/env python3

''' ID generator script '''

from optparse import OptionParser
import sys
import os
from os.path import join, getsize
import re
import math
from collections import Counter

ID_BITS = 32 #bit

# Max values
MAJOR = 16
MINOR = 32
BUILD = 32

# Find log messages, there is a format ID string parameter
log_re_string = r'log_(?P<TYPE>.*)\s*\(\s*(?P<COMPONENT>[A-Z]*)\s*,\s*(?P<ID>\d+)\s*,\s*(?P<MSG>(.|\s)*?)\s*\)\s*;'
log_re = re.compile(log_re_string, re.MULTILINE)

all_logs = []

VERSION_SHIFT = 0
MAJOR_SHIFT = 0
MINOR_SHIFT = 0

def get_prefix(version_file):
  ''' Read VERSION file and calculate prefix for IDs '''

  global MAJOR, MINOR, BUILD
  global VERSION_SHIFT, MAJOR_SHIFT, MINOR_SHIFT
  if not os.path.exists(version_file):
    print('VERSION file doesn\'t exists', file=sys.stderr)
    exit(1)

  f = open(version_file, 'r')
  ver = f.read().strip()
  version_parts = ver.split('.')

  # Remove alphanumeric letters
  version_parts[-1] = re.sub('^(?P<NUM>\d+).*$', '\g<NUM>', version_parts[-1])

  if len(version_parts) == 2:
    version_parts.append('0')

  # Convert string to int
  version_parts = list(map(int, version_parts))

  # Map MAJOR version 1 -> 0
  version_parts[0] = version_parts[0] - 1

  if version_parts[0] >= MAJOR or version_parts[1] >= MINOR or version_parts[2] >= BUILD:
    print('ERROR you have reached the limit of the version number! Max is: %d-%d-%d (No the limit is not the sky)' % (MAJOR, MINOR, BUILD), ver, file=sys.stderr)
    exit(1)

  ret_val = (version_parts[0] * MAJOR_SHIFT + version_parts[1] * MINOR_SHIFT + version_parts[2]) * VERSION_SHIFT
  print('Prefix for log IDs:', ret_val)
  return ret_val

def any_match(path, excludes):
  for exclude in excludes:
    if re.search(exclude, path) is not None:
      return True

  return False

def collect_files(directory, excludes, extensions):
  ''' Collect files with the given extensions from the given directory '''
  all_files = []
  for root, dirs, files in os.walk(directory):
    for name in dirs:
      if any_match(os.path.join(root, name), excludes):
        del dirs[dirs.index(name)]

    for name in files:
      path = os.path.join(root, name)
      if re.match(extensions, path) is not None and not any_match(path, excludes):
        all_files.append(path)

  return all_files

def collect_all_logs(_file):
  with open(_file, 'r') as f:
    logs = re.findall(log_re, f.read())
    if logs:
      all_logs.append({'file': _file, "logs": logs})

def max_log_ID(max_id, prefix):
  global VERSION_SHIFT
  for logs in all_logs:
    for log in logs['logs']:
      log_id = int(log[2])
      if log_id != 0 and (log_id >= prefix and log_id < (prefix + VERSION_SHIFT)) and (max_id < log_id):
        max_id = int(log[2])

  return max_id

def check_ids(exit_if_zero):
  ''' Find colliding IDs '''
  count = Counter({'0': 0})
  for logs in all_logs:
    count += (Counter(log_ID[2] for log_ID in logs['logs']))

  duplacated_ids = [k for (k,v) in Counter(count).items() if v > 1]
  print("0 ID count:", count['0'])

  if (duplacated_ids or count['0']) and exit_if_zero:
    for i in duplacated_ids:
      print("logID:", i, "is duplacated", count[i], "times")
    exit(1)

def replace_log_in_file(file_with_logs, max_id, prefix):
  ''' Replace the log in the file '''
  with open (file_with_logs['file'], 'r+' ) as f:
    content = f.read()
    f.seek(0)

    for match in re.finditer(log_re_string, content):
      if match['ID'] == '0':
        max_id += 1
        new_log = re.sub('0', str(int(max_id)), match.group(0))
        print(new_log)
        content = content.replace(match.group(0), new_log)

    f.write(content)
    f.truncate()

  return max_id

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
    print('ERROR Wrong settings, ID_BITS are too low', file=sys.stderr)
    exit(1)

  VERSION_SHIFT = 2 ** (ID_BITS - version_bits)
  MINOR_SHIFT = 2 ** needed_bits[2]
  MAJOR_SHIFT = 2 ** (needed_bits[2] + needed_bits[1])

def main(directory, check, excludes, extensions):
  print('In Main', directory)
  calculate_shifts()

  files = collect_files(directory, excludes, extensions)

  prefix = get_prefix(os.path.join(directory, 'VERSION'))
  max_id = prefix

  for _file in files:
    collect_all_logs(_file)

  max_id = max_log_ID(max_id, prefix)

  check_ids(check)

  if not check:
    for file_with_logs in all_logs:
      max_id = replace_log_in_file(file_with_logs, max_id, prefix)

if __name__ == '__main__':
  parser = OptionParser()
  parser.add_option("-d", "--directory", dest="directory", nargs=1, help="Source directory")
  parser.add_option("-c", "--check", dest="check", action="store_true", default=False, help="Check for colliding IDs")
  parser.add_option("-e", "--excludes", dest="excludes", action="append", default=[], type=str, help="Exclude regex pattern")
  parser.add_option("-f", "--file-extensions", dest="extensions", action="append", default=r'.*\.(cc|hh|cpp|h)$', type=str, help="Source file regex pattern")
  (options, args) = parser.parse_args()

  directory = options.directory
  check = options.check
  excludes = [re.compile(exclude) for exclude in options.excludes]
  extensions = re.compile(options.extensions)

  if directory is None or not os.path.exists(directory):
    print("No directory given or specified directory does'nt exist", file=sys.stderr)
  else:
    main(directory, check, excludes, extensions)
