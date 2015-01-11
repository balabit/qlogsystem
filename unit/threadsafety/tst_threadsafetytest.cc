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

#include <QString>
#include <QtTest>
#include <QThread>
#include <QBuffer>
#include <QStringList>
#include <QDateTime>

#include "qlogsystem.hh"
#include "timestampedstandardlogformatter.hh"
#include "iodeviceoutput.hh"

class ThreadsafetyTest : public QObject
{
  Q_OBJECT

public:
  ThreadsafetyTest();

private Q_SLOTS:
  void init();
  void cleanup();

  void test_iodevice_with_multiple_thread();
  void test_manager_locker();
  void test_logger_init_from_multiple_thread();

private:
  QBuffer *device;
};

ThreadsafetyTest::ThreadsafetyTest()
{ }

void
ThreadsafetyTest::init()
{
  LOG::Manager::destroy();

  device = new QBuffer();

  LOG::Manager::Locker locker;
  locker.mutable_logger()->set_formatter(new LOG::TimestampedStandardLogFormatter());
  locker.mutable_logger()->set_output(LOG::IODeviceOutput::create(device));
  locker.mutable_logger()->set_level(LOG::DUMP);
}

void
ThreadsafetyTest::cleanup()
{
  LOG::Manager::destroy();
}

class LoggerThread : public QThread
{
  Q_OBJECT

public:
  LoggerThread(const QString &message, QObject *parent = 0)
    : QThread(parent),
      message(message),
      message_count(10000)
  { }

  int get_message_count() const
  { return message_count; }

protected:
  virtual void run()
  {
    for (int i = 0; i < message_count; ++i)
      {
        log_debug("TEST", 100, message);
      }
  }

private:
  QString message;
  int message_count;
};

void
ThreadsafetyTest::test_iodevice_with_multiple_thread()
{
  LoggerThread t1("thread1");
  LoggerThread t2("thread2");

  t1.start();
  t2.start();
  t1.wait();
  t2.wait();

  QCOMPARE(device->buffer().count("thread1"), t1.get_message_count());
  QCOMPARE(device->buffer().count("thread2"), t2.get_message_count());
}

class OutputChangerThread : public QThread
{
  Q_OBJECT

public:
  OutputChangerThread(QObject *parent = 0)
    : QThread(parent)
  { }

protected:
  virtual void run()
  {
    for (int i = 0; i < 10000; ++i)
      {
        LOG::Manager::Locker lock;
        lock.mutable_logger("TEST")->set_output(LOG::IODeviceOutput::create(new QBuffer()));
      }
  }
};

void
ThreadsafetyTest::test_manager_locker()
{
  LoggerThread t1("thread1");
  LoggerThread t2("thread2");
  OutputChangerThread t3;

  t1.start();
  t2.start();
  t3.start();
  t1.wait();
  t2.wait();
  t3.wait();

  QVERIFY(true); // No segfault
}

class LoggerInitThread : public QThread
{
  Q_OBJECT

public:
  LoggerInitThread(const QStringList &loggers, QObject *parent = 0)
    : QThread(parent),
      loggers(loggers),
      _was_null_logger(false)
  { }

  bool was_null_logger()
  { return _was_null_logger; }

protected:
  virtual void run()
  {
    for (int i = 0; i < 10; ++i)
      {
        foreach (const QString &logger, loggers)
          {
            LOG::Manager::LoggerRef l = LOG::Manager::instance()->logger(logger);
            if (!l.operator ->())
              {
                _was_null_logger = true;
              }
          }
      }
  }

private:
  QStringList loggers;
  bool _was_null_logger;
};

void
ThreadsafetyTest::test_logger_init_from_multiple_thread()
{
  qsrand(123456789);

  QStringList loggers;

  static const int COMPONENTS_SIZE = 10;
  static const int LOGGERS_SIZE = 1000;
  while (loggers.count() != LOGGERS_SIZE)
    {
      int hierarchy_size = (qrand() % COMPONENTS_SIZE) + 1;

      QString id;
      while (hierarchy_size > 0)
        {
          id += QString::number((qrand() % COMPONENTS_SIZE) + 1);

          --hierarchy_size;
        }

      loggers << id;
    }

  static const int THREAD_COUNT = 30;

  for (int i = 0; i < 5; ++i)
    {
      LOG::Manager::destroy();

      QList< LoggerInitThread* > threads;
      for (int i = 0; i < THREAD_COUNT; ++i)
        {
          threads << new LoggerInitThread(loggers);
        }

      foreach (LoggerInitThread *thread, threads)
        {
          thread->start();
        }

      foreach (LoggerInitThread *thread, threads)
        {
          thread->wait();
          QVERIFY(!thread->was_null_logger());
        }

      qDeleteAll(threads);
    }
}

QTEST_APPLESS_MAIN(ThreadsafetyTest)

#include "tst_threadsafetytest.moc"
