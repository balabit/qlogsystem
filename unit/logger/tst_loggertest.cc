#include <QString>
#include <QtTest>

#include "logger.hh"

#include "../common.hh"

class LoggerTest : public QObject
{
  Q_OBJECT

public:
  LoggerTest();

private Q_SLOTS:
  void init();
  void cleanup();
  void test_need_log();
  void test_log();
  void test_logger_use_parent();
  void test_logger_different_log_level_than_parent();
  void test_logger_different_formatter_than_parent();
  void test_logger_different_output_than_parent();
  void test_logger_change_formatter();
  void test_logger_change_output();

private:
  void assert_output_and_formatter(const QString &logger_name);

private:
  LoggerMock *configured_logger;
  FormatterMock *formatter;
  OutputMock *output;
  QString logger_name;
  QString message;
};

LoggerTest::LoggerTest()
{ }

void
LoggerTest::init()
{
  message = "message";

  formatter = new FormatterMock();
  output = new OutputMock();

  logger_name = "123";

  configured_logger = new LoggerMock(logger_name);
  configured_logger->set_formatter(formatter);
  configured_logger->set_output(output);
}

void
LoggerTest::cleanup()
{
  delete configured_logger;
}

void
LoggerTest::test_need_log()
{
  LoggerMock logger;

  QVERIFY(logger.need_log(LOG::CRITICAL));

  QVERIFY(logger.need_log(LOG::DEBUG) == false);

  logger.set_level(LOG::DUMP);

  QVERIFY(logger.need_log(LOG::DEBUG));
}

void
LoggerTest::test_log()
{
  configured_logger->log(LOG::CRITICAL, 100, message);

  assert_output_and_formatter(logger_name);
}

void
LoggerTest::test_logger_use_parent()
{
  configured_logger->set_level(LOG::DEBUG);

  QString logger_name("logger");
  LoggerMock logger(logger_name, configured_logger);

  logger.log(LOG::CRITICAL, 100, message);
  QVERIFY(logger.need_log(LOG::DEBUG));

  assert_output_and_formatter(logger_name);
}

void
LoggerTest::test_logger_different_log_level_than_parent()
{
  LoggerMock logger("logger", configured_logger);
  logger.set_level(LOG::DUMP);

  QVERIFY(configured_logger->need_log(LOG::DEBUG) == false);
  QVERIFY(logger.need_log(LOG::DEBUG));
}

void
LoggerTest::test_logger_different_formatter_than_parent()
{
  QString logger_name("logger");
  LoggerMock logger(logger_name, configured_logger);

  FormatterMock *formatter2 = new FormatterMock();
  logger.set_formatter(formatter2);

  logger.log(LOG::CRITICAL, 100, message);

  QVERIFY(formatter->last_name.isEmpty());
  QCOMPARE(formatter2->last_name, logger_name);
}

void
LoggerTest::test_logger_different_output_than_parent()
{
  QString logger_name("logger");
  LoggerMock logger(logger_name, configured_logger);

  OutputMock *output2 = new OutputMock();
  logger.set_output(output2);

  logger.log(LOG::CRITICAL, 100, message);

  QVERIFY(output->buffered_message.isEmpty());
  QCOMPARE(output2->buffered_message, message);
}

void
LoggerTest::test_logger_change_formatter()
{
  QVERIFY(&(configured_logger->formatter()) == formatter);
}

void
LoggerTest::test_logger_change_output()
{
  QVERIFY(&(configured_logger->output()) == output);
}

void
LoggerTest::assert_output_and_formatter(const QString &logger_name)
{
  QCOMPARE(formatter->last_name, logger_name);
  QCOMPARE(formatter->last_level, LOG::CRITICAL);
  QCOMPARE(formatter->last_log_id, quint32(100));
  QCOMPARE(formatter->last_message, message);

  QCOMPARE(output->buffered_message, message);
}

QTEST_APPLESS_MAIN(LoggerTest)

#include "tst_loggertest.moc"
