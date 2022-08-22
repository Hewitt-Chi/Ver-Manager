// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Version-ManagementView.cpp : implementation of the CVersionManagementView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VersionManagement.h"
#endif

#include "VersionManagementSet.h"
#include "VersionManagementDoc.h"
#include "VersionManagementView.h"
#include "VersionInputDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVersionManagementView

IMPLEMENT_DYNCREATE(CVersionManagementView, CRecordView)

BEGIN_MESSAGE_MAP(CVersionManagementView, CRecordView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVersionManagementView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LCtrlVerView, &CVersionManagementView::OnLvnItemchangedLctrlverview)

	ON_COMMAND(ID_BtnVersionInput, &CVersionManagementView::OnBtnVersionDataAddClick)
END_MESSAGE_MAP()

// CVersionManagementView construction/destruction

CVersionManagementView::CVersionManagementView()
	: CRecordView(IDD_VERSIONMANAGEMENT_FORM)
{
	m_pSet = NULL;
	// TODO: add construction code here

}

CVersionManagementView::~CVersionManagementView()
{
}

void CVersionManagementView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// you can insert DDX_Field* functions here to 'connect' your controls to the database fields, ex.
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// See MSDN and ODBC samples for more information
	DDX_Control(pDX, IDC_LCtrlVerView, m_VersionList);
}

BOOL CVersionManagementView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CVersionManagementView::OnInitialUpdate() 
{
	m_pSet = &GetDocument()->m_VersionManagementSet;
	CRecordView::OnInitialUpdate();

	VERIFY(m_Font.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial"));                 // lpszFacename
	DWORD dwStyleView = m_VersionList.GetExtendedStyle();
	dwStyleView |= LVS_EX_GRIDLINES; //網格線（只適用與report風格的listctrl）
	dwStyleView |= LVS_EX_ONECLICKACTIVATE;
	dwStyleView |= LVS_EX_SUBITEMIMAGES;
	m_VersionList.SetExtendedStyle(dwStyleView);
	m_VersionList.SetFont(&m_Font);

	CString LColumnStr[] = { "Item","ID","Customer", "Model Type","Version","Start Date","Release Date","Release Note","Work hours","Release Type" ,"Work Days","Level","Developer","Comment" };

	for (int i = 0; i<14; i++)
	{
		m_VersionList.InsertColumn(i + 1, _T(LColumnStr[i]), LVCFMT_CENTER, 80);
	}

	InitListCtrl();

}


// CVersionManagementView printing


void CVersionManagementView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CVersionManagementView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVersionManagementView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVersionManagementView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVersionManagementView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVersionManagementView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVersionManagementView diagnostics

#ifdef _DEBUG
void CVersionManagementView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CVersionManagementView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CVersionManagementDoc* CVersionManagementView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVersionManagementDoc)));
	return (CVersionManagementDoc*)m_pDocument;
}
#endif //_DEBUG


// CVersionManagementView database support
CRecordset* CVersionManagementView::OnGetRecordset()
{
	return m_pSet;
}

void CVersionManagementView::InitListCtrl()
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_VersionList.GetDlgItem(0);
	ASSERT(pHeader);
	if (pHeader)
	{
		m_VersionList.SetRedraw(FALSE);
		int iNbrOfColumns = pHeader->GetItemCount();
		int iNbrOfCols = 15;
		for (int iCurrCol = 0; iCurrCol<iNbrOfColumns + 1; iCurrCol++)
		{
			// m_ListCtrl.SetColumnWidth(iCurrCol,LVSCW_AUTOSIZE);
			int nCurrWidth = m_VersionList.GetColumnWidth(iCurrCol);

			m_VersionList.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE_USEHEADER);
			int nColHdrWidth = m_VersionList.GetColumnWidth(iCurrCol);
			m_VersionList.SetColumnWidth(iCurrCol, max(nCurrWidth, nColHdrWidth));
		}
		m_VersionList.SetRedraw(true);
		m_VersionList.Invalidate();
	}
}


// CVersionManagementView message handlers


void CVersionManagementView::OnLvnItemchangedLctrlverview(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}



void CVersionManagementView::OnBtnVersionDataAddClick()
{
	// TODO: Add your command handler code here

	//CVersionInputDlg Dlg;

	
}
