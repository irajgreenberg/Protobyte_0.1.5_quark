/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#ifndef OSC_MIDIOutput_H
#define OSC_MIDIOutput_H

#include <windows.h>
#include <mmsystem.h>
#include "OSC_Defines.h"
#include "OSC_MIDIMessage.h"

/**
	This class does MIDI output. It lets the user get a list of 
	available MIDI output devices, open a MIDI output device and
	send MIDI messages to that device.

	A program using this class might do something like this:
	<ul>
		<li> GetListOfDevices(...) to get the display names of all available 
		MIDI output Devices</li>
		<li> Open(deviceid) - Open a device</li>
		<li> SendMIDIMessage(...) - send cool messages</li>
		<li> Close() - Close device</li>
	</ul>

*/
class OSC_MIDIOutput  
{
private:
	int m_deviceid;
	HMIDIOUT m_midiOutHandle;
	MMRESULT m_lastMMError;

	bool m_open;

protected:
	OSC_MIDIOutput(const OSC_MIDIOutput &); // No Copy-constructor
	const OSC_MIDIOutput & operator= (const OSC_MIDIOutput &); // No assignment
	OSC_ERR SetDeviceId(int deviceid);
public:
	///
	OSC_MIDIOutput();
	///
	virtual ~OSC_MIDIOutput();

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

	/// Opens the device. Must be called before calling SendMIDIMessage(...).
	OSC_ERR Open(int deviceid);
	/// Closes the device
	OSC_ERR Close();

	/// Sends a MIDI message
	void SendMIDIMessage(OSC_MIDIDataShort status,
					  OSC_MIDIDataShort data1,
					  OSC_MIDIDataShort data2);
	/// Sends a MIDI message
	void SendMIDIMessage(const OSC_MIDIMessage &message)
	{
		SendMIDIMessage(message.GetStatusByte(), message.GetDataByte1(), 
			message.GetDataByte2());
	};

	/// Returns the latest error (if any) from the Windows MultiMedia system
	MMRESULT GetLastMMError()
	{	return m_lastMMError; };
	/// Returns the latest error in text format
	std::string GetLastMMErrorDescription();
};

#endif
