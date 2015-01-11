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

#include "standardlogformatter.hh"

class StandardlogformatterTest : public QObject
{
  Q_OBJECT

public:
  StandardlogformatterTest();

private Q_SLOTS:
  void init();
  void cleanup();
  void test_default_settings();
  void test_log_id_padding();
  void test_name_padding();

private:
  LOG::StandardLogFormatter *formatter;
};

StandardlogformatterTest::StandardlogformatterTest()
{ }

void
StandardlogformatterTest::init()
{
  formatter = new LOG::StandardLogFormatter();
}

void
StandardlogformatterTest::cleanup()
{
  delete formatter;
}

void
StandardlogformatterTest::test_default_settings()
{
  QCOMPARE(formatter->format_log("name", LOG::CRITICAL, 100, "message"),
           QString("      name-0-00100 message"));
}

void
StandardlogformatterTest::test_log_id_padding()
{
  formatter->set_log_id_padding(6);
  QCOMPARE(formatter->format_log("name", LOG::CRITICAL, 100, "message"),
           QString("      name-0-000100 message"));
}

void
StandardlogformatterTest::test_name_padding()
{
  formatter->set_name_padding(5);
  QCOMPARE(formatter->format_log("name", LOG::CRITICAL, 100, "message"),
           QString(" name-0-00100 message"));
}

QTEST_APPLESS_MAIN(StandardlogformatterTest)

#include "tst_standardlogformattertest.moc"
