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

#ifndef QLOGSYSTEM_STANDARDLOGFORMATTER_HH
#define QLOGSYSTEM_STANDARDLOGFORMATTER_HH

#include "qlogsystem_global.hh"
#include "logformatter.hh"

namespace LOG
{

  /**
   * The StandardLogFormatter class.
   *
   * Format: &lt;component_name&gt;-&lt;log_level&gt;-&lt;log_id&gt; logmessage
   *
   * component_name - right justified (padded with ' ')
   * log_id         - right justified (padded with 0)
   *
   * e.g: 1-0-00000 Hello qlogsystem!
   */
  class QLOGSYSTEMSHARED_EXPORT StandardLogFormatter : public LogFormatter
  {
  public:
    StandardLogFormatter();
    virtual ~StandardLogFormatter();

    void set_name_padding(int value);
    void set_log_id_padding(int value);

    virtual QString format_log(const QString &name, const Level &level,
                               const quint32 &log_id, const QString &message);


  protected:
    int name_padding;
    int log_id_padding;
  };

} // LOG

#endif // QLOGSYSTEM_STANDARDLOGFORMATTER_HH
