/**********************************************************************************
 * Copyright (c) 2013-2015 BalaBit IT Ltd, Budapest, Hungary
 *
 * This file is part of qlogsystem.
 *
 * qlogsystem is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * qlogsystem is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with qlogsystem; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************************/

#include "manager.hh"

#include "logformatter.hh"
#include "logoutput.hh"

#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>

#include <QHash>

#include <QStringList>

namespace LOG
{

  typedef QHash< QString, Logger* > LoggerHash;

  class ManagerPrivate
  {
  public:
    ManagerPrivate()
    { }

    ~ManagerPrivate()
    {
      qDeleteAll(loggers.values());
    }

    Logger *create_logger(const QString &id);

  public:
    QMutex logger_create_mutex;
    LoggerHash loggers;
    QAtomicInt logger_count;
    QWaitCondition wait_condition;
  };

  class LoggerRefPrivate
  {
  public:
    LoggerRefPrivate(Logger *logger, Manager *manager)
      : logger(logger),
        manager(manager)
    { }

    ~LoggerRefPrivate()
    { }

  public:
    Logger *logger;
    Manager *manager;
  };

  /**
   * Null object pattern.
   */
  class NullFormatter : public LogFormatter
  {
  public:
    virtual QString format_log(const QString &name, const Level &level,
                               const quint32 &log_id, const QString &message)
    {
      Q_UNUSED(name); Q_UNUSED(level); Q_UNUSED(log_id); Q_UNUSED(message);
      return QString();
    }
  };

  /**
   * Null object pattern.
   */
  class NullOutput : public LogOutput
  {
  public:
    virtual void write_log(const QString &message)
    { Q_UNUSED(message); }
  };

} // LOG

using namespace LOG;

static QMutex manager_create_mutex;

Manager *Manager::manager = 0;

// LoggerRef

Manager::LoggerRef::LoggerRef(Logger *logger, Manager *manager)
  : d(new LoggerRefPrivate(logger, manager))
{
  d->manager->refLogger();
}

Manager::LoggerRef::~LoggerRef()
{
  d->manager->derefLogger();
  delete d;
}

Manager::LoggerRef::LoggerRef(const Manager::LoggerRef &other)
  : d(new LoggerRefPrivate(*other.d))
{
  d->manager->refLogger();
}

const Logger *
Manager::LoggerRef::operator->() const
{
  return d->logger;
}

// Locker

Manager::Locker::Locker()
{
  Manager::instance()->lock();
}

Manager::Locker::~Locker()
{
  Manager::instance()->unlock();
}

Logger *
Manager::Locker::mutable_logger(const QString &id)
{
  return Manager::instance()->mutable_logger(id);
}

void
Manager::Locker::delete_logger(const QString &id)
{
  if (!id.isEmpty())
    {
      Manager *manager = Manager::instance();

      foreach (const QString &key, manager->d->loggers.keys())
        {
          if (key.startsWith(id))
            {
              delete manager->d->loggers.take(key);
            }
        }
    }
}

// Manager

Manager::Manager()
  : d(new ManagerPrivate())
{
  Logger *root_logger = new Logger("");

  root_logger->set_formatter(new NullFormatter());
  root_logger->set_output(new NullOutput());

  d->loggers.insert("", root_logger);
}

Manager::~Manager()
{
  delete d;
}

Manager *
Manager::instance()
{
  if (!manager)
    {
      QMutexLocker lock(&manager_create_mutex);
      if (!manager)
        {
          // For thread safety
          Manager *tmp = new Manager();
          manager = tmp;
        }
    }

  return manager;
}

void
Manager::destroy()
{
  delete manager;
  manager = 0;
}

Manager::LoggerRef
Manager::logger(const QString &id)
{
  QMutexLocker lock(&d->logger_create_mutex);

  return LoggerRef(mutable_logger(id), this);
}

Logger *
Manager::mutable_logger(const QString &id)
{
  Logger *logger = d->loggers.value(id, 0);

  if (!logger)
    {
      logger = d->create_logger(id);
    }

  return logger;
}

void
Manager::lock()
{
  d->logger_create_mutex.lock();
  while (d->logger_count.fetchAndAddOrdered(0) != 0)
    {
      d->wait_condition.wait(&d->logger_create_mutex, 100);
    }
}

void
Manager::unlock()
{
  d->logger_create_mutex.unlock();
}

void
Manager::refLogger()
{
  d->logger_count.ref();
}

void
Manager::derefLogger()
{
  if (!d->logger_count.deref())
    {
      d->wait_condition.wakeAll();
    }
}

// LogManagerPrivate

Logger *
ManagerPrivate::create_logger(const QString &id)
{
  QStringList hierarchy_should_be_created;

  QString parent_id = id;
  Logger *parent_logger = 0;

  do
    {
      int last_separator_post = parent_id.lastIndexOf('.');

      if (last_separator_post != -1)
        {
          parent_id.remove(last_separator_post, parent_id.size());
        }
      else
        {
          parent_id.clear();
        }

      parent_logger = loggers.value(parent_id, 0);

      if (!parent_logger)
        {
          hierarchy_should_be_created.prepend(parent_id);
        }
    }
  while (parent_logger == 0);

  foreach (const QString &logger_name, hierarchy_should_be_created)
    {
      Logger *tmp = new Logger(logger_name, parent_logger);
      loggers.insert(logger_name, tmp);
      parent_logger = tmp;
    }

  Logger *tmp = new Logger(id, parent_logger);
  loggers.insert(id, tmp);

  return tmp;
}
