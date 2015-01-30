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

#include "timestampedstandardlogformatter.hh"

class TimestampedstandardlogformatterTest : public QObject
{
  Q_OBJECT

public:
  TimestampedstandardlogformatterTest();

private Q_SLOTS:
  void test_default_settings();
};

TimestampedstandardlogformatterTest::TimestampedstandardlogformatterTest()
{ }

void
TimestampedstandardlogformatterTest::test_default_settings()
{
  LOG::TimestampedStandardLogFormatter formatter;

  QString msg = formatter.format_log("name", LOG::CRITICAL, 100, "message");
  QVERIFY(msg.contains("      name-0-00100 message"));
  QVERIFY(msg.size() == 51); // with timestamp
}

QTEST_APPLESS_MAIN(TimestampedstandardlogformatterTest)

#include "tst_timestampedstandardlogformattertest.moc"
