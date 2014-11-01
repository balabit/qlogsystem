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

#ifndef QLOGSYSTEM_IODEVICEOUTPUT_HH
#define QLOGSYSTEM_IODEVICEOUTPUT_HH

#include "qlogsystem_global.hh"
#include "logoutput.hh"

class QIODevice;
struct _IO_FILE;

namespace LOG
{

  /**
   * IODeviceOutput uses a QIODevice as it's output.
   * UTF-8 codec is used for saving the log messages.
   */
  class QLOGSYSTEMSHARED_EXPORT IODeviceOutput : public LogOutput
  {
  public:
    /**
     * Creates an IODeviceOutput for the given filepath.
     *
     * @param filepath The path for the log output.
     * @return An IODeviceOutput on success, otherwise 0.
     */
    static IODeviceOutput *create_from_file(const QString &filepath);

    /**
     * Creates an IODeviceOutput for the standard error.
     *
     * @return An IODeviceOutput on success, otherwise 0.
     */
    static IODeviceOutput *create_from_file(FILE *file_descriptor);

    /**
     * Creates an IODeviceOutput from the given device.
     * It takes the OWNERSHIP of the device!
     *
     * @return An IODeviceOutput on success, otherwise 0.
     */
    static IODeviceOutput *create(QIODevice *device);
    virtual ~IODeviceOutput();

    /**
     * Writes the log messages to the output.
     */
    virtual void write_log(const QString &message);

  private:
    IODeviceOutput(QIODevice *device);
    Q_DISABLE_COPY(IODeviceOutput)
  private:
    class IODeviceOutputPrivate *d;
  };

} // LOG

#endif // QLOGSYSTEM_IODEVICEOUTPUT_HH
