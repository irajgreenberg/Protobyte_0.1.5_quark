#!/bin/bash
# Create new Protobyte project with new name - **for Dev work only**
# This should eventualy be converted to C++ prog using Boost FileSystem
# for cross-platform compatibility.

cp  -r ../ProtoTemplate/__Protobyte_Project_Template__ ../Projects
cd ../Projects

projName=$1

if [ -z "$projName" ]
  then
  	#http://stackoverflow.com/questions/1401482/yyyy-mm-dd-format-date-in-shell-script
  	DATE=`date +%Y%m%d%H%M%S`
    projName="sketch_"$DATE
fi

mv __Protobyte_Project_Template__ $projName
cd $projName
mv *.vcxproj $projName.vcxproj
mv *.vcxproj.filters $projName.vcxproj.filters
echo "\"Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio 2013
VisualStudioVersion = 12.0.21005.1
MinimumVisualStudioVersion = 10.0.40219.1
Project("\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\"") = "\"$projName\"", "\"$projName.vcxproj\"", "\"{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}\""
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|Win32 = Debug|Win32
		Release|Win32 = Release|Win32
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}.Debug|Win32.ActiveCfg = Debug|Win32
		{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}.Debug|Win32.Build.0 = Debug|Win32
		{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}.Release|Win32.ActiveCfg = Release|Win32
		{4DF3E3D9-2197-48F1-80E4-3F0E3E408694}.Release|Win32.Build.0 = Release|Win32
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
EndGlobal\"" > $projName.sln
ls -a
