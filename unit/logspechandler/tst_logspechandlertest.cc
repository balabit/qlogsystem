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
  QVERIFY(logspec_handler->update_logsystem("a") == false);
  QCOMPARE(LOG::LogSpecHandler::InvalidPair, logspec_handler->error());
  QVERIFY(logspec_handler->errorString().contains("^"));

  QVERIFY(logspec_handler->update_logsystem("a:b:c") == false);
  QCOMPARE(LOG::LogSpecHandler::InvalidPair, logspec_handler->error());
  QVERIFY(logspec_handler->errorString().contains("^"));
}

void
LogspechandlerTest::test_invalid_log_level()
{
  QVERIFY(logspec_handler->update_logsystem("a:b") == false);
  QCOMPARE(LOG::LogSpecHandler::InvalidLogLevel, logspec_handler->error());
  QVERIFY(logspec_handler->errorString().contains("  ^"));
}

void
LogspechandlerTest::test_long_spec_error_string()
{
  QVERIFY(logspec_handler->update_logsystem("a:1;a:2;a:3;a:4;b:c;c:3") == false);
  QVERIFY(logspec_handler->errorString().contains("                ^"));
  QVERIFY(logspec_handler->update_logsystem("a:1;a:2;a:3;a:4;b:c:d;c:3") == false);
  QVERIFY(logspec_handler->errorString().contains("              ^"));
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

QTEST_APPLESS_MAIN(LogspechandlerTest)

#include "tst_logspechandlertest.moc"
