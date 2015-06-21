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
#include "OSC_MIDIOutput.h"

// Link with winmm.lib
#pragma comment(lib, "winmm.lib")

OSC_MIDIOutput::OSC_MIDIOutput()
{
	m_deviceid=0;
	m_lastMMError=0;
	m_open = false;
}

OSC_MIDIOutput::~OSC_MIDIOutput()
{
	if (m_open)
		Close();
}

OSC_ERR OSC_MIDIOutput::Open(int deviceid)
{
	OSC_ERR err;

	err = SetDeviceId(deviceid);
	if (err!=OSC_ERR_OK)
		return err;

	if (m_open)
	{
		err = Close();
		if (err!=OSC_ERR_OK)
			return err;
	};

	m_lastMMError=midiOutOpen(&m_midiOutHandle, m_deviceid, NULL, NULL, CALLBACK_NULL);
	
	if (m_lastMMError)
		return OSC_ERR_MM;

	m_open=true;

	return OSC_ERR_OK;
};

OSC_ERR OSC_MIDIOutput::Close()
{
	if (!m_open)
		return OSC_ERR_OK;

	m_lastMMError=midiOutClose(m_midiOutHandle);

	if (m_lastMMError)
		return OSC_ERR_MM;

	m_open=false;

	return OSC_ERR_OK;
};

int OSC_MIDIOutput::GetNumDevices()
{
	return midiOutGetNumDevs();
};

void OSC_MIDIOutput::GetListOfDevices(OSC_StringArray  &list, bool includeDeviceNumber)
{
	list.clear();
	int num;
	num=GetNumDevices();
	list.resize(num);

	MIDIOUTCAPS caps;
	char buf[MAXPNAMELEN];

	for (int n=0; n<num; n++)
	{
		midiOutGetDevCaps(n,&caps,sizeof(MIDIOUTCAPS));
		if (includeDeviceNumber)
			sprintf(buf,"%d  %s", n, caps.szPname);
		else
			sprintf(buf,"%s", caps.szPname);
		list[n]=std::string(buf);
	};
};

OSC_ERR OSC_MIDIOutput::GetDevName(std::string &name)
{
	return GetDevName(m_deviceid, name);
};

OSC_ERR OSC_MIDIOutput::GetDevName(int deviceid, std::string &name)
{
	int num;
	num=GetNumDevices();
	if ((deviceid<0) || (deviceid>=num))
		return OSC_ERR_ILLEGAL_DEVICE_ID;

	MIDIOUTCAPS caps;
	m_lastMMError = midiOutGetDevCaps(deviceid, &caps, sizeof(MIDIOUTCAPS));
	if (m_lastMMError)
		return OSC_ERR_MM;
	name = std::string(caps.szPname);
	return OSC_ERR_OK;
};

OSC_ERR OSC_MIDIOutput::GetDevID(const std::string &name, int &deviceid)
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


OSC_ERR OSC_MIDIOutput::SetDeviceId(int deviceid)
{
	if (deviceid>=(UINT)GetNumDevices())
		return OSC_ERR_ILLEGAL_DEVICE_ID;
	m_deviceid=deviceid;
	return OSC_ERR_OK;
};

std::string OSC_MIDIOutput::GetLastMMErrorDescription()
{
	switch (m_lastMMError)
	{
	case 0:						return std::string("No Error"); break;
	case MMSYSERR_INVALHANDLE : return std::string("The specified device handle is invalid"); break;
	case MMSYSERR_ALLOCATED :	return std::string("The specified resource is already allocated"); break;
	case MMSYSERR_BADDEVICEID : return std::string("The specified device identifier is out of range"); break;
	case MMSYSERR_INVALFLAG :	return std::string("The flags specified by dwFlags are invalid"); break;
	case MMSYSERR_INVALPARAM :	return std::string("The specified pointer or structure is invalid"); break;
	case MMSYSERR_NOMEM :		return std::string("The system is unable to allocate or lock memory"); break;
	default:					return std::string("Unknown Error"); break;
	};
};

void OSC_MIDIOutput::SendMIDIMessage(OSC_MIDIDataShort status,
							   OSC_MIDIDataShort data1,
							   OSC_MIDIDataShort data2)
{
	// Convert 3 bytes to one double word (32 bits unsigned integer)
	OSC_DWORD_4BYTES data;
	data.b[0]=status;
	data.b[1]=data1;
	data.b[2]=data2;
	data.b[3]=0;

	// send the data to the midi output device
	midiOutShortMsg(m_midiOutHandle, data.d);
};

