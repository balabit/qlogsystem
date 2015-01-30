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

#ifndef QLOGSYSTEM_LOGSPECHANDLER_HH
#define QLOGSYSTEM_LOGSPECHANDLER_HH

#include "manager.hh"

namespace LOG
{

  /**
   * With LogSpecHandler one can update the log levels of the components by a simple string.
   */
  class QLOGSYSTEMSHARED_EXPORT LogSpecHandler
  {
  public:
    enum Error
    {
      None,
      InvalidPair,
      InvalidLogLevel
    };

    LogSpecHandler();
    ~LogSpecHandler();

    /**
     * Updates the logsystem with the given log spec.
     * The changes takes place only if there was not any error.
     *
     * syntax: &lt;component_name&gt;:&lt;log_level&gt;;&lt;component_name&gt;:&lt;log_level&gt;
     *
     * @param log_spec The log spec to use.
     * @return True if success.
     */
    bool update_logsystem(const QString &log_spec);

    /**
     * The error type.
     *
     * @return The type of the error, or None.
     */
    Error error() const;

    /**
     * The error string if an error happend otherwise an empty string.
     *
     * @return The error string.
     */
    const QString &errorString() const;

  private:
    class LogSpecHandlerPrivate *d;
  };

} // LOG

#endif // QLOGSYSTEM_LOGSPECHANDLER_HH
