#include <QString>
#include <QtTest>
#include <QRect>

#include "loglevels.hh"
#include "loghelpers.hh"

#include "../common.hh"

class LoghelpersTest : public QObject
{
  Q_OBJECT

public:
  LoghelpersTest();

private Q_SLOTS:
  void init();
  void cleanup();
  void test_qdebug_to_qstring();
  void test_parameter_pair_empty();
  void test_parameter_pair_normal();
  void test_parameter_pair_custom_delimiter();
  void test_log_func_no_extra_params();
  void test_log_func_no_extra_params_all_extra_params();
  void test_hexdump_with_null_length();
  void test_hexdump_exactly_online_partial();
  void test_hexdump_full();
  void test_hexdump_larger_than_text();
  void test_hexdump_5_byte();
  void test_hexdump_indent_2();

protected:
  OutputMock *output;
  LoggerMock *logger;
};

LoghelpersTest::LoghelpersTest()
{ }

void
LoghelpersTest::init()
{
  output = new OutputMock();

  logger = new LoggerMock();
  logger->set_output(output);
  logger->set_formatter(new FormatterMock());
  logger->set_level(LOG::DUMP);
}

void
LoghelpersTest::cleanup()
{
  delete logger;
}

void
LoghelpersTest::test_qdebug_to_qstring()
{
  QCOMPARE(LOG::qdebug_to_string(QRect(10, 10, 50, 50)),
           QString("QRect(10,10 50x50)"));

  QCOMPARE(LOG::qdebug_to_string(QString("a")),
           QString("a"));
}

void
LoghelpersTest::test_parameter_pair_empty()
{
  QCOMPARE(LOG::ParameterPair().string(),
           QString());
}

void
LoghelpersTest::test_parameter_pair_normal()
{
  QCOMPARE(LOG::ParameterPair("key", "value").string(),
           QString(", key='value'"));
}

void
LoghelpersTest::test_parameter_pair_custom_delimiter()
{
  QCOMPARE(LOG::ParameterPair("key", "value").string(";"),
           QString("; key='value'"));
}

void
LoghelpersTest::test_log_func_no_extra_params()
{
  LOG::log_func(logger, LOG::DEBUG, 100, "message");

  QCOMPARE(output->buffered_message,
           QString("message"));
}

void
LoghelpersTest::test_log_func_no_extra_params_all_extra_params()
{
  LOG::log_func(logger, LOG::DEBUG, 100, "message",
                LOG::ParameterPair("key1", "value1"),
                LOG::ParameterPair("key2", "value2"),
                LOG::ParameterPair("key3", "value3"),
                LOG::ParameterPair("key4", "value4"),
                LOG::ParameterPair("key5", "value5"),
                LOG::ParameterPair("key6", "value6"),
                LOG::ParameterPair("key7", "value7"),
                LOG::ParameterPair("key8", "value8"),
                LOG::ParameterPair("key9", "value9"),
                LOG::ParameterPair("key10", "value10")
                );

  QCOMPARE(output->buffered_message,
           QString("message; key1='value1', key2='value2', key3='value3', key4='value4', key5='value5', key6='value6', key7='value7', key8='value8', key9='value9', key10='value10'"));
}

void
LoghelpersTest::test_hexdump_with_null_length()
{
  LOG::log_hexdump_func(logger, 1, (const quint8*)"valuevaluevaluevaluevaluevaluevaluevaluevalue", 0);
  QVERIFY(output->buffered_message.isEmpty());
}

void
LoghelpersTest::test_hexdump_exactly_online_partial()
{
  LOG::log_hexdump_func(logger, 1, (const quint8*)"valuevaluevaluevaluevaluevaluevaluevaluevalue", 15);
  QCOMPARE(output->buffered_message,
           QString("00000000  76 61 6c 75 65 76 61 6c 75 65 76 61 6c 75 65      valuevaluevalue "));
}

void
LoghelpersTest::test_hexdump_full()
{
  LOG::log_hexdump_func(logger, 1, (const quint8*)"valuevaluevaluevaluevaluevaluevaluevaluevalue", 16);
  QCOMPARE(output->buffered_message,
           QString("00000000  76 61 6c 75 65 76 61 6c 75 65 76 61 6c 75 65 76   valuevaluevaluev"));
}

void
LoghelpersTest::test_hexdump_larger_than_text()
{
  LOG::log_hexdump_func(logger, 1, (const quint8*)"valuevaluevaluevaluevaluevaluevaluevaluevalue", 45);
  QCOMPARE(output->buffered_message,
           QString("00000000  76 61 6c 75 65 76 61 6c 75 65 76 61 6c 75 65 76   valuevaluevaluev"
                   "00000010  61 6c 75 65 76 61 6c 75 65 76 61 6c 75 65 76 61   aluevaluevalueva"
                   "00000020  6c 75 65 76 61 6c 75 65 76 61 6c 75 65            luevaluevalue   "));
}

void
LoghelpersTest::test_hexdump_5_byte()
{
  LOG::log_hexdump_func(logger, 1, (const quint8*)"valuevaluevaluevaluevaluevaluevaluevaluevalue", 4, 0, 5);
  QCOMPARE(output->buffered_message,
           QString("00000000  76616c7565 76616c7565 76616c7565 76  value value value v"
                   "00000010  616c7565                             alue               "));
}

void
LoghelpersTest::test_hexdump_indent_2()
{
  LOG::log_hexdump_func(logger, 1, (const quint8*)"valuevaluevaluevaluevaluevaluevaluevaluevalue", 16, 2);
  QCOMPARE(output->buffered_message,
           QString("    00000000  76 61 6c 75 65 76 61 6c 75 65 76 61 6c 75 65 76   valuevaluevaluev"));
}

QTEST_APPLESS_MAIN(LoghelpersTest)

#include "tst_loghelperstest.moc"
