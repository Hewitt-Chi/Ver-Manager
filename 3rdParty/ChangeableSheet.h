// mysheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeableSheet

class CChangeableSheet : public CPropertySheet
{
    DECLARE_DYNAMIC(CChangeableSheet)

public:
    // Construction
    CChangeableSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    CChangeableSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    virtual ~CChangeableSheet();


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
