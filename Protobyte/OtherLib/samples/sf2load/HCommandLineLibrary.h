/*
	This file is a part of the OSC Library (Open Sound Code). 
	Visit the OSC website at http://www.pvv.org/~thammer/HammerSound/osc/
	for the complete OSC library, the latest update, documentation,
	user forum, etc.

	Allthough the source code to the OSC Library is publicly available,
	use and distribution of the OSC Library is governed by a license agreement. 
	The License Agreement can be found at the OSC website.
*/

#ifndef HCOMMANDLINELIBRARY_H
#define HCOMMANDLINELIBRARY_H

#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
#pragma warning( disable : 4786 ) // Disable debug warnings for long id-names

#include <assert.h>
#include <stdlib.h>

/*

  A little note about using option prefix:
	You still have to include the prefix when specifying the template
	Syntax checking will be stricter

  */

class HCLL_Template
{
private:
	map<string, int> m_optionMap; // m_option[label]=numParams

	string m_optionPrefix;
	bool m_useOptionPrefix;

public:
	HCLL_Template()
	{
		m_useOptionPrefix=false;
	};
	HCLL_Template(const HCLL_Template &t)
	{
		operator=(t);
	}
	const HCLL_Template &operator=(const HCLL_Template &t)
	{
		m_optionMap=t.m_optionMap; // Hmmm...
		m_optionPrefix=t.m_optionPrefix;
		m_useOptionPrefix=t.m_useOptionPrefix;
		return *this;
	}

	void setOptionPrefix(string pre)
	{
		m_useOptionPrefix=true;
		m_optionPrefix=pre;
	};

	const string &getOptionPrefix()
	{
		return m_optionPrefix;
	};


	bool usingOptionPrefix()
	{
		return m_useOptionPrefix;
	}

	void addOption(const string &label, int numParams)
	{
		m_optionMap[label]=numParams;
	}

	bool optionExists(const string &label) const
	{
		return m_optionMap.find(label) != m_optionMap.end();
	}
	

	int operator[](const string &label)
	{
		if (optionExists(label))
			return m_optionMap[label];
		else
			return 0; 
			// ERROR (but it is not reported, it is the caller's
			// responsibility to check optionExists() first !
	}

};

class HCLL_VarType
{
private:
	string m_string;
public:
	HCLL_VarType()
	{
		setString("");
	}
	HCLL_VarType(const string &str)
	{
		setString(str);
	}
	bool operator<(const HCLL_VarType &vt) const
	{	
		return m_string<vt.getString();
	};
	bool operator==(const HCLL_VarType &vt) const
	{	
		return m_string==vt.getString();
	};

	void setString(const string &str)
	{
		m_string=str;
	}
	const string & getString()	const
	{
		return m_string;
	}
	long getInt() const
	{
		return atol(m_string.c_str());
	}
	double getFloat() const
	{
		return atof(m_string.c_str());
	}
};

typedef vector<HCLL_VarType> HCLL_Option;
typedef map<string, HCLL_Option> HCLL_OptionMap; // HCLL_OptionMap["label"] = HCLL_Option
typedef vector<HCLL_VarType> HCLL_VarTypeArray;

#define HCLL_RESULT_OK 0
#define HCLL_RESULT_ERROR_TOO_FEW_OPTION_PARAMS 1
#define HCLL_RESULT_ERROR_UNRECOGNIZED_OPTION 2

typedef int HCLL_Result;

class HCLL_CommandLine
{
private:
	HCLL_VarTypeArray m_progParam;
	HCLL_OptionMap m_optionMap;
	HCLL_Template m_template;
	string m_lastOptionParsed;

public:
	// må ha templaten først
	void setTemplate(const HCLL_Template &t)
	{
		m_template=t;
	}
	HCLL_Result parse(int argc, char* argv[]);
	const string &getLastOptionParsed() const
	{
		return m_lastOptionParsed;
	}
	void dump(); // for debugging
	int getNumProgParams() const
	{
		return m_progParam.size();
	};
	const HCLL_VarType &getProgParam(int i) const
	{
		assert( (i>=0) && (i<m_progParam.size()) ); // should do proper error checking
		return m_progParam[i]; 
	};
	int getNumOptions() const
	{
		return m_optionMap.size();
	};
	bool optionExists(const string &label) const
	{
		return m_optionMap.find(label) != m_optionMap.end();
	}
	int getNumOptionParams(const string &label) 
	{
//		const_cast<HCLL_OptionMap>(m_optionMap);
		return m_optionMap[label].size();
	};
	const HCLL_VarType &getOptionParam(const string &label, int i) 
	{
		assert( (i>=0) && (i<m_optionMap[label].size()) ); // should do proper error checking
		return (m_optionMap[label])[i]; 
	};


};

#endif
