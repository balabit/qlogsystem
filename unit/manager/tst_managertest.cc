#include <QString>
#include <QtTest>

#include "manager.hh"

class ManagerTest : public QObject
{
  Q_OBJECT

public:
  ManagerTest();

private Q_SLOTS:
  void init();
  void cleanup();
  void test_root_logger();
  void test_logger_hierarchy();
  void test_loggerref_copy_and_locker();
  void test_logger_deletion();
};

ManagerTest::ManagerTest()
{ }

void
ManagerTest::init()
{
  LOG::Manager::destroy();
}

void
ManagerTest::cleanup()
{
  LOG::Manager::destroy();
}

void
ManagerTest::test_root_logger()
{
  QVERIFY(LOG::Manager::instance()->logger()->need_log(LOG::CRITICAL));

  LOG::Manager::instance()->logger()->log(LOG::CRITICAL, 0, "message");

  QVERIFY(true); // No segfault
}

void
ManagerTest::test_logger_hierarchy()
{
  LOG::Manager::Locker locker;
  LOG::Logger *child_logger = locker.mutable_logger("1.2");
  LOG::Logger *parent_logger = locker.mutable_logger("1");

  QVERIFY(child_logger->need_log(LOG::DEBUG) == false);

  parent_logger->set_level(LOG::DEBUG);

  QVERIFY(child_logger->need_log(LOG::DEBUG));
}

void
ManagerTest::test_loggerref_copy_and_locker()
{
  {
    LOG::Manager::LoggerRef logger = LOG::Manager::instance()->logger();
    LOG::Manager::LoggerRef copy(logger);
  }

  LOG::Manager::Locker locker;

  QVERIFY(true); // No deadlock happend
}

void
ManagerTest::test_logger_deletion()
{
  {
    LOG::Manager::Locker locker;
    locker.mutable_logger("1.2");
    locker.mutable_logger("1");

    locker.mutable_logger("1")->set_level(LOG::DEBUG);
  }

  QVERIFY(LOG::Manager::instance()->logger("1.2")->need_log(LOG::DEBUG));
  QVERIFY(LOG::Manager::instance()->logger("1")->need_log(LOG::DEBUG));

  {
    LOG::Manager::Locker locker;
    locker.delete_logger("1");
  }

  QVERIFY(LOG::Manager::instance()->logger("1.2")->need_log(LOG::DEBUG) == false);
  QVERIFY(LOG::Manager::instance()->logger("1")->need_log(LOG::DEBUG) == false);

  {
    LOG::Manager::Locker locker;
    locker.delete_logger(""); // root logger cannot be deleted
  }

  QVERIFY(LOG::Manager::instance()->logger("1.2")->need_log(LOG::DEBUG) == false);
  QVERIFY(LOG::Manager::instance()->logger("1")->need_log(LOG::DEBUG) == false);
}

QTEST_APPLESS_MAIN(ManagerTest)

#include "tst_managertest.moc"
