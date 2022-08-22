#pragma once


#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


// VersionInfoControl command target

class VersionInfoControl : public CYCComponent
{
	DECLARE_DYNAMIC(VersionInfoControl)
public:
	VersionInfoControl();
	virtual ~VersionInfoControl();
	bool LoadConfigSettingFile();
	bool SaveConfigSettingFile();

	bool SaveConfigCustomerToFile(CYCMemIniFile *AFile);
private:
	std::deque<CString > m_CustomerName;
	std::deque<CString > m_ModeType;
	std::deque<CString > m_DeveloperName;
	std::deque<CString > m_DeveloperLevel;
	std::deque<CString> m_DeveloperType;

	bool LoadSWFileNameFromFile(CYCMemIniFile *AFile);

};


