#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


// CYCDialogPanel

class CYCDialogPanel : public CWnd
{
	DECLARE_DYNAMIC(CYCDialogPanel)

public:
    enum enmDialogLayout
    {
        dlNone,
        dlCenter,
        dlDialogFitPanel,
        dlPanelFitDialog
    };



	CYCDialogPanel();
	virtual ~CYCDialogPanel();


    //=======================================
    CDialog*    Dialog();
    void        SetDialog(CDialog  *ADialog, enmDialogLayout ALayout = dlCenter);

protected:
    virtual void    PreSubclassWindow();
    afx_msg void    OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg void    WMUpdateCommandUI(CCmdUI* ACmdUI);
    //afx_msg LRESULT WMKickIdle(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()

private:
    static bool     m_IsRegisterThisClass;
    static LPCSTR   m_ClassName;

    static bool RegisterThisClass();

private:
    enmDialogLayout m_Layout;
    CDialog         *m_Dialog;


    void    UpdateDialogDisplay();

};


