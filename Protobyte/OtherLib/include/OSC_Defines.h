/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#ifndef OSC_DEFINES_H
#define OSC_DEFINES_H

#include <vector>
#include <string>

// MIDI data types

typedef unsigned char OSC_MIDIDataShort;
typedef unsigned short OSC_MIDIDataLong;
typedef UINT   OSC_MIDITimeStamp;

// MIDI Messages

	// Masks
#define OSC_MIDI_MESSAGE_CHANNEL_MASK		0x0F
#define OSC_MIDI_MESSAGE_TYPE_MASK			0xF0

	// Message Categories (Lower bounds)
#define OSC_MIDI_MESSAGE_SYSTEM_VOICE		0x80
#define OSC_MIDI_MESSAGE_SYSTEM_COMMON		0xF0
#define OSC_MIDI_MESSAGE_SYSTEM_REALTIME	0xF8

	// Message Types
#define OSC_MIDI_MESSAGE_NOTE_OFF			0x80
#define OSC_MIDI_MESSAGE_NOTE_ON			0x90
#define OSC_MIDI_MESSAGE_KEY_PRESSURE		0xA0
#define OSC_MIDI_MESSAGE_CONTROL_CHANGE		0xB0
#define OSC_MIDI_MESSAGE_PROGRAM_CHANGE		0xC0
#define OSC_MIDI_MESSAGE_CHANNEL_PRESSURE	0xD0
#define OSC_MIDI_MESSAGE_PITCH_WHEEL		0xE0

#define OSC_MIDI_MESSAGE_SYSTEM_COMMON_SYSTEM_EXCLUSIVE			0xF0
#define OSC_MIDI_MESSAGE_SYSTEM_COMMON_MTC_QUARTER_FRAME		0xF1
#define OSC_MIDI_MESSAGE_SYSTEM_COMMON_SONG_POSITION_POINTER	0xF2
#define OSC_MIDI_MESSAGE_SYSTEM_COMMON_SONG_SELECT				0xF3
#define OSC_MIDI_MESSAGE_SYSTEM_COMMON_TUNE_REQUEST				0xF6
#define OSC_MIDI_MESSAGE_SYSTEM_COMMON_END_OF_SYSEX				0xF7

#define OSC_MIDI_MESSAGE_SYSTEM_REALTIME_MIDI_CLOCK				0xF8
#define OSC_MIDI_MESSAGE_SYSTEM_REALTIME_MIDI_START				0xFA
#define OSC_MIDI_MESSAGE_SYSTEM_REALTIME_MIDI_CONTINUE			0xFB
#define OSC_MIDI_MESSAGE_SYSTEM_REALTIME_MIDI_STOP				0xFC
#define OSC_MIDI_MESSAGE_SYSTEM_REALTIME_ACTIVE_SENSE			0xFE
#define OSC_MIDI_MESSAGE_SYSTEM_REALTIME_RESET					0xFF

	// Controller Messages
#define OSC_MIDI_MESSAGE_CONTROL_BANK_SELECT		0x00
#define OSC_MIDI_MESSAGE_CONTROL_MOD_WHEEL_MSB		0x01
#define OSC_MIDI_MESSAGE_CONTROL_DATA_ENTRY_MSB		0x06
#define OSC_MIDI_MESSAGE_CONTROL_VOLUME_MSB			0x07
#define OSC_MIDI_MESSAGE_CONTROL_PAN				0x0A
#define OSC_MIDI_MESSAGE_CONTROL_DATA_ENTRY_LSB		0x26
#define OSC_MIDI_MESSAGE_CONTROL_NRPN_LSB			0x62
#define OSC_MIDI_MESSAGE_CONTROL_NRPN_MSB			0x63
#define OSC_MIDI_MESSAGE_CONTROL_ALL_NOTES_OFF		0x7B



// Data conversion

union OSC_DWORD_4BYTES
{
	unsigned int d;
	unsigned char b[4];
};


// String array for list of devices

typedef std::vector<std::string> OSC_StringArray;


// Error constants

typedef int OSC_ERR;

#define OSC_ERR_BASE_SFMAN 500 

#define OSC_ERR_OK 0
#define OSC_ERR_FAIL 1
#define OSC_ERR_ILLEGAL_DEVICE_ID 2
#define OSC_ERR_ILLEGAL_DEVICE_NAME 3
#define OSC_ERR_MM 100

#define OSC_ERR_TIMER_UNAVAILABLE 200

#define OSC_ERR_SFMAN_COULDNT_GET_SFMAN_FUNCTION_TABLE	OSC_ERR_BASE_SFMAN
#define OSC_ERR_SFMAN_COULDNT_GET_SFMAN_INTERFACE		OSC_ERR_BASE_SFMAN + 1
#define OSC_ERR_SFMAN_INVALID_DEVICE_NUMBER				OSC_ERR_BASE_SFMAN + 2

#endif
