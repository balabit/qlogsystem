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

#ifndef QLOGSYSTEM_QTCOMPATIBILITY_HH
#define QLOGSYSTEM_QTCOMPATIBILITY_HH

#include <QTextStream>

#if (QT_VERSION < QT_VERSION_CHECK(5, 15, 0))

namespace Qt
{

  QTextStream &endl(QTextStream &s);

}  // namespace Qt

#endif

#endif // QLOGSYSTEM_QTCOMPATIBILITY_HH
