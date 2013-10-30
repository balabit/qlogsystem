#include "manager.hh"
#include "timestampedstandardlogformatter.hh"
#include "iodeviceoutput.hh"

#include "qlogsystem.hh"
#include "logspechandler.hh"

#include <QCoreApplication>
#include <QStringList>
#include <QRect>

#include <iostream>
#include <stdio.h>

const quint8 hexdump[] =
{
    0x01, 0x00, 0x0b, 0x00, 0x00, 0x00, 0xcf, 0x03, 0x50, 0x5c, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x05,
    0xff, 0xff, 0x1f, 0x00, 0x00, 0x01, 0x00, 0x00, 0x14, 0x00, 0xff, 0xff, 0x01, 0x07, 0x00, 0x00,
    0x20, 0x20, 0x08, 0xff, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x65, 0x20, 0x58, 0x2e, 0x4f, 0x72,
    0x67, 0x20, 0x46, 0x6f, 0x75, 0x6e, 0x64, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x01, 0x01, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x20, 0x00
};

/**
 * \image hierarchy.png
 */
void
init_logger_hierarchy()
{
  // LOG::Manager::Locker will ensure thread-safety
  // (it locks the Manager in it's constructor and releases it in it's destructor)
  LOG::Manager::Locker locker;

  // Blue nodes
  locker.mutable_logger()->set_formatter(new LOG::StandardLogFormatter());
  locker.mutable_logger()->set_output(LOG::IODeviceOutput::create_from_file(stdout));
  locker.mutable_logger()->set_level(LOG::NOTICE);
  // c2 and c3 will use this settings automatically

  // Green nodes
  locker.mutable_logger("c1")->set_formatter(new LOG::TimestampedStandardLogFormatter());
  locker.mutable_logger("c1")->set_output(LOG::IODeviceOutput::create_from_file(stderr));
  locker.mutable_logger("c1")->set_level(LOG::INFO);
  // c1.c11 and c1.c12 will use this settings automatically

  // Yellow node
  locker.mutable_logger("c3.c31")->set_formatter(new LOG::TimestampedStandardLogFormatter());
  locker.mutable_logger("c3.c31")->set_output(LOG::IODeviceOutput::create_from_file("logoutput.txt"));
  locker.mutable_logger("c3.c31")->set_level(LOG::DUMP);
}


int
main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  Q_UNUSED(app);

  init_logger_hierarchy();

  QStringList args = app.arguments();
  if (args.count() == 2)
    {
      LOG::LogSpecHandler logspec;
      if (!logspec.update_logsystem(args.at(1)))
        {
          std::cout << logspec.errorString().toStdString() << std::endl;
          return 1;
        }
    }

  QString key("value");
  int twenty = 20;
  QRect rect(0, 0, 100, 100);

  // standard error
  log_critical("c1", 0, "Hello qlogsystem!");
  log_error("c1", 1, "log message - parameters without name", P1(key), P1(twenty), P1(rect));
  log_notice("c1", 2, "log message - parameters with name", P2("name", 5), P2("key", "value"), P2("rect", QRect(2, 3, 5, 5)));
  log_info("c1.c12", 2, "cat logoutput.txt");

  // stdout
  log_info("c2", 3, "Hello to stdout!");
  // won't be logged (log level...)
  log_debug("c3", 4, "Hello to stdout! It will not be logged to stdout");

  // standard error
  log_info("c1.c11", 5, "it will be logged to the standard error");
  // won't be logged (log level...)
  log_extended_info("c1.c11", 6, "it will not be logged to the standard error");

  // file
  log_debug("c3.c31", 8, "log level test");
  log_trace("c3.c31", 8, "log level test");
  log_dump("c3.c31", 9, "log level test");
  log_hexdump("c3.c31", 10, hexdump, sizeof(hexdump));

  LOG::Manager::destroy();

  return 0;
}
