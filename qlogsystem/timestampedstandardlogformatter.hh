#ifndef QLOGSYSTEM_TIMESTAMPEDSTANDARDLOGFORMATTER_HH
#define QLOGSYSTEM_TIMESTAMPEDSTANDARDLOGFORMATTER_HH

#include "qlogsystem_global.hh"
#include "standardlogformatter.hh"

namespace LOG
{

  /**
   * TimestampedStandardLogFormatter class
   *
   * DateTime format: yyyy-MM-dd hh:mm:ss.zzz
   */
  class QLOGSYSTEMSHARED_EXPORT TimestampedStandardLogFormatter : public StandardLogFormatter
  {
  public:
    TimestampedStandardLogFormatter();
    virtual ~TimestampedStandardLogFormatter();

    virtual QString format_log(const QString &name, const Level &level,
                               const quint32 &log_id, const QString &message);
  };

} // LOG

#endif // QLOGSYSTEM_TIMESTAMPEDSTANDARDLOGFORMATTER_HH
