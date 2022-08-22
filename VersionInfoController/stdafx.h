// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER                // Allow use of features specific to Windows XP or later.
#define WINVER 0x0501        // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501    // Change this to the appropriate value to target other versions of Windows.
#endif                        

#ifndef _WIN32_WINDOWS        // Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE            // Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600    // Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN        // Exclude rarely-used stuff from Windows headers
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS    // some CString constructors will be explicit

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers
#endif

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components

//#include <3rdParty/DIB.h>
//#include <3rdParty/Picture.h>
//#include <3rdParty/Serial.h>
//#include <3rdParty/Color.h>
//#include <3rdParty/ColorEdit.h>
//#include <3rdParty/ColorListCtrl.h>
//#include <3rdParty/ColorStatic.h>
//#include <3rdParty/ColorButton.h>
//#include <3rdParty/LedButton.h>
//#include <3rdParty/xSkinButton.h>
//#include <3rdParty/BmpButton.h>
//#include <3rdParty/ChangeableSheet.h>
//#include <3rdParty/MatrixStatic.h>
//#include <3rdParty/BarChart.h>
//#include <3rdParty/tooltip2.h>
//#include <3rdParty/ColorCursor.h>
//#include <3rdParty/ButtonST.h>
//#include <3rdParty/MirrorButton.h>
//#include <3rdParty/HoverButton.h>
//#include <3rdParty/SxLogFont.h>     // add by Mike, for Stripper Recipe Dialog, 20130726
//#include <3rdParty/SxGroupBox.h>    // add by Mike, for Stripper Recipe Dialog, 20130726
//#include <3rdParty/ChartCtrl/ChartCtrl.h>
//
//
//#include <3rdParty/ColourPicker/ColourPicker.h>
//#include <3rdParty/ChartCtrl/ChartLineSerie.h>
//
//#include "3rdParty/ChartCtrl/ChartLineSerie.h"
//#include "3rdParty/ChartCtrl/ChartPointsSerie.h"
//#include "3rdParty/ChartCtrl/ChartSurfaceSerie.h"
//#include "3rdParty/ChartCtrl/ChartGrid.h"
//
//
//
//#include "3rdParty/ChartCtrl/ChartBarSerie.h"
//#include "3rdParty/ChartCtrl/ChartLabel.h"
//
//#include "3rdParty/ChartCtrl/ChartAxisLabel.h"
//#include "3rdParty/ChartCtrl/ChartStandardAxis.h"
//#include "3rdParty/ChartCtrl/ChartDateTimeAxis.h"
//
//#include "3rdParty/ChartCtrl/ChartCrossHairCursor.h"
//#include "3rdParty/ChartCtrl/ChartDragLineCursor.h"
//
//#include "3rdParty/LCDLib/COLOR.H"
//#include "3rdParty/LCDLib/GdiBorder.h"
//#include "3rdParty/LCDLib/GdiPlusWnd.h"
//#include "3rdParty/LCDLib/IsiCompBase.h"
//#include "3rdParty/LCDLib/IsiLcdDisplay.h"
//#include "3rdParty/LCDLib/MemDC.h"
//#include "3rdParty/LCDLib/RoundRect.h"
//
//
//#include <YCMFCEx/YCFileVersion.h>
//#include <YCMFCEx/YCUtils.h>
//#include <YCMFCEx/YCIniFile.h>
//#include <YCMFCEx/YCDialog.h>
//#include <YCMFCEx/YCDialogPanel.h>
//#include <YCMFCEx/YCNotifyButton.h>
//#include <YCMFCEx/YCBitStatic.h>
//#include <YCMFCEx/YCSignalLightStatic.h>
//#include <YCMFCEx/YCSwitchDialogLangText.h>
//#include <YCMFCEx/YCListCtrl.h>



// TODO: reference additional headers your program requires here

