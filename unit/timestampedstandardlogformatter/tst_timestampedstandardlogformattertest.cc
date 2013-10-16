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
