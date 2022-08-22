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

// Version-ManagementView.h : interface of the CVersionManagementView class
//

#pragma once
#include "afxcmn.h"

class CVersionManagementSet;

class CVersionManagementView : public CRecordView
{
protected: // create from serialization only
	CVersionManagementView();
	DECLARE_DYNCREATE(CVersionManagementView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_VERSIONMANAGEMENT_FORM };
#endif
	CVersionManagementSet* m_pSet;

// Attributes
public:
	CVersionManagementDoc* GetDocument() const;

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
	virtual ~CVersionManagementView();
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

	void InitListCtrl();
public:
	afx_msg void OnLvnItemchangedLctrlverview(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBtnVersionDataAddClick();
};

#ifndef _DEBUG  // debug version in Version-ManagementView.cpp
inline CVersionManagementDoc* CVersionManagementView::GetDocument() const
   { return reinterpret_cast<CVersionManagementDoc*>(m_pDocument); }
#endif

