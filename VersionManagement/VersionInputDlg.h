#pragma once


#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif
#include "afxcmn.h"
//#pragma comment(lib, "E://Projects//TemperatureMonitor//Output//YCMFCEx//Debug//FO//YCMFCEx.lib")
// CVersionInputDlg dialog

class CVersionInputDlg : public CYCDialog
{
	DECLARE_DYNAMIC(CVersionInputDlg)

public:
	CVersionInputDlg( CWnd* pParent = NULL);   // standard constructor
	virtual ~CVersionInputDlg();
	enum { IDD = IDD_VersionInfoInput};


// Dialog Data
#ifdef AFX_DESIGN_TIME

#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CVersionManagementSet* m_pSet;



	DECLARE_MESSAGE_MAP()


};
