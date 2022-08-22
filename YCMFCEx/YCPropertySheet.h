// mysheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYCPropertySheet

class CYCPropertySheet : public CPropertySheet
{
    DECLARE_DYNAMIC(CYCPropertySheet)

public:
    // Construction
    CYCPropertySheet(UINT AIDCaption, CWnd* AParentWnd = NULL, UINT ASelectPage = 0);
    CYCPropertySheet(LPCTSTR ACaption, CWnd* AParentWnd = NULL, UINT ASelectPage = 0);
    virtual ~CYCPropertySheet();


    virtual void BuildPropPageArray();


protected:
    RECT    m_rctPage;
    CFont   m_fntPage;


    virtual BOOL OnInitDialog();
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg LONG CMResizePage(UINT, LONG);


    DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////
// CppgServiceBaseController
//
class CYCPropertyPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CYCPropertyPage)

public:

    IN CString  m_Caption;


    CYCPropertyPage(UINT AIDTemplate, UINT AIDCaption = 0, DWORD ASize = sizeof(PROPSHEETPAGE));
    virtual ~CYCPropertyPage();


protected:

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg void DoOnUpdateCommandUI(CCmdUI *ACmdUI);


    virtual void OnUpdateCommandUI(CCmdUI *ACmdUI);


    DECLARE_MESSAGE_MAP()

private:
    LONG    m_OrgWidth;
    LONG    m_OrgHeight;

};
//
// CppgServiceBaseController
//////////////////////////////////////////
