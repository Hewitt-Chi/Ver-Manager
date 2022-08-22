// VersionInfoControl.cpp : implementation file
//

#include "stdafx.h"
#include <YCMFCEx/YCIniFile.h>
#include <YCMFCEx/YCObject.h>
#include <YCMFCEx/YCComponent.h>

#include "..\DeveloperSystem\DeveloperPublic\DeveloperPublicDefine.h"
#include "VersionInfoControl.h"


// VersionInfoControl
IMPLEMENT_DYNAMIC(VersionInfoControl, CYCComponent)
VersionInfoControl::VersionInfoControl()
{
}

VersionInfoControl::~VersionInfoControl()
{
}

bool VersionInfoControl::LoadConfigSettingFile()
{
	return true;
}
bool VersionInfoControl::SaveConfigSettingFile()
{
	return true;
}

bool VersionInfoControl::LoadSWFileNameFromFile(CYCIniFile * AFile)
{
	return true;
}
bool VersionInfoControl::SaveConfigCustomerToFile(CYCIniFile *AFile)
{
	int CustomerCount;
	if (AFile->IsOpened())
	{
		CustomerCount = m_CustomerName.size();
		//AFile.SetSectionName(Config_Section_Customer);
		YCIniSecWriteInt(AFile, Config_Section_Customer, CustomerCount);

		for (int I = 0; I < CustomerCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
#define WriteDefField( __Func)                                 \
	CustomerFormat.Format("CustomerName[%d]", I);    \
    AFile->__Func(Config_Section_Customer,CustomerFormat, CustomerName)
			//YCIniSecWriteStr(AFile, Config_Section_Customer, CustomerName);

			CustomerName = m_CustomerName[I];
			WriteDefField(WriteString);
		}


	}



	
	return true;
}
// VersionInfoControl member functions
