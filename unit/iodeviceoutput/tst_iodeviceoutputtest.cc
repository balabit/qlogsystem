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
#include <QTemporaryFile>
#include <QBuffer>
#include <QTextStream>
#include <stdio.h>

#include "iodeviceoutput.hh"
#include "qtcompatibility.hh"

class IodeviceoutputTest : public QObject
{
  Q_OBJECT

public:
  IodeviceoutputTest();

private Q_SLOTS:
  void test_invalid_device();
  void test_write_log();
  void test_create_file();
  void test_create_filedescriptor();

private:
  QByteArray expected_output()
  {
    QByteArray message;
    QTextStream stream(&message);
    stream << "message" << Qt::endl;

    return message;
  }
};

IodeviceoutputTest::IodeviceoutputTest()
{ }

void
IodeviceoutputTest::test_invalid_device()
{
  QVERIFY(LOG::IODeviceOutput::create(0) == 0);

  QTemporaryFile file;
  QVERIFY(file.open());

  file.setPermissions(file.permissions() & ~QFile::WriteUser & ~QFile::WriteOwner);

  QVERIFY(LOG::IODeviceOutput::create_from_file(file.fileName()) == 0);

  file.setPermissions(file.permissions() | QFile::WriteUser | QFile::WriteOwner);
}

void
IodeviceoutputTest::test_write_log()
{
  QBuffer *buffer = new QBuffer();

  LOG::IODeviceOutput *output = LOG::IODeviceOutput::create(buffer);
  QVERIFY(output != 0);

  output->write_log("message");

  QCOMPARE(buffer->buffer(), expected_output());
}

void
IodeviceoutputTest::test_create_file()
{
  QTemporaryFile file;

  QVERIFY(file.open());

  LOG::IODeviceOutput *output = LOG::IODeviceOutput::create_from_file(file.fileName());
  QVERIFY(output != 0);

  output->write_log("message");

  QCOMPARE(file.readAll(), expected_output());
}

void
IodeviceoutputTest::test_create_filedescriptor()
{
  LOG::IODeviceOutput *output = LOG::IODeviceOutput::create_from_file(stderr);
  QVERIFY(output != 0);
}

QTEST_APPLESS_MAIN(IodeviceoutputTest)

#include "tst_iodeviceoutputtest.moc"
