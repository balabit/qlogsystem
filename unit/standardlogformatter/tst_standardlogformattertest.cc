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
