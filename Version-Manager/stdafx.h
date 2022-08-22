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

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes


 // Here, minimal DB support is requested.  No view is chosen.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars






#include <afxdb.h>        // ODBC



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <3rdParty/DIB.h>
#include <3rdParty/Picture.h>
#include <3rdParty/Serial.h>
#include <3rdParty/Color.h>
#include <3rdParty/ColorEdit.h>
#include <3rdParty/ColorListCtrl.h>
#include <3rdParty/ColorStatic.h>
#include <3rdParty/ColorButton.h>
#include <3rdParty/LedButton.h>
#include <3rdParty/xSkinButton.h>
#include <3rdParty/BmpButton.h>
#include <3rdParty/ChangeableSheet.h>
#include <3rdParty/MatrixStatic.h>
#include <3rdParty/BarChart.h>
#include <3rdParty/tooltip2.h>
#include <3rdParty/ColorCursor.h>
#include <3rdParty/ButtonST.h>
#include <3rdParty/MirrorButton.h>
#include <3rdParty/HoverButton.h>
#include <3rdParty/SxLogFont.h>     // add by Mike, for Stripper Recipe Dialog, 20130726
#include <3rdParty/SxGroupBox.h>    // add by Mike, for Stripper Recipe Dialog, 20130726
#include <3rdParty/ChartCtrl/ChartCtrl.h>


#include <3rdParty/ColourPicker/ColourPicker.h>
#include <3rdParty/ChartCtrl/ChartLineSerie.h>

#include "3rdParty/ChartCtrl/ChartLineSerie.h"
#include "3rdParty/ChartCtrl/ChartPointsSerie.h"
#include "3rdParty/ChartCtrl/ChartSurfaceSerie.h"
#include "3rdParty/ChartCtrl/ChartGrid.h"



#include "3rdParty/ChartCtrl/ChartBarSerie.h"
#include "3rdParty/ChartCtrl/ChartLabel.h"

#include "3rdParty/ChartCtrl/ChartAxisLabel.h"
#include "3rdParty/ChartCtrl/ChartStandardAxis.h"
#include "3rdParty/ChartCtrl/ChartDateTimeAxis.h"

#include "3rdParty/ChartCtrl/ChartCrossHairCursor.h"
#include "3rdParty/ChartCtrl/ChartDragLineCursor.h"

#include "3rdParty/LCDLib/COLOR.H"
#include "3rdParty/LCDLib/GdiBorder.h"
#include "3rdParty/LCDLib/GdiPlusWnd.h"
#include "3rdParty/LCDLib/IsiCompBase.h"
#include "3rdParty/LCDLib/IsiLcdDisplay.h"
#include "3rdParty/LCDLib/MemDC.h"
#include "3rdParty/LCDLib/RoundRect.h"


#include <YCMFCEx/YCFileVersion.h>
#include <YCMFCEx/YCUtils.h>
#include <YCMFCEx/YCIniFile.h>
#include <YCMFCEx/YCDialog.h>
#include <YCMFCEx/YCDialogPanel.h>
#include <YCMFCEx/YCNotifyButton.h>
#include <YCMFCEx/YCBitStatic.h>
#include <YCMFCEx/YCSignalLightStatic.h>
#include <YCMFCEx/YCSwitchDialogLangText.h>
#include <YCMFCEx/YCListCtrl.h>
#include <YCMFCEx/YCObject.h>
#include <YCMFCEx/YCComponent.h>

