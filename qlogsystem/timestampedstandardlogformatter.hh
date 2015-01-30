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

#ifndef QLOGSYSTEM_TIMESTAMPEDSTANDARDLOGFORMATTER_HH
#define QLOGSYSTEM_TIMESTAMPEDSTANDARDLOGFORMATTER_HH

#include "qlogsystem_global.hh"
#include "standardlogformatter.hh"

namespace LOG
{

  /**
   * TimestampedStandardLogFormatter class
   *
   * DateTime format: yyyy-MM-dd hh:mm:ss.zzz
   */
  class QLOGSYSTEMSHARED_EXPORT TimestampedStandardLogFormatter : public StandardLogFormatter
  {
  public:
    TimestampedStandardLogFormatter();
    virtual ~TimestampedStandardLogFormatter();

    virtual QString format_log(const QString &name, const Level &level,
                               const quint32 &log_id, const QString &message);
  };

} // LOG

#endif // QLOGSYSTEM_TIMESTAMPEDSTANDARDLOGFORMATTER_HH
