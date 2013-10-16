#include "logger.hh"

#include "logformatter.hh"
#include "logoutput.hh"

namespace LOG
{

  class LoggerPrivate
  {
  public:
    LoggerPrivate(const QString &name, Logger *parent)
      : name(name),
        parent(parent),
        formatter(0),
        log_output(0),
        level(CRITICAL),
        use_parent_level(true)
    { }

    ~LoggerPrivate()
    {
      delete formatter;
      delete log_output;
    }

    QString format_log(const QString &name, const Level &level, const quint32 &log_id, const QString &message);

    void log(const QString &message);

    bool need_log(const Level &level);

  public:
    QString name;
    Logger  *parent;

    LogFormatter *formatter;
    LogOutput    *log_output;

    Level level;
    bool  use_parent_level;
  };

} // LOG

using namespace LOG;

Logger::Logger(const QString &name, Logger *parent)
  : d(new LoggerPrivate(name, parent))
{ }

Logger::~Logger()
{
  delete d;
}

void
Logger::set_formatter(LogFormatter *formatter)
{
  delete d->formatter;
  d->formatter = formatter;
}

void
Logger::set_output(LogOutput *log_output)
{
  delete d->log_output;
  d->log_output = log_output;
}

void
Logger::set_level(const Level &level)
{
  d->use_parent_level = false;
  d->level = level;
}

bool
Logger::need_log(const Level &level) const
{
  return d->need_log(level);
}

void
Logger::log(const Level &level, const quint32 &log_id, const QString &message) const
{
  d->log(d->format_log(d->name, level, log_id, message));
}

// LoggerPrivate

QString
LoggerPrivate::format_log(const QString &name, const Level &level, const quint32 &log_id, const QString &message)
{
  return (formatter) ? formatter->format_log(name, level, log_id, message) :
                       parent->d->format_log(name, level, log_id, message);
}

void
LoggerPrivate::log(const QString &message)
{
  return (log_output) ? log_output->write_log(message) :
                        parent->d->log(message);
}

bool
LoggerPrivate::need_log(const Level &level)
{
  return (use_parent_level && parent) ? parent->d->need_log(level) : this->level >= level;
}
