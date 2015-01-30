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

#include "logspechandler.hh"

class LogspechandlerTest : public QObject
{
  Q_OBJECT

public:
  LogspechandlerTest();

private Q_SLOTS:
  void init();
  void cleanup();
  void test_invalid_pair();
  void test_invalid_log_level();
  void test_long_spec_error_string();
  void test_valid_case();
  void test_update_logspec_is_transaction_like();
  void test_error_is_only_for_the_last_update();

private:
  LOG::LogSpecHandler *logspec_handler;
};

LogspechandlerTest::LogspechandlerTest()
{ }

void
LogspechandlerTest::init()
{
  LOG::Manager::destroy();

  logspec_handler = new LOG::LogSpecHandler();
}

void
LogspechandlerTest::cleanup()
{
  delete logspec_handler;

  LOG::Manager::destroy();
}

void
LogspechandlerTest::test_invalid_pair()
{
  QVERIFY(logspec_handler->update_logsystem(      "a") == false);
  QVERIFY(logspec_handler->errorString().contains("^"));
  QCOMPARE(LOG::LogSpecHandler::InvalidPair, logspec_handler->error());

  QVERIFY(logspec_handler->update_logsystem(      "a:b:c") == false);
  QVERIFY(logspec_handler->errorString().contains("^"));
  QCOMPARE(LOG::LogSpecHandler::InvalidPair, logspec_handler->error());
}

void
LogspechandlerTest::test_invalid_log_level()
{
  QVERIFY(logspec_handler->update_logsystem(      "a:b") == false);
  QVERIFY(logspec_handler->errorString().contains("  ^"));
  QCOMPARE(LOG::LogSpecHandler::InvalidLogLevel, logspec_handler->error());
}

void
LogspechandlerTest::test_long_spec_error_string()
{
  QVERIFY(logspec_handler->update_logsystem(      "a:1;a:2;a:3;a:4;b:c;c:3") == false);
  QVERIFY(logspec_handler->errorString().contains("                  ^"));
  QVERIFY(logspec_handler->update_logsystem(      "a:1;a:2;a:3;a:4;b:c:d;c:3") == false);
  QVERIFY(logspec_handler->errorString().contains("                ^"));
}

void
LogspechandlerTest::test_valid_case()
{
  logspec_handler->update_logsystem("comp1:5;comp2:3");

  QVERIFY(LOG::Manager::instance()->logger("comp1")->need_log(LOG::DEBUG));
  QVERIFY(LOG::Manager::instance()->logger("comp1")->need_log(LOG::TRACE) == false);

  QVERIFY(LOG::Manager::instance()->logger("comp2")->need_log(LOG::INFO));
  QVERIFY(LOG::Manager::instance()->logger("comp2")->need_log(LOG::EXTENDED_INFO) == false);
}

void
LogspechandlerTest::test_update_logspec_is_transaction_like()
{
  logspec_handler->update_logsystem("comp1:5;comp2:3;a:b");

  QVERIFY(LOG::Manager::instance()->logger("comp1")->need_log(LOG::DEBUG) == false);
  QVERIFY(LOG::Manager::instance()->logger("comp2")->need_log(LOG::INFO) == false);
}

void
LogspechandlerTest::test_error_is_only_for_the_last_update()
{
  logspec_handler->update_logsystem("a:b");
  QCOMPARE(LOG::LogSpecHandler::InvalidLogLevel, logspec_handler->error());
  logspec_handler->update_logsystem("a:1");
  QCOMPARE(LOG::LogSpecHandler::None, logspec_handler->error());
}

QTEST_APPLESS_MAIN(LogspechandlerTest)

#include "tst_logspechandlertest.moc"
