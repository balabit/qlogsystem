#include "iodeviceoutput.hh"

#include <QTextStream>
#include <QIODevice>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>

#include <stdio.h>

namespace LOG
{

  class IODeviceOutputPrivate
  {
  public:
    IODeviceOutputPrivate(QIODevice *device)
      : device(device),
        stream(device)
    {
      stream.setCodec("utf-8");
    }

    ~IODeviceOutputPrivate()
    { delete device; }

  public:
    QMutex mutex;
    QIODevice  *device;
    QTextStream stream;
  };

}

using namespace LOG;

IODeviceOutput *
IODeviceOutput::create_from_file(const QString &filepath)
{
  return IODeviceOutput::create(new QFile(filepath));
}

IODeviceOutput *
IODeviceOutput::create_from_file(_IO_FILE *file_descriptor)
{
  QFile *filelogger = new QFile();
  filelogger->open(file_descriptor, QIODevice::WriteOnly | QIODevice::Text);
  return IODeviceOutput::create(filelogger);
}

IODeviceOutput *
IODeviceOutput::create(QIODevice *device)
{
  IODeviceOutput *output = 0;

  if (device &&
      (device->isOpen() ||
       device->open(QIODevice::WriteOnly | QIODevice::Text)))
    {
      output = new IODeviceOutput(device);
    }
  else
    {
      delete device;
    }

  return output;
}

IODeviceOutput::IODeviceOutput(QIODevice *device)
  : LogOutput(),
    d(new IODeviceOutputPrivate(device))
{ }

IODeviceOutput::~IODeviceOutput()
{ delete d; }

void
IODeviceOutput::write_log(const QString &message)
{
  QMutexLocker lock(&d->mutex);

  d->stream << message << endl;
}
