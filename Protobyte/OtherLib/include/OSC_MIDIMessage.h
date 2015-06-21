/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#ifndef OSC_MIDIMESSAGE_H
#define OSC_MIDIMESSAGE_H

#include "OSC_Defines.h"

/**
	A helper-class to represent a MIDI message. The class has simple access functions
	to make it easy to construct a MIDI message.
*/
class OSC_MIDIMessage
{
private:
	OSC_MIDITimeStamp m_timeStamp;
	OSC_MIDIDataShort m_status;
	OSC_MIDIDataShort m_data1;
	OSC_MIDIDataShort m_data2;
public:
	///
	OSC_MIDIMessage(OSC_MIDIDataShort status=0, OSC_MIDIDataShort data1=0, 
		OSC_MIDIDataShort data2=0, OSC_MIDITimeStamp timeStamp=0)
	{	Init(status, data1, data2, timeStamp); };
	
	///
	~OSC_MIDIMessage()
	{};

	///
	OSC_MIDIMessage(const OSC_MIDIMessage &m)
	{
		operator=(m);
	};

	///
	const OSC_MIDIMessage &operator=(const OSC_MIDIMessage &m)
	{	Init(m.m_status, m.m_data1, m.m_data2, m_timeStamp);
		return *this; };

	///
	bool operator==(const OSC_MIDIMessage &m) const
	{	return (m_status==m.m_status) && (m_data1==m.m_data1) &&
			(m_data2==m.m_data2) && m_timeStamp==m.m_timeStamp; };

	///
	bool operator<(const OSC_MIDIMessage &m) const
	{	return (m_timeStamp<m.m_timeStamp); }

	///
	void Clear()
	{
		Init();
	}

	///
	void Init(OSC_MIDIDataShort status=0, OSC_MIDIDataShort data1=0, OSC_MIDIDataShort data2=0, 
		      OSC_MIDITimeStamp timeStamp=0 )
	{	m_status=status; m_data1=data1; m_data2=data2;
		m_timeStamp=timeStamp; };

	///
	OSC_MIDITimeStamp GetTimeStamp() const
	{	return m_timeStamp; };

	///
	bool IsVoiceMessage() const
	{	return m_status<OSC_MIDI_MESSAGE_SYSTEM_COMMON; };

	///
	bool IsKeyMessage() const
	{	return m_status<OSC_MIDI_MESSAGE_CONTROL_CHANGE; };

	///
	bool IsNoteOnOff() const
	{	return m_status<OSC_MIDI_MESSAGE_KEY_PRESSURE; };

	///
	OSC_MIDIDataShort GetMessageType() const
	{	
		if ( m_status>=OSC_MIDI_MESSAGE_SYSTEM_COMMON)
		{	// system common or system realtime
			return m_status;
		}
		else
		{	// system voice
			if ( ((m_status&OSC_MIDI_MESSAGE_TYPE_MASK)==OSC_MIDI_MESSAGE_NOTE_ON) && (m_data2==0) )
				return OSC_MIDI_MESSAGE_NOTE_OFF;
			else return m_status & OSC_MIDI_MESSAGE_TYPE_MASK; 
		};
	};

	///
	void SetMessageType(const OSC_MIDIDataShort messagetype)
	{
		m_status=(m_status&OSC_MIDI_MESSAGE_CHANNEL_MASK)
			    |(messagetype&OSC_MIDI_MESSAGE_TYPE_MASK);
	}

	///
	OSC_MIDIDataShort GetChannel() const
	{	return m_status & OSC_MIDI_MESSAGE_CHANNEL_MASK; };

	///
	void SetChannel(const OSC_MIDIDataShort &channel)
	{	m_status=(m_status&OSC_MIDI_MESSAGE_TYPE_MASK) // remove old channel info
		        | (channel&OSC_MIDI_MESSAGE_CHANNEL_MASK); // add new channel info
	};

	///
	const OSC_MIDIDataShort &GetNoteNumber() const
	{	return m_data1; };

	///
	const OSC_MIDIDataShort &GetNoteVelocity() const
	{	return m_data2; };

	///
	void SetNoteNumber(const OSC_MIDIDataShort &number)
	{	m_data1=number; };

	///
	void SetNoteVelocity(const OSC_MIDIDataShort &velocity)
	{	m_data2=velocity; };

	///
	const OSC_MIDIDataShort &GetKeyPressure()  const// e.g. After touch
	{	return m_data2; };

	///
	const OSC_MIDIDataShort &GetControllerNumber() const
	{	return m_data1; };

	///
	void SetControllerNumber(const OSC_MIDIDataShort &data)
	{
		m_data1=data;
	}
	
	///
	const OSC_MIDIDataShort &GetControllerValue() const
	{	return m_data2; };

	///
	void SetControllerValue(const OSC_MIDIDataShort &data)
	{
		m_data2=data;
	}

	///
	const OSC_MIDIDataShort &GetProgram() const
	{	return m_data1; };

	///
	void SetProgram(const OSC_MIDIDataShort &data)
	{
		m_data1=data;
	}

	///
	const OSC_MIDIDataShort &GetChannelPressure() const // e.g. Channel Pressure
	{	return m_data1; };

	///
	OSC_MIDIDataLong  GetPitchWheel() const
	{	return GetMIDIDataLong(); };

	///
	OSC_MIDIDataLong GetMIDIDataLong() const
	{	unsigned short data14bit= (unsigned short) m_data2;
		data14bit<<=7;
		data14bit|=(unsigned short) m_data1;
		return data14bit; 
	};

	///
	const OSC_MIDIDataShort &GetDataByte1()  const
	{
		return m_data1;
	};

	///
	void SetDataByte1(const OSC_MIDIDataShort &data)
	{
		m_data1=data;
	}

	///
	const OSC_MIDIDataShort &GetDataByte2() const
	{
		return m_data2;
	};

	///
	void SetDataByte2(const OSC_MIDIDataShort &data)
	{
		m_data2=data;
	}

	///
	const OSC_MIDIDataShort &GetStatusByte() const
	{
		return m_status;
	};

	///
	void SetStatusByte(const OSC_MIDIDataShort &data)
	{
		m_status=data;
	}
};

#endif