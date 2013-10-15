#ifndef QLOGSYSTEM_STANDARDLOGFORMATTER_HH
#define QLOGSYSTEM_STANDARDLOGFORMATTER_HH

#include "qlogsystem_global.hh"
#include "logformatter.hh"

namespace LOG
{

  /**
   * The StandardLogFormatter class.
   *
   * Format: &lt;component_name&gt;-&lt;log_level&gt;-&lt;log_id&gt; logmessage
   *
   * component_name - right justified (padded with ' ')
   * log_id         - right justified (padded with 0)
   *
   * e.g: 1-0-00000 Hello qlogsystem!
   */
  class QLOGSYSTEMSHARED_EXPORT StandardLogFormatter : public LogFormatter
  {
  public:
    StandardLogFormatter();
    virtual ~StandardLogFormatter();

    void set_name_padding(int value);
    void set_log_id_padding(int value);

    virtual QString format_log(const QString &name, const Level &level,
                               const quint32 &log_id, const QString &message);


  protected:
    int name_padding;
    int log_id_padding;
  };

} // LOG

#endif // QLOGSYSTEM_STANDARDLOGFORMATTER_HH
