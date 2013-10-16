#ifndef QLOGSYSTEM_LOGOUTPUT_HH
#define QLOGSYSTEM_LOGOUTPUT_HH

#include <QString>

namespace LOG
{

  /**
   * Interface for handling the final (formatted) log messages.
   *
   * The subclasses must take care of thread safetiness.
   */
  class LogOutput
  {
  public:
    LogOutput() { }
    virtual ~LogOutput() { }

    /**
     * By subclassing the LogOutput one can forward log messages to some output.
     *
     * @param message   The formatted message.
     */
    virtual void write_log(const QString &message) = 0;
  };

} // LOG

#endif // QLOGSYSTEM_LOGOUTPUT_HH
