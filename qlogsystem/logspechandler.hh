#ifndef QLOGSYSTEM_LOGSPECHANDLER_HH
#define QLOGSYSTEM_LOGSPECHANDLER_HH

#include "manager.hh"

namespace LOG
{

  /**
   * With LogSpecHandler one can update the log components log levels
   * by a simple string.
   */
  class LogSpecHandler
  {
  public:
    enum Error
    {
      None,
      InvalidPair,
      InvalidLogLevel
    };

    LogSpecHandler();
    ~LogSpecHandler();

    /**
     * Updates the logsystem with the given log spec.
     *
     * syntax: &lt;component_name&gt;:&lt;log_level&gt;;&lt;component_name&gt;:&lt;log_level&gt;
     *
     * @param log_spec The log spec to use.
     * @return True if success.
     */
    bool update_logsystem(const QString &log_spec);

    Error error() const;

    /**
     * The error string if an error happend otherwise an empty string.
     *
     * @return The error string.
     */
    const QString &errorString() const;

  private:
    class LogSpecHandlerPrivate *d;
  };

} // LOG

#endif // QLOGSYSTEM_LOGSPECHANDLER_HH
