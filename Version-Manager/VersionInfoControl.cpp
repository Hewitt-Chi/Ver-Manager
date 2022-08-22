// VersionInfoControl.cpp : implementation file
//

#include "stdafx.h"

#include "..\DeveloperSystem\DeveloperPublic\DeveloperPublicDefine.h"
#include "VersionInfoControl.h"


// VersionInfoControl
IMPLEMENT_DYNAMIC(VersionInfoControl, CYCComponent)
VersionInfoControl::VersionInfoControl()
{
	m_CustomerName.clear();
	m_DeveloperLevel.clear();
	m_DeveloperName.clear();
	m_DeveloperType.clear();
	m_ModeType.clear();
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

bool VersionInfoControl::LoadSWFileNameFromFile()
{
	CString LFilePath = FILENAME_dlgModuleConfig;
	int KeyCount;
	CYCMemIniFile LFile;
	//nspTrack::TrackFileNameOf(FID_SWConfig);
	LFile.Open(LFilePath);
	if (LFile.IsOpened())
	{
		//Costomer Name
		KeyCount = LFile.ReadInt(Config_Section_Customer, Config_Key_CustomerName, 0,true);
		m_CustomerName.resize(KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Customer Name[%d]", I);

			CustomerName = LFile.ReadString(Config_Section_Customer, CustomerFormat, 0, true);
			
			m_CustomerName[I] = CustomerName;
		}
		//Mode Type
		KeyCount = LFile.ReadInt(Config_Section_Customer, Config_Key_ModeType, 0, true);
		m_ModeType.resize(KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Mode Type[%d]", I);

			CustomerName = LFile.ReadString(Config_Section_Customer, CustomerFormat, 0, true);

				m_ModeType[I] = CustomerName;
		}

		//Developer Name
		KeyCount = LFile.ReadInt(Config_Section_Developer, Config_Key_DeveloperName, 0, true);
		m_DeveloperName.resize(KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Developer Name[%d]", I);

			CustomerName = LFile.ReadString(Config_Section_Developer, CustomerFormat, 0, true);
			
			m_DeveloperName[I] = CustomerName;
		}

		//Developer Level
		KeyCount = LFile.ReadInt(Config_Section_Developer, Config_Key_DeveloperLevel, 0, true);
		m_DeveloperLevel.resize(KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Developer Level[%d]", I);

			CustomerName = LFile.ReadString(Config_Section_Developer, CustomerFormat, 0, true);
			
				m_DeveloperLevel[I] = CustomerName;
		}

		//Developer Type
		KeyCount = LFile.ReadInt(Config_Section_Developer, Config_Key_DeveloperType, 0, true);
		m_DeveloperType.resize(KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Developer Type[%d]", I);

			CustomerName = LFile.ReadString(Config_Section_Developer, CustomerFormat, 0, true);
	
			m_DeveloperType[I] = CustomerName;
		}
		return true;
	}
}
bool VersionInfoControl::SaveConfigCustomerToFile()
{
	CString LFilePath = FILENAME_dlgModuleConfig;
	int KeyCount;
	CYCMemIniFile LFile;
	//nspTrack::TrackFileNameOf(FID_SWConfig);
	LFile.Open(LFilePath);
	if (LFile.IsOpened())
	{
		KeyCount = m_CustomerName.size();
		//LFile->SetSectionName(Config_Section_Customer);
		//YCIniSecWriteInt(LFile, Config_Section_Customer, CustomerCount);
		LFile.WriteInt(Config_Section_Customer, Config_Key_CustomerName, KeyCount);
 		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Customer Name[%d]", I);
			CustomerName = m_CustomerName[I];
			LFile.WriteString(Config_Section_Customer, CustomerFormat, CustomerName);

		}
		KeyCount = m_ModeType.size();
		LFile.WriteInt(Config_Section_Customer, Config_Key_ModeType, KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Mode Type[%d]", I);
			CustomerName = m_ModeType[I];
			LFile.WriteString(Config_Section_Customer, CustomerFormat, CustomerName);

		}

		KeyCount = m_DeveloperName.size();
		LFile.WriteInt(Config_Section_Developer, Config_Key_DeveloperName, KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Developer Name[%d]", I);
			CustomerName = m_DeveloperName[I];
			LFile.WriteString(Config_Section_Developer, CustomerFormat, CustomerName);

		}

		KeyCount = m_DeveloperLevel.size();
		LFile.WriteInt(Config_Section_Developer, Config_Key_DeveloperLevel, KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Developer Level[%d]", I);
			CustomerName = m_DeveloperLevel[I];
			LFile.WriteString(Config_Section_Developer, CustomerFormat, CustomerName);

		}

		KeyCount = m_DeveloperType.size();
		LFile.WriteInt(Config_Section_Developer, Config_Key_DeveloperType, KeyCount);
		for (int I = 0; I < KeyCount; I++)
		{

			CString CustomerFormat;
			CString CustomerName;
			//#define WriteDefField( __Func)                                 
			CustomerFormat.Format("Developer Type[%d]", I);
			CustomerName = m_DeveloperType[I];
			LFile.WriteString(Config_Section_Developer, CustomerFormat, CustomerName);

		}

	}
 

	LFile.Close();

	return true;
}


void VersionInfoControl::GetCustomerNames(std::deque<CString> &AData)
{
	AData.clear();
	std::deque<CString>::iterator LIter;
	for (LIter = m_CustomerName.begin(); LIter != m_CustomerName.end(); LIter++)
	{
		if (LIter->GetBuffer() != "")
			AData.push_back(*LIter);
	}
}
void VersionInfoControl::GetModeTypes(std::deque<CString> &AData)
{
	AData.clear();
	std::deque<CString>::iterator LIter;
	for (LIter = m_ModeType.begin(); LIter != m_ModeType.end(); LIter++)
	{
		if (LIter->GetBuffer() != "")
			AData.push_back(*LIter);
	}
}
void VersionInfoControl::GetDeveloperNames(std::deque<CString> &AData)
{
	AData.clear();
	std::deque<CString>::iterator LIter;
	for (LIter = m_DeveloperName.begin(); LIter != m_DeveloperName.end(); LIter++)
	{
		if (LIter->GetBuffer() != "")
			AData.push_back(*LIter);
	}
}
void VersionInfoControl::GetDeveloperLevels(std::deque<CString> &AData)
{
	AData.clear();
	std::deque<CString>::iterator LIter;
	for (LIter = m_DeveloperLevel.begin(); LIter != m_DeveloperLevel.end(); LIter++)
	{
		if (LIter->GetBuffer() != "" )
			AData.push_back(*LIter);
	}
}
void VersionInfoControl::GetDeveloperTypes(std::deque<CString> &AData)
{
	AData.clear();
	std::deque<CString>::iterator LIter;
	for (LIter = m_DeveloperType.begin(); LIter != m_DeveloperType.end(); LIter++)
	{
		if (LIter->GetBuffer() != "")
			AData.push_back(*LIter);
	}
}

// VersionInfoControl member functions
