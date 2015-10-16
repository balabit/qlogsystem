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

#include "logger.hh"

#include "logformatter.hh"
#include "logoutput.hh"

namespace LOG
{

  class LoggerPrivate
  {
  public:
    LoggerPrivate(const QString &name, Logger *parent)
      : name(name),
        parent(parent),
        formatter(0),
        log_output(0),
        level(CRITICAL),
        use_parent_level(true)
    { }

    ~LoggerPrivate()
    {
      delete formatter;
      delete log_output;
    }

    QString format_log(const QString &name, const Level &level, const quint32 &log_id, const QString &message);

    void log(const QString &message);

    bool need_log(const Level &level);

    Level get_level() const;

    LogFormatter *get_formatter();
    LogOutput *get_output();

  public:
    QString name;
    Logger  *parent;

    LogFormatter *formatter;
    LogOutput    *log_output;

    Level level;
    bool  use_parent_level;
  };

} // LOG

using namespace LOG;

Logger::Logger(const QString &name, Logger *parent)
  : d(new LoggerPrivate(name, parent))
{ }

Logger::~Logger()
{
  delete d;
}

void
Logger::set_formatter(LogFormatter *formatter)
{
  delete d->formatter;
  d->formatter = formatter;
}

void
Logger::set_output(LogOutput *log_output)
{
  delete d->log_output;
  d->log_output = log_output;
}

LogFormatter &
Logger::formatter()
{
  return *(d->get_formatter());
}

LogOutput &
Logger::output()
{
  return *(d->get_output());
}

void
Logger::set_level(const Level &level)
{
  d->use_parent_level = false;
  d->level = level;
}

Level
Logger::get_level() const
{
  return d->get_level();
}

bool
Logger::need_log(const Level &level) const
{
  return d->need_log(level);
}

void
Logger::log(const Level &level, const quint32 &log_id, const QString &message) const
{
  d->log(d->format_log(d->name, level, log_id, message));
}

// LoggerPrivate

QString
LoggerPrivate::format_log(const QString &name, const Level &level, const quint32 &log_id, const QString &message)
{
  return get_formatter()->format_log(name, level, log_id, message);
}

void
LoggerPrivate::log(const QString &message)
{
  get_output()->write_log(message);
}

bool
LoggerPrivate::need_log(const Level &level)
{
  return (use_parent_level && parent) ? parent->d->need_log(level) : this->level >= level;
}

Level
LoggerPrivate::get_level() const
{
  if (use_parent_level && parent)
    return parent->get_level();
  else
    return level;
}

LogFormatter *
LoggerPrivate::get_formatter()
{
  return (formatter) ? formatter : parent->d->get_formatter();
}

LogOutput *
LoggerPrivate::get_output()
{
  return (log_output) ? log_output : parent->d->get_output();
}
