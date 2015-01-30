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

#ifndef QLOGSYSTEM_LOGOUTPUT_HH
#define QLOGSYSTEM_LOGOUTPUT_HH

#include <QString>

namespace LOG
{

  /**
   * Interface for handling the final (formatted) log messages.
   *
   * The subclasses must take care of thread safetiness.
   */
  class LogOutput
  {
  public:
    LogOutput() { }
    virtual ~LogOutput() { }

    /**
     * By subclassing the LogOutput one can forward log messages to some output.
     *
     * @param message   The formatted message.
     */
    virtual void write_log(const QString &message) = 0;
  };

} // LOG

#endif // QLOGSYSTEM_LOGOUTPUT_HH
