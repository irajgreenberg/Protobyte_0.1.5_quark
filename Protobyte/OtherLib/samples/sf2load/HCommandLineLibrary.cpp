/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#include "HCommandLineLibrary.h"

HCLL_Result HCLL_CommandLine::parse(int argc, char* argv[])
{
	int a=0;
	while (a<argc)
	{
		if (m_template.optionExists(argv[a]))
		{	// arg is an option
			m_lastOptionParsed=string(argv[a]);
			HCLL_Option option;
			// loop through all option params
			int o=1;
			while ( (o<=m_template[argv[a]]) && (o+a<argc) )
			{
				if (m_template.usingOptionPrefix())
				{ // check that the arg does not have an option prefix
					string strarg;
					strarg=string(argv[a+o]);
					strarg.erase(m_template.getOptionPrefix().size(), strarg.size() - m_template.getOptionPrefix().size());
					if (strarg==m_template.getOptionPrefix())
					return HCLL_RESULT_ERROR_TOO_FEW_OPTION_PARAMS;
				};
				option.push_back(string(argv[a+o]));
				o++;
			}
			// if to few, return error
			if (o<=m_template[argv[a]])
				return HCLL_RESULT_ERROR_TOO_FEW_OPTION_PARAMS;
			m_optionMap[argv[a]]=option;
			a+=o;
		}
		else
		{	
			if (m_template.usingOptionPrefix())
			{ // check that the arg does not have an option prefix
				string strarg;
				strarg=string(argv[a]);
				strarg.erase(m_template.getOptionPrefix().size(), strarg.size() - m_template.getOptionPrefix().size());
				if (strarg==m_template.getOptionPrefix())
				{
					m_lastOptionParsed=string(argv[a]);
					return HCLL_RESULT_ERROR_UNRECOGNIZED_OPTION;
				};
			};
			// arg is a program parameter
			// add it to the progParam list
			m_progParam.push_back(string(argv[a++]));
		}
	};

	return HCLL_RESULT_OK; // OK
	
};

void HCLL_CommandLine::dump()
{
	cout<<"Program Parameters:";
	HCLL_VarTypeArray::iterator vti=m_progParam.begin();
	if (vti==m_progParam.end())
		cout<<" <none>";
	else
		while (vti!=m_progParam.end())
		{
			cout<<" "<<vti->getString();
			vti++;
		};
	cout<<"\n";

	cout<<"Options:\n";
	HCLL_OptionMap::iterator omi=m_optionMap.begin(); 
	if (omi==m_optionMap.end())
		cout<<"   <none>";
	else
		while(omi!=m_optionMap.end())
		{
			cout<<"   "<<omi->first<<" : ";
			vti=omi->second.begin();
			if (vti==omi->second.end())
				cout<<"<none>";
			else
				while (vti!=omi->second.end())
				{
					cout<<vti->getString()<<" ";
					vti++;
				}
			cout<<"\n";
			omi++;
		};
};
