#!/usr/bin/env python3


import datetime
import fnmatch
import os


license_template = \
"""\
/**********************************************************************************
 * Copyright (c) 2013-{CURRENT_YEAR} BalaBit IT Ltd, Budapest, Hungary
 *
 * This file is part of qlogsystem.
 *
 * qlogsystem is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * qlogsystem is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with qlogsystem; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************************/

"""


def main():
    license = license_template.format(CURRENT_YEAR=datetime.datetime.now().year)
    first_line, second_line = license.split('\n')[0:2]
    copyright = second_line[:21]
    for root, dirnames, filenames in os.walk(os.path.dirname(os.path.abspath(__file__))):
        if root.startswith('.'):
            continue

        for filename in (fnmatch.filter(filenames, '*.hh') + fnmatch.filter(filenames, '*.cc')):
            filename = os.path.join(root, filename)
            with open(filename, 'r+') as f:
                if f.readline().startswith(first_line) and f.readline().startswith(copyright):
                    print("Updating copyright on " + filename)
                    f.seek(0, 0)
                    f.write(license)
                else:
                    print("Adding copyright to " + filename)
                    f.seek(0, 0)
                    content = f.read()
                    f.seek(0, 0)
                    f.write(license)
                    f.write(content)



if __name__ == "__main__":
    main()
