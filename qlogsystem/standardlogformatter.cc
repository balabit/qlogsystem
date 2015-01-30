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

#include "standardlogformatter.hh"

using namespace LOG;

StandardLogFormatter::StandardLogFormatter()
  : LogFormatter(),
    name_padding(10),
    log_id_padding(5)
{ }

StandardLogFormatter::~StandardLogFormatter()
{ }

void
StandardLogFormatter::set_name_padding(int value)
{
  name_padding = value;
}

void
StandardLogFormatter::set_log_id_padding(int value)
{
  log_id_padding = value;
}

QString
StandardLogFormatter::format_log(const QString &name, const Level &level,
                                 const quint32 &log_id, const QString &message)
{
  return QString("%1-%2-%3 %4")
      .arg(name.rightJustified(name_padding, ' '))
      .arg(level)
      .arg(QString::number(log_id).rightJustified(log_id_padding, '0'))
      .arg(message);
}
