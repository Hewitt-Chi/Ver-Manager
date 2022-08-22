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

// Version-ManagerView.h : interface of the CVersionManagerView class
//
#include "VersionInfoControl.h"
#include "VersionInputDlg.h"
#pragma once

class CVersionManagerSet;

class CVersionManagerView : public CRecordView
{
protected: // create from serialization only
	CVersionManagerView();
	DECLARE_DYNCREATE(CVersionManagerView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_VERSIONMANAGER_FORM };
#endif
	CVersionManagerSet* m_pSet;

// Attributes
public:
	CVersionManagerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CVersionManagerView();

	void InitListCtrl();

	afx_msg void OnLvnItemchangedLctrlverview(NMHDR *pNMHDR, LRESULT *pResult);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_VersionList;

	CFont m_Font;
	int m_DataCount;
	VersionInfoControl m_VerDlgInfo;

	CVersionInputDlg m_InputDlg;
public:
	afx_msg void OnTest();
};

#ifndef _DEBUG  // debug version in Version-ManagerView.cpp
inline CVersionManagerDoc* CVersionManagerView::GetDocument() const
   { return reinterpret_cast<CVersionManagerDoc*>(m_pDocument); }
#endif

