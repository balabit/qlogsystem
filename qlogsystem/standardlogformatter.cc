#include "standardlogformatter.hh"

using namespace LOG;

StandardLogFormatter::StandardLogFormatter()
  : LogFormatter(),
    name_padding(10),
    log_id_padding(5)
{ }

StandardLogFormatter::~StandardLogFormatter()
{ }

void
StandardLogFormatter::set_name_padding(int value)
{
  name_padding = value;
}

void
StandardLogFormatter::set_log_id_padding(int value)
{
  log_id_padding = value;
}

QString
StandardLogFormatter::format_log(const QString &name, const Level &level,
                                 const quint32 &log_id, const QString &message)
{
  return QString("%1-%2-%3 %4")
      .arg(name.rightJustified(name_padding, ' '))
      .arg(level)
      .arg(QString::number(log_id).rightJustified(log_id_padding, '0'))
      .arg(message);
}
