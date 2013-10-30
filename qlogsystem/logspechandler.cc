#include "logspechandler.hh"

#include <QStringList>
#include <QTextStream>

namespace LOG
{

  class LogSpecHandlerPrivate
  {
  public:
    LogSpecHandlerPrivate()
      : error(LogSpecHandler::None)
    { }

    void createErrorString(const QString &log_spec, int pos);

    QString errorString;
    LogSpecHandler::Error error;
  };

} // LOG

using namespace LOG;

LogSpecHandler::LogSpecHandler()
  : d(new LogSpecHandlerPrivate())
{ }

LogSpecHandler::~LogSpecHandler()
{
  delete d;
}

bool
LogSpecHandler::update_logsystem(const QString &log_spec)
{
  QStringList setting_entries = log_spec.split(";", QString::SkipEmptyParts);

  int pos = 0;
  foreach (const QString &component_setup, setting_entries)
    {
      QStringList pair = component_setup.split(":");

      if (pair.size() != 2)
        {
          d->error = InvalidPair;
          d->createErrorString(log_spec, pos);
          return false;
        }

      const QString &component_name = pair.at(0);

      pos += component_name.size();
      pos += 1; // < :

      bool ok = false;
      int log_level = pair.at(1).toInt(&ok);

      if (!ok)
        {
          d->error = InvalidLogLevel;
          d->createErrorString(log_spec, pos);
          return false;
        }

      pos += pair.at(1).size();
      pos += 1; // < ;

      Manager::Locker locker;
      locker.mutable_logger(component_name)->set_level(get_log_level_from_int(log_level));
    }

  return true;
}

LogSpecHandler::Error
LogSpecHandler::error() const
{
  return d->error;
}

const QString &
LogSpecHandler::errorString() const
{
  return d->errorString;
}

// LogSpecHandlerPrivate

void
LogSpecHandlerPrivate::createErrorString(const QString &log_spec, int pos)
{
  errorString.clear();

  QTextStream stream(&errorString);
  stream.setCodec("utf-8");

  stream << "Invalid logspec syntax:" << endl << endl;
  stream << log_spec << endl;
  stream << QString("^").rightJustified(pos + 1);
}
