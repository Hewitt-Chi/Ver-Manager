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

// Version-ManagerSet.h: interface of the CVersionManagerSet class
//


#pragma once

// code generated on 2019年1月13日, 下午 02:27

class CVersionManagerSet : public CRecordset
{
public:
	CVersionManagerSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CVersionManagerSet)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

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

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

