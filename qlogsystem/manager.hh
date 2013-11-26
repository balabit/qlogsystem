#ifndef QLOGSYSTEM_MANAGER_HH
#define QLOGSYSTEM_MANAGER_HH

#include "qlogsystem_global.hh"
#include "logger.hh"

namespace LOG
{

  /**
   * Manager implements a singleton pattern with late initialization.
   *
   * Threadsafe.
   *
   * The loggers are automatically created by the first logger("<id>") call.
   * The loggers are organized in a tree structure. So one can easily change
   * the log output/level/format of a group, by setting the config to their parent
   * node.
   *
   * There is always a root logger (id=""), by default the root logger does not log anything.
   *
   * Logger hierarchy
   *
   * \image html hierarchy.png
   *
   * Logger id syntax:
   *  "component.subcomponent.subsubcomponent"
   *
   */
  class QLOGSYSTEMSHARED_EXPORT Manager
  {
  public:
    /**
     * LoggerRef provides a const Logger pointer interface for logging.
     * The acquired logger count is maintained in the manager.
     */
    class LoggerRef
    {
    public:
      ~LoggerRef();
      LoggerRef(const LoggerRef &other);

      const Logger *operator->() const;

    private:
      LoggerRef(Logger *logger, Manager *manager);
      LoggerRef &operator=(const LoggerRef &other);

    private:
      class LoggerRefPrivate *d;
      friend class Manager;
    };

    /**
     * The Locker ensures thread-safety.
     * The loggers can be changed only by the Locker.
     *
     * The locker can be used only when all LoggerRef was freed, otherwise
     * it will end up in a mutex-lock (deadlock).
     */
    class Locker
    {
    public:
      /**
       * Locks the loggers.
       */
      Locker();
      /**
        * Unlocks the loggers.
        */
      ~Locker();

      /**
       * Getter for a mutable logger instance.
       *
       * @param id The logger id.
       * @return The logger which can be safely changed.
       */
      Logger *mutable_logger(const QString &id = "");

      /**
       * Delete logger and it's children.
       *
       * @param id The logger's id.
       */
      void delete_logger(const QString &id);
    };

    ~Manager();

    /**
     * If it does not exist, creates the instance, then returns a pointer to it.
     *
     * @return Pointer to the log manager instance.
     */
    static Manager *instance();

    /**
     * Destroys the log manager instance.
     *
     * It should only be called in the main thread after waiting all sub-threads having finished.
     */
    static void destroy();

    /**
     * If the logger does not exist with the given id then it will be created.
     * The closest available parent will be set as the parent.
     *
     * The logger in the LoggerRef cannot be changed, and the LoggerRef should not be stored.
     *
     * @param id Logger id. Syntax: "component.subcomponent.subsubcomponent".
     * @return The loggerref.
     */
    Manager::LoggerRef logger(const QString &id = "");

  private:
    /**
     * Gets a pointer for the logger.
     *
     * @param id The logger id.
     * @return Pointer for the logger.
     */
    Logger *mutable_logger(const QString &id);

    /**
     * Helper functions to ensure thread-safety.
     */
    void lock();
    void unlock();
    void refLogger();
    void derefLogger();
  private:
    class ManagerPrivate *d;
    friend class LoggerRef;
    friend class Locker;

  private:
    Manager();
    Q_DISABLE_COPY(Manager)

    static Manager *manager;
  };

} // LOG

#endif // QLOGSYSTEM_MANAGER_HH
