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

#ifndef QLOGSYSTEM_QLOGSYSTEM_HH
#define QLOGSYSTEM_QLOGSYSTEM_HH

#include "manager.hh"
#include "loghelpers.hh"

#define log_critical(LOGGER,ID,MESSAGE,...)                      qlog_helper_function(LOGGER,ID,LOG::CRITICAL,MESSAGE,##__VA_ARGS__)
#define log_error(LOGGER,ID,MESSAGE,...)                         qlog_helper_function(LOGGER,ID,LOG::ERROR,MESSAGE,##__VA_ARGS__)
#define log_notice(LOGGER,ID,MESSAGE,...)                        qlog_helper_function(LOGGER,ID,LOG::NOTICE,MESSAGE,##__VA_ARGS__)
#define log_info(LOGGER,ID,MESSAGE,...)                          qlog_helper_function(LOGGER,ID,LOG::INFO,MESSAGE,##__VA_ARGS__)
#define log_extended_info(LOGGER,ID,MESSAGE,...)                 qlog_helper_function(LOGGER,ID,LOG::EXTENDED_INFO,MESSAGE,##__VA_ARGS__)
#define log_debug(LOGGER,ID,MESSAGE,...)                         qlog_helper_function(LOGGER,ID,LOG::DEBUG,MESSAGE,##__VA_ARGS__)
#define log_trace(LOGGER,ID,MESSAGE,...)                         qlog_helper_function(LOGGER,ID,LOG::TRACE,MESSAGE,##__VA_ARGS__)
#define log_dump(LOGGER,ID,MESSAGE,...)                          qlog_helper_function(LOGGER,ID,LOG::DUMP,MESSAGE,##__VA_ARGS__)
#define log_hexdump(LOGGER,ID,DATA,SIZE)                         qlog_helper_hexdump_function(LOGGER,ID,LOG::DUMP,DATA,SIZE,0,1)
#define log_hexdump2(LOGGER,ID,DATA,SIZE,INDENTATION,BLOCKSIZE)  qlog_helper_hexdump_function(LOGGER,ID,LOG::DUMP,DATA,SIZE,INDENTATION,BLOCKSIZE)

#define P1(a)   LOG::ParameterPair(QString(#a), LOG::qdebug_to_string(a))
#define P2(a,b) LOG::ParameterPair(QString(a),  LOG::qdebug_to_string(b))

#endif // QLOGSYSTEM_QLOGSYSTEM_HH
