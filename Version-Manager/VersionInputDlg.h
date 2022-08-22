#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "..\DeveloperSystem\DeveloperPublic\DeveloperPublicDefine.h"

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif
#include "afxcmn.h"

// CVersionInputDlg dialog

class CVersionInputDlg : public CYCDialog
{
	DECLARE_DYNAMIC(CVersionInputDlg)

public:
	CVersionInputDlg( CWnd* pParent = NULL);   // standard constructor
	virtual ~CVersionInputDlg();

 	virtual BOOL OnInitDialog();
	
	enum { IDD = IDD_VersionInfoInput};


// Dialog Data
#ifdef AFX_DESIGN_TIME

#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

//	CVersionManagerSet* m_pSet;

	virtual void PreInitDialog();



	DECLARE_MESSAGE_MAP()
private:

	long	m_DDX_ID;
	int 	m_DDX_Customer;
	int 	m_DDX_ModelType;
	CString	m_DDX_Version;
	CTime	m_DDX_StartDate;
	CTime	m_DDX_ReleaseDate;
	CString	m_DDX_ReleaseNote;
	CString	m_DDX_Comment;
	long	m_DDX_Workhours;
	int 	m_DDX_ReleaseType;
	long	m_DDX_WorkDays;
	int 	m_DDX_Level;
	int 	m_DDX_Developer;
	long	m_DDX_Item;
	CString	m_DDX_Link;



public:
	afx_msg void OnbtnAddClick();
	

	long	m_ID;
	CString	m_Customer;
	CString	m_ModelType;
	CString	m_Version;
	CTime	m_StartDate;
	CTime	m_ReleaseDate;
	CString	m_ReleaseNote;
	CString	m_Comment;
	long	m_Workhours;
	CString	m_ReleaseType;
	long	m_WorkDays;
	CString	m_Level;
	CString	m_Developer;
	long	m_Item;
	CString	m_Link;
private:
	CComboBox m_cmbxCustomer;
	CComboBox m_cmbxModeType;
	CComboBox m_cmbxDeveloper;
	CComboBox m_cmbxLevel;
	CComboBox m_cmbxDeveloerType;

	CMonthCalCtrl m_MonCalStartDate;
	CMonthCalCtrl m_MonCalEndDate;


	DeqDef m_CustomerNameDeq;
	DeqDef m_ModeTypeDeq;
	DeqDef m_DeveloperNameDeq;
	DeqDef m_DeveLevelDeq;
	DeqDef m_DeveTypeDeq;


public:
	bool SetCustomerInfo(DeqDef ACustomerName);
	bool SetModeInfo(DeqDef AModeType);
	bool SetDeveName(DeqDef ADeveName);
	bool SetDeveLevel(DeqDef ADeveLevel);
	bool SetDeveType(DeqDef ADeveType);

	long GetWorkDays();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


private:
	CEdit m_edtVersion;
	CEdit m_edtWorkdays;
	CEdit m_edtWorkHour;
public:
	CEdit m_edtReleaseNote;
	CEdit m_edtHistory;
	afx_msg void OnMonClStartSelChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMonCalEndSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnGetDayStartStats(NMHDR *pNMHDR, LRESULT *pResult);
};
