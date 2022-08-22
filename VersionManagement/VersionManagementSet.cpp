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

// Version-ManagementSet.cpp : implementation of the CVersionManagementSet class
//

#include "stdafx.h"
#include "VersionManagement.h"
#include "VersionManagementSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVersionManagementSet implementation

// code generated on 2018年12月28日, 上午 12:04

IMPLEMENT_DYNAMIC(CVersionManagementSet, CRecordset)

CVersionManagementSet::CVersionManagementSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Customer = L"";
	m_ModelType = L"";
	m_Version = L"";
	m_StartDate;
	m_ReleaseDate;
	m_ReleaseNote = L"";
	m_Comment = L"";
//	m_Link = L"";
	m_Workhours = 0;
	m_ReleaseType = 0;
	m_WorkDays = 0;
	m_Level = L"";
	m_Developer = L"";
	m_Item = 0;
	m_nFields = 14;
	m_nDefaultType = snapshot;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CVersionManagementSet::GetDefaultConnect()
{
	return _T("DSN=Version management;DBQ=C:\\VerControl.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=1234;UID=Hewitt;");
}

CString CVersionManagementSet::GetDefaultSQL()
{
	return _T("[Version]");
}

void CVersionManagementSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
//	RFX_Text(pFX, _T("[Customer]"), m_Customer);
//	RFX_Text(pFX, _T("[Model Type]"), m_ModelType);
//	RFX_Text(pFX, _T("[Version]"), m_Version);
//	RFX_Date(pFX, _T("[Start Date]"), m_StartDate);
//	RFX_Date(pFX, _T("[Release Date]"), m_ReleaseDate);
//	RFX_Text(pFX, _T("[Release Note]"), m_ReleaseNote);
//	RFX_Text(pFX, _T("[Comment]"), m_Comment);
	//RFX_Text(pFX, _T("[欄位1]"), m_Link);
//	RFX_Long(pFX, _T("[Work hours]"), m_Workhours);
//	RFX_Long(pFX, _T("[Release Type]"), m_ReleaseType);
//	RFX_Long(pFX, _T("[Work Days]"), m_WorkDays);
//	RFX_Text(pFX, _T("[Level]"), m_Level);
	//RFX_Text(pFX, _T("[Developer]"), m_Developer);
//	RFX_Long(pFX, _T("[Item]"), m_Item);

}
/////////////////////////////////////////////////////////////////////////////
// CVersionManagementSet diagnostics

#ifdef _DEBUG
void CVersionManagementSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVersionManagementSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

