#include "logger.hh"
#include "logoutput.hh"
#include "logformatter.hh"

class LoggerMock : public LOG::Logger
{
public:
  LoggerMock(const QString &name = "name", Logger *parent = 0)
    : LOG::Logger(name, parent)
  { }
};

class FormatterMock : public LOG::LogFormatter
{
public:
  FormatterMock()
    : LOG::LogFormatter()
  { }

  virtual QString format_log(const QString &name, const LOG::Level &level,
                             const quint32 &log_id, const QString &message)
  {
    last_name = name;
    last_level = level;
    last_log_id = log_id;
    last_message = message;
    return message;
  }

  QString last_name;
  LOG::Level last_level;
  quint32 last_log_id;
  QString last_message;
};

class OutputMock : public LOG::LogOutput
{
public:
  OutputMock()
    : LOG::LogOutput()
  { }

  virtual void write_log(const QString &message)
  {
    buffered_message += message;
  }

  QString buffered_message;
};
