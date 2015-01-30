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

#ifndef QLOGSYSTEM_LOGFORMATTER_HH
#define QLOGSYSTEM_LOGFORMATTER_HH

#include "loglevels.hh"

#include <QString>

namespace LOG
{

  /**
   * Interface for formatting a log message.
   *
   * The subclasses must take care of thread safetiness.
   */
  class LogFormatter
  {
  public:
    LogFormatter() { }
    virtual ~LogFormatter() { }

    /**
     * By subclassing the LogFormatter one can create custom formatted log messages.
     *
     * @param name    The logger's name.
     * @param level   The log message's level.
     * @param log_id  The unique id of the message.
     * @param message The log message itself.
     * @return Should return a message composed from these parameters.
     */
    virtual QString format_log(const QString &name, const Level &level,
                               const quint32 &log_id, const QString &message) = 0;
  };

} // LOG

#endif // QLOGSYSTEM_LOGFORMATTER_HH
