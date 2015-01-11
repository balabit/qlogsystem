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

#ifndef QLOGSYSTEM_TESTS_COMMON_HH
#define QLOGSYSTEM_TESTS_COMMON_HH

#include "logger.hh"
#include "logoutput.hh"
#include "logformatter.hh"
#include "loghelpers.hh"

class LoggerMock : public LOG::Logger
{
public:
  LoggerMock(const QString &name = "name", Logger *parent = 0)
    : LOG::Logger(name, parent)
  { }
};

class FormatterMock : public LOG::LogFormatter
{
public:
  FormatterMock()
    : LOG::LogFormatter()
  { }

  virtual QString format_log(const QString &name, const LOG::Level &level,
                             const quint32 &log_id, const QString &message)
  {
    last_name = name;
    last_level = level;
    last_log_id = log_id;
    last_message = message;
    return message;
  }

  QString last_name;
  LOG::Level last_level;
  quint32 last_log_id;
  QString last_message;
};

class OutputMock : public LOG::LogOutput
{
public:
  OutputMock()
    : LOG::LogOutput()
  { }

  virtual void write_log(const QString &message)
  {
    buffered_message += message;
  }

  QString buffered_message;
};

QString
log_parameter_as_string(LOG::ParameterPair parameter, const QString &delimiter = QString(","))
{
  QString string;
  QTextStream stream(&string);
  parameter.delimiter = delimiter;
  stream << parameter;
  stream.flush();
  return string;
}

#endif // QLOGSYSTEM_TESTS_COMMON_HH
