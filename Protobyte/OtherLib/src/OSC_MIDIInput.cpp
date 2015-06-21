/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#include <windows.h>
#include "OSC_MIDIInput.h"

// Link with winmm.lib
#pragma comment(lib, "winmm.lib")

OSC_CritSec OSC_MIDIInput::m_isInOSC_MIDIInputCallback;

OSC_MIDIInput::OSC_MIDIInput()
{
	m_deviceid=0;
	m_lastMMError=0;
	m_midiInputCallbackData.pseudoThis= (DWORD) this;
	m_open = m_start = false;
};

OSC_MIDIInput::~OSC_MIDIInput()
{
	if (m_start)
		Stop();
	if (m_open)
		Close();
};

int OSC_MIDIInput::GetNumDevices()
{
	return midiInGetNumDevs();
};

void OSC_MIDIInput::GetListOfDevices(OSC_StringArray &list, bool includeDeviceNumber)
{
	list.clear();
	int num;
	num=GetNumDevices();
	list.resize(num);

	MIDIINCAPS caps;
	char buf[MAXPNAMELEN];

	for (int n=0; n<num; n++)
	{
		midiInGetDevCaps(n,&caps,sizeof(MIDIINCAPS));
		if (includeDeviceNumber)
			sprintf(buf,"%d  %s", n, caps.szPname);
		else
			sprintf(buf,"%s", caps.szPname);
		list[n]=std::string(buf);
	};
};

OSC_ERR OSC_MIDIInput::SetDeviceId(int deviceid)
{
	if ((deviceid>=GetNumDevices()) || (deviceid<0))
		return OSC_ERR_ILLEGAL_DEVICE_ID;
	m_deviceid=deviceid;
	return OSC_ERR_OK;
};

OSC_ERR OSC_MIDIInput::GetDevName(std::string &name)
{
	return GetDevName(m_deviceid, name);
};

OSC_ERR OSC_MIDIInput::GetDevName(int deviceid, std::string &name)
{
	int num;
	num=GetNumDevices();
	if ((deviceid<0) || (deviceid>=num))
		return OSC_ERR_ILLEGAL_DEVICE_ID;

	MIDIINCAPS caps;
	m_lastMMError = midiInGetDevCaps(deviceid, &caps, sizeof(MIDIOUTCAPS));
	if (m_lastMMError)
		return OSC_ERR_MM;
	name = std::string(caps.szPname);
	return OSC_ERR_OK;
};

OSC_ERR OSC_MIDIInput::GetDevID(const std::string &name, int &deviceid)
{
	// loop through all devices and see if we can find a match
	int num;
	num=GetNumDevices();
	std::string ndevname;
	int found=-1;

	for (int n=0; n<num; n++)
	{
		GetDevName(n, ndevname);
		if (ndevname == name)
			found = n;
	};
	if (found==-1)
		return OSC_ERR_ILLEGAL_DEVICE_NAME;

	deviceid=found;
	return OSC_ERR_OK;
};


OSC_ERR OSC_MIDIInput::Open(int deviceid)
{
	OSC_ERR err;
	if (m_open)
	{
		err = Close(); // close if we're allready open
		if (err!=OSC_ERR_OK)
			return err;
	};

	err = SetDeviceId(deviceid);
	if (err!=OSC_ERR_OK)
		return err;

	m_lastMMError=midiInOpen(&m_midiInHandle, m_deviceid, (DWORD) OSC_MIDIInputCallback, 
		(DWORD) &m_midiInputCallbackData, CALLBACK_FUNCTION);
	
	if (m_lastMMError)
		return OSC_ERR_MM;

	m_open = true;
	
	return OSC_ERR_OK;
};

OSC_ERR OSC_MIDIInput::Close()
{
	if (!m_open)
		return OSC_ERR_OK;

	m_lastMMError=midiInClose(m_midiInHandle);

	if (m_lastMMError)
		return OSC_ERR_MM;

	m_open = false;
	
	return OSC_ERR_OK;
};

OSC_ERR OSC_MIDIInput::Start()
{
	if (m_start)
		return OSC_ERR_OK; // We've allready been started

	m_lastMMError=midiInStart(m_midiInHandle);

	if (m_lastMMError)
		return OSC_ERR_MM;

	m_start = true;

	return OSC_ERR_OK;
};

OSC_ERR OSC_MIDIInput::Stop()
{
	if (!m_start)
		return OSC_ERR_OK; // We're not running

	m_lastMMError=midiInStop(m_midiInHandle);

	if (m_lastMMError)
		return OSC_ERR_MM;

	m_start = false;

	return OSC_ERR_OK;
};

std::string OSC_MIDIInput::GetLastMMErrorDescription()
{
	switch (m_lastMMError)
	{
	case 0: return std::string("No Error"); break;
	case MMSYSERR_INVALHANDLE :	return std::string("The specified device handle is invalid"); break;
	case MMSYSERR_ALLOCATED :	return std::string("The specified resource is already allocated"); break;
	case MMSYSERR_BADDEVICEID : return std::string("The specified device identifier is out of range"); break;
	case MMSYSERR_INVALFLAG :	return std::string("The flags specified by dwFlags are invalid"); break;
	case MMSYSERR_INVALPARAM :	return std::string("The specified pointer or structure is invalid"); break;
	case MMSYSERR_NOMEM :		return std::string("The system is unable to allocate or lock memory"); break;
	default:					return std::string("Unknown Error"); break;
	};
};

void OSC_MIDIInput::MidiInput(OSC_MIDIMessage message)
{
	// Overload this function to do something useful.
};


void CALLBACK OSC_MIDIInput::OSC_MIDIInputCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, 
									DWORD dwParam1, DWORD dwParam2)

{
	OSC_AutoLock mutex(&m_isInOSC_MIDIInputCallback);

	if (wMsg==MM_MIM_DATA)
	{
		// Convert to midi-data

		OSC_DWORD_4BYTES mididata;
		mididata.d=dwParam1;

		// get classpointer and call the midiInput function

		OSC_MIDIInputCallbackData *data=(OSC_MIDIInputCallbackData *)dwInstance; 
		OSC_MIDIInput *pseudoThis=(OSC_MIDIInput *)data->pseudoThis;

		pseudoThis->MidiInput(OSC_MIDIMessage(mididata.b[0], mididata.b[1], mididata.b[2], dwParam2));
	};
}; 
