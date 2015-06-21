#ifndef OSC_TIMER_H
#define OSC_TIMER_H

#include <mmsystem.h>

/*

Instructions:

Make a subclass using the timer class template with the sub class 
as the template parameter.

Call setTimerCallbackClass(this); from the constructor

define the function void timerCallback();


Example of use:

#include <windows.h> // or "stdafx.h"
#include "OSC_Timer.h"


class TestTimer : public OSC_Timer<TestTimer>
{
public:
	TestTimer()
	{	setTimerCallbackClass(this); };
	void timerCallback()
	{	printf("Ping\n"); };
};


*/


template <class T>
class OSC_Timer
{
private:
	unsigned int m_timerID;
	T *m_timerCallbackClass;
	unsigned int m_delay;
	unsigned int m_resolution;
private:
	static void CALLBACK TimerCallback(UINT uTimerID, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
	{
		((OSC_Timer *)dwInstance)->m_timerCallbackClass->TimerCallback();
	};
protected:
	OSC_Timer(const OSC_Timer &); // No copy-constructor
	const OSC_Timer & operator= (const OSC_Timer &); // No assignment
public:
	OSC_Timer()
	{	m_timerID=0; setTimerDelay(1000); 
		m_timerCallbackClass=NULL; };

	virtual ~OSC_Timer()
	{	if (m_timerID!=0)
			timeKillEvent(m_timerID); 
	};

	void SetTimerCallbackClass( T *timerCallbackClass)
	{	 m_timerCallbackClass= timerCallbackClass; };
	
	void SetTimerDelay(int delay, int resolution=-1)
	{	m_delay=delay; 
		if (resolution==-1)
			m_resolution=m_delay/2;
		else
			m_resolution=resolution; 
	};

	int StartTimer()
	{
		if (m_timerCallbackClass==NULL)
		{
			return (m_timerID=0); // you must set the callback class reference first!
		};
		m_timerID=timeSetEvent(m_delay, m_resolution, timerCallback, 
			(DWORD) this, TIME_PERIODIC);
		return m_timerID;

	};
	void StopTimer()
	{	if (m_timerID!=0)
			timeKillEvent(m_timerID); 
		m_timerID=0;
	};

	int GetTimerID()
	{	return m_timerID; };

	bool TimerIsRunning()
	{	return m_timerID!=0; };

	unsigned int GetTimerDelay()
	{	return m_delay; };
};

#endif