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

#include "loglevels.hh"

class LoglevelsTest : public QObject
{
  Q_OBJECT

public:
  LoglevelsTest();

private Q_SLOTS:
  void test_too_low();
  void test_too_high();
  void test_critical();
  void test_error();
  void test_notice();
  void test_info();
  void test_extended_info();
  void test_debug();
  void test_trace();
  void test_dump();
};

LoglevelsTest::LoglevelsTest()
{ }

void
LoglevelsTest::test_too_low()
{
  QCOMPARE(LOG::get_log_level_from_int(-1), LOG::CRITICAL);
}

void
LoglevelsTest::test_too_high()
{
  QCOMPARE(LOG::get_log_level_from_int(10), LOG::DUMP);
}

void
LoglevelsTest::test_critical()
{
  QCOMPARE(LOG::get_log_level_from_int(0), LOG::CRITICAL);
}

void
LoglevelsTest::test_error()
{
  QCOMPARE(LOG::get_log_level_from_int(1), LOG::ERROR);
}

void
LoglevelsTest::test_notice()
{
  QCOMPARE(LOG::get_log_level_from_int(2), LOG::NOTICE);
}

void
LoglevelsTest::test_info()
{
  QCOMPARE(LOG::get_log_level_from_int(3), LOG::INFO);
}

void
LoglevelsTest::test_extended_info()
{
  QCOMPARE(LOG::get_log_level_from_int(4), LOG::EXTENDED_INFO);
}

void
LoglevelsTest::test_debug()
{
  QCOMPARE(LOG::get_log_level_from_int(5), LOG::DEBUG);
}

void
LoglevelsTest::test_trace()
{
  QCOMPARE(LOG::get_log_level_from_int(6), LOG::TRACE);
}

void
LoglevelsTest::test_dump()
{
  QCOMPARE(LOG::get_log_level_from_int(7), LOG::DUMP);
}

QTEST_APPLESS_MAIN(LoglevelsTest)

#include "tst_loglevelstest.moc"
