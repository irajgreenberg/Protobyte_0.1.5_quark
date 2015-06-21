/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#include "OSC_SFManager.h"

OSC_SFManager::OSC_SFManager()
{
	m_hSFMANDLL=NULL;
	m_currentDevice = -1;
	m_deviceOpen = false;
};

OSC_SFManager::~OSC_SFManager()
{
	if (IsDeviceOpen())
		Close();
	if (m_hSFMANDLL!=NULL)
		FreeLibrary(m_hSFMANDLL);
};

bool OSC_SFManager::SFManError()
{
	return (bool) (m_lastSFMError!=SFERR_NOERR);
}

std::string OSC_SFManager::GetLastSFManErrorText()
{
	std::string ret;
	switch (m_lastSFMError)
	{
	case	SFERR_NOERR					:	ret = std::string(""); break;
	case	SFERR_UNDEFINE_ERROR        :	ret = std::string("Undefined Error"); break;
	case	SFERR_LOAD_DLL_FAIL         :	ret = std::string("Load Dll Failed"); break;
	case	SFERR_GET_ENTRYPOINT_FAIL   :	ret = std::string("Get Entrypoint Fail"); break;
	case	SFERR_DEVICE_NOT_FOUND      :	ret = std::string("Device Not Found"); break;
	case	SFERR_INTERFACE_NOT_SUPPORTED :	ret = std::string("Interface Not Supported"); break;
	case	SFERR_LAST_API              :	ret = std::string("Last API"); break;
	case	SFERR_SYNTH_INVALID         :	ret = std::string("Synth Invalid"); break;
	case	SFERR_BANK_INDEX_INVALID    :	ret = std::string("Bank Index Invalid"); break;
	case	SFERR_PATHNAME_INVALID      :	ret = std::string("Pathname Invalid"); break;
	case	SFERR_FORMAT_INVALID        :	ret = std::string("Format Invalid"); break;
	case	SFERR_PRESET_INDEX_INVALID  :	ret = std::string("Preset Index Invalid"); break;
	case	SFERR_ACCESS_NOT_PERMITTED  :	ret = std::string("Access Not Permitted"); break;
	case	SFERR_VERSION_INVALID       :	ret = std::string("Version Invalid"); break;
	case	SFERR_DEVICE_INVALID        :	ret = std::string("Device Invalid"); break;
	case	SFERR_SUPPORT_INVALID       :	ret = std::string("Support Invalid"); break;
	case	SFERR_INVALID_SOUND_ROM     :	ret = std::string("Invalid Sound Rom"); break;
	case	SFERR_NOT_STATIC_MEMORY     :	ret = std::string("Not Static Memory"); break;
	case	SFERR_LAST_INVALID          :	ret = std::string("Last Invalid"); break;
	case	SFERR_DLL_BUSY              :	ret = std::string("Dll Busy"); break;
	case	SFERR_DEVICE_BUSY           :	ret = std::string("Device Busy"); break;
	case	SFERR_RESOURCE_INSUFFICIENT :	ret = std::string("Resource Insufficient"); break;
	case	SFERR_SYSMEM_INSUFFICIENT   :	ret = std::string("System Memory Insufficient"); break;
	case	SFERR_SOUNDMEM_INSUFFICIENT :	ret = std::string("Sound Memory Insufficient"); break;
	case	SFERR_LAST_CONTENTION       :	ret = std::string("Last Contention"); break;
	default : ret = std::string("Unknown Error");
	};

	return ret;
};


OSC_ERR OSC_SFManager::ConnectToDLL()
{
	if (m_hSFMANDLL!=NULL)
		FreeLibrary(m_hSFMANDLL);
	m_hSFMANDLL = NULL;
	m_hSFMANDLL = LoadLibrary (SF_MASTER_MANAGER_FILENAME);
	if (m_hSFMANDLL == NULL ) 
		return OSC_ERR_FAIL;
	else
		return OSC_ERR_OK;
};

OSC_ERR OSC_SFManager::GetSFMan()
{
	OSC_ERR res;
	res = ConnectToDLL();
	if (res!=OSC_ERR_OK)
		return res;

	// Get the address of the SoundFont manager function table
    m_lpSFManagerFunctionTable = (PSFMANAGER)GetProcAddress(m_hSFMANDLL, SF_FUNCTION_TABLE_NAME);
    
	// If this fails, unload the library and report an error
	if  (m_lpSFManagerFunctionTable == NULL) 
	{
		return OSC_ERR_SFMAN_COULDNT_GET_SFMAN_FUNCTION_TABLE;
	}

	// Use SF_QueryInterface to get access to the appropriate function table
    if (m_lpSFManagerFunctionTable->SF_QueryInterface(ID_SFMANL101API, (PDWORD) &m_SFMan))
    {
		return OSC_ERR_SFMAN_COULDNT_GET_SFMAN_INTERFACE;
    }

	return OSC_ERR_OK;
};

OSC_ERR OSC_SFManager::Init()
{
	OSC_ERR res;
	res = GetSFMan();
	return res;
};

int OSC_SFManager::GetNumDevs()
{
	WORD numSFDevs;
	m_lastSFMError = m_SFMan->SF_GetNumDevs(&numSFDevs);
	return numSFDevs;
};

OSC_ERR OSC_SFManager::GetListOfDevices(OSC_StringArray &list, bool includeDeviceNumber)
{
	OSC_ERR res = OSC_ERR_OK;
	CSFCapsObject caps;
	list.clear();
	char buf[512];
	for (int i=0; i<GetNumDevs(); i++)
	{
		m_lastSFMError = GetDevCaps(i, &caps);
		if (m_lastSFMError!=SFERR_NOERR)
		{
			res = OSC_ERR_FAIL;
			break;
		};
		if (includeDeviceNumber)
			sprintf(buf,"%d  %s", i, caps.m_DevName);
		else
			sprintf(buf,"%s", caps.m_DevName);
		list.push_back(buf);
	}
	return res;
};


OSC_ERR OSC_SFManager::Open(int deviceno)
{
	if ((deviceno<0) || (deviceno>=GetNumDevs()))
		return OSC_ERR_SFMAN_INVALID_DEVICE_NUMBER;
	if (IsDeviceOpen())
		Close();
	m_currentDevice = deviceno;
	m_deviceOpen=true;
	m_lastSFMError = m_SFMan->SF_Open(m_currentDevice);
	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};

OSC_ERR OSC_SFManager::Close()
{
	m_lastSFMError = m_SFMan->SF_Close(m_currentDevice);
	m_currentDevice = -1;
	m_deviceOpen=false;
	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};

bool OSC_SFManager::IsDeviceOpen()
{
	return m_deviceOpen;
};

int OSC_SFManager::GetCurrentOpenDevice()
{
	return m_currentDevice;
};

bool OSC_SFManager::IsDeviceFree(int deviceno)
{
	m_lastSFMError = m_SFMan->SF_IsDeviceFree(deviceno);
	if (m_lastSFMError == SFERR_NOERR)
		return true;
	else
		return false;
};

OSC_ERR OSC_SFManager::LoadBank(int bankno, const std::string &path)
{
	CSFMIDILocation midi;
	CSFBufferObject buf;
	char textbuf[1024];
	textbuf[1023] = 0;
	strncpy (textbuf, path.c_str(), 1023);
	midi.m_BankIndex = bankno;
	buf.m_Flag = SFFLAG_OPER_FILE;
	buf.m_Buffer = textbuf;
	buf.m_Size = strlen(textbuf) + 1;
	m_lastSFMError = m_SFMan->SF_LoadBank(m_currentDevice, &midi, &buf);
	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
}; 

OSC_ERR OSC_SFManager::ClearLoadedBank(int bankno)
{
	CSFMIDILocation midi;
	midi.m_BankIndex = bankno;
	bool done=false;
	while (!done)
	{
		m_lastSFMError = m_SFMan->SF_ClearLoadedBank(m_currentDevice, &midi);
		if (m_lastSFMError != OSC_ERR_OK)
			return OSC_ERR_FAIL;
		if (IsMIDIBankUsed(bankno)!=bankno)
			done = true;
	};
	return OSC_ERR_OK;
};

OSC_ERR OSC_SFManager::ClearAllLoadedBanks(bool alsoBank0)
{
	// Note: Will not clear bank 0, the emulation bank
	OSC_ERR res = OSC_ERR_OK;
	int start;
	start = alsoBank0 ? 0 : 1;

	for (int i=start; i<=127; i++)
		if (IsMIDIBankUsed(i)==i)
		{
			res = ClearLoadedBank(i);
			if (res != OSC_ERR_OK)
				break;
		};
	return res;
};

int OSC_SFManager::IsMIDIBankUsed(int bankno)
{
	WORD index = bankno;
	m_lastSFMError = m_SFMan->SF_IsMIDIBankUsed(m_currentDevice, &index);
	if (index==65535)
		return -1;
	else
		return index;
};

bool OSC_SFManager::BoolIsMIDIBankUsed(int bankno)
{
	return (bool) (IsMIDIBankUsed(bankno) == bankno);
};


OSC_ERR OSC_SFManager::GetLoadedBankDescriptor(int bankno, std::string &desc)
{
	CSFMIDILocation midi;
	CSFBufferObject buf;
	char textbuf[1024];
	textbuf[1023] = 0;
	midi.m_BankIndex = bankno;
	buf.m_Buffer = textbuf;
	buf.m_Size = 1023;

	m_lastSFMError = m_SFMan->SF_GetLoadedBankDescriptor(m_currentDevice, &midi, &buf);

	if (m_lastSFMError == SFERR_NOERR)
		desc = std::string(buf.m_Buffer);
	else
		desc = std::string();

	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};

OSC_ERR OSC_SFManager::GetLoadedBankPathname(int bankno, std::string &path)
{
	CSFMIDILocation midi;
	CSFBufferObject buf;
	char textbuf[1024];
	textbuf[1023] = 0;
	midi.m_BankIndex = bankno;
	buf.m_Buffer = textbuf;
	buf.m_Size = 1023;

	m_lastSFMError = m_SFMan->SF_GetLoadedBankPathname(m_currentDevice, &midi, &buf);

	if (m_lastSFMError == SFERR_NOERR)
		path = std::string(buf.m_Buffer);
	else
		path = std::string();

	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};

OSC_ERR OSC_SFManager::GetLoadedPresetDescriptor(int bankno, int presetno, std::string &desc)
{
	CSFMIDILocation midi;
	CSFBufferObject buf;
	char textbuf[1024];
	textbuf[1023] = 0;
	midi.m_BankIndex = bankno;
	midi.m_PresetIndex = presetno;
	buf.m_Buffer = textbuf;
	buf.m_Size = 1023;

	m_lastSFMError = m_SFMan->SF_GetLoadedPresetDescriptor(m_currentDevice, &midi, &buf);

	if (m_lastSFMError == SFERR_NOERR)
	{
		if ((buf.m_SizeUsed > 1) || (textbuf[0] != 0))
			desc = std::string(buf.m_Buffer);
		else
			desc = std::string();
	}
	else
		desc = std::string();

	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};


OSC_ERR OSC_SFManager::GetDevCaps(PSFCAPSOBJECT pCaps)
{
	m_lastSFMError =  m_SFMan->SF_GetDevCaps(m_currentDevice, pCaps);

	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};

OSC_ERR OSC_SFManager::GetDevCaps(int deviceno, PSFCAPSOBJECT pCaps)
{
	m_lastSFMError =  m_SFMan->SF_GetDevCaps(deviceno, pCaps);
	
	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};

OSC_ERR OSC_SFManager::GetDevName(std::string &name)
{
	return GetDevName(m_currentDevice, name);
};

OSC_ERR OSC_SFManager::GetDevName(int deviceno, std::string &name)
{
	OSC_ERR res;
	CSFCapsObject caps;
	res = GetDevCaps(deviceno, &caps);
	if (res != OSC_ERR_OK)
		return res;
	name = std::string(caps.m_DevName);
	return res;
};

OSC_ERR OSC_SFManager::GetDevNo(const std::string &name, int &deviceno)
{
	// loop through all devices and see if we can find a match
	int num;
	num=GetNumDevs();
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

	deviceno=found;
	return OSC_ERR_OK;
};



OSC_ERR OSC_SFManager::QueryStaticSampleMemorySize(int &maxmem, int & availmem)
{
	DWORD max, avail;
	m_lastSFMError = m_SFMan->SF_QueryStaticSampleMemorySize(m_currentDevice, &max, &avail);
	maxmem = max;
	availmem = avail;

	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};


OSC_ERR OSC_SFManager::LoadPreset(int sourceBankno, int sourcePreset, 
		           int destBankno, int destPreset, 
				   const std::string &path)
{
	CSFMIDILocation midisource;
	CSFMIDILocation mididest;
	CSFBufferObject buf;
	char textbuf[1024];
	textbuf[1023] = 0;
	strncpy (textbuf, path.c_str(), 1023);
	midisource.m_BankIndex = sourceBankno;
	midisource.m_PresetIndex = sourcePreset;
	mididest.m_BankIndex = destBankno;
	mididest.m_PresetIndex = destPreset;
	buf.m_Flag = SFFLAG_OPER_FILE;
	buf.m_Buffer = textbuf;
	buf.m_Size = strlen(textbuf) + 1;
	m_lastSFMError = m_SFMan->SF_LoadPreset(m_currentDevice, &midisource, &mididest, &buf);
	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
};

OSC_ERR OSC_SFManager::ClearLoadedPreset(int bankno, int preset)
{
	CSFMIDILocation midi;
	midi.m_BankIndex = bankno;
	midi.m_PresetIndex = preset;
	m_lastSFMError = m_SFMan->SF_ClearLoadedPreset(m_currentDevice, &midi);
	if (m_lastSFMError != OSC_ERR_OK)
		return OSC_ERR_FAIL;
	return OSC_ERR_OK;
};

OSC_ERR OSC_SFManager::LoadWaveform(int destBankno,   int destPreset, 
					 const std::string &path)
{
	CSFMIDILocation mididest;
	CSFBufferObject buf;
	char textbuf[1024];
	textbuf[1023] = 0;
	strncpy (textbuf, path.c_str(), 1023);
	mididest.m_BankIndex = destBankno;
	mididest.m_PresetIndex = destPreset;
	buf.m_Flag = SFFLAG_OPER_FILE;
	buf.m_Buffer = textbuf;
	buf.m_Size = strlen(textbuf) + 1;
	m_lastSFMError = m_SFMan->SF_LoadWaveform(m_currentDevice, &mididest, &buf);
	if (m_lastSFMError == SFERR_NOERR)
		return OSC_ERR_OK;
	else
		return OSC_ERR_FAIL;
}; 

OSC_ERR OSC_SFManager::ClearLoadedWaveform(int bankno, int preset)
{
	CSFMIDILocation midi;
	midi.m_BankIndex = bankno;
	midi.m_PresetIndex = preset;
	m_lastSFMError = m_SFMan->SF_ClearLoadedWaveform(m_currentDevice, &midi);
	if (m_lastSFMError != OSC_ERR_OK)
		return OSC_ERR_FAIL;
	return OSC_ERR_OK;
}; 

OSC_ERR OSC_SFManager::GetAllSynthEmulations(OSC_StringArray &list)
{
	CSFBufferObject buf;
	char textbuf[2048];
	textbuf[2047] = 0;
	buf.m_Buffer = textbuf;
	buf.m_Size = 2047;

	m_lastSFMError = m_SFMan->SF_GetAllSynthEmulations(m_currentDevice, &buf);

	if (m_lastSFMError == SFERR_NOERR)
	{
		list.clear();
		std::string current("");
		char char2str[2];
		char2str[1]=0;
		for (int i=0; i<buf.m_SizeUsed-1; i++)
		{
			if (buf.m_Buffer[i]!=0)
			{
				char2str[0]=buf.m_Buffer[i];
				current+=std::string(char2str);
			}
			else
			{
				list.push_back(current);
				current = std::string("");
			};
		};
		return OSC_ERR_OK;
	}
	else
		return OSC_ERR_FAIL;
	return OSC_ERR_FAIL; 
};

OSC_ERR OSC_SFManager::GetSynthEmulation(int &index, std::string &name)
{
	CSFBufferObject buf;
	char textbuf[1024];
	textbuf[1023] = 0;
	buf.m_Buffer = textbuf;
	buf.m_Size = 1023;

	m_lastSFMError = m_SFMan->SF_GetSynthEmulation(m_currentDevice, &buf);

	if (m_lastSFMError == SFERR_NOERR)
	{
		index = buf.m_Flag;
		name = std::string(buf.m_Buffer);
		return OSC_ERR_OK;
	}
	else
		return OSC_ERR_FAIL;
};

OSC_ERR OSC_SFManager::SelectSynthEmulation(int index)
{
	m_lastSFMError = m_SFMan->SF_SelectSynthEmulation(m_currentDevice, index);
	if (m_lastSFMError != OSC_ERR_OK)
		return OSC_ERR_FAIL;
	return OSC_ERR_OK;
};

int OSC_SFManager::GetNumSynthEmulations()
{
	OSC_StringArray list;
	OSC_ERR err = GetAllSynthEmulations(list);
	if (err!=OSC_ERR_OK)
		return 0;
	return list.size();
};

OSC_ERR OSC_SFManager::GetSynthEmulationDescription(int index, std::string &name)
{
	OSC_StringArray list;
	OSC_ERR err = GetAllSynthEmulations(list);
	if (err!=OSC_ERR_OK)
		return err;
	if ((index<0) || (index>=list.size()))
		return OSC_ERR_FAIL; // wrong index
	name = list[index];
	return OSC_ERR_OK;
};
