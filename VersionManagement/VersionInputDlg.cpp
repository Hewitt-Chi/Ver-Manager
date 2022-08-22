// VersionInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "VersionManagementSet.h"
#include "VersionInputDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// CVersionInputDlg dialog

IMPLEMENT_DYNAMIC(CVersionInputDlg, CYCDialog)

CVersionInputDlg::CVersionInputDlg( CWnd* pParent/* = NULL*/)
	: CYCDialog(CVersionInputDlg::IDD, pParent)

{
	m_pSet = NULL;
}

CVersionInputDlg::~CVersionInputDlg()
{
}

void CVersionInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CYCDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVersionInputDlg, CYCDialog)
END_MESSAGE_MAP()


// CVersionInputDlg message handlers
