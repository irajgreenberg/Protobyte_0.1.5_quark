#ifndef OSCMULTITHREADING_H
#define OSCMULTITHREADING_H

#include <windows.h>

/** Multithreading support. Wrapper for whatever critical section we have
*/
class OSC_CritSec {

    // make copy constructor and assignment operator inaccessible

    OSC_CritSec(const OSC_CritSec &refCritSec);
    OSC_CritSec &operator=(const OSC_CritSec &refCritSec);

    CRITICAL_SECTION m_CritSec;

public:
	///
    OSC_CritSec() 
	{
		InitializeCriticalSection(&m_CritSec);
    };

	///
    ~OSC_CritSec() 
	{
		DeleteCriticalSection(&m_CritSec);
    };

	/// Lock critical section. Block execution if critical section allready lock.
    void Lock() 
	{
		EnterCriticalSection(&m_CritSec);
    };

	/// Unlock critrical section. Unblock threads waiting for this critical section.
    void Unlock() 
	{
		LeaveCriticalSection(&m_CritSec);
    };
};


/** Multithreading support. Locks a critical section, and unlocks it automatically
	when the lock goes out of scope
	*/
class OSC_AutoLock 
{
    // make copy constructor and assignment operator inaccessible
    OSC_AutoLock(const OSC_AutoLock &refAutoLock);
    OSC_AutoLock &operator=(const OSC_AutoLock &refAutoLock);

protected:
    OSC_CritSec * m_pLock;

public:
	///
	OSC_AutoLock(OSC_CritSec * plock)
    {
        m_pLock = plock;
        m_pLock->Lock();
    };
	///
    ~OSC_AutoLock() 
	{
        m_pLock->Unlock();
    };
};

#endif 
