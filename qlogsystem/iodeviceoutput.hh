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
    static IODeviceOutput *create_from_file(_IO_FILE *file_descriptor);

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
