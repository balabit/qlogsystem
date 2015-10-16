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

#ifndef QLOGSYSTEM_LOGGER_HH
#define QLOGSYSTEM_LOGGER_HH

#include <QString>

#include "qlogsystem_global.hh"
#include "loglevels.hh"

namespace LOG
{

  class LogFormatter;
  class LogOutput;

  /**
   * The Logger uses a LogFormatter to format the log messages,
   * and forwards the messages the the LogOutput.
   *
   * A logger may have a parent, if no formatter or output or log level
   * has been set, it will use the parent's formatter/output/level.
   */
  class QLOGSYSTEMSHARED_EXPORT Logger
  {
  public:
    ~Logger();

    /**
     * Sets the formatter to the given one.
     * It takes the OWNERSHIP of the formatter!
     *
     * @param formatter The Formatter to use.
     */
    void set_formatter(LogFormatter *formatter);

    /**
     * Sets the output to the given one.
     * It takes the OWNERSHIP of the output!
     *
     * @param log_output The output to use.
     */
    void set_output(LogOutput *log_output);

    /**
     * Getter for the current log formatter.
     *
     * @return Reference for the formatter.
     */
    LogFormatter &formatter();

    /**
     * Getter for the current log output.
     *
     * @return Reference for the output.
     */
    LogOutput &output();

    /**
     * Sets the log level to the given level.
     *
     * @param level The maximum level of messages to log.
     */
    void set_level(const Level &level);

    Level get_level() const;

    /**
     * Whether to need log or not on the given level.
     *
     * @param level The given level.
     * @return Returns true if the logger's level <= the given level.
     */
    bool need_log(const Level &level) const;

    /**
     * Logs a message.
     * (The level is not checked here, one should use the need_log() method before)
     *
     * @param level   The message's log level.
     * @param log_id  The unique id of the message.
     * @param message The message itself.
     */
    void log(const Level &level, const quint32 &log_id, const QString &message) const;

  protected:
    /**
     * Constructs a Logger with the given name and parent.
     *
     * @param name   The logger's name.
     * @param parent The logger's parent.
     */
    Logger(const QString &name, Logger *parent = 0);
    Q_DISABLE_COPY(Logger)

  private:
    class LoggerPrivate *d;

    friend class LoggerPrivate;
    friend class ManagerPrivate;
    friend class Manager;
  };

} // LOG

#endif //QLOGSYSTEM_ LOGGER_HH
