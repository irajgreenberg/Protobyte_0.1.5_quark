/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/
 

/*
SF2LOAD 
  
			ThH		v1.0 16-bit, Borland C++ 4.5
19971022	ThH		v1.1 First VC++5.0 & Win32 version up and running
1998....	ThH		v1.2beta Now supports bat-file generation
19990117	ThH		v2.0beta First version using SFMan
19990423	ThH		v2.1 added support for listing preset names
19990522	ThH		v2.2 added support for loading presets and waveforms,
					     and listing & loading synth emulations
*/


#include "OSC_SFManager.h"
#include "HCommandLineLibrary.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#include <vector>
#include <string>
#include <iomanip>
#pragma warning( disable : 4786 ) // Disable debug warnings for long id-names

void main(int argc, char* argv[])
{
	bool verbose=false;
	WORD deviceno=0;
	int i;
	
	HCLL_Template clt;
	clt.setOptionPrefix("-");
	clt.addOption("-debug", 0);	// Debug
	clt.addOption("-h", 0);		// Help
	clt.addOption("-v", 0);		// Be verbose
	clt.addOption("-nt", 0);	// Do not print program title
	clt.addOption("-t", 0);	    // Print program title
	clt.addOption("-d", 1);		// Dump banks to batfile
	clt.addOption("-dist", 1);	// Dump banks to batfile (distribution), Use filename only, not full path
	clt.addOption("-distm", 1);	// Dump banks to batfile (distribution), Use filename only, not full path, adds mediaplayer
//	clt.addOption("-bank0", 0);	// Include bank 0 when creating batfile
	clt.addOption("-c", 1);		// Clear one bank
	clt.addOption("-C", 0);		// Clear all banks
//	clt.addOption("-CA", 0);	// Clear all banks, including bank 0 (Default MIDI bank)
	clt.addOption("-n", 1);		// Set device number (for multiple devices)
	clt.addOption("-i", 0);		// Print a lot of info
	clt.addOption("-l", 0);		// List active soundfont names
	clt.addOption("-L", 0);		// List active soundfont names, including path names
	clt.addOption("-fx", 3);	// Load effect <type> <variation> <value>
	clt.addOption("-ea", 0);	// List all Synthesizer emulations
	clt.addOption("-es", 1);	// Set Synthesizer emulation
	clt.addOption("-ec", 0);	// List current Synthesizer emulation
	clt.addOption("-p", 1);		// list preset names for <bank>
	clt.addOption("-wl", 3);	// Load <wavefile> into <preset> in <bank>
	clt.addOption("-wc", 2);	// Clear wavefile loaded in <preset> in <bank>
	clt.addOption("-pl", 5);	// Load <sourcepreset> from <sourcebank> in <soundfont> into <destpreset> in <destbank>
	clt.addOption("-pc", 2);	// Clear <preset> in <bank>
	
	HCLL_CommandLine cl;
	cl.setTemplate(clt);
	HCLL_Result cl_res;
	cl_res=cl.parse(argc, argv);
	if (cl_res!=HCLL_RESULT_OK)
	{
		cout<<"Parse error: ";

		switch (cl_res)
		{
		case HCLL_RESULT_ERROR_TOO_FEW_OPTION_PARAMS :
			cout<<"too few parameters to the '"<<cl.getLastOptionParsed()<<"' option\n";
			break;
		case HCLL_RESULT_ERROR_UNRECOGNIZED_OPTION:
			cout<<"unrecognized option '"<<cl.getLastOptionParsed()<<"'\n";;
			break;
		default:
			cout<<"unknown error\n";
			break;
		};
		printf("SF2LOAD v2.2 (c) 1998-1999 Thomas Hammer  thammer@pvv.org\n");
		printf("                 http://listen.to/HammerSound\n");
		printf("\n");
		cout<<"usage:  SF2LOAD  [<options>] [<bank number> <soundfont name>] \n\n";
		cout<<"        SF2LOAD -h for help\n";
		return;
	}

	if (!cl.optionExists("-nt"))
	{
		printf("SF2LOAD v2.2 (c) 1998-1999 Thomas Hammer  thammer@pvv.org\n");
		printf("                 http://listen.to/HammerSound\n");
		printf("\n");
	};

	if (cl.optionExists("-v"))
	{
		verbose=true;
		cout <<"Verbose mode on\n";
	}

	if (cl.optionExists("-debug"))
	{
		if (verbose)
			cout<<"debug mode on\n";
		cl.dump();
		cout<<"Path: '"<<argv[0]<<"'"<<endl;
	}

	if (   ((cl.getNumOptions()==0) && (cl.getNumProgParams()==1))
		|| ((cl.getNumProgParams()==2) || (cl.getNumProgParams()>3))
		)
	{
		cout<<"usage:  SF2LOAD  [<option>] [<bank number> <soundfont name>] \n";
		cout<<"        SF2LOAD -h for help\n";
		return;
	}

	if (cl.optionExists("-h")) 
	{
		cout<<"usage:  SF2LOAD  [<option>] [<bank number> <soundfont filename>] \n\n";
		cout<<"-h                Help"<<endl;
		cout<<"-d <filename>     Create a bat-file for loading all soundfonts currently"<<endl;
		cout<<"                  in memory. Use full pathnames."<<endl;
		cout<<"-dist <filename>  Create a bat-file for loading all soundfonts currently"<<endl;
		cout<<"                  in memory. Use filenames only (suitable for distribution)"<<endl;
		cout<<"-distm <filename> Create a bat-file (filename.bat) for loading all soundfonts"<<endl;
		cout<<"                  in memory. Use filenames only and include a line to"<<endl;
		cout<<"                  play the MIDI file (filename.mid) using mediaplayer"<<endl;
//		cout<<"-bank0            Include bank 0 (Default MIDI bank) when creating bat-files"<<endl;
		cout<<"-c <bank>         Clear the specified soundbank (remove it from memory)"<<endl;
		cout<<"-C                Clear all soundbanks currently in memory"<<endl;
//		cout<<"-CA               Clear all soundbanks currently in memory (incl. bank 0)"<<endl;
		cout<<"-n <device>       Set SoundFont device number (for users with multiple devices)"<<endl;
		cout<<"-l                List all soundfonts currently in memory"<<endl;
		cout<<"-L                List all soundfonts currently in memory (with filenames)"<<endl;
		cout<<"-p <bankno>       List all (melodic) presets in bank"<<endl;
		cout<<"-wl <wavefile> <bank> <preset>"<<endl;
		cout<<"                  Load a wavefile (*.wav) into a preset in a bank."<<endl;
		cout<<"-wc <bank> <preset> Clear a waveform previously loaded into a preset in a bank"<<endl;
		cout<<"-pl <soundfont> <sourcebank> <sourcepreset> <destbank> <destpreset>"<<endl;
		cout<<"                  Load a preset from a soundfont into a preset in a bank"<<endl;
		cout<<"-pc <bank> <preset> Clear a preset in a bank"<<endl;
		cout<<"-ea               List all synthesizer emulations"<<endl;
		cout<<"-es <no>          Set synthesizer emulation"<<endl;
		cout<<"-ec               List current synthesizer emulation"<<endl;
		cout<<"-i                Print information about the SoundFont device"<<endl;
		cout<<"-v                Enable verbose mode"<<endl;
		cout<<"-nt               Do not print the program title"<<endl;
		cout<<"-t                Print the program title"<<endl;
		return;
	}


	if (cl.optionExists("-n"))
	{
		deviceno=cl.getOptionParam("-n",0).getInt();
		if (verbose)
			cout<<"deviceno set to "<<deviceno<<endl;
	}

	// Open the SoundFont Manager

	OSC_SFManager sfm;
	OSC_ERR res;

	res = sfm.Init();
	if (res!=OSC_ERR_OK)
	{
		cout<<"Error initializing the SoundFont Manager : "<<sfm.GetLastSFManErrorText()<<endl;
		cout<<"Make sure you have installed the SoundFont Manager, and that you use the latest drivers"<<endl;
		cout<<"for your SoundFont device"<<endl;
		return;
	}
	else
		if (verbose)
			cout<<"SoundFont Manager Initialized OK"<<endl;

	res = sfm.Open(deviceno);
	if (res!=OSC_ERR_OK)
	{
		cout<<"Error trying to open SoundFont device number "<<deviceno
			<<". "<<sfm.GetLastSFManErrorText()<<endl;
		return;
	};

//// -c
	if (cl.optionExists("-c"))
	{
		long bankno = cl.getOptionParam("-c",0).getInt();
		if (verbose)
			cout<<"Clearing SoundBank "<<bankno<<endl;
		if ( (bankno<0) || (bankno>127) )
		{
			cout<<"Error: Bank number out of range. The banknumber specified is "<<bankno<<", it should be in the range [0..127]\n";
		}
		else 
		{
			if (sfm.IsMIDIBankUsed(bankno)==-1)
				cout<<"Error: Bank number "<<bankno<<" is not in use and can not be cleared"<<endl;
			else if (sfm.IsMIDIBankUsed(bankno) != bankno)
				cout<<"Error: Bank number "<<bankno<<" is owned by bank "<<sfm.IsMIDIBankUsed(bankno)
				<<" and can not be cleared"<<endl;
			else
			{
				if ( (res=sfm.ClearLoadedBank(bankno)) != OSC_ERR_OK)
					cout<<"Error: Couldn't clear bank number "<<bankno<<". "<<sfm.GetLastSFManErrorText()<<endl;
				else
					if (verbose)
						cout<<"Bank number "<<bankno<<" has been cleared successfully\n";
			};
		};
	};

//// -es
	if (cl.optionExists("-es"))
	{
		// This function will set the current synthesizer emulation, but this 
		// only lasts until the device is closed (at the end of sf2load)
		// so it's really not much point in using it... :-(
		if (verbose)
			cout<<"Setting current Synthesizer Emulation..."<<endl;
		int index = cl.getOptionParam("-es",0).getInt();
		if ( (res=sfm.SelectSynthEmulation(index)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't set Synthesizer Emulation. "<<sfm.GetLastSFManErrorText()<<endl;
		else
			if (verbose)
				cout<<"Current Synthesizer Emulation has been set to "<<index<<endl;
	}

//// -ea
	if (cl.optionExists("-ea"))
	{
		if (verbose)
			cout<<"Listing all Synthesizer Emulations..."<<endl;
		OSC_StringArray list;
		if ( (res=sfm.GetAllSynthEmulations(list)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't list Synthesizer Emulations. "<<sfm.GetLastSFManErrorText()<<endl;
		else
		{
			int n=0;
			for (OSC_StringArray::iterator i = list.begin(); i!=list.end(); i++)
			{
				cout<<n++<<" "<<*i<<endl;
			}
		};
	}

//// -ec
	if (cl.optionExists("-ec"))
	{
		if (verbose)
			cout<<"Listing current Synthesizer Emulation..."<<endl;
		std::string name;
		int index;
		if ( (res=sfm.GetSynthEmulation(index, name)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't list Synthesizer Emulation. "<<sfm.GetLastSFManErrorText()<<endl;
		else
		{
			cout<<index<<" "<<name<<endl;
		};
	}

//// -wl
	if (cl.optionExists("-wl"))
	{
		std::string filename = cl.getOptionParam("-wl",0).getString();
		int bank = cl.getOptionParam("-wl",1).getInt();
		int preset = cl.getOptionParam("-wl",2).getInt();
		if (verbose)
			cout<<"Loading waveform '"<<filename<<"' into bank "<<bank<<", preset "<<preset<<endl;

		if ( (res=sfm.LoadWaveform(bank, preset, filename)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't load waveform. "<<sfm.GetLastSFManErrorText()<<endl;
	}

//// -wc
	if (cl.optionExists("-wc"))
	{
		int bank = cl.getOptionParam("-wc",0).getInt();
		int preset = cl.getOptionParam("-wc",1).getInt();
		if (verbose)
			cout<<"Clearing waveform from bank "<<bank<<", preset "<<preset<<endl;

		if ( (res=sfm.ClearLoadedWaveform(bank, preset)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't clear waveform. "<<sfm.GetLastSFManErrorText()<<endl;
	}

//// -pl
	if (cl.optionExists("-pl"))
	{
		std::string filename = cl.getOptionParam("-pl",0).getString();
		int sourcebank = cl.getOptionParam("-pl",1).getInt();
		int sourcepreset = cl.getOptionParam("-pl",2).getInt();
		int destbank = cl.getOptionParam("-pl",3).getInt();
		int destpreset = cl.getOptionParam("-pl",4).getInt();
		if (verbose)
			cout<<"Loading from soundfont '"<<filename<<"', bank "<<sourcebank<<", preset "<<sourcepreset
				<<", into bank "<<destbank<<", preset "<<destpreset<<endl;

		if ( (res=sfm.LoadPreset(sourcebank, sourcepreset, destbank, destpreset, filename)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't load preset. "<<sfm.GetLastSFManErrorText()<<endl;
	}

//// -pc
	if (cl.optionExists("-pc"))
	{
		int bank = cl.getOptionParam("-pc",0).getInt();
		int preset = cl.getOptionParam("-pc",1).getInt();
		if (verbose)
			cout<<"Clearing preset from bank "<<bank<<", preset "<<preset<<endl;

		if ( (res=sfm.ClearLoadedPreset(bank, preset)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't clear preset. "<<sfm.GetLastSFManErrorText()<<endl;
	}

//// -C
	if (cl.optionExists("-C"))
	{
		if (verbose)
			cout<<"Clearing all SoundBanks...";
		if ( (res=sfm.ClearAllLoadedBanks()) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't clear banks. "<<sfm.GetLastSFManErrorText()<<endl;
		else
			if (verbose)
				cout<<"All Soundbanks have been cleared successfully\n";
	}

/*
//// -CA
	if (cl.optionExists("-CA"))
	{
		if (verbose)
			cout<<"Clearing all SoundBanks (including bank 0)...";
		if ( (res=sfm.ClearAllLoadedBanks(true)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't clear banks. "<<sfm.GetLastSFManErrorText()<<endl;
		else
			if (verbose)
				cout<<"All Soundbanks have been cleared successfully\n";
	}
*/

//// -l | -L
	if (cl.optionExists("-l") || cl.optionExists("-L"))
	{
		if (verbose)
			cout<<"Listing SoundBanks\n";
		string name;
		string filename;

		for (i=0; i<128; i++)
		{
			if (sfm.IsMIDIBankUsed(i)==i)
			{
				if ( (res=sfm.GetLoadedBankDescriptor(i, name)) != OSC_ERR_OK)
					break;
				else
				{
					cout<<"[";
					if (i<100)
						cout<<" ";
					if (i<10)
						cout<<" ";
					cout<<i<<"] "<<name;
					if (cl.optionExists("-L"))
					{
						if ( (sfm.GetLoadedBankPathname(i, filename)) != OSC_ERR_OK)
							;
						else
							cout<<" ("<<filename<<")";
					}
					cout<<endl;
				};
			}
		};
		if (res!=OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't get bank name (bank "<<i<<"). "<<sfm.GetLastSFManErrorText()<<endl;
	};

//// -i
	if (cl.optionExists("-i"))
	{
		int numdevices = sfm.GetNumDevs();
		if (numdevices==0)
			cout<<"There are no SoundFont devices installed on this computer\n";
		else if (numdevices==1)
			cout<<"There is 1 SoundFont device installed on this computer\n";
		else
			cout<<"There are "<<numdevices<<" SoundFont devices installed on this computer\n";

		CSFCapsObject caps;
		int olddev;
		bool wasOpen = sfm.IsDeviceOpen();
		if (wasOpen)
		{
			olddev = sfm.GetCurrentOpenDevice();
			sfm.Close();
		}

		for (i=0; i<sfm.GetNumDevs(); i++)
		{
			cout<<"   ["<<i<<"] ";
			if (sfm.IsDeviceFree(i))
				cout<<"(free) ";
			else
				cout<<"(busy) ";
			if ( (res=sfm.Open(i)) != OSC_ERR_OK)
			{
				cout<<endl<<"Error: Couldn't open device "<<i<<". "<<sfm.GetLastSFManErrorText()<<endl;
				break;
			}
			if ( (res=sfm.GetDevCaps(&caps)) != OSC_ERR_OK)
			{
				cout<<endl<<"Error: Couldn't get device capabilities. "<<sfm.GetLastSFManErrorText()<<endl;
				break;
			};
			cout <<caps.m_DevName<<endl;
			sfm.Close();
		};

		if (wasOpen)
			if ( (res=sfm.Open(olddev)) != OSC_ERR_OK)
			{
				cout<<endl<<"Error: Couldn't open device "<<i<<". "<<sfm.GetLastSFManErrorText()<<endl;
			}

		if ( (res=sfm.GetDevCaps(&caps)) != OSC_ERR_OK)
			cout<<endl<<"Error: Couldn't get device capabilities. "<<sfm.GetLastSFManErrorText()<<endl;
		else
		{
			cout<<"The following information is for device "<<deviceno<<endl;
			cout<<"   Device name: "<<caps.m_DevName<<"    "
				<<"Device Manager: "<<caps.m_DevMgrName<<" ("<<caps.m_DevMgrEntry<<")"<<endl;

			if (caps.m_DevCaps & SFMANCAP_DYNAMIC_MEM_CAP)
				cout<<"   The device uses System Ram to store samples. ";
			else
				cout<<"   The device uses Dedicated Ram to store samples. ";

			int max, avail;
			sfm.QueryStaticSampleMemorySize(max, avail);
			cout<<std::setiosflags(ios::fixed)<<std::setprecision(1)
				<<"Available: "<<(double)avail/(1024.0*1024.0)<<"MB, "
				<<"Max: "<<(double)max/(1024.0*1024.0)<<"MB"<<endl;

			if (caps.m_DevCaps & SFMANCAP_SOFTWARE_SYNTH_CAP)
				cout<<"   The device has a Software Synth engine"<<endl;
			else
				cout<<"   The device has a Hardware Synth engine"<<endl;

			// rom id, rom version
			// synth emulations
		};
	};


//// -d, -dist, -distm
	// Create bat-file
	if (cl.optionExists("-d") || cl.optionExists("-dist") || cl.optionExists("-distm"))
	{	
		if (verbose)
			cout<<"Bat file creation\n";
		
		FILE *file;
		string batfilename;
		string midifilename;
		if (cl.optionExists("-d"))
			batfilename=cl.getOptionParam("-d",0).getString();
		else if (cl.optionExists("-dist"))
			batfilename=cl.getOptionParam("-dist",0).getString();
		else
			batfilename=cl.getOptionParam("-distm",0).getString();
		midifilename=batfilename;

		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char tmp[_MAX_PATH];
		_splitpath(batfilename.c_str(), drive, dir, fname, ext);
		_makepath(tmp, drive, dir, fname, ".bat");
		batfilename=string(tmp);
		_makepath(tmp, drive, dir, fname, ".mid");
		midifilename=string(tmp);


		file=fopen(batfilename.c_str(), "wt");
		if (file==NULL)
		{
			cout<<"Error: Couldn't open file '"<<batfilename.c_str()<<"' for writing";
		}
		else
		{
		
			if (verbose)
			{
				printf("Creating SF2LOAD compatible .bat file (%s) with the folowing soundfonts :\n", batfilename.c_str());
			};

			time_t ltime;
			_tzset();
			char timestr[128];
			time( &ltime );
			sprintf(timestr,"%s", ctime( &ltime ));
			timestr[24]=0;
	//		timestr[23]=0;
	//		if (strlen(timestr)>2)
	//			timestr[strlen(timestr)-3];

			fprintf(file,"@ECHO OFF\n");
			fprintf(file, "REM This bat file was created at %s by SF2LOAD v2.2\n", timestr);
			fprintf(file, "REM      SF2LOAD is (c) 1998-1999 Thomas Hammer  thammer@pvv.org\n");
			fprintf(file, "REM                 http://listen.to/HammerSound\n");
			fprintf(file,"\n");
			fprintf(file, "sf2load -t\n");
			fprintf(file,"\n");
			fprintf(file,"ECHO Clearing all User Banks\n");
			if (cl.optionExists("-bank0"))
				fprintf(file, "sf2load -nt -CA\n");
			else
				fprintf(file, "sf2load -nt -C\n");
			fprintf(file,"\n");
			fprintf(file,"ECHO \xff\n");

			// Load soundfonts
			fprintf(file,"ECHO Loading SoundFonts\n");

			string filename;
			int start;
//			start = cl.optionExists("-bank0") ? 0 : 1;
			start = 1;
			for (i=start; i<=127; i++)
			{
				if (sfm.IsMIDIBankUsed(i)==i)
				{
					if ( (res=sfm.GetLoadedBankPathname(i, filename)) != OSC_ERR_OK)
						break;

					if (cl.optionExists("-dist") || cl.optionExists("-distm")) // use filename only
					{
					   char fname[_MAX_FNAME];
					   char ext[_MAX_EXT];
					   _splitpath(filename.c_str(), NULL, NULL, fname, ext);
					   filename=string(fname)+string(ext);
					}
					fprintf(file, "sf2load -nt %3d \"%s\"\n", i, filename.c_str());
				}
				if (verbose)
					cout<<i<<"  "<<filename<<endl;
			};

			if (res==OSC_ERR_OK)
			{
				fprintf(file,"ECHO \xff\n");
				cout<<"Created-bat file '"<<batfilename<<"'"<<endl;

				if (cl.optionExists("-distm")) 
				{
		//			string midifilename=cl.getOptionParam("-distm",1).getString();
					fprintf(file,"ECHO Starting MediaPlayer for playing MIDI file %s\n", midifilename.c_str());
					fprintf(file,"start mplayer.exe %s\n", midifilename.c_str());
					fprintf(file,"ECHO \xff\n");
				};
			}

			fclose(file);
			
			if (res!=OSC_ERR_OK)
			{
				cout<<"Error creating .bat file. "<<sfm.GetLastSFManErrorText()<<endl;
			}
		};
	}

	if (cl.optionExists("-p"))
	{
		// print all preset names for <bank>
		int bank = cl.getOptionParam("-p",0).getInt();
		if (sfm.IsMIDIBankUsed(bank)!=bank)
			cout<<"<empty bank>"<<endl;
		else
		{
			std::string bankname;
			sfm.GetLoadedBankDescriptor(bank, bankname);
	//		cout<<"Melodic Presets for SoundFont: [";
			cout<<bankname<<endl<<endl;

			std::string presetname;
			for (int i=0; i<128; i++)
			{
				sfm.GetLoadedPresetDescriptor(bank, i, presetname);
				if (!presetname.empty())
				{
					cout<<"[";
					if (i<100)
						cout<<" ";
					if (i<10)
						cout<<" ";
					cout<<i<<"] "<<presetname<<endl;
				};
			}
		};
	}

	if (cl.getNumProgParams()==3)
	{
		if (verbose)
			cout<<"Loading SoundFont\n";
		//  we're supposed to load a bank

		// append .sf2 if needed
	   char fname[_MAX_FNAME];
	   char ext[_MAX_EXT];
	   string path=cl.getProgParam(2).getString();
	   _splitpath(path.c_str(), NULL, NULL, fname, ext);
	   if (ext[0]==0)
		   path+=string(".sf2");

		// make full path
		char fullpath[_MAX_PATH];
		if ( _fullpath( fullpath, path.c_str(), _MAX_PATH ) == NULL )
			cout<<"Error: Invalid SoundFont filename '"<<cl.getProgParam(2).getString()<<"'"<<endl;

		// load soundfont
		if ( (res=sfm.LoadBank(cl.getProgParam(1).getInt(), fullpath)) != OSC_ERR_OK)
				cout<<"Error: Couldn't load bank "<<cl.getProgParam(1).getInt()<<". "<<sfm.GetLastSFManErrorText()<<endl;
		else
			printf("[%3d]  %s\n", cl.getProgParam(1).getInt(), fullpath);

	};

	// Close the SoundFont Manager

	if ( (res=sfm.Close()) != OSC_ERR_OK)
		cout<<endl<<"Error: Couldn't close device. "<<sfm.GetLastSFManErrorText()<<endl;
	else
		if (verbose)
			cout<<"Device closed\n";
};
