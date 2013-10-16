#ifndef QLOGSYSTEM_LOGLEVELS_HH
#define QLOGSYSTEM_LOGLEVELS_HH

namespace LOG
{

  enum Level
  {
    CRITICAL = 0,
    ERROR,
    NOTICE,
    INFO,
    EXTENDED_INFO,
    DEBUG,
    TRACE,
    DUMP
  };

  /**
   * Gets a log level enum from the given int.
   */
  inline Level get_log_level_from_int(const int &log_level)
  {
    Level level;

    if (log_level > DUMP)
      {
        level = DUMP;
      }
    else if (log_level < CRITICAL)
      {
        level = CRITICAL;
      }
    else
      {
        level = static_cast< Level >(log_level);
      }

    return level;
  }

} // LOG

#endif // QLOGSYSTEM_LOGLEVELS_HH
