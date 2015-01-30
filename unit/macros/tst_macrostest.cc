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
#include <QRect>

#include "qlogsystem.hh"

#include "../common.hh"

class MacrosTest : public QObject
{
  Q_OBJECT

public:
  MacrosTest();

private Q_SLOTS:
  void init();
  void cleanup();
  void test_P1();
  void test_P2();
  void test_log_critical();
  void test_log_error();
  void test_log_notice();
  void test_log_info();
  void test_log_extended_info();
  void test_log_debug();
  void test_log_trace();
  void test_log_dump();
  void test_log_hexdump();
  void test_log_hexdump2();
  void test_macros_combined_with_P();

private:
  OutputMock *output;
  QString message;
};

MacrosTest::MacrosTest()
{ }

void
MacrosTest::init()
{
  LOG::Manager::destroy();

  output = new OutputMock();
  message = "message";

  LOG::Manager::Locker locker;
  locker.mutable_logger()->set_formatter(new FormatterMock());
  locker.mutable_logger()->set_output(output);
  locker.mutable_logger()->set_level(LOG::DUMP);
}

void
MacrosTest::cleanup()
{
  LOG::Manager::destroy();
}

void
MacrosTest::test_P1()
{
  int value = 5;
  QRect rect(0, 0, 10, 10);
  QCOMPARE(log_parameter_as_string(P1(value)), log_parameter_as_string(LOG::ParameterPair("value", "5")));
  QCOMPARE(log_parameter_as_string(P1(rect)), log_parameter_as_string(LOG::ParameterPair("rect", "QRect(0,0 10x10)")));
}

void
MacrosTest::test_P2()
{
  QCOMPARE(log_parameter_as_string(P2("value", 5)), log_parameter_as_string(LOG::ParameterPair("value", "5")));
  QCOMPARE(log_parameter_as_string(P2("rect", QRect(0, 0, 10, 10))), log_parameter_as_string(LOG::ParameterPair("rect", "QRect(0,0 10x10)")));
}

void
MacrosTest::test_log_critical()
{
  log_critical("TEST", 0, message);
  QCOMPARE(output->buffered_message, message);
}

void
MacrosTest::test_log_error()
{
  log_error("TEST", 0, message);
  QCOMPARE(output->buffered_message, message);
}

void
MacrosTest::test_log_notice()
{
  log_notice("TEST", 0, message);
  QCOMPARE(output->buffered_message, message);
}

void
MacrosTest::test_log_info()
{
  log_info("TEST", 0, message);
  QCOMPARE(output->buffered_message, message);
}

void
MacrosTest::test_log_extended_info()
{
  log_extended_info("TEST", 0, message);
  QCOMPARE(output->buffered_message, message);
}

void
MacrosTest::test_log_debug()
{
  log_debug("TEST", 0, message);
  QCOMPARE(output->buffered_message, message);
}

void
MacrosTest::test_log_trace()
{
  log_trace("TEST", 0, message);
  QCOMPARE(output->buffered_message, message);
}

void
MacrosTest::test_log_dump()
{
  log_dump("TEST", 0, message);
  QCOMPARE(output->buffered_message, message);
}

void
MacrosTest::test_log_hexdump()
{
  log_hexdump("TEST", 0, (const quint8*)"valuevaluevaluevaluevaluevaluevaluevaluevalue", 16);
  QCOMPARE(output->buffered_message, QString("00000000  76 61 6c 75 65 76 61 6c 75 65 76 61 6c 75 65 76   valuevaluevaluev"));
}

void
MacrosTest::test_log_hexdump2()
{
  log_hexdump2("TEST", 0, (const quint8*)"valuevaluevaluevaluevaluevaluevaluevaluevalue", 4, 0, 5);
  QCOMPARE(output->buffered_message, QString("00000000  76616c7565 76616c7565 76616c7565 76  value value value v"
                                             "00000010  616c7565                             alue               "));
}

void
MacrosTest::test_macros_combined_with_P()
{
  int log_me = 42;
  log_critical("TEST", 0, message, P1(log_me), P2("a", "b"));
  log_error("TEST", 0, message, P1(log_me), P2("a", "b"));
  log_notice("TEST", 0, message, P1(log_me), P2("a", "b"));
  log_info("TEST", 0, message, P1(log_me), P2("a", "b"));
  log_extended_info("TEST", 0, message, P1(log_me), P2("a", "b"));
  log_debug("TEST", 0, message, P1(log_me), P2("a", "b"));
  log_trace("TEST", 0, message, P1(log_me), P2("a", "b"));
  log_dump("TEST", 0, message, P1(log_me), P2("a", "b"));
  QCOMPARE(output->buffered_message, QString("message; log_me='42', a='b'"
                                             "message; log_me='42', a='b'"
                                             "message; log_me='42', a='b'"
                                             "message; log_me='42', a='b'"
                                             "message; log_me='42', a='b'"
                                             "message; log_me='42', a='b'"
                                             "message; log_me='42', a='b'"
                                             "message; log_me='42', a='b'"));
}

QTEST_APPLESS_MAIN(MacrosTest)

#include "tst_macrostest.moc"
