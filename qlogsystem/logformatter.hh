#ifndef QLOGSYSTEM_LOGFORMATTER_HH
#define QLOGSYSTEM_LOGFORMATTER_HH

#include "loglevels.hh"

#include <QString>

namespace LOG
{

  /**
   * Interface for formatting a log message.
   *
   * The subclasses must take care of thread safetiness.
   */
  class LogFormatter
  {
  public:
    LogFormatter() { }
    virtual ~LogFormatter() { }

    /**
     * By subclassing the LogFormatter one can create custom formatted log messages.
     *
     * @param name    The logger's name.
     * @param level   The log message's level.
     * @param log_id  The unique id of the message.
     * @param message The log message itself.
     * @return Should return a message composed from these parameters.
     */
    virtual QString format_log(const QString &name, const Level &level,
                               const quint32 &log_id, const QString &message) = 0;
  };

} // LOG

#endif // QLOGSYSTEM_LOGFORMATTER_HH
