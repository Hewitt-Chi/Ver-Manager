#pragma once


#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


#include <vector>
#include <deque>
#include <map>
#include <functional>
#include <algorithm>
#include <afxmt.h>
#include <afxcmn.h>
#include <stdlib.h>
#include <atlimage.h>
#include <gdiplusimaging.h>
#include <afxdlgs.h>
#include <afxmt.h>
#include <Vfw.h>
#include <shlwapi.h>
#include <math.h>
#include <search.h>
#include <float.h>

//#include <ELSUM.h>

#include <3rdParty/Serial.h>

#include <YCMFCEx/YCUtils.h>
#include <YCMFCEx/YCIniFile.h>
#include <YCMFCEx/YCObject.h>
#include <YCMFCEx/YCXML.h>
#include <YCMFCEx/YCWaitableTimer.h>
#include <YCMFCEx/YCMemoryMapping.h>
#include <YCMFCEx/YCOneInstance.h>
#include <YCMFCEx/YCComponent.h>
#include <YCMFCEx/YCData.h>
#include <YCMFCEx/YCMemoryBuffer.h>
#include <YCMFCEx/YCException.h>
#include <YCMFCEx/YCCompletionObject.h>
#include <YCMFCEx/YCControl.h>
#include <YCMFCEx/YCThread.h>
#include <YCMFCEx/YCDialog.h>
#include <YCMFCEx/YCNotifyButton.h>
#include <YCMFCEx/YCBMPDisplayer.h>
#include <YCMFCEx/YCBitStatic.h>
#include <YCMFCEx/YCSignalLightStatic.h>
#include <YCMFCEx/YCSimpleTCPConnection.h>
#include <YCMFCEx/YCSimpleTCPClient.h>
#include <YCMFCEx/YCEventLogger.h>


enum enmTrackControllerID
{
    /* Main controller */
    CONTROLLERID_MainController = 1,

    /* Main controller */
    CONTROLLERID_SECSGEMController,                 // add by Mike, 20140527

    /* Main controller */
    CONTROLLERID_CIMController,
	
    /* base(card) */
    CONTROLLERID_Indicator = 10,
    CONTROLLERID_EnigneerInfoController,            // add by Mike, 20131211
    CONTROLLERID_IOController,
    CONTROLLERID_WaferMover,
    CONTROLLERID_UserControllers,

    CONTROLLERID_ExtAutoFuncController,             // add by Mike, 20151004

};




////////////////////////////////////////////////////////
// 檔案路徑id
//
enum enmTrackDirectoryId
{
    /**/DID_AppDir = 0,

    /**/DID_Config,
#define DID_Config_Text                 "Config"

    /**/DID_AppData,
#define DID_AppData_Text                "AppData"

    /**/DID_Recipe,
#define DID_Recipe_Text                 "Recipe"

    /**/DID_Log,
#define DID_Log_Text                    "Log"

    /**/DID_AutoRunAnalyzeLog,
#define DID_AutoRunAnalyzeLog_Text      "AutoRunAnalyze"

    /**/DID_ProcessLog,
#define DID_ProcessLog_Text             "ProcessLog"

    /**/DID_Temp,
#define DID_Temp_Text                   "Temp"

    /**/DID_TestData,
#define DID_TestData_Text               "TestData"

    /**/DID_Alarm,    //add by Tom , 20150224
#define DID_Alarm_Text               "Alarm"

	/**/DID_FDCLog,
#define DID_FDCLog_Text                 "FDCLog"          // add by Hewitt 20160108


    /**/DID_Count
};


////////////////////////////////////////////////////////
// 檔案id
//
enum enmTrackFileId
{
    /**/FID_App = 0,              // Track.exe

    /**/FID_System,
#define FID_System_Text                     "Track.system"

    /**/FID_HWConfig,
#define FID_HWConfig_Text                   "Track.hwc"

    /**/FID_SWConfig,
#define FID_SWConfig_Text                   "Track.ini"

    /**/FID_PLCIODef,
#define FID_PLCIODef_Text                   "PLCIO.def"

    /**/FID_WaferDef,
#define FID_WaferDef_Text                   "Wafer.def"

    /**/FID_PRDef,
#define FID_PRDef_Text                      "PR.def"

    /**/FID_ERDef,
#define FID_ERDef_Text                      "ER.def"

    /**/FID_BRDef,
#define FID_BRDef_Text                      "BR.def"

    /**/FID_AgentDef,
#define FID_AgentDef_Text                   "Agent.def"

    /**/FID_InitMacro,
#define FID_InitMacro_Text                  "Init.macro"

    /**/FID_PLCModuleText,
#define FID_PLCModuleText_Text              "PLCModuleText.ini"

    /**/FID_PLCModuleTextZHTW,
#define FID_PLCModuleTextZHTW_Text          "PLCModuleTextZHTW.alm"

    /**/FID_Log,
#define FID_Log_Text                        "Track.log"

    /**/FID_AlarmLog,
#define FID_AlarmLog_Text                   "Alarm.log"

	/**/FID_TrackFilter,  //add by Tom , 20140919
#define FID_TrackFilter_Text                   "TrackFilter.ini"
    
    /**/FID_AgentStatus , //add by Tom , 20150417
#define FID_AgentStatus_Text                   "AgnetStatus.ini"
 
    /**/FID_AlarmDayFile , //add by Tom , 20150710
#define FID_AlarmDayFile_Text                   "AlarmDay.ini"    

    /**/FID_Count,
};
namespace nspTrack
{
	extern  CString TrackDirectoryOf(enmTrackDirectoryId AId);
	extern  bool    DeveloperPublicInitialize();
	//extern  void    DeveloperPublicFinalize();
	extern  CString TrackDirectoryOf(enmTrackDirectoryId AId);
	extern  CString YearMonthDay();    //add by Tom , 20150224 , 回傳今天的年月日
	extern  CString TrackFileNameOf(enmTrackFileId AId);
}

#define     FILENAME_dlgModuleConfig        (nspTrack::TrackDirectoryOf(DID_Config) + "\\Config.ini")
#define     DeqDef              std::deque<CString>
#define     DeqItor             std::deque<CString>Iteraotr

#define Config_Section_Customer             "Customer Info"
#define Config_Section_Developer            "Developer Info"

#define Config_Key_CustomerCNT              "Customer Counter"
#define Config_Key_CustomerName             "Customer"
#define Config_Key_ModeCNT                  "Mode Counter"
#define Config_Key_ModeType                 "Mode Type"
#define Config_Key_DeveloperCNT             "Developer Counter"
#define Config_Key_DeveloperName            "Developer Name"
#define Config_Key_DeveloperLevel           "Developer Level"
#define Config_Key_DeveloperType            "Developer Type"

//enum Config_Section_Type
//{




//};