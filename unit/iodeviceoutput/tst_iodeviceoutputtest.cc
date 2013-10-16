#include <QString>
#include <QtTest>
#include <QTemporaryFile>
#include <QBuffer>
#include <QTextStream>
#include <stdio.h>

#include "iodeviceoutput.hh"

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
    stream << "message" << endl;

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
