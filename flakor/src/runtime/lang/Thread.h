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

#endif
