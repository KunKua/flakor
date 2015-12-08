#ifndef RUNTIME_LANG_THREAD_H
#define RUNTIME_LANG_THREAD_H

enum ThreadPrioroty
{
	/** Normal priority. */
	TP_Normal,

	/** Above normal priority. */
	TP_AboveNormal,

	/** Below normal priority. */
	TP_BelowNormal,
    
    /** Highest priority. */
    TP_Highest
}

class ThreadEvent
{
public:
		virtual bool create(bool isManualReset = false) = 0;
		virtual bool isManualReset() = 0;
		virtual void trigger() = 0;
		virtual void reset() = 0;
		virtual bool wait(uint32 waitTime,cons bool ignoreThreadIdleStats = false) = 0;
		bool wait()
		{
			return wait(MAX_uint32);
		}
		bool wait(const Timespan& WaitTime, const bool ignoreThreadIdleStats = false)
		/** Virtual destructor. */
		virtual ~ThreadEvent() { }
}


class Runnable
{
public:
	/**
	 * Initializes the runnable object.
	 *
	 * This method is called in the context of the thread object that aggregates this, not the
	 * thread that passes this runnable to a new thread.
	 *
	 * @return True if initialization was successful, false otherwise
	 * @see Run, Stop, Exit
	 */
	virtual bool init()
	{
		return true;
	}

	/**
	 * Runs the runnable object.
	 *
	 * This is where all per object thread work is done. This is only called if the initialization was successful.
	 *
	 * @return The exit code of the runnable object
	 * @see Init, Stop, Exit
	 */
	virtual uint32 run() = 0;

	/**
	 * Stops the runnable object.
	 *
	 * This is called if a thread is requested to terminate early.
	 * @see Init, Run, Exit
	 */
	virtual void stop() { }

	/**
	 * Exits the runnable object.
	 *
	 * Called in the context of the aggregating thread to perform any cleanup.
	 * @see Init, Run, Stop
	 */
	virtual void exit() { }

	/**
	 * Gets single thread interface pointer used for ticking this runnable when multi-threading is disabled.
	 * If the interface is not implemented, this runnable will not be ticked when FPlatformProcess::SupportsMultithreading() is false.
	 *
	 * @return Pointer to the single thread interface or nullptr if not implemented.
	 */
	virtual class FSingleThreadRunnable* GetSingleThreadInterface( )
	{
		return nullptr;
	}

	/** Virtual destructor */
	virtual ~Runnable() { }
}

class RunnableThread
{
public:
	/** Gets a new Tls slot for storing the runnable thread pointer. */
	static uint32 getTlsSlot();
	static RunnableThread create(Runnabel runnable,
								String name,
								ThreadPriority priority);
	/**
	 * Changes the thread priority of the currently running thread
	 *
	 * @param NewPriority The thread priority to change to
	 */
	virtual void setThreadPriority( ThreadPriority NewPriority ) = 0;

	/**
	 * Tells the thread to either pause execution or resume depending on the
	 * passed in value.
	 *
	 * @param bShouldPause Whether to pause the thread (true) or resume (false)
	 */
	virtual void suspend( bool shouldPause = true ) = 0;

	/**
	 * Tells the thread to exit. If the caller needs to know when the thread
	 * has exited, it should use the bShouldWait value and tell it how long
	 * to wait before deciding that it is deadlocked and needs to be destroyed.
	 * The implementation is responsible for calling Stop() on the runnable.
	 * NOTE: having a thread forcibly destroyed can cause leaks in TLS, etc.
	 *
	 * @param bShouldWait If true, the call will wait for the thread to exit
	 * @return True if the thread exited graceful, false otherwise
	 */
	virtual bool kill( bool shouldWait = false ) = 0;

	/** Halts the caller until this thread is has completed its work. */
	virtual void waitForCompletion() = 0;

	/**
	 * Thread ID for this thread 
	 *
	 * @return ID that was set by CreateThread
	 * @see GetThreadName
	 */
	const uint32 getThreadID() const
	{
		return _threadID;
	}

	/**
	 * Retrieves the given name of the thread
	 *
	 * @return Name that was set by CreateThread
	 * @see GetThreadID
	 */
	const String& getThreadName() const
	{
		return _name;
	}

	/** Default constructor. */
	RunnableThread();

	/** Virtual destructor */
	virtual ~RunnableThread(){}
	
protected:
	/** ID set during thread creation*/
	uint32 _threadId;
	/** the priority to run the thread at */
	ThreadPriority _priority;
	/** the name of this thread */
	String _name;
	/** the runnable object to execute on this thread. */
	Runnable _runnable;
	/** Sync event to make sure that Init() has been completed before allowing the main thread to continue. */
	ThreadEvent _initSyncEvent;

	/** The Affinity to run the thread with. */
	uint64 _affinityMask;
	
private:
	static uint32 runnableTlsSlot;
}

#endif
