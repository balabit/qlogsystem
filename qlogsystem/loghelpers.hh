#ifndef LOGSYSTEM_LOGHELPERS_HH
#define LOGSYSTEM_LOGHELPERS_HH

#include <QDebug>

#include "logger.hh"

namespace LOG
{

  /**
   * Gets the string representation of the given Qt object.
   * (Uses the QDebug stream)
   */
  template< class _T >
  inline QString qdebug_to_string(const _T &qt_object)
  {
    QString string;
    QDebug debug(&string);
    debug.nospace() << qt_object;
    return string.trimmed();
  }

  /**
   * ParameterPair represents a key value pair.
   */
  struct ParameterPair
  {
    ParameterPair()
      : empty(true)
    { }

    ParameterPair(const QString &key,
                  const QString &value)
      : empty(false),
        key(key),
        value(value)
    { }

    QString string(const QString &delimiter = ",") const
    {
      if (!empty)
        {
          return QString("%1 %2='%3'")
              .arg(delimiter)
              .arg(key)
              .arg(value);
        }

      return QString();
    }

  private:
    bool empty;
    QString key;
    QString value;
  };

  /**
   * Constructs a log message with parameters.
   */
  inline void
  log_func(const Logger *logger, const Level &level, const quint32 &log_id, const QString &msg,
           const ParameterPair &param1 = ParameterPair(), const ParameterPair &param2 = ParameterPair(),
           const ParameterPair &param3 = ParameterPair(), const ParameterPair &param4 = ParameterPair(),
           const ParameterPair &param5 = ParameterPair(), const ParameterPair &param6 = ParameterPair(),
           const ParameterPair &param7 = ParameterPair(), const ParameterPair &param8 = ParameterPair(),
           const ParameterPair &param9 = ParameterPair(), const ParameterPair &param10 = ParameterPair())
  {
    logger->log(level, log_id,
                QString("%1%2%3%4%5%6%7%8%9%10%11")
                .arg(msg)
                .arg(param1.string(";"))
                .arg(param2.string())
                .arg(param3.string())
                .arg(param4.string())
                .arg(param5.string())
                .arg(param6.string())
                .arg(param7.string())
                .arg(param8.string())
                .arg(param9.string())
                .arg(param10.string())
                );
  }

  inline quint32 align(const quint32 &value, const quint32 &alignment)
  {
    if (value % alignment == 0)
      return value;
    return ((value + alignment) - (value % alignment));
  }

  /**
   * Logs a quint8 array as a hexdump by the given logger.
   */
  inline void
  log_hexdump_func(const Logger *logger, const quint32 &log_id,
                   const quint8 *data, const quint32 &count,
                   int indentation = 0, quint32 blocksize = 1)
  {
    static const int bytes_per_line = 16;

    quint32 bytes = count * blocksize;
    quint32 padded_size = align(bytes, bytes_per_line);
    QString prefix;

    if (indentation > 0)
      prefix.fill(' ', 2 * indentation);

    for (quint32 i = 0; i < padded_size; i += bytes_per_line)
      {
        QString hex;
        QString chars;

        for (quint32 j = i; j < i + bytes_per_line; ++j)
          {
            if (j < bytes)
              {
                QChar ch((char)data[j]);
                hex.append(QString("%1").arg(data[j], 2, 16, QChar('0')));

                if (ch.isPrint())
                  chars.append(ch);
                else
                  chars.append('.');
              }
            else
              {
                hex.append("  ");
                chars.append(' ');
              }

            if (((j - i) % blocksize) == (blocksize - 1))
              {
                hex.append(' ');
                if (blocksize > 1)
                  chars.append(' ');
              }
          }

        logger->log(DUMP, log_id, QString("%1%2  %3  %4").arg(prefix).arg(i, 8, 16, QChar('0')).arg(hex).arg(chars));
      }
  }

} // LOG

// Macro magic
#define qcall_log_func(ID,LEVEL,MESSAGE...) LOG::log_func(logger.operator->(), LEVEL, ID, MESSAGE);
#define qcall_log_hexdump(ID,LEVEL,DATA,SIZE,INDENTATION,BLOCKSIZE) LOG::log_hexdump_func(logger.operator->(), LEVEL, static_cast< const quint8* >(DATA), SIZE, INDENTATION, BLOCKSIZE);

#define qcall_function_when_needed(LOGGER,ID,LEVEL,FUNCTION)  \
  do { \
    LOG::Manager::LoggerRef logger(LOG::Manager::instance()->logger(LOGGER)); \
    if (logger->need_log(LEVEL)) \
      FUNCTION \
  }while(0)

#define qlog_helper_function(LOGGER,ID,LEVEL,MESSAGE...) qcall_function_when_needed(LOGGER,ID,LEVEL,qcall_log_func(ID,LEVEL,MESSAGE))
#define qlog_helper_hexdump_function(LOGGER,ID,LEVEL,DATA,SIZE,INDENTATION,BLOCKSIZE) qcall_function_when_needed(LOGGER,ID,LEVEL,qcall_log_hexdump(ID,LEVEL,DATA,SIZE,INDENTATION,BLOCKSIZE))

#endif // LOGSYSTEM_LOGHELPERS_HH
