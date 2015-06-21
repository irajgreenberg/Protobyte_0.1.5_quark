#include <stdio.h>
#include <conio.h>

#include <string>

#include <OSC_MIDIOutput.h>
#include <OSC_MIDIInput.h>
#include <OSC_SFManager.h>

class TutorialMIDIInput : public OSC_MIDIInput
{
private:
	OSC_MIDIOutput *m_midiout;
public:
	void SetMIDIOutput(OSC_MIDIOutput *out)
	{
		m_midiout = out;
	};
	virtual void MidiInput(OSC_MIDIMessage message)
	{
		m_midiout->SendMIDIMessage(message);
	};
};

void main()
{
	printf("--- The OSC Tutorial ---\n\n");

	OSC_MIDIOutput midiout;
	OSC_MIDIMessage msg;

	// MIDI Output

	printf("Select MIDI Output Device:\n");

	OSC_StringArray devicelist;
	midiout.GetListOfDevices(devicelist, true);

	for (int i=0; i<devicelist.size(); i++)
		printf("   %s\n", devicelist[i].c_str());

	int midioutdevice;
	scanf("%d", &midioutdevice);

	midiout.Open(midioutdevice);

	TutorialMIDIInput midiin;

	// MIDI Input
	
	printf("Select MIDI Input Device:\n");

	midiin.GetListOfDevices(devicelist, true);

	for (i=0; i<devicelist.size(); i++)
		printf("   %s\n", devicelist[i].c_str());

	int midiindevice;
	scanf("%d", &midiindevice);

	midiin.SetMIDIOutput(&midiout);
	midiin.Open(midiindevice);

	// SoundFonts
	
	OSC_SFManager sfman;
	sfman.Init();
	
	printf("Select SoundFont device (should match the MIDI Output Device):\n");
	
	sfman.GetListOfDevices(devicelist, true);

	for (i=0; i<devicelist.size(); i++)
		printf("   %s\n", devicelist[i].c_str());

	int soundfontdevice;
	scanf("%d", &soundfontdevice);

	sfman.Open(soundfontdevice);

	// Banks

	printf("Select Bank:\n");

	for (i=0; i<128; i++)
		if (sfman.BoolIsMIDIBankUsed(i))
		{
			std::string name;
			if ( (sfman.GetLoadedBankDescriptor(i, name)) != OSC_ERR_OK)
				break;
			else
				printf("[%d]  %s\n", i, name.c_str());
		}

	int bank;
	scanf("%d", &bank);

	// Presets

	printf("Select Preset:\n");

	for (i=0; i<128; i++)
	{
		std::string presetname;
		sfman.GetLoadedPresetDescriptor(bank, i, presetname);
		if (!presetname.empty())
		{
			printf("[%d]  %s\n", i, presetname.c_str());
		};
	}

	int preset;
	scanf("%d", &preset);

	// Set MIDI bank & preset

	// CC0 bank
	msg.Clear();
	msg.SetMessageType(OSC_MIDI_MESSAGE_CONTROL_CHANGE);
	msg.SetChannel(0);
	msg.SetControllerNumber(OSC_MIDI_MESSAGE_CONTROL_BANK_SELECT);
	msg.SetControllerValue(bank);
	midiout.SendMIDIMessage(msg);
	// PgChg program
	msg.Clear();
	msg.SetMessageType(OSC_MIDI_MESSAGE_PROGRAM_CHANGE);
	msg.SetChannel(0);
	msg.SetProgram(preset);
	midiout.SendMIDIMessage(msg);

	midiin.Start();

	printf("Listening to MIDI Device %d, playing on MIDI Device %d\n", 
		midiindevice, midioutdevice);

	printf("Hit a key to exit\n");
	getch();

	midiin.Stop();
	sfman.Close();
	midiin.Close();
	midiout.Close();

};