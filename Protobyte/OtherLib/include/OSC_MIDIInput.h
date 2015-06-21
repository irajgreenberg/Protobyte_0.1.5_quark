/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#ifndef OSC_MIDIINPUT_H
#define OSC_MIDIINPUT_H

#include <windows.h>
#include <mmsystem.h>
#include <string>

#include "OSC_Defines.h"
#include "OSC_MIDIMessage.h"
#include "OSC_MultiThreading.h"

struct OSC_MIDIInputCallbackData
{
	DWORD pseudoThis;
	DWORD dwInstance;
};

/**
	Base class for generic MIDI input. This class can be used to query the 
	system about available MIDI input devices, and to open any MIDI input device
	and start receiving MIDI input messages.

	When using this class in a project, make your own MIDIInput class that inherits
	from this class, and overload the MidiInput(...) function. This function will
	be called whenever new MIDI data arrives.

	A program using this class might do something like this:
	<ul>
		<li> GetListOfDevices(...) to get the display names of all available 
		MIDI input Devices</li>
		<li> Open(deviceid) - Open a device</li>
		<li> Start() - Start receiving data</li>
		<li> Process all data in the overload MidiInput(...) function</li>
		<li> Stop() - Stop receiving data</li>
		<li> Close() - Close device</li>
	</ul>

*/
class OSC_MIDIInput
{
protected:
	int m_deviceid;
	HMIDIIN m_midiInHandle;
	MMRESULT m_lastMMError;
	OSC_MIDIInputCallbackData m_midiInputCallbackData;
	bool m_open;
	bool m_start;
	static OSC_CritSec m_isInOSC_MIDIInputCallback;

protected:
	OSC_MIDIInput(const OSC_MIDIInput &); // No Copy Constructor
	const OSC_MIDIInput & operator=(const OSC_MIDIInput &); // No assignment
	OSC_ERR SetDeviceId(int deviceid);
public:
	///
	OSC_MIDIInput();
	///
	virtual ~OSC_MIDIInput();

	/// Returns a list of installed MIDI input devices
	void GetListOfDevices(OSC_StringArray  &list, bool includeDeviceNumber = false);
	/// Returns the number of installed devices
	int GetNumDevices();
	/// Get the name of the current open device
	OSC_ERR GetDevName(std::string &name);
	/// Get the name of the specified device (number)
	OSC_ERR GetDevName(int deviceid, std:: string &name);
	/// Get the device id of the specified device (name)
	OSC_ERR GetDevID(const std::string &name, int &deviceid);

	/// Open the device, must be done before running Start()
	OSC_ERR Open(int deviceid);
	///	Close the device
	OSC_ERR Close();
	/// Start recieving MIDI messages. MidiInput(...) will be called for every MIDI message received by the system.
	OSC_ERR Start();
	/// Stop receiving MIDI messages. MidiInput(...) will no longer be called
	OSC_ERR Stop();

	/// Recieves the MIDI input data. Overload this function to do something useful with the MIDI Input
	virtual void MidiInput(OSC_MIDIMessage message);

	/// Returns the latest error (if any) from the Windows MultiMedia system
	MMRESULT GetLastMMError()
	{	return m_lastMMError; };
	/// Returns the latest error in text format
	std::string GetLastMMErrorDescription();

	static void CALLBACK OSC_MIDIInputCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, 
									DWORD dwParam1, DWORD dwParam2); 
};

#endif

