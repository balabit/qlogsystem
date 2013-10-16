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
  QCOMPARE(P1(value).string(), LOG::ParameterPair("value", "5").string());
  QCOMPARE(P1(rect).string(), LOG::ParameterPair("rect", "QRect(0,0 10x10)").string());
}

void
MacrosTest::test_P2()
{
  QCOMPARE(P2("value", 5).string(), LOG::ParameterPair("value", "5").string());
  QCOMPARE(P2("rect", QRect(0, 0, 10, 10)).string(), LOG::ParameterPair("rect", "QRect(0,0 10x10)").string());
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

QTEST_APPLESS_MAIN(MacrosTest)

#include "tst_macrostest.moc"
