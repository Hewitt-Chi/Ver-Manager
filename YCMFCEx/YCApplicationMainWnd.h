#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

class CYCApplicationMainWnd : public CDialog
{
	DECLARE_DYNAMIC(CYCApplicationMainWnd)

public:
    CDialog     *m_dlgMain;



    CYCApplicationMainWnd(void);
    virtual ~CYCApplicationMainWnd(void);   


    inline LPCSTR   Caption() const               { return m_Caption; }
    void            SetCaption(LPCSTR AValue);

    afx_msg void    OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg void    OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg LRESULT CMDoModal(WPARAM, LPARAM);
    afx_msg LRESULT WMSetText(WPARAM, LPARAM);
    afx_msg LRESULT WMKickIdle(WPARAM, LPARAM);

protected:

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

private:

    CString     m_Caption;
    BYTE        *m_DlgTemplate;
    bool        m_IsDoModaling;
    bool        m_IsRequestDoModal;
};
