// VersionInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "Version-ManagerSet.h"
#include "VersionInputDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 //CVersionInputDlg dialog

IMPLEMENT_DYNAMIC(CVersionInputDlg, CYCDialog)

CVersionInputDlg::CVersionInputDlg( CWnd* pParent/* = NULL*/)
	: CYCDialog(CVersionInputDlg::IDD, pParent)
	,m_DDX_Customer(0)
	,m_DDX_ModelType(0)
	,m_DDX_Developer(0)
	,m_DDX_Level(0)
	,m_DDX_ReleaseType(0)
	,m_ID(0)
	,m_Customer("")
	,m_ModelType("")
	,m_Version("")
	,m_StartDate()
	,m_ReleaseDate()
	,m_ReleaseNote("")
	,m_Comment("")
	,m_Workhours(0)
	,m_ReleaseType("")
	,m_WorkDays(0)
	,m_Level("")
	,m_Developer("")
	,m_Item()
	,m_Link("")
{


	


//	m_pSet = NULL;
}

CVersionInputDlg::~CVersionInputDlg()
{
}

void CVersionInputDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CombCustomer, m_cmbxCustomer);
	DDX_Control(pDX, IDC_CombModeType, m_cmbxModeType);
	DDX_Control(pDX, IDC_CombDveploperName, m_cmbxDeveloper);
	DDX_Control(pDX, IDC_CombLevel, m_cmbxLevel);
	DDX_Control(pDX, IDC_CombDeveloperType, m_cmbxDeveloerType);


	DDX_CBIndex(pDX, IDC_CombCustomer, m_DDX_Customer);
	DDX_CBIndex(pDX, IDC_CombModeType, m_DDX_ModelType);
	DDX_CBIndex(pDX, IDC_CombDveploperName, m_DDX_Developer);
	DDX_CBIndex(pDX, IDC_CombLevel, m_DDX_Level);
	DDX_CBIndex(pDX, IDC_CombDeveloperType, m_DDX_ReleaseType);

	DDX_Control(pDX, IDC_MonCalStartDate, m_MonCalStartDate);
	DDX_Control(pDX, IDC_MonCalEndDate, m_MonCalEndDate);



	DDX_Control(pDX, IDC_EdtVersion, m_edtVersion);
	DDX_Control(pDX, IDC_EdtWorkDay, m_edtWorkdays);
	DDX_Control(pDX, IDC_EdtWorkHours, m_edtWorkHour);
	DDX_Control(pDX, IDC_edtReleaseNote, m_edtReleaseNote);
	DDX_Control(pDX, IDC_edtHistory, m_edtHistory);
}


BEGIN_MESSAGE_MAP(CVersionInputDlg, CYCDialog)
	ON_BN_CLICKED(IDOK, &CVersionInputDlg::OnbtnAddClick)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(MCN_SELCHANGE, IDC_MonCalStartDate, &CVersionInputDlg::OnMonClStartSelChange)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MonCalEndDate, &CVersionInputDlg::OnMonCalEndSelchange)
	ON_NOTIFY(MCN_GETDAYSTATE, IDC_MonCalStartDate, &CVersionInputDlg::OnGetDayStartStats)
END_MESSAGE_MAP()

BOOL CVersionInputDlg::OnInitDialog()
{
	__super::OnInitDialog();


	for (int LDeqValue = 0; LDeqValue < m_CustomerNameDeq.size(); LDeqValue++)
	{

		int LActionValue = LDeqValue ? 0x0001 << (LDeqValue - 1) : 0;

		const int LNum = m_cmbxCustomer.AddString(m_CustomerNameDeq[LDeqValue]);

		m_cmbxCustomer.SetItemData(LNum, LActionValue);

		if (LActionValue == m_DDX_Customer || m_DDX_Customer == -1)
		{
			m_DDX_Customer = LNum;
			m_cmbxCustomer.SetCurSel(LNum);
		}

	}
	//m_cmbxCustomer.SetCurSel(0);

	for (int LDeqValue = 0; LDeqValue < m_ModeTypeDeq.size(); LDeqValue++)
	{
		int LActionValue = LDeqValue ? 0x0001 << (LDeqValue - 1) : 0;

		const int LNum = m_cmbxModeType.AddString(m_ModeTypeDeq[LDeqValue]);

		m_cmbxModeType.SetItemData(LNum, LActionValue);

		if (LActionValue == m_DDX_ModelType || m_DDX_ModelType == -1)
		{
			m_DDX_ModelType = LNum;
			m_cmbxModeType.SetCurSel(LNum);
		}
	}
//	m_cmbxModeType.SetCurSel(0);


	for (int LDeqValue = 0; LDeqValue < m_DeveloperNameDeq.size(); LDeqValue++)
	{
		int LActionValue = LDeqValue ? 0x0001 << (LDeqValue - 1) : 0;

		const int LNum = m_cmbxDeveloper.AddString(m_DeveloperNameDeq[LDeqValue]);

		m_cmbxDeveloper.SetItemData(LNum, LActionValue);

		if (LActionValue == m_DDX_Developer || m_DDX_Developer == -1)
		{
			m_DDX_Developer = LNum;
			m_cmbxDeveloper.SetCurSel(LNum);
		}
	}
//	m_cmbxDeveloper.SetCurSel(0);
	if (m_DeveloperNameDeq.size() <= 1)
	{
		m_cmbxDeveloper.EnableWindow(FALSE);
	}

	for (int LDeqValue = 0; LDeqValue < m_DeveLevelDeq.size(); LDeqValue++)
	{
		int LActionValue = LDeqValue ? 0x0001 << (LDeqValue - 1) : 0;

		const int LNum = m_cmbxLevel.AddString(m_DeveLevelDeq[LDeqValue]);

		m_cmbxLevel.SetItemData(LNum, LActionValue);

		if (LActionValue == m_DDX_Level || m_DDX_Level == -1)
		{
			m_DDX_Level = LNum;
			m_cmbxLevel.SetCurSel(LNum);
		}
	}
	//m_cmbxLevel.SetCurSel(0);

	for (int LDeqValue = 0; LDeqValue < m_DeveTypeDeq.size(); LDeqValue++)
	{
		int LActionValue = LDeqValue ? 0x0001 << (LDeqValue - 1) : 0;

		const int LNum = m_cmbxDeveloerType.AddString(m_DeveTypeDeq[LDeqValue]);

		m_cmbxDeveloerType.SetItemData(LNum, LActionValue);

		if (LActionValue == m_DDX_ReleaseType || m_DDX_ReleaseType == -1)
		{
			m_DDX_ReleaseType = LNum;
			m_cmbxDeveloerType.SetCurSel(LNum);
		}
	}
	m_edtWorkdays.EnableWindow(FALSE);
	m_edtWorkHour.EnableWindow(FALSE);

	CenterWindow();


	return TRUE;
}

void CVersionInputDlg::PreInitDialog()
{
	__super::PreInitDialog();

	for (int I = 0; I < m_CustomerNameDeq.size(); I++)
	{
		if (m_Customer == m_CustomerNameDeq[I])
		{
			m_DDX_Customer = I ? 0x0001 << (I - 1) : 0;

		}
	}

	for (int I = 0; I < m_ModeTypeDeq.size(); I++)
	{
		if (m_ModelType == m_ModeTypeDeq[I])
		{
			m_DDX_ModelType  = I ? 0x0001 << (I - 1) : 0;

		}

	}

	for (int I = 0; I < m_DeveloperNameDeq.size(); I++)
	{
		if (m_Developer == m_DeveloperNameDeq[I])
		{
			m_DDX_Developer  = I ? 0x0001 << (I - 1) : 0;
		}
	}

	for (int I = 0; I < m_DeveLevelDeq.size(); I++)
	{
		if (m_Level == m_DeveLevelDeq[I])
		{
			m_DDX_Level = I ? 0x0001 << (I - 1) : 0;
		}
	}

	for (int I = 0; I < m_DeveTypeDeq.size(); I++)
	{
		if (m_ReleaseType == m_DeveTypeDeq[I])
		{
			m_DDX_ReleaseType = I ? 0x0001 << (I - 1) : 0;
		}
	}

}


// CVersionInputDlg message handlers


void CVersionInputDlg::OnbtnAddClick()
{
	// TODO: Add your control notification handler code here
	int LcmbxIdx;
	CString LCmbxStr;
	LcmbxIdx = m_cmbxCustomer.GetCurSel();
	m_cmbxCustomer.GetLBText(LcmbxIdx, LCmbxStr);
	m_Customer = LCmbxStr;

	LcmbxIdx = m_cmbxModeType.GetCurSel();
	m_cmbxModeType.GetLBText(LcmbxIdx, LCmbxStr);
	m_ModelType = LCmbxStr;

	LcmbxIdx = m_cmbxDeveloper.GetCurSel();
	m_cmbxDeveloper.GetLBText(LcmbxIdx, LCmbxStr);
	m_Developer = LCmbxStr;

	LcmbxIdx = m_cmbxLevel.GetCurSel();
	m_cmbxLevel.GetLBText(LcmbxIdx, LCmbxStr);
	m_Level = LCmbxStr;

	LcmbxIdx = m_cmbxDeveloerType.GetCurSel();
	m_cmbxDeveloerType.GetLBText(LcmbxIdx, LCmbxStr);
	m_ReleaseType = LCmbxStr;

	 m_edtVersion.GetWindowTextA(m_Version);
	

	
	m_MonCalStartDate.GetCurSel(m_StartDate);
	
	m_MonCalEndDate.GetCurSel(m_ReleaseDate);
	
	long Days = GetWorkDays();
	//if (Days < 0)
	//	return ;
	CString DateFmt;
	DateFmt.Format("%d", Days);
	m_edtWorkdays.SetWindowTextA(DateFmt);
	long WorksHours = Days * 8;
	DateFmt.Format("%d", WorksHours);
	m_edtWorkHour.SetWindowTextA(DateFmt);

	m_WorkDays = Days;
	m_Workhours = WorksHours;
	__super::OnOK();

}
bool CVersionInputDlg::SetCustomerInfo(DeqDef ACustomerName)
{
	
	m_CustomerNameDeq = ACustomerName;

	
	return TRUE;
}

bool CVersionInputDlg::SetModeInfo(DeqDef AModeType)
{
	m_ModeTypeDeq = AModeType;
	
	return TRUE;
}
bool CVersionInputDlg::SetDeveName(DeqDef ADeveName)
{
	m_DeveloperNameDeq = ADeveName;

	
	return TRUE;
}
bool CVersionInputDlg::SetDeveLevel(DeqDef ADeveLevel)
{
	m_DeveLevelDeq = ADeveLevel;

	
	return TRUE;
}
bool CVersionInputDlg::SetDeveType(DeqDef ADeveType)
{
	m_DeveTypeDeq = ADeveType;

	
	return TRUE;
}

HBRUSH CVersionInputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CYCDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired

	CBrush LBrush;
	LBrush.CreateSolidBrush(RGB(0, 0, 255));
	if (nCtlColor == CTLCOLOR_DLG)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(clDarkGray2);
		HBRUSH b = CreateSolidBrush(clDarkGray2);
		return b;
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(clDarkGray2);
		HBRUSH b = CreateSolidBrush(clDarkGray2);
		return b;
	}
	return hbr;
}


void CVersionInputDlg::OnMonClStartSelChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here

	m_MonCalStartDate.GetCurSel(m_StartDate);

	m_MonCalEndDate.GetCurSel(m_ReleaseDate);

	long Days = GetWorkDays();
	if (Days < 0)
		return;
	//YCSystemTimeCompare(LStartTime, LEndTime);
	CString LedtStr;

	m_WorkDays = Days;
	m_Workhours = Days * 8;
	LedtStr.Format("%d", m_WorkDays);

	m_edtWorkdays.SetWindowTextA(LedtStr);
	LedtStr.Format("%d", m_Workhours);
	m_edtWorkHour.SetWindowTextA(LedtStr);
	
	*pResult = 0;
}


void CVersionInputDlg::OnMonCalEndSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_MonCalStartDate.GetCurSel(m_StartDate);

	m_MonCalEndDate.GetCurSel(m_ReleaseDate);

	//if (m_StartDate > m_ReleaseDate)
	//	return;
	//const CTimeSpan LTimeSpan = m_ReleaseDate - m_StartDate;
	
	long Days = GetWorkDays();
	if (Days < 0)
		return;
	//YCSystemTimeCompare(LStartTime, LEndTime);
	CString LedtStr;

	m_WorkDays = Days;
	m_Workhours = Days * 8;
	LedtStr.Format("%d", m_WorkDays);

	m_edtWorkdays.SetWindowTextA(LedtStr);
	LedtStr.Format("%d", m_Workhours);
	m_edtWorkHour.SetWindowTextA(LedtStr);
	*pResult = 0;
}


void CVersionInputDlg::OnGetDayStartStats(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDAYSTATE pDayState = reinterpret_cast<LPNMDAYSTATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	pDayState->cDayState;
	*pResult = 0;
}

long CVersionInputDlg::GetWorkDays()
{
	if (m_StartDate > m_ReleaseDate)
		return -1;
	const CTimeSpan LTimeSpan = m_ReleaseDate - m_StartDate;
	long Days = LTimeSpan.GetDays() + 1;
	return Days;
}
