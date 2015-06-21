/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#ifndef OSC_SFMAN_H
#define OSC_SFMAN_H

/*
History:
					v1.0 Released
	19990604 ThH	Added function GetDevNo(...)
	19990623 ThH	Added function 	GetNumSynthEmulations() and 
					GetSynthEmulationDescription(...) to have an alternative way
					of retrieving info about synth emulations. This method is used
					in the OSC_SFMan ActiveX control.
*/


// This is the sfman.h header file which is part of the SFMS (see below)
// make sure it's in the path (Project | settings | C++ | Preprocessor | Additional include directories)
#include "sfman.h"

#include "OSC_Defines.h"

/** This class is a wrapper class for the SoundFont
    Management System. The SoundFont Management System 
	(SFMS) from Creative Labs is a device independent API
	for SoundFont compatible devices. The API lets the
	programmer load and clear SoundFonts, and retrieve
	information about loaded SoundFonts and about
	the SoundFont compatible device(s).

	To use this class, you will need to download and install
	Creative Labs' SoundFont Management System SDK
	from http://developer.soundblaster.com/ (Developer Tools).

	To fully understand all the functions in this class,
	it is recommended to read Creative Labs' description
	of the SoundFont Management System included in the above
	mentioned SDK.

	For a good example of using this class in a real world program,
	take a look at the source code for SF2LOAD.

**/
class OSC_SFManager
{
protected:
	HINSTANCE m_hSFMANDLL;
	PSFMANAGER  m_lpSFManagerFunctionTable;
	PSFMANL101API m_SFMan;
	int m_currentDevice;
	bool m_deviceOpen;
	LRESULT m_lastSFMError;

protected:
	OSC_ERR ConnectToDLL();
	OSC_ERR GetSFMan();
	OSC_SFManager(const OSC_SFManager&); // No copy-constructor
	const OSC_SFManager & operator=(const OSC_SFManager&); // No assignment
public:
	///
	OSC_SFManager();
	///
	virtual ~OSC_SFManager();
	/// Initialize the SoundFont Manager. Must be called before any of the other functions.
	OSC_ERR Init();
	/// Returns true if the last SFMS API call returned an error.
	bool SFManError();
	/// Returns a textual description of the last SFMS error
	std::string GetLastSFManErrorText();

	/// Returns the number of SoundFont compatible devices installed in the system 
	int GetNumDevs();
	/// Get a list of SoundFont compatible devices
	OSC_ERR GetListOfDevices(OSC_StringArray &list, bool includeDeviceNumber = false);
	/// Returns true if the specified device is free (and can be opened)
	bool IsDeviceFree(int deviceno);

	/// Open the specified device. This must be done before calling any of the functions below.
	OSC_ERR Open(int deviceno);
	/// Close the specified device. This should be done when you're done using the device, letting other applications access the device again.
	OSC_ERR Close();
	/// Get the device number for the current open device
	int GetCurrentOpenDevice();

	/// Has a device been opened (is this object an open device)
	bool IsDeviceOpen();
	/// Load a SoundFont (from disk) into a bank (in memory accessible by the SoundFont device)
	OSC_ERR LoadBank(int bankno, const std::string &path); 
	/// Clear a loaded bank (remove SoundFont from memory)
	OSC_ERR ClearLoadedBank(int bankno);
	/// Clear all loaded banks (frees all the memory) except the synthesizer bank (GM/GS)
	OSC_ERR ClearAllLoadedBanks(bool alsoBank0 = false);
	/** This function is used to check if a particular bank is in use.
		If the bank is in use, the function will 
		return the number of the bank that owns the specified bank.
		If the bank is not in use, the function will return -1.
	**/
	int IsMIDIBankUsed(int bankno);
	/** A simplified version of IsMIDIBank used(...) that
		returns true if the specified bank is in use
		and it is 'owned' by itself. In other words, if
		a SoundFont has been loaded specifically into this bank, 
		and the bank is not owned by another bank.
	**/
	bool BoolIsMIDIBankUsed(int bankno);

	/// Load a preset in a SoundFont on disk into a preset in a bank
	OSC_ERR LoadPreset(int sourceBankno, int sourcePreset, 
		               int destBankno,   int destPreset, 
					   const std::string &path); 
	/// Clear a loaded preset
	OSC_ERR ClearLoadedPreset(int bankno, int preset); 
	/// Load a waveform on disk into a preset in a bank
	OSC_ERR LoadWaveform(int destBankno,   int destPreset, 
					     const std::string &path); 
	/// Clear a loaded waveform
	OSC_ERR ClearLoadedWaveform(int bankno, int preset); 

	/// Get the name of the SoundFont in specified bank (as specified inside the SoundFont file by the author)
	OSC_ERR GetLoadedBankDescriptor(int bankno, std::string &desc);
	/// Get the path to the SoundFont in the specified bank
	OSC_ERR GetLoadedBankPathname(int bankno, std::string &path);
	/// Get the name of the specified preset of the SoundFont in the specified bank
	OSC_ERR GetLoadedPresetDescriptor(int bankno, int presetno, std::string &desc);
	/// Get the capabilities of the specified device (you don't have to open the device first)
	OSC_ERR GetDevCaps(int deviceno, PSFCAPSOBJECT pCaps);
	/// Get the capabilities of the current open device (see SFMS sdk doc for details)
	OSC_ERR GetDevCaps(PSFCAPSOBJECT pCaps);
	/// Get the name of the speified device (you don't have to open the device first)
	OSC_ERR GetDevName(int deviceno, std:: string &name);
	/// Get the name of the current open device
	OSC_ERR GetDevName(std::string &name);
	/// Get the device number of the specified device (name)
	OSC_ERR GetDevNo(const std::string &name, int &deviceno);
	/// Get the maximum amount of memory and the available memory for the current open device
	OSC_ERR QueryStaticSampleMemorySize(int &maxmem, int & availmem);

	/// Get a list of supported synthesizer emulations
	OSC_ERR GetAllSynthEmulations(OSC_StringArray &list);
	/// Get the name and index of the current synthesizer emulation
	OSC_ERR GetSynthEmulation(int &index, std::string &name);
	/// Select the new current synthesizer emulation
	OSC_ERR SelectSynthEmulation(int index);

	/// 
	int GetNumSynthEmulations();
	///
	OSC_ERR GetSynthEmulationDescription(int index, std::string &name);
};

#endif