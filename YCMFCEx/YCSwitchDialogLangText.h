#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif



class CYCSwitchDialogLangText : public CObject
{
    DECLARE_DYNAMIC(CYCSwitchDialogLangText)

public:
    CYCSwitchDialogLangText();
    virtual ~CYCSwitchDialogLangText();


    void        SetIniFileName(LPCSTR AFileName);
    void        InitDialogText(HWND AHwnd, bool AIsWMInitDialog = false);
    LRESULT     CallNextHookEx(int nCode, WPARAM wParam, LPARAM lParam);

private:
    HHOOK       m_Hook;

    CYCMemIniFile
        /**/    m_IniFile;


    static BOOL CALLBACK
        /**/    EnumChildProc(HWND hwndChild, LPARAM lParam);


    void        InitDialogTextFromOrgRes(CDialog *ADialog);
};
