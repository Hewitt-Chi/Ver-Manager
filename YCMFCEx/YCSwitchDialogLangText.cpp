#include "StdAfx.h"

#include "YCUtils.h"
#include "YCIniFile.h"
#include "YCSwitchDialogLangText.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


using namespace ATL;

namespace nspYCSwitchDialogLangText
{
    static CYCSwitchDialogLangText *Switch = NULL;


    LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        if (nCode == HC_ACTION)
        {
            PCWPSTRUCT LCwp = ((PCWPSTRUCT)lParam);

            if (LCwp->message == WM_INITDIALOG)
            {
                if (Switch)
                {
                    Switch->InitDialogText(LCwp->hwnd, true);
                }
                else
                {
                    ASSERT(FALSE);
                }
            }
        }
        else if (nCode < 0)
        {
        }

        if (Switch)
            return Switch->CallNextHookEx(nCode, wParam, lParam);

        return 0;
    }

}



BOOL CALLBACK CYCSwitchDialogLangText::EnumChildProc(HWND hwndChild, LPARAM lParam) 
{
    std::vector<HWND>   *LChildHwnds = (std::vector<HWND>*)lParam;

    LChildHwnds->push_back(hwndChild);
    return TRUE;
}

IMPLEMENT_DYNAMIC(CYCSwitchDialogLangText, CObject)


CYCSwitchDialogLangText::CYCSwitchDialogLangText() : CObject()
{
    ASSERT(!nspYCSwitchDialogLangText::Switch);

    nspYCSwitchDialogLangText::Switch = this;
    m_Hook = SetWindowsHookEx(WH_CALLWNDPROC, nspYCSwitchDialogLangText::CallWndProc, NULL, GetCurrentThreadId());
}

CYCSwitchDialogLangText::~CYCSwitchDialogLangText()
{
    if (m_Hook)
        UnhookWindowsHookEx(m_Hook);

    if (nspYCSwitchDialogLangText::Switch == this)
        nspYCSwitchDialogLangText::Switch = NULL;
}

void CYCSwitchDialogLangText::SetIniFileName(LPCSTR AFileName)
{
    m_IniFile.Close();

    if (PathFileExists(AFileName))
        m_IniFile.Open(AFileName);
}

void CYCSwitchDialogLangText::InitDialogText(HWND AHwnd, bool AIsWMInitDialog/* = false*/)
{
    CDialog *LDialog = dynamic_cast<CDialog *>(CWnd::FromHandlePermanent(AHwnd));

    if (LDialog)
    {
        if (m_IniFile.IsOpened() && PathFileExists(m_IniFile.FileName()))
        {
#if 0
            CString LSectionName = typeid(*LDialog).name();
#else
            CString LSectionName = LDialog->GetRuntimeClass()->m_lpszClassName;
#endif

            LSectionName.Replace("class ", "");
            LSectionName.Trim();

            if (m_IniFile.IsSectionNameExists(LSectionName))
            {
                std::vector<HWND>   LChildHwnds;

                EnumChildWindows(AHwnd, EnumChildProc, PtrToUlong(&LChildHwnds));

                for (int I = 0; I < (int)LChildHwnds.size(); I ++)
                {
                    const int LCtrlID = GetDlgCtrlID(LChildHwnds[I]);

                    CString LCtrlIDValueText = "";
                    CString LCtrlIDValueName = "";

                    LCtrlIDValueName.Format("%d", LCtrlID);

                    if (m_IniFile.IsValueNameExists(LSectionName, LCtrlIDValueName))
                    {
                        LCtrlIDValueText = m_IniFile.ReadString(LSectionName, LCtrlIDValueName, "", false);

                        SetWindowText(LChildHwnds[I], LCtrlIDValueText);
                    }
                }

                CString LStr;

                LDialog->GetWindowText(LStr);
                LDialog->SetWindowText(m_IniFile.ReadString(LSectionName, "Caption", LStr, false));
            }
        }
        else if (!AIsWMInitDialog)
        {
            InitDialogTextFromOrgRes(LDialog);
        }
    }
}

void CYCSwitchDialogLangText::InitDialogTextFromOrgRes(CDialog *ADialog)
{
    class CDialogWrapper : public CDialog
    {
        friend void CYCSwitchDialogLangText::InitDialogTextFromOrgRes(CDialog *ADialog);
    public:
    };

    CDialogWrapper *LDialog = (CDialogWrapper *)ADialog;


    if (LDialog->m_lpDialogInit != NULL)
    {

    }
    else
    {
        ASSERT(LDialog->m_lpszTemplateName != NULL);

        HINSTANCE   LInst = AfxFindResourceHandle(LDialog->m_lpszTemplateName, RT_DIALOG);
        HRSRC       LResource = ::FindResource(LInst, LDialog->m_lpszTemplateName, RT_DIALOG);

        if (LResource == NULL)
        {
            if (DWORD_PTR(LDialog->m_lpszTemplateName) > 0xffff)
            {
                TRACE(traceAppMsg, 0, _T("ERROR: Cannot find dialog template named '%s'.\n"),
                    LDialog->m_lpszTemplateName);
            }
            else
            {
                TRACE(traceAppMsg, 0, "ERROR: Cannot find dialog template with IDD 0x%04X.\n",
                    LOWORD((DWORD_PTR)LDialog->m_lpszTemplateName));
            }

            return;
        }

        // we must check that the dialog template is for an invisible child
        //  window that can be used for a form-view or dialog-bar
        HGLOBAL LTemplateHandle = LoadResource(LInst, LResource);

        if (LTemplateHandle == NULL)
        {
            TRACE(traceAppMsg, 0, "Warning: LoadResource failed for dialog template.\n");
            // this is only a warning, the real call to CreateDialog will fail
            return;        // not a program error - just out of memory
        }

        DLGTEMPLATE *LDlgTemplate = (DLGTEMPLATE*)LockResource(LTemplateHandle);

        try
        {
            DWORD   LStyle;
            BOOL    LIsDialogEx = _DialogSplitHelper::IsDialogEx(LDlgTemplate);

            {
                WORD* LPW;

                if (LIsDialogEx)
                {
                    LPW = (WORD*)((_DialogSplitHelper::DLGTEMPLATEEX*)LDlgTemplate + 1);
                    LStyle = ((_DialogSplitHelper::DLGTEMPLATEEX*)LDlgTemplate)->style;
                }
                else
                {
                    LPW = (WORD*)(LDlgTemplate + 1);
                    LStyle = LDlgTemplate->style;
                }

                // Check for presence of menu and skip it if there is one
                // 0x0000 means there is no menu
                // 0xFFFF means there is a menu ID following
                // Everything else means that this is a NULL terminated Unicode string
                // which identifies the menu resource
                if (*LPW == 0xFFFF)
                    LPW += 2;                // Has menu ID, so skip 2 words
                else
                    while (*LPW++);            // Either No menu, or string, skip past terminating NULL

                // Check for presence of class name string
                // 0x0000 means "Use system dialog class name"
                // 0xFFFF means there is a window class (atom) specified
                // Everything else means that this is a NULL terminated Unicode string
                // which identifies the menu resource
                if (*LPW == 0xFFFF)
                    LPW += 2;                // Has class atom, so skip 2 words
                else
                    while (*LPW++);            // Either No class, or string, skip past terminating NULL

                // Skip caption string
                //while (*LPW++);
                ::SetWindowTextW(ADialog->m_hWnd, (LPCWSTR)LPW);
            }


            {
                DLGITEMTEMPLATE *LItemTemplate = _DialogSplitHelper::FindFirstDlgItem(LDlgTemplate);

                const int LChildCount = (int)_DialogSplitHelper::DlgTemplateItemCount(LDlgTemplate);

                for (int I = 0; I < LChildCount; I ++)
                {
                    WORD*   LPW;
                    DWORD   LID;
                    LPCWSTR LText;

                    // First skip fixed size header information, size of which depends
                    // if this is a DLGITEMTEMPLATE or DLGITEMTEMPLATEEX
                    if (LIsDialogEx)
                    {
                        LPW = (WORD*)((_DialogSplitHelper::DLGITEMTEMPLATEEX*)LItemTemplate + 1);
                        LID = ((_DialogSplitHelper::DLGITEMTEMPLATEEX*)LItemTemplate)->id;
                    }
                    else
                    {
                        LPW = (WORD*)(LItemTemplate + 1);
                        LID = LItemTemplate->id;
                    }

                    if (*LPW == 0xFFFF) // Skip class name ordinal or string
                        LPW += 2; // (WORDs)
                    else
                        while (*LPW++);

                    LText = (LPCWSTR)LPW;

                    ::SetDlgItemTextW(ADialog->m_hWnd, LID, (LPCWSTR)LText);

                    LItemTemplate = _DialogSplitHelper::FindNextDlgItem(LItemTemplate, LIsDialogEx);
                }
            }
        }
        catch (...)
        {
            TRACE("Exception : %s(%d, %s)", __FILE__, __LINE__, __FUNCDNAME__);
        }

        UnlockResource(LTemplateHandle);
        FreeResource(LTemplateHandle);
    }
}

LRESULT CYCSwitchDialogLangText::CallNextHookEx(int nCode, WPARAM wParam, LPARAM lParam)
{
    return ::CallNextHookEx(m_Hook, nCode, wParam, lParam);
}
