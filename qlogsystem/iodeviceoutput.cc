/**********************************************************************************
 * Copyright (c) 2013-2015 BalaBit IT Ltd, Budapest, Hungary
 *
 * This file is part of qlogsystem.
 *
 * qlogsystem is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * qlogsystem is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with qlogsystem; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************************/

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
IODeviceOutput::create_from_file(FILE *file_descriptor)
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
