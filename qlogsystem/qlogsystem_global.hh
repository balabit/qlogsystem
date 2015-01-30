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

#ifndef QLOGSYSTEM_GLOBAL_HH
#define QLOGSYSTEM_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(QLOGSYSTEM_LIBRARY)
#  define QLOGSYSTEMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QLOGSYSTEMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QLOGSYSTEM_GLOBAL_HH
