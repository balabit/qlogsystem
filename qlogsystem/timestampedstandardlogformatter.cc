#include "timestampedstandardlogformatter.hh"

#include <QDateTime>

using namespace LOG;

TimestampedStandardLogFormatter::TimestampedStandardLogFormatter()
  : StandardLogFormatter()
{ }

TimestampedStandardLogFormatter::~TimestampedStandardLogFormatter()
{ }

QString
TimestampedStandardLogFormatter::format_log(const QString &name, const Level &level,
                                            const quint32 &log_id, const QString &message)
{
  return QString("%1  %2")
      .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
      .arg(StandardLogFormatter::format_log(name, level, log_id, message));
}
