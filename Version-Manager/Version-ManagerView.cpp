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

// Version-ManagerView.cpp : implementation of the CVersionManagerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Version-Manager.h"
#endif

#include "Version-ManagerSet.h"
#include "Version-ManagerDoc.h"
#include "Version-ManagerView.h"

#include "..\DeveloperSystem\DeveloperPublic\DeveloperPublicDefine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVersionManagerView

IMPLEMENT_DYNCREATE(CVersionManagerView, CRecordView)

BEGIN_MESSAGE_MAP(CVersionManagerView, CRecordView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVersionManagerView::OnFilePrintPreview)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LCtrlVerView, &CVersionManagerView::OnLvnItemchangedLctrlverview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_TEST, &CVersionManagerView::OnTest)
END_MESSAGE_MAP()

// CVersionManagerView construction/destruction

CVersionManagerView::CVersionManagerView()
	: CRecordView(IDD_VERSIONMANAGER_FORM)
{
	m_pSet = NULL;


	
	nspTrack::DeveloperPublicInitialize();
	m_VerDlgInfo.LoadSWFileNameFromFile();

	DeqDef LTempDeq;
	m_VerDlgInfo.GetCustomerNames(LTempDeq);
	m_InputDlg.SetCustomerInfo(LTempDeq);

	m_VerDlgInfo.GetModeTypes(LTempDeq);
	m_InputDlg.SetModeInfo(LTempDeq);

	m_VerDlgInfo.GetDeveloperNames(LTempDeq);
	m_InputDlg.SetDeveName(LTempDeq);

	m_VerDlgInfo.GetDeveloperLevels(LTempDeq);
	m_InputDlg.SetDeveLevel(LTempDeq);

	m_VerDlgInfo.GetDeveloperTypes(LTempDeq);
	m_InputDlg.SetDeveType(LTempDeq);
	 


	// TODO: add construction code here

}

CVersionManagerView::~CVersionManagerView()
{
	m_VerDlgInfo.SaveConfigCustomerToFile();
}

void CVersionManagerView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// you can insert DDX_Field* functions here to 'connect' your controls to the database fields, ex.
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// See MSDN and ODBC samples for more information

	DDX_Control(pDX, IDC_LCtrlVerView, m_VersionList);
}

BOOL CVersionManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CVersionManagerView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_VersionManagerSet;
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

	CString LColumnStr[] = { "Item","ID","Customer", "Model Type","Version","Start Date","Release Date","Release Note","Work hours","Release Type" ,"Work Days","Level","Developer","Comment","Link" };

	for (int i = 0; i<15; i++)
	{
		m_VersionList.InsertColumn(i + 1, _T(LColumnStr[i]), LVCFMT_CENTER, 80);
	}

	InitListCtrl();

	
}


// CVersionManagerView printing


void CVersionManagerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CVersionManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVersionManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVersionManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVersionManagerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVersionManagerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVersionManagerView diagnostics

#ifdef _DEBUG
void CVersionManagerView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CVersionManagerView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CVersionManagerDoc* CVersionManagerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVersionManagerDoc)));
	return (CVersionManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CVersionManagerView database support
CRecordset* CVersionManagerView::OnGetRecordset()
{
	return m_pSet;
}

 void CVersionManagerView::InitListCtrl()
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

 void CVersionManagerView::OnLvnItemchangedLctrlverview(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

// CVersionManagerView message handlers


 void CVersionManagerView::OnTest()
 {
	 // TODO: Add your command handler code here

	 CString LFileName = FILENAME_dlgModuleConfig;
	 //LFile->Open("C://Test.ini");
	// VersionInfoControl LVer;
	 //LVer.LoadSWFileNameFromFile(LFileName);
	 //LVer.SaveConfigCustomerToFile(LFileName);
//	 m_InputDlg.m_Customer = "KYEC";
//	 m_InputDlg.m_ModelType = "NS8160MS";
//	 m_InputDlg.m_Developer = "Hewitt";
//	 m_InputDlg.m_ReleaseType = "Imporve";
//	 m_InputDlg.m_Level = 'A';
//	 m_InputDlg.DoModal();
/*	 if (m_InputDlg.DoModal() == IDOK)
	 {
		 if (m_pSet->CanAppend())
		 {
			 try {


				 m_pSet->AddNew();
				 m_pSet->m_ID = 0;
				 m_pSet->m_Item = 0;

				 m_pSet->m_Customer = m_InputDlg.m_Customer;
				 m_pSet->m_ModelType = m_InputDlg.m_ModelType;
				 m_pSet->m_Developer = m_InputDlg.m_Developer;
				 m_pSet->m_ReleaseType = m_InputDlg.m_ReleaseType;
				 m_pSet->m_Level = m_InputDlg.m_Level;
				 m_pSet->m_StartDate = m_InputDlg.m_StartDate;
				 m_pSet->m_ReleaseDate = m_InputDlg.m_ReleaseDate;

				 m_pSet->m_Comment = m_InputDlg.m_Comment;
				 m_pSet->m_ReleaseNote = m_InputDlg.m_ReleaseNote;
				 m_pSet->m_Version = m_InputDlg.m_Version;
				 m_pSet->m_Comment = m_InputDlg.m_Comment;

				 

				 m_pSet->Update();
			 }
			 catch (CException * pEX)
			 {
				 pEX->ReportError();
			 }

		 }
	 }*/


 }
