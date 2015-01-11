/**********************************************************************************
 * Copyright (c) 2013-2015 BalaBit IT Ltd, Budapest, Hungary
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

#ifndef QLOGSYSTEM_LOGLEVELS_HH
#define QLOGSYSTEM_LOGLEVELS_HH

namespace LOG
{

  enum Level
  {
    CRITICAL = 0,
    ERROR,
    NOTICE,
    INFO,
    EXTENDED_INFO,
    DEBUG,
    TRACE,
    DUMP
  };

  /**
   * Gets a log level enum from the given int.
   */
  inline Level get_log_level_from_int(const int &log_level)
  {
    Level level;

    if (log_level > DUMP)
      {
        level = DUMP;
      }
    else if (log_level < CRITICAL)
      {
        level = CRITICAL;
      }
    else
      {
        level = static_cast< Level >(log_level);
      }

    return level;
  }

} // LOG

#endif // QLOGSYSTEM_LOGLEVELS_HH
