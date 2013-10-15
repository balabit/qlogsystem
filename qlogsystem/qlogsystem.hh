#ifndef QLOGSYSTEM_QLOGSYSTEM_HH
#define QLOGSYSTEM_QLOGSYSTEM_HH

#include "manager.hh"
#include "loghelpers.hh"

#define log_critical(LOGGER,ID,MESSAGE...)                      qlog_helper_function(LOGGER,ID,LOG::CRITICAL,MESSAGE)
#define log_error(LOGGER,ID,MESSAGE...)                         qlog_helper_function(LOGGER,ID,LOG::ERROR,MESSAGE)
#define log_notice(LOGGER,ID,MESSAGE...)                        qlog_helper_function(LOGGER,ID,LOG::NOTICE,MESSAGE)
#define log_info(LOGGER,ID,MESSAGE...)                          qlog_helper_function(LOGGER,ID,LOG::INFO,MESSAGE)
#define log_extended_info(LOGGER,ID,MESSAGE...)                 qlog_helper_function(LOGGER,ID,LOG::EXTENDED_INFO,MESSAGE)
#define log_debug(LOGGER,ID,MESSAGE...)                         qlog_helper_function(LOGGER,ID,LOG::DEBUG,MESSAGE)
#define log_trace(LOGGER,ID,MESSAGE...)                         qlog_helper_function(LOGGER,ID,LOG::TRACE,MESSAGE)
#define log_dump(LOGGER,ID,MESSAGE...)                          qlog_helper_function(LOGGER,ID,LOG::DUMP,MESSAGE)
#define log_hexdump(LOGGER,ID,DATA,SIZE)                        qlog_helper_hexdump_function(LOGGER,ID,LOG::DUMP,DATA,SIZE,0,1)
#define log_hexdump2(LOGGER,ID,DATA,SIZE,INDENTATION,BLOCKSIZE) qlog_helper_hexdump_function(LOGGER,ID,LOG::DUMP,DATA,SIZE,INDENTATION,BLOCKSIZE)

#define P1(a)   LOG::ParameterPair(QString(#a), LOG::qdebug_to_string(a))
#define P2(a,b) LOG::ParameterPair(QString(a),  LOG::qdebug_to_string(b))

#endif // QLOGSYSTEM_QLOGSYSTEM_HH
