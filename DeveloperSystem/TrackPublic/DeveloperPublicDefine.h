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

/*#include <YCAutoControlFW/ACDefine.h>
#include <YCAutoControlFW/ACController.h>
#include <YCAutoControlFW/ACBaseJob.h>
#include <YCAutoControlFW/ACBaseRobot.h>
#include <YCAutoControlFW/ACDefaultEventLogger.h>
#include <YCAutoControlFW/ACBaseTemperatureController.h>

#include <RobotYaskawaM201/ACYaskawaNXC100.h>
#include <RobotYaskawaM201/ACYaskawaM201.h>
#include <RobotBrooksATR8/ACBrooksSeries8.h>
#include <RobotBrooksATR8/ACBrooksATR8.h>
#include <RobotMilaraH314/ACMilaraH313X20.h>

//#include <PLC/MitEthernet.h>
#include <PLC/ACBasePLCComm.h>
#include <PLC/ACMitsubishiMELSECQCommunication.h>
#include <PLC/ACVirtualPLCCommunication.h>
#include <PLC/ACQ64TC.h>
#include <PLC/ACNXTC.h>

#include <TemperatureController/SeecWT404.h>
#include <TemperatureController/ACSeecWT404.h>




////////////////////////////////////////////////////////
// PLC Module Consts
//
#define PLCMODULE_Enabled                       0
#define PLCMODULE_Disabled                      1

#define PLCMODULE_HeatingEnabled                1           // add by Mike, 20131008
#define PLCMODULE_HeatingDisabled               0           // add by Mike, 20131008
#define PLCMODULE_TrueIsEnabled                 1           // add by Mike, 20131014
#define PLCMODULE_FalseIsDisabled               0           // add by Mike, 20131014
#define PLCMODULE_EnabledIsTrue                 1           // add by Mike, 20131017
#define PLCMODULE_DisabledIsFalse               0           // add by Mike, 20131017

#define PLCMODULE_OperationMode_Auto            0
#define PLCMODULE_OperationMode_Manual          1


#define PLCMODULE_Buzzer_Enabled                1
#define PLCMODULE_Buzzer_Disabled               0


#define PLCMODULE_RobotAlarm_NoAlarm            0
#define PLCMODULE_RobotAlarm_Alarm              1



////////////////////////////////////////////////////////
// Function Result
//
enum enmTrackSuccFuncCode
{
    TRACK_Func_ICDPending = ACCONTROLLER_Func_SuccUser,
    TRACK_Func_ManualContinueAbort,

    PLCMODULE_Func_GotPLCModuleFailStatus,
    PLCMODULE_Func_WaferDetected,
    PLCMODULE_Func_WaferNotDetected,

    PROCESSSTATION_Func_Processing,
    PROCESSSTATION_Func_ProcessFinish,
    PROCESSSTATION_Func_ProcessSuspended,

    AUTORUNNEXTSTEP_Func_AnalyzeNextStepSucc,
    AUTORUNNEXTSTEP_Func_NoMoreStep,
    AUTORUNNEXTSTEP_Func_MovingToPickStandbySucc,
    AUTORUNNEXTSTEP_Func_PickWaferSucc,
    AUTORUNNEXTSTEP_Func_PlaceWaferSucc,
    AUTORUNNEXTSTEP_Func_LoadWaferSucc,
    AUTORUNNEXTSTEP_Func_UnloadWaferSucc,
    AUTORUNNEXTSTEP_Func_WaitTemperatureStable,
    AUTORUNNEXTSTEP_Func_WaitTemperatureStableComplete,
    AUTORUNNEXTSTEP_Func_SetupHPTemperature,
};


#define TRACK_Func_FailBase                                         ACCONTROLLER_Func_FailUser
#define TRACK_FuncFail(__Offset)                                    (TRACK_Func_FailBase + __Offset)

// CTrackWaferMover function result
#define WAFERMOVER_Func_LoadWaferFail                               TRACK_FuncFail(-0)


// CTrackRobotEndeffector function result
#define ROBOTENDEFFECTOR_Func_WaferNotExists                        TRACK_FuncFail(-20)
#define ROBOTENDEFFECTOR_Func_WaferExists                           TRACK_FuncFail(-21)


// CTrackBaseLoaderUnloader function result
#define LOADERUNLOADER_Func_CassetteExists                          TRACK_FuncFail(-30)
#define LOADERUNLOADER_Func_CassetteNotExists                       TRACK_FuncFail(-31)


// CTrackWaferHolder function result 
#define WAFERHOLDER_Func_PrePickFail                                TRACK_FuncFail(-40)
#define WAFERHOLDER_Func_PickFail                                   TRACK_FuncFail(-41)
#define WAFERHOLDER_Func_PostPickFail                               TRACK_FuncFail(-42)
#define WAFERHOLDER_Func_PrePlaceFail                               TRACK_FuncFail(-43)
#define WAFERHOLDER_Func_PlaceFail                                  TRACK_FuncFail(-44)
#define WAFERHOLDER_Func_PostPlaceFail                              TRACK_FuncFail(-45)
#define WAFERHOLDER_Func_WaferExists                                TRACK_FuncFail(-46)
#define WAFERHOLDER_Func_WaferNotExists                             TRACK_FuncFail(-47)


// CTrackProcessStation function result
#define PROCESSSTATION_Func_Cancel                                  TRACK_FuncFail(-60)
#define PROCESSSTATION_Func_WaferStateCannotProcess                 TRACK_FuncFail(-61)


// CTrachHotplate
#define HOTPLATE_Func_CantSetOccupiedHotPlateTemperature            TRACK_FuncFail(-70)
#define HOTPLATE_Func_InsufficientHotPlateCount                     TRACK_FuncFail(-71)


// CTrackAutoRunNextStepExecuter function result
#define AUTORUNNEXTSTEP_Func_InvalidCompletionState                 TRACK_FuncFail(-100)
#define AUTORUNNEXTSTEP_Func_AnalyzeNextStepFail                    TRACK_FuncFail(-101)
#define AUTORUNNEXTSTEP_Func_AnalyzeNoUsablePS                      TRACK_FuncFail(-102)
#define AUTORUNNEXTSTEP_Func_NextStepFail                           TRACK_FuncFail(-103)
#define AUTORUNNEXTSTEP_Func_NextStepMoveWaferFail                  TRACK_FuncFail(-104)
#define AUTORUNNEXTSTEP_Func_NextStepBlocked                        TRACK_FuncFail(-105)
#define AUTORUNNEXTSTEP_Func_SetupHPTemperatureFail                 TRACK_FuncFail(-106)


// CTrackAutoRunner function result
#define AUTORUNNER_Func_NoWaferToManualLoad                         TRACK_FuncFail(-110)


// CMainController function result
#define MAINCONTROLLER_Func_NoSpecifiedController                   TRACK_FuncFail(-160)


////////////////////////////////////////////////////////
// event code
//
enum enmTrackEventCode
{
    //////////////////////////////////////////////////////////////////
    WAFERMOVER_Event_RequestUnloadingInfo = ACCONTROLLER_Event_User,
    //   AParam1 : int pointer for receiving OrgCassetteIdx.
    //   AParam2 : int pointer for receiving OrgSlotIdx.
    //   AParam3 : LRESULT pointer for receiving Result of this Request.



    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_CassettePlaced,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_CassetteRemoved,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

	//////////////////////////////////////////////////////////////////      // add by Mike, 20141013
    // Cassette
    LOADERUNLOADER_Event_CarrierTypeIsNotVerify,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////      // add by Mike, 20141013
    // Cassette
    LOADERUNLOADER_Event_CarrierTypeIsVerify,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_FoupClamp,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_FoupNotClamp,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_FoupDocked,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_FoupUndocked,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_DoorOpen,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_DoorClose,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_MappingStart,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_MappingSucc,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_MappingFail,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_ReportMapInfo,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 : TTrackCassetteSlotWaferStates *
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_CarrierIdle,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_ReadCarrierId,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette
    LOADERUNLOADER_Event_AWaferStart,
    //   AParam1 : SlotIdx
    //   AParam2 : Index of Loader(Cassette)
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette開始製程
    LOADERUNLOADER_Event_CassetteStart,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette完成製程了
    LOADERUNLOADER_Event_AllWaferProcessCompletion,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette取消未完成的製程
    LOADERUNLOADER_Event_CassetteCancel,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette完成製程了
    LOADERUNLOADER_Event_AllWaferReturn,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette完成製程後被移走了
    LOADERUNLOADER_Event_CassetteCompleteUnloaded,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

#if 0
    //////////////////////////////////////////////////////////////////
    // Cassette被移走了
    LOADERUNLOADER_Event_CassetteUnloaded,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :
#endif

    //////////////////////////////////////////////////////////////////
    // Cassette被移走了
    LOADERUNLOADER_Event_CassetteStateChange,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 : new state
    //   AParam3 :

#if 0
    //////////////////////////////////////////////////////////////////
    // Cassette被載入
    LOADERUNLOADER_Event_CassetteLoaded,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :
#endif

    //////////////////////////////////////////////////////////////////
    // 設定一個進行製程的Cassette
    LOADERUNLOADER_Event_SetRunningCassette,
    //   AParam1 : Index of Loader(Cassette)
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // 一片Wafer完成被送回Cassette
    LOADERUNLOADER_Event_AWaferComplete,
    //   AParam1 : CTrackWafer *
    //   AParam2 : 
    //   AParam3 :

    //////////////////////////////////////////////////////////////////     //add by Tom , 20150202
    // 在取消製程時候,拿起Loader是否要移除資訊
    LOADERUNLOADER_Event_ProcessCancelCanClearLoaderInfo,
    //   AParam1 : TRUE --> Clear Loader Info , FALSE -->Not
    //   AParam2 : 
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // Cassette的最後一片Wafer被移走了
    LOADERUNLOADER_Event_CassetteLastWaferPicked,
    //   AParam1 : SlotIdx
    //   AParam2 : Index of Loader(Cassette)
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    WAFERHOLDER_Event_WaferPick,
    //   AParam1 : SlotIdx
    //   AParam2 : Index of Loader(Cassette)
    //   AParam3 : m_Index (Module Index)

    //////////////////////////////////////////////////////////////////
    WAFERHOLDER_Event_WaferPlace,
    //   AParam1 : SlotIdx
    //   AParam2 : Index of Loader(Cassette)
    //   AParam3 : m_Index (Module Index)

    //////////////////////////////////////////////////////////////////
    WAFERHOLDER_Event_WaferSet,
    //   AParam1 : SlotIdx
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    WAFERHOLDER_Event_WaferReset,
    //   AParam1 : SlotIdx
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////      // add by Mike, 20140720
    PROCESSSTATION_Event_ReportTemperatureState,
    //   AParam1 : m_Index
    //   AParam2 : Temperature (xxx.xx * 100)
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    PROCESSSTATION_Event_Idle,
    //   AParam1 : SlotIdx
    //   AParam2 : Index of Loader(Cassette)
    //   AParam3 : m_Index (Module Index)

    //////////////////////////////////////////////////////////////////
    PROCESSSTATION_Event_ProcessStart,
    //   AParam1 : SlotIdx
    //   AParam2 : IsOcupied
    //   AParam3 :

    //////////////////////////////////////////////////////////////////      // add by Mike, 20140523
    PROCESSSTATION_Event_Processing,
    //   AParam1 : SlotIdx
    //   AParam2 : IsOcupied
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    PROCESSSTATION_Event_ProcessCancel,
    //   AParam1 : SlotIdx
    //   AParam2 : IsOcupied
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    PROCESSSTATION_Event_ProcessComplete,    
    //   AParam1 : SlotIdx
    //   AParam2 : IsOcupied
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    PROCESSSTATION_Event_ProcessFail,
    //   AParam1 : SlotIdx
    //   AParam2 : IsOcupied
    //   AParam3 :


    //////////////////////////////////////////////////////////////////
    PROCESSSTATION_Event_ProcessSuspended,
    //   AParam1 : TRUE --> Suspended, FALSE --> Continue/Cancel
    //   AParam2 :
    //   AParam3 :


    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    AUTORUNNER_Event_DoAutoTestNotify,
    //   AParam1 : 
    //   AParam2 : 
    //   AParam3 : 


    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    AUTORUNNER_Event_AutoRunStart,
    //   AParam1 : TRUE --> Auto Mode, FALSE --> Manual Mode.
    //   AParam2 : 
    //   AParam3 : 


    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    AUTORUNNER_Event_AutoRunStop,
    //   AParam1 : TRUE --> Auto Mode, FALSE --> Manual Mode.
    //   AParam2 : 
    //   AParam3 : 


    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    AUTORUNNER_Event_AutoRunSDStop,
    //   AParam1 : TRUE --> Auto Mode, FALSE --> Manual Mode.
    //   AParam2 : 
    //   AParam3 : 


    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    AUTORUNNER_Event_AutoRunSuspend,
    //   AParam1 : TRUE --> Auto Mode, FALSE --> Manual Mode.
    //   AParam2 : 
    //   AParam3 : 


    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    AUTORUNNER_Event_AutoRunResume,
    //   AParam1 : TRUE --> Auto Mode, FALSE --> Manual Mode.
    //   AParam2 : 
    //   AParam3 : 


    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    AUTORUNNER_Event_AutoRunDoorOpenStop,
    //   AParam1 : 
    //   AParam2 : 
    //   AParam3 : 

	  ////////////////////////////////////////////////////////////////// add by Mike, 20151103
  
  // 參數修改                                     //          以下    add by Hewitt 20151213  用於Etching E3換酸頁面
    CuEtching001755_EVENT_EnableAutoChange,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

	CuEtching001755_EVENT_PLCEnableAutoChange,
	  //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

	CuEtching001755_EVENT_PreAutoChange,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

	
    CuEtching001755_EVENT_AutoChangeStart,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :
	CuEtching001755_EVENT_AutoChangeFinsh,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :
	CuEtching001755_EVENT_AutoChangeTimesLimit,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :



///////////////////////////////////////////////////////////////     以上      add by Hewitt 20151214
    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    UTILITY_Event_DoorOpen,
    //   AParam1 : TRUE --> Door is opened, FALSE --> Door is closed. 
    //   AParam2 : 
    //   AParam3 : 


    //////////////////////////////////////////////////////////////////
    // 自動測試流程
    UTILITY_Event_HWAutoModeSwitchChanged,
    //   AParam1 : TRUE --> Auto Mode, FALSE --> Manual Mode. 
    //   AParam2 : 
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management Add Group              // add by Mike, 20140610
    RECIPEMANAGEMENT_Event_AddGroup,
    //   AParam1 : CString * (GroupName)
    //   AParam2 : 
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management Delete Group           // add by Mike, 20140610
    RECIPEMANAGEMENT_Event_DeleteGroup,
    //   AParam1 : CString * (GroupName)
    //   AParam2 : 
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management Rename Group           // add by Mike, 20140611
    RECIPEMANAGEMENT_Event_RenameGroup,
    //   AParam1 : CString * (GroupName)
    //   AParam2 : 
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management Add Recipe             // add by Mike, 20140610
    RECIPEMANAGEMENT_Event_AddRecipe,
    //   AParam1 : CString * (RecipeName)
    //   AParam2 : CString * (RecipeFileName)
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management Remove Recipe          // add by Mike, 20140610
    RECIPEMANAGEMENT_Event_RemoveRecipe,
    //   AParam1 : CString * (RecipeName)
    //   AParam2 : CString * (RecipeFileName)
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management New Recipe             // add by Mike, 20140610
    RECIPEMANAGEMENT_Event_NewRecipe,
    //   AParam1 : CString * (RecipeName)
    //   AParam2 : CString * (RecipeFileName)
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management Save Recipe            // add by Mike, 20140610
    RECIPEMANAGEMENT_Event_SaveRecipe,
    //   AParam1 : CString * (RecipeName)
    //   AParam2 : CString * (RecipeFileName)
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management                    
    RECIPEMANAGEMENT_Event_RecipeModified,
    //   AParam1 : CString * (RecipeName)
    //   AParam2 : CString * (RecipeFileName)
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // PID寫入0 Mike Debug
    DEBUG_Event_PIDWriteZero,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////////20141125 By Poni
	//操作流程設定
	OPERATIONFLOW_Event_SetInfo,
    //   AParam1 : LoaderUnLoader Index
    //   AParam2 : enmSetOperationFlow
    //   AParam3 : 
	//操作流程設定發送讀取Info
	OPERATIONFLOW_Event_SendInfo,
    //   AParam1 : Code
    //   AParam2 : 
    //   AParam3 : 

    ////////////////////////////////////////////////////////////////// ECN20150821MIKE02
    // 參數修改
    PARAMETERCHANGE_Event_SaveParameter,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////////20150724 By Poni
    //Operation Mode Change
    OPERATIONMODE_Event_Change,
    //   AParam1 : Code
    //   AParam2 : 
    //   AParam3 : 

    //////////////////////////////////////////////////////////////////
    // Recipe Management Select Recipe            // add by Poni, 20150916
    RECIPEMANAGEMENT_Event_SelectRecipe,
    //   AParam1 : CString * (RecipeName)
    //   AParam2 : CString * (RecipeFileName)
    //   AParam3 : 

    ////////////////////////////////////////////////////////////////// add by Mike, 20151004
    // 參數修改
    AUTOCLEANCUPFUNC_EVENT_WillEnableCupClean,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////// add by Mike, 20151004
    // 參數修改
    AUTOCLEANCUPFUNC_EVENT_CupCleanStart,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////// add by Mike, 20151004
    // 參數修改
    AUTOCLEANCUPFUNC_EVENT_CupCleanFinish,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////// add by Mike, 20151103
    // 參數修改
    COATER001119_EVENT_EnableBSRBufTankAutoFillRequest,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////// add by Mike, 20151103
    // 參數修改
    AUTOBSRBUFTANKFILLFUNC_EVENT_WillEnableBSRBufTankAutoFill,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////// add by Mike, 20151103
    // 參數修改
    AUTOBSRBUFTANKFILLFUNC_EVENT_BSRBufTankAutoFillStart,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////// add by Mike, 20151103
    // 參數修改
    AUTOBSRBUFTANKFILLFUNC_EVENT_BSRBufTankAutoFillFinish,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    ////////////////////////////////////////////////////////////////// add by Mike, 20151004
    // 參數修改
    EXTAUTOFUNC_EVENT_ProcessEnd,
    //   AParam1 : 
    //   AParam2 :
    //   AParam3 :

    //////////////////////////////////////////////////////////////////
    // ExtAutoFuncEvent
    EXTAUTOFUNC_Event_DlgMsgChange,
    //   AParam1 : SlotIdx
    //   AParam2 : Index of Loader(Cassette)
    //   AParam3 :

};

//////////////////////////////////////////////////////////////////////
////CIM Event
enum enmCIMLotInfoStatus
{
    CIM_CORRECTLOTINFO_Event = 0,
#define CIM_CORRECTLOTINFO_Text        "The correct LOTINFO."

    CIM_RECIPEERROR_Event,
#define CIM_RECIPEERROR_Text    "The recipe have erred!"

    CIM_SIZEERROR_Event,
#define CIM_SIZEERROR_Text   "Size have erred!"

    CIM_PIECESERROR_Event,
#define CIM_PIECESERROR_Text    "Pieces have erred!"

    CIM_LOADERNUMBERERROR_Event,
#define CIM_LOADERNUMBERERROR_Text  "Loader No. have erred!"

    CIM_LOTIDERROR_Event,
#define CIM_LOTIDERROR_Text  "LOT ID have erred!"
};


//////////////////////////////////////////////////////////////////////
////SECSGEM Event
enum enmSECSGEMStatus
{
    SECSGEM_CANCEL_Event = 10,
};

//////////////////////////////////////////////////////////////////////
////設定操作流程
//
enum enmSetOperationFlow
{
    CIM = 0,
    CIMDoubleCheckLotID,
    SECSGEM,
    CIM001125,                  // ECN20160314MIKE01
    OperationFlow_count,
};

////////////////////////////////////////////////////////////////////
// Track SECS/GEM Control Mode Code
//
enum enmTrackControlModeCode
{
    Track_Mode_Online = 0,
    Track_Mode_Local = 3,
};

////////////////////////////////////////////////////////
// alarm code
//
//======================================Wafer Holder
#define WAFERHOLDER_Alarm_Base                                      (ACCONTROLLER_Alarm_User)
#define WAFERHOLDER_Alarm(__Offset)                                 (WAFERHOLDER_Alarm_Base + __Offset)

#define WAFERHOLDER_Alarm_PlaceStandbyFail                          WAFERHOLDER_Alarm(0)
#define WAFERHOLDER_Alarm_PlaceStandbyFail_Level                    ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_PlaceStandbyFail_Text                     "WaferHolder(%s) place standby failed."

#define WAFERHOLDER_Alarm_PrePlaceFail                              WAFERHOLDER_Alarm(1)
#define WAFERHOLDER_Alarm_PrePlaceFail_Level                        ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_PrePlaceFail_Text                         "WaferHolder(%s) pre-place failed."

#define WAFERHOLDER_Alarm_PlaceFail                                 WAFERHOLDER_Alarm(2)
#define WAFERHOLDER_Alarm_PlaceFail_Level                           ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_PlaceFail_Text                            "WaferHolder(%s) place failed."

#define WAFERHOLDER_Alarm_PostPlaceFail                             WAFERHOLDER_Alarm(3)
#define WAFERHOLDER_Alarm_PostPlaceFail_Level                       ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_PostPlaceFail_Text                        "WaferHolder(%s) post-place failed."

#define WAFERHOLDER_Alarm_PickStandbyFail                           WAFERHOLDER_Alarm(4)
#define WAFERHOLDER_Alarm_PickStandbyFail_Level                     ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_PickStandbyFail_Text                      "WaferHolder(%s) pick standby failed."

#define WAFERHOLDER_Alarm_PrePickFail                               WAFERHOLDER_Alarm(5)
#define WAFERHOLDER_Alarm_PrePickFail_Level                         ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_PrePickFail_Text                          "WaferHolder(%s) pre-pick failed."

#define WAFERHOLDER_Alarm_PickFail                                  WAFERHOLDER_Alarm(6)
#define WAFERHOLDER_Alarm_PickFail_Level                            ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_PickFail_Text                             "WaferHolder(%s) pick failed."

#define WAFERHOLDER_Alarm_PostPickFail                              WAFERHOLDER_Alarm(7)
#define WAFERHOLDER_Alarm_PostPickFail_Level                        ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_PostPickFail_Text                         "WaferHolder(%s) post-pick failed."

#define WAFERHOLDER_Alarm_WaferExists                               WAFERHOLDER_Alarm(8)
#define WAFERHOLDER_Alarm_WaferExists_Level                         ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_WaferExists_Text                          "WaferHolder(%s) have a wafer in it."

#define WAFERHOLDER_Alarm_WaferNotExists                            WAFERHOLDER_Alarm(9)
#define WAFERHOLDER_Alarm_WaferNotExists_Level                      ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_WaferNotExists_Text                       "WaferHolder(%s) have no wafer in it."

#define WAFERHOLDER_Alarm_PrePlaceTimeout                           WAFERHOLDER_Alarm(10)
#define WAFERHOLDER_Alarm_PrePlaceTimeout_Level                     ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_PrePlaceTimeout_Text                      "WaferHolder(%s) pre-place timeout for waiting process complete."

#define WAFERHOLDER_Alarm_PrePickTimeout                            WAFERHOLDER_Alarm(11)
#define WAFERHOLDER_Alarm_PrePickTimeout_Level                      ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_PrePickTimeout_Text                       "WaferHolder(%s) pre-pick timeout for waiting process complete."

#define WAFERHOLDER_Alarm_StillInProcessing                         WAFERHOLDER_Alarm(12)
#define WAFERHOLDER_Alarm_StillInProcessing_Level                   ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_StillInProcessing_Text                    "WaferHolder(%s) is still in processing."

#define WAFERHOLDER_Alarm_PickCancel                                WAFERHOLDER_Alarm(13)
#define WAFERHOLDER_Alarm_PickCancel_Level                          ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_PickCancel_Text                           "WaferHolder(%s) pick cancel"

#define WAFERHOLDER_Alarm_PlaceCancel                               WAFERHOLDER_Alarm(14)
#define WAFERHOLDER_Alarm_PlaceCancel_Level                         ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_PlaceCancel_Text                          "WaferHolder(%s) place cancel"

#define WAFERHOLDER_Alarm_IsOccupied                                WAFERHOLDER_Alarm(15)
#define WAFERHOLDER_Alarm_IsOccupied_Level                          ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_IsOccupied_Text                           "WaferHolder(%s) is occupied."

#define WAFERHOLDER_Alarm_WaferStateIsNotValid                      WAFERHOLDER_Alarm(16)
#define WAFERHOLDER_Alarm_WaferStateIsNotValid_Level                ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_WaferStateIsNotValid_Text                 "WaferHolder(%s) wafer state is not valid."

#define WAFERHOLDER_Alarm_SetCompatibleWaferTypeFail                WAFERHOLDER_Alarm(17)
#define WAFERHOLDER_Alarm_SetCompatibleWaferTypeFail_Level          ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_SetCompatibleWaferTypeFail_Text           "WaferHolder(%s) set compatible wafer type failed."

#define WAFERHOLDER_Alarm_WaferTypeIsIncompatible                   WAFERHOLDER_Alarm(18)
#define WAFERHOLDER_Alarm_WaferTypeIsIncompatible_Level             ALARMLEVEL_ModuleAlarm2
#define WAFERHOLDER_Alarm_WaferTypeIsIncompatible_Text              "WaferHolder(%s) wafer type is incompatible."

#define WAFERHOLDER_Alarm_InteractivePlaceFail                      WAFERHOLDER_Alarm(19)
#define WAFERHOLDER_Alarm_InteractivePlaceFail_Level                ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_InteractivePlaceFail_Text                 "WaferHolder(%s) interactive place fail."

#define WAFERHOLDER_Alarm_InteractivePickFail                       WAFERHOLDER_Alarm(20)
#define WAFERHOLDER_Alarm_InteractivePickFail_Level                 ALARMLEVEL_SystemAlarm
#define WAFERHOLDER_Alarm_InteractivePickFail_Text                  "WaferHolder(%s) interactive pick fail."



//======================================PLC Module
#define PLCMODULE_Alarm_Base                                        (ACCONTROLLER_Alarm_User + 100) 
#define PLCMODULE_Alarm(__Offset)                                   (PLCMODULE_Alarm_Base + __Offset)


#define PLCMODULE_Alarm_ReadDataFail                                PLCMODULE_Alarm(0)
#define PLCMODULE_Alarm_ReadDataFail_Level                          ALARMLEVEL_ModuleAlarm2
#define PLCMODULE_Alarm_ReadDataFail_Text                           "PLCModule(%s) read data failed."

#define PLCMODULE_Alarm_StatusFail                                  PLCMODULE_Alarm(1)
#define PLCMODULE_Alarm_StatusFail_Level                            ALARMLEVEL_ModuleAlarm2
#define PLCMODULE_Alarm_StatusFail_Text                             "PLCModule(%s) status failed."

#define PLCMODULE_Alarm_ReadWarning2Fail                            PLCMODULE_Alarm(2)
#define PLCMODULE_Alarm_ReadWarning2Fail_Level                      ALARMLEVEL_ModuleAlarm2
#define PLCMODULE_Alarm_ReadWarning2Fail_Text                       "PLCModule(%s) read warning2 failed."

#define PLCMODULE_Alarm_ReadError1Fail                              PLCMODULE_Alarm(3)
#define PLCMODULE_Alarm_ReadError1Fail_Level                        ALARMLEVEL_ModuleAlarm2
#define PLCMODULE_Alarm_ReadError1Fail_Text                         "PLCModule(%s) read error1 failed."

#define PLCMODULE_Alarm_ReadError2Fail                              PLCMODULE_Alarm(4)
#define PLCMODULE_Alarm_ReadError2Fail_Level                        ALARMLEVEL_ModuleAlarm2
#define PLCMODULE_Alarm_ReadError2Fail_Text                         "PLCModule(%s) read error2 failed."

#define PLCMODULE_Alarm_WriteDataFail                               PLCMODULE_Alarm(5)
#define PLCMODULE_Alarm_WriteDataFail_Level                         ALARMLEVEL_ModuleAlarm2
#define PLCMODULE_Alarm_WriteDataFail_Text                          "PLCModule(%s) write data failed(%s %u %s)."

#define PLCMODULE_Alarm_WriteCommandFail                            PLCMODULE_Alarm(6)
#define PLCMODULE_Alarm_WriteCommandFail_Level                      ALARMLEVEL_ModuleAlarm2
#define PLCMODULE_Alarm_WriteCommandFail_Text                       "PLCModule(%s) write command failed."

#define PLCMODULE_Alarm_ThrowWarning1                               PLCMODULE_Alarm(7)
#define PLCMODULE_Alarm_ThrowWarning1_Level                         ALARMLEVEL_Warning1
#define PLCMODULE_Alarm_ThrowWarning1_Text                          "PLCModule(%s) throw a warning1(%s)."

#define PLCMODULE_Alarm_ThrowWarning2                               PLCMODULE_Alarm(8)
#define PLCMODULE_Alarm_ThrowWarning2_Level                         ALARMLEVEL_Warning2
#define PLCMODULE_Alarm_ThrowWarning2_Text                          "PLCModule(%s) throw a warning2(%s)."

#define PLCMODULE_Alarm_ThrowError1                                 PLCMODULE_Alarm(9)
#define PLCMODULE_Alarm_ThrowError1_Level                           ALARMLEVEL_ModuleAlarm1
#define PLCMODULE_Alarm_ThrowError1_Text                            "PLCModule(%s) throw an error1(%s)."

#define PLCMODULE_Alarm_ThrowError2                                 PLCMODULE_Alarm(10)
#define PLCMODULE_Alarm_ThrowError2_Level                           ALARMLEVEL_ModuleAlarm2
#define PLCMODULE_Alarm_ThrowError2_Text                            "PLCModule(%s) throw an error2(%s)."

#define PLCMODULE_Alarm_ThrowSystemError                            PLCMODULE_Alarm(11)
#define PLCMODULE_Alarm_ThrowSystemError_Level                      ALARMLEVEL_SystemAlarm
#define PLCMODULE_Alarm_ThrowSystemError_Text                       "PLCModule(%s) throw an system error(%s)."


//======================================Process Station
#define PROCESSSTATION_Alarm_Base                                   (ACCONTROLLER_Alarm_User + 200)
#define PROCESSSTATION_Alarm(__Offset)                              (PROCESSSTATION_Alarm_Base + __Offset)

#define PROCESSSTATION_Alarm_ProcessFail                            PROCESSSTATION_Alarm(0)
#define PROCESSSTATION_Alarm_ProcessFail_Level                      ALARMLEVEL_ModuleAlarm2
#define PROCESSSTATION_Alarm_ProcessFail_Text                       "ProcessStation(%s) process failed."

#define PROCESSSTATION_Alarm_ProcessTimeout                         PROCESSSTATION_Alarm(1)
#define PROCESSSTATION_Alarm_ProcessTimeout_Level                   ALARMLEVEL_ModuleAlarm2
#define PROCESSSTATION_Alarm_ProcessTimeout_Text                    "ProcessStation(%s) process timeout."

#define PROCESSSTATION_Alarm_WaferStateCannotProcess                PROCESSSTATION_Alarm(2)
#define PROCESSSTATION_Alarm_WaferStateCannotProcess_Level          ALARMLEVEL_ModuleAlarm2
#define PROCESSSTATION_Alarm_WaferStateCannotProcess_Text           "ProcessStation(%s) wafer state is not correct."

#define PROCESSSTATION_Alarm_WaferStartProcessFail                  PROCESSSTATION_Alarm(3)
#define PROCESSSTATION_Alarm_WaferStartProcessFail_Level            ALARMLEVEL_ModuleAlarm2
#define PROCESSSTATION_Alarm_WaferStartProcessFail_Text             "ProcessStation(%s) start wafer process failed."

#define PROCESSSTATION_Alarm_WaferIsNotExists                       PROCESSSTATION_Alarm(4)
#define PROCESSSTATION_Alarm_WaferIsNotExists_Level                 ALARMLEVEL_ModuleAlarm2
#define PROCESSSTATION_Alarm_WaferIsNotExists_Text                  "ProcessStation(%s) wafer is not exists."

#define PROCESSSTATION_Alarm_WaferRecipeNotCompatible               PROCESSSTATION_Alarm(5)
#define PROCESSSTATION_Alarm_WaferRecipeNotCompatible_Level         ALARMLEVEL_ModuleAlarm2
#define PROCESSSTATION_Alarm_WaferRecipeNotCompatible_Text          "ProcessStation(%s) wafer's recipe is not compatible."


//======================================Loader/Unloader
#define LOADERUNLOADER_Alarm_Base                                           (ACCONTROLLER_Alarm_User + 300)
#define LOADERUNLOADER_Alarm(__Offset)                                      (LOADERUNLOADER_Alarm_Base + __Offset)

#define LOADERUNLOADER_Alarm_CassetteHasBeenSet                             LOADERUNLOADER_Alarm(0)
#define LOADERUNLOADER_Alarm_CassetteHasBeenSet_Level                       ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_CassetteHasBeenSet_Text                        "LoaderUnloader(%s) cassette has been set."

#define LOADERUNLOADER_Alarm_CassetteNotExists                              LOADERUNLOADER_Alarm(1)
#define LOADERUNLOADER_Alarm_CassetteNotExists_Level                        ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_CassetteNotExists_Text                         "LoaderUnloader(%s) cassette does not exist."

#define LOADERUNLOADER_Alarm_ProcessingCassetteDisappear                    LOADERUNLOADER_Alarm(2)
#define LOADERUNLOADER_Alarm_ProcessingCassetteDisappear_Level              ALARMLEVEL_SystemAlarm
#define LOADERUNLOADER_Alarm_ProcessingCassetteDisappear_Text               "LoaderUnloader(%s) processing cassette disappeared."

#define LOADERUNLOADER_Alarm_UnloaderCassetteIsNotFound                     LOADERUNLOADER_Alarm(3)
#define LOADERUNLOADER_Alarm_UnloaderCassetteIsNotFound_Level               ALARMLEVEL_SystemAlarm
#define LOADERUNLOADER_Alarm_UnloaderCassetteIsNotFound_Text                "LoaderUnloader(%s) unloader cassette is not found."

#if 0
#define LOADERUNLOADER_Alarm_LoadWaferFail                                  LOADERUNLOADER_Alarm(4)
#define LOADERUNLOADER_Alarm_LoadWaferFail_Level                            ALARMLEVEL_SystemAlarm
#define LOADERUNLOADER_Alarm_LoadWaferFail_Text                             "LoaderUnloader(%s) load wafer failed."

#define LOADERUNLOADER_Alarm_UnloadWaferFail                                LOADERUNLOADER_Alarm(5)
#define LOADERUNLOADER_Alarm_UnloadWaferFail_Level                          ALARMLEVEL_SystemAlarm
#define LOADERUNLOADER_Alarm_UnloadWaferFail_Text                           "LoaderUnloader(%s) unload wafer failed."
#endif

#define LOADERUNLOADER_Alarm_SlotIsOccupied                                 LOADERUNLOADER_Alarm(6)
#define LOADERUNLOADER_Alarm_SlotIsOccupied_Level                           ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_SlotIsOccupied_Text                            "LoaderUnLoader(%s) slot(%d) is occupied."

#define LOADERUNLOADER_Alarm_LoaderUnloaderCassetteSizeNotTheSame           LOADERUNLOADER_Alarm(7)
#define LOADERUNLOADER_Alarm_LoaderUnloaderCassetteSizeNotTheSame_Level     ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_LoaderUnloaderCassetteSizeNotTheSame_Text      "LoaderUnLoader(%s) cassettes size are not the same."

#define LOADERUNLOADER_Alarm_NotOwnWafer                                    LOADERUNLOADER_Alarm(8)
#define LOADERUNLOADER_Alarm_NotOwnWafer_Level                              ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_NotOwnWafer_Text                               "LoaderUnLoader(%s) does not own the wafer(%s)."

#define LOADERUNLOADER_Alarm_WaferSizeIsNotCompatible                       LOADERUNLOADER_Alarm(9)
#define LOADERUNLOADER_Alarm_WaferSizeIsNotCompatible_Level                 ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_WaferSizeIsNotCompatible_Text                  "LoaderUnLoader(%s) wafer size is not compatible."

#define LOADERUNLOADER_Alarm_SlotIdxIsNotValid                              LOADERUNLOADER_Alarm(10)
#define LOADERUNLOADER_Alarm_SlotIdxIsNotValid_Level                        ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_SlotIdxIsNotValid_Text                         "LoaderUnLoader(%s) new slot index(%d) is not the same with specified(%d)."

#define LOADERUNLOADER_Alarm_SlotIdxIsOutOfRange                            LOADERUNLOADER_Alarm(11)
#define LOADERUNLOADER_Alarm_SlotIdxIsOutOfRange_Level                      ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_SlotIdxIsOutOfRange_Text                       "LoaderUnLoader(%s) slot index(%d) is out of range."

#define LOADERUNLOADER_Alarm_LoaderStatusFailOnPrePick                            LOADERUNLOADER_Alarm(12)
#define LOADERUNLOADER_Alarm_LoaderStatusFailOnPrePick_Level                      ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_LoaderStatusFailOnPrePick_Text                       "LoaderUnLoader(%s) Status(%d) Fail On PrePick."

#define LOADERUNLOADER_Alarm_LoaderStatusFailOnPrePlace                            LOADERUNLOADER_Alarm(13)
#define LOADERUNLOADER_Alarm_LoaderStatusFailOnPrePlace_Level                      ALARMLEVEL_ModuleAlarm2
#define LOADERUNLOADER_Alarm_LoaderStatusFailOnPrePlace_Text                       "LoaderUnLoader(%s) Status(%d) Fail On PrePlace."


//======================================Wafer mover
#define WAFERMOVER_Alarm_Base                                       (ACCONTROLLER_Alarm_User + 400)
#define WAFERMOVER_Alarm(__Offset)                                  (WAFERMOVER_Alarm_Base + __Offset)

#define WAFERMOVER_Alarm_PickFail                                   WAFERMOVER_Alarm(0)
#define WAFERMOVER_Alarm_PickFail_Level                             ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_PickFail_Text                              "WaferMover(%s) pick wafer failed."

#define WAFERMOVER_Alarm_PlaceFail                                  WAFERMOVER_Alarm(1)
#define WAFERMOVER_Alarm_PlaceFail_Level                            ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_PlaceFail_Text                             "WaferMover(%s) place wafer failed."

#define WAFERMOVER_Alarm_1StepPickFail                              WAFERMOVER_Alarm(2)
#define WAFERMOVER_Alarm_1StepPickFail_Level                        ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_1StepPickFail_Text                         "WaferMover(%s) one step pick wafer failed(step %d)(%s)."

#define WAFERMOVER_Alarm_1StepPlaceFail                             WAFERMOVER_Alarm(3)
#define WAFERMOVER_Alarm_1StepPlaceFail_Level                       ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_1StepPlaceFail_Text                        "WaferMover(%s) one step place wafer failed(step %d)(%s)."

#define WAFERMOVER_Alarm_2StepPickFail                              WAFERMOVER_Alarm(4)
#define WAFERMOVER_Alarm_2StepPickFail_Level                        ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_2StepPickFail_Text                         "WaferMover(%s) two steps pick wafer failed(step %d)(%s)."

#define WAFERMOVER_Alarm_2StepPlaceFail                             WAFERMOVER_Alarm(5)
#define WAFERMOVER_Alarm_2StepPlaceFail_Level                       ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_2StepPlaceFail_Text                        "WaferMover(%s) two steps place wafer failed(step %d)(%s)."

#define WAFERMOVER_Alarm_ExchangeFail                               WAFERMOVER_Alarm(6)
#define WAFERMOVER_Alarm_ExchangeFail_Level                         ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_ExchangeFail_Text                          "WaferMover(%s) swap wafer failed."

#define WAFERMOVER_Alarm_LoadFail                                   WAFERMOVER_Alarm(7)
#define WAFERMOVER_Alarm_LoadFail_Level                             ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_LoadFail_Text                              "WaferMover(%s) load wafer failed(step %d)(%s)."

#define WAFERMOVER_Alarm_UnloadFail                                 WAFERMOVER_Alarm(8)
#define WAFERMOVER_Alarm_UnloadFail_Level                           ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_UnloadFail_Text                            "WaferMover(%s) unload wafer failed(step %d)(%s)."

#define WAFERMOVER_Alarm_IncorrectWaferHolder                       WAFERMOVER_Alarm(9)
#define WAFERMOVER_Alarm_IncorrectWaferHolder_Level                 ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_IncorrectWaferHolder_Text                  "WaferMover(%s) incorrect wafer holder."

#define WAFERMOVER_Alarm_IncorrectRobotTarget                       WAFERMOVER_Alarm(10)
#define WAFERMOVER_Alarm_IncorrectRobotTarget_Level                 ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_IncorrectRobotTarget_Text                  "WaferMover(%s) incorrect robot target."

#define WAFERMOVER_Alarm_NoWaferToPick                              WAFERMOVER_Alarm(11)
#define WAFERMOVER_Alarm_NoWaferToPick_Level                        ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_NoWaferToPick_Text                         "WaferMover(%s) no wafer to pick."

#define WAFERMOVER_Alarm_NoWaferToPlace                             WAFERMOVER_Alarm(12)
#define WAFERMOVER_Alarm_NoWaferToPlace_Level                       ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_NoWaferToPlace_Text                        "WaferMover(%s) no wafer to place."

#define WAFERMOVER_Alarm_TargetIsOccupied                           WAFERMOVER_Alarm(13)
#define WAFERMOVER_Alarm_TargetIsOccupied_Level                     ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_TargetIsOccupied_Text                      "WaferMover(%s) robot target is occupied."

#define WAFERMOVER_Alarm_NoEmptyRobotEndeffector                    WAFERMOVER_Alarm(14)
#define WAFERMOVER_Alarm_NoEmptyRobotEndeffector_Level              ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_NoEmptyRobotEndeffector_Text               "WaferMover(%s) robot end effectors are occupied."

#define WAFERMOVER_Alarm_TargetIsNotProcessStation                  WAFERMOVER_Alarm(15)
#define WAFERMOVER_Alarm_TargetIsNotProcessStation_Level            ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_TargetIsNotProcessStation_Text             "WaferMover(%s) target is not a process station."

#define WAFERMOVER_Alarm_TargetIsNotLoader                          WAFERMOVER_Alarm(16)
#define WAFERMOVER_Alarm_TargetIsNotLoader_Level                    ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_TargetIsNotLoader_Text                     "WaferMover(%s) target is not a loader."

#define WAFERMOVER_Alarm_TargetIsNotUnloader                        WAFERMOVER_Alarm(17)
#define WAFERMOVER_Alarm_TargetIsNotUnloader_Level                  ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_TargetIsNotUnloader_Text                   "WaferMover(%s) target is not a unloader."

#define WAFERMOVER_Alarm_TargetIsNotLoaderOrUnloader                WAFERMOVER_Alarm(18)
#define WAFERMOVER_Alarm_TargetIsNotLoaderOrUnloader_Level          ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_TargetIsNotLoaderOrUnloader_Text           "WaferMover(%s) target is not a loader/unloader."

#define WAFERMOVER_Alarm_RobotUnloadingInfoIsInvalid                WAFERMOVER_Alarm(19)
#define WAFERMOVER_Alarm_RobotUnloadingInfoIsInvalid_Level          ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_RobotUnloadingInfoIsInvalid_Text           "WaferMover(%s) robot unloading info is invalid."

#define WAFERMOVER_Alarm_WaferIsNotOnRobotEndeffector               WAFERMOVER_Alarm(20)
#define WAFERMOVER_Alarm_WaferIsNotOnRobotEndeffector_Level         ALARMLEVEL_SystemAlarm
#define WAFERMOVER_Alarm_WaferIsNotOnRobotEndeffector_Text          "WaferMover(%s) wafer is not on robot endeffector."


//======================================Auto runner
#define AUTORUNNER_Alarm_Base                                       (ACCONTROLLER_Alarm_User + 500)
#define AUTORUNNER_Alarm(__Offset)                                  (AUTORUNNER_Alarm_Base + __Offset)

#define AUTORUNNER_Alarm_NextStepFail                               AUTORUNNER_Alarm(0)
#define AUTORUNNER_Alarm_NextStepFail_Level                         ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_NextStepFail_Text                          "AutoRunner(%s) execute next step failed."

#define AUTORUNNER_Alarm_AnalyzeNextStepFail                        AUTORUNNER_Alarm(1)
#define AUTORUNNER_Alarm_AnalyzeNextStepFail_Level                  ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_AnalyzeNextStepFail_Text                   "AutoRunner(%s) analyze next step failed."

#define AUTORUNNER_Alarm_AutoTrackIsNoClear                         AUTORUNNER_Alarm(2)
#define AUTORUNNER_Alarm_AutoTrackIsNoClear_Level                   ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_AutoTrackIsNoClear_Text                    "AutoRunner(%s) track is not clear."

#define AUTORUNNER_Alarm_PrealignerIsNoClear                        AUTORUNNER_Alarm(3)
#define AUTORUNNER_Alarm_PrealignerIsNoClear_Level                  ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_PrealignerIsNoClear_Text                   "AutoRunner(%s) prealigner is not clear."

#define AUTORUNNER_Alarm_NextRunFail                                AUTORUNNER_Alarm(4)
#define AUTORUNNER_Alarm_NextRunFail_Level                          ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_NextRunFail_Text                           "AutoRunner(%s) run failed."

#define AUTORUNNER_Alarm_LoadWaferFail                              AUTORUNNER_Alarm(5)
#define AUTORUNNER_Alarm_LoadWaferFail_Level                        ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_LoadWaferFail_Text                         "AutoRunner(%s) manual load wafer failed."

#define AUTORUNNER_Alarm_UnloadWaferFail                            AUTORUNNER_Alarm(6)
#define AUTORUNNER_Alarm_UnloadWaferFail_Level                      ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_UnloadWaferFail_Text                       "AutoRunner(%s) manual unload wafer failed."

#define AUTORUNNER_Alarm_ClearWafersFail                            AUTORUNNER_Alarm(7)
#define AUTORUNNER_Alarm_ClearWafersFail_Level                      ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_ClearWafersFail_Text                       "AutoRunner(%s) clear wafers failed."

#define AUTORUNNER_Alarm_MoveWaferFail                              AUTORUNNER_Alarm(8)
#define AUTORUNNER_Alarm_MoveWaferFail_Level                        ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_MoveWaferFail_Text                         "AutoRunner(%s) move wafer(%s) from %s to %s failed."

#define AUTORUNNER_Alarm_SetTemperatureSetupFail                    AUTORUNNER_Alarm(9)
#define AUTORUNNER_Alarm_SetTemperatureSetupFail_Level              ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_SetTemperatureSetupFail_Text               "AutoRunner(%s) set temperature setup fail(%s)."

#define AUTORUNNER_Alarm_SetTemperatureSVFail                       AUTORUNNER_Alarm(10)
#define AUTORUNNER_Alarm_SetTemperatureSVFail_Level                 ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_SetTemperatureSVFail_Text                  "AutoRunner(%s) set temperature sv fail(%s)."

#define AUTORUNNER_Alarm_SetTemperaturePVOSFail                     AUTORUNNER_Alarm(11)
#define AUTORUNNER_Alarm_SetTemperaturePVOSFail_Level               ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_SetTemperaturePVOSFail_Text                "AutoRunner(%s) set temperature pvos fail(%s)."

#define AUTORUNNER_Alarm_SetTemperatureAlarmRangeFail               AUTORUNNER_Alarm(12)
#define AUTORUNNER_Alarm_SetTemperatureAlarmRangeFail_Level         ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_SetTemperatureAlarmRangeFail_Text          "AutoRunner(%s) set temperature alarm range fail(%s)."

#define AUTORUNNER_Alarm_RecipeCannotRunInSystem                    AUTORUNNER_Alarm(13)
#define AUTORUNNER_Alarm_RecipeCannotRunInSystem_Level              ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_RecipeCannotRunInSystem_Text               "AutoRunner(%s) recipe can not run in system."

#define AUTORUNNER_Alarm_SystemIsBlocked                            AUTORUNNER_Alarm(14)
#define AUTORUNNER_Alarm_SystemIsBlocked_Level                      ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_SystemIsBlocked_Text                       "AutoRunner(%s) system is blocked."

#define AUTORUNNER_Alarm_SetupHPTemperatureFail                     AUTORUNNER_Alarm(15)
#define AUTORUNNER_Alarm_SetupHPTemperatureFail_Level               ALARMLEVEL_SystemAlarm
#define AUTORUNNER_Alarm_SetupHPTemperatureFail_Text                "AutoRunner(%s) setup hp temperature fail."
//======================================ClearWafer001812
#define CLEARWAFER001812_Alarm_Base                                 (ACCONTROLLER_Alarm_User + 600)
#define CLEARWAFER001812_Alarm(__Offset)                            (CLEARWAFER001812_Alarm_Base + __Offset)

#define CLEARWAFER001812_Alarm_NeedChangeBrushError1                      CLEARWAFER001812_Alarm(0)
#define CLEARWAFER001812_Alarm_NeedChangeBrushError1_Level                ALARMLEVEL_ModuleAlarm1
#define CLEARWAFER001812_Alarm_NeedChangeBrushError1_Text                 "Need Change New Brush!!(%s)."

#define CLEARWAFER001812_Alarm_NeedChangeBrushFeedStop                      CLEARWAFER001812_Alarm(1)
#define CLEARWAFER001812_Alarm_NeedChangeBrushFeedStop_Level                ALARMLEVEL_Warning2
#define CLEARWAFER001812_Alarm_NeedChangeBrushFeedStop_Text                 "Need Change New Brush!!(%s)(Feed Stop)."

#define CLEARWAFER001812_Alarm_AdjustBrushError1                      CLEARWAFER001812_Alarm(2)
#define CLEARWAFER001812_Alarm_AdjustBrushError1_Level                ALARMLEVEL_ModuleAlarm1
#define CLEARWAFER001812_Alarm_AdjustBrushError1_Text                 "Need Adjust Brush!!(%s)."

#define CLEARWAFER001812_Alarm_AdjustBrushFeedStop                      CLEARWAFER001812_Alarm(3)
#define CLEARWAFER001812_Alarm_AdjustBrushFeedStop_Level                ALARMLEVEL_Warning2
#define CLEARWAFER001812_Alarm_AdjustBrushFeedStop_Text                 "Need Adjust Brush!!(%s)(Feed Stop)."


//======================================Developer001346
#define DEVELOPER001346_Alarm_Base                                 (ACCONTROLLER_Alarm_User + 700)
#define DEVELOPER001346_Alarm(__Offset)                            (DEVELOPER001346_Alarm_Base + __Offset)

#define DEVELOPER001346_Alarm_Base_Alarm_CleanCupFuncFail           DEVELOPER001346_Alarm(0)
#define DEVELOPER001346_Alarm_Base_Alarm_CleanCupFuncFail_Level     ALARMLEVEL_ModuleAlarm2
#define DEVELOPER001346_Alarm_Base_Alarm_CleanCupFuncFail_Text      "%s Clean Cup Func Fail(Current : %d)."

*/
////////////////////////////////////////////////////////
// 控制器識別碼
//
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

////////////////////////////////////////////////////////
//
//

/*enum enmTrackWaferLoadUnloadMode
{
    // 出：A1，回：A1
    LOADUNLOADMODE_ALoadAUnload  = 0,

    // 出：A25，回：A25
    LOADUNLOADMODE_ALoadRAUnload,

    // 出：A1，回：B1
    LOADUNLOADMODE_ALoadBUnload,

    // 出：A1，回：B25
    LOADUNLOADMODE_ALoadBUnloadR,

    // 出：A25，回：B25
    LOADUNLOADMODE_ALoadRBUnload,

    // 出：A25，回：B1
    LOADUNLOADMODE_ALoadRBUnloadR,
};


#if 0
enum enmTrackAutoRunStopMode
{
    // 減速停止(做完機台中所有執行中的wafer)
    AUTORUNSTOPMODE_SlowDown,

    // 急停(馬上停下來)
    AUTORUNSTOPMODE_EMS,

    // cassette 減速停止(做完目前正在做的cassette)
    AUTORUNSTOPMODE_CassetteSlowDown,
};
#endif


////////////////////////////////////////////////////////
//
//
enum enmTrackAutoRunState
{
    AUTORUNSTATE_Idle,
    AUTORUNSTATE_Running,
    AUTORUNSTATE_RunningSDStop,
#ifdef __SUPPORT_CassetteSDStop
    AUTORUNSTATE_RunningCassetteSDStop,
#endif
    AUTORUNSTATE_RunningEMS,
    AUTORUNSTATE_Suspended,
};


////////////////////////////////////////////////////////
//
//
namespace nspWaferType
{

#define WAFERSHAPE_Circle           0
#define WAFERSHAPE_Rectangle        1
#define WAFERSHAPE_Polygon          2


    struct strWaferType
    {
        GUID    Id;
        CString Name;
        CString ShortName;
        CString Description;
        int     Shape;
        double  WidthMM;
        double  HeightMM;
    };


    extern  int     WaferTypeCount();
    extern  bool    WaferTypeAt(int AIdx, OUT strWaferType *AResult);
    extern  bool    WaferTypeOf(const GUID &AId, OUT strWaferType *AResult);
    extern  CString WaferTypeTextAt(int AIdx, bool AIsShortFormat = false);
    extern  CString WaferTypeTextOf(const GUID &AId, bool AIsShortFormat = false);
    extern  GUID    WaferTypeIdAt(int AIdx);
    extern  int     WaferTypeIdxOf(const GUID &AId);
}


////////////////////////////////////////////////////////
//
//
namespace nspTrackPR
{
    extern  CString TrackPRTextOf(const GUID &AId, bool AIsShortFormat);
    extern  CString TrackPRTextAt(int AIdx, bool AIsShortFormat);
    extern  GUID    TrackPRIdAt(int AIdx);
    extern  int     TrackPRIdxOf(const GUID &AId);
    extern  int     TrackPRCount();
}


////////////////////////////////////////////////////////
//
//
namespace nspTrackER
{
    extern  CString TrackERTextOf(const GUID &AId, bool AIsShortFormat);
    extern  CString TrackERTextAt(int AIdx, bool AIsShortFormat);
    extern  GUID    TrackERIdAt(int AIdx);
    extern  int     TrackERIdxOf(const GUID &AId);
    extern  int     TrackERCount();
}


////////////////////////////////////////////////////////
//
//
namespace nspTrackBR
{
    extern  CString TrackBRTextOf(const GUID &AId, bool AIsShortFormat);
    extern  CString TrackBRTextAt(int AIdx, bool AIsShortFormat);
    extern  GUID    TrackBRIdAt(int AIdx);
    extern  int     TrackBRIdxOf(const GUID &AId);
    extern  int     TrackBRCount();
}


////////////////////////////////////////////////////////
//
//
namespace nspTrackAgent
{
    extern  CString TrackAgentTextOf(const GUID &AId, bool AIsShortFormat);
    extern  CString TrackAgentTextAt(int AIdx, bool AIsShortFormat);
    extern  GUID    TrackAgentIdAt(int AIdx);
    extern  int     TrackAgentIdxOf(const GUID &AId);
    extern  int     TrackAgentCount();
}


////////////////////////////////////////////////////////
//
//
namespace nspTrackPLCModule
{
#define PLCMODULECODEGROUPNAME_Command          "Command"
#define PLCMODULECODEGROUPNAME_Status           "Status"
#define PLCMODULECODEGROUPNAME_Warning1         "Warning1"
#define PLCMODULECODEGROUPNAME_Warning2         "Warning2"
#define PLCMODULECODEGROUPNAME_Error1           "Error1"
#define PLCMODULECODEGROUPNAME_Error2           "Error2"
#define PLCMODULECODEGROUPNAME_SystemError      "SystemError"


    extern  CString TrackFormatPLCModuleText(LPCSTR AModuleName, LPCSTR AGroupName, DWORD ACode);
    extern  void    TrackSetPLCModuleTextFile(CYCMemIniFile *AFile);
}


////////////////////////////////////////////////////////
//
//
*/
//class CTrackTemperatureSetupDB;
//
//namespace nspTrackTemperatureSetup
//{
//    extern  void    TrackTemperatureSetupDBSaveToFile();
//
//    extern  CTrackTemperatureSetupDB&
//        /**/        TrackTemperatureSetupDB();
//
//}


////////////////////////////////////////////////////////
//
//
namespace nspTrack
{

	//#define SummaryEmpty()              m_Summary.Empty()
	//#define SummaryAppend               m_Summary.Append
	//#define SummaryAppendFormat         m_Summary.AppendFormat
	//#define SummaryFormat               m_Summary.Format
	//#define SummaryAppendChar           m_Summary.AppendChar
	//#define SummaryAssign(X)            (m_Summary = X)
	//#define CreateAssign(X)             m_##X = A##X
	//
	//
	extern  bool    TrackPublicInitialize();
	extern  void    TrackPublicFinalize();
	extern  CString TrackDirectoryOf(enmTrackDirectoryId AId);
	extern  CString YearMonthDay();    //add by Tom , 20150224 , 回傳今天的年月日
	extern  CString TrackFileNameOf(enmTrackFileId AId);
}
//
//
//    extern  bool    IsTrackSystemAlarm(BYTE ATestLevel);
//    extern  void    TrackQueryController(DWORD AId, CACController **AController);
//    extern  bool    IsTrackHWAutoMode();
//    extern  bool    IsTrackDoorOpened();
//    extern  bool    IsTrackAutoRunTerminated();
//
//    static  bool    m_IsRemoteMode;
//    extern  void    SetIsRemoteControlMode(bool ASetValue);
//    extern  bool    IsRemoteControlMode();
//
//    extern  LPCSTR  TrackFormatWaferLoadUnloadModeText(enmTrackWaferLoadUnloadMode AValue, bool AIsShortFormat);
//    
//    extern  enmSetOperationFlow ReadOperationFlowText(const char* AOperationFlowText);
//
//} // namespace nspTrack
//
//
//////////////////////////////////////////////////////////
////
////
//struct strTrackAgentPipeDefinition
//{
//    GUID        Id;
//    bool        IsEnabled;
//
//    // 吐液值與plc設定的的轉換常數
//    double      DispensePLCModuleValueConvertConst;
//
//    // 吐液值與時間的轉換常數
//    double      DispenseTimeMSecConvertConst;
//};
//
//
//
//////////////////////////////////////////////////////////
////
////
//struct strTrackFlowMeterData
//{
//    // 是否可是可使用的
//    bool        IsEnabled;
//
//    // 是否支援上下限設定 
//    bool        IsSupport2AlarmValue;   // add by Mike, 20141027
//
//    // 警報設定值
//    double      AlarmValue;
//
//    // 警報設定值1
//    double      Alarm1Value;            // add by Mike, 20141027
//
//    // 警報設定值2
//    double      Alarm2Value;            // add by Mike, 20141027
//
//    // 目前流量
//    double      CurrentFlow;
//};
//
//
//////////////////////////////////////////////////////////
////
////
//struct strTrackAgentDispenseData
//{
//    // 主要所在位置(0~)
//    int         Location;
//
//    // 次要所在位置(0~)
//    int         SubLocation;
//
//    // Agent Id
//    GUID        AgentId;
//
//    // 是否可是可使用的
//    bool        IsEnabled;
//
//    // 吐液量(手動模式操作)
//    double      DispenseCount;
//
//    // 吐液次數(手動模式操作)
//    int         DispenseTimes;
//
//    // 吐液值與plc設定的的轉換常數
//    double      DispenseHWModuleValueConvertConst;
//
//    // 吐液值與時間的轉換常數
//    double      DispenseTimeMSecConvertConst;
//
//    // 流量錶是否有配置
//    bool        IsFlowMeterEquipped;
//
//    // 流量錶的值
//    strTrackFlowMeterData
//        /**/    FlowMeterData;
//
//    // 是否支援 Fill On Function    // add by Mike, 20140516
//    bool        IsFillFuncSupport;
//
//    // 是否支援 Purge Function      // add by Mike, 20140516
//    bool        IsPurgeFuncSupport;
//
//    // 是否支援 On Function         // add by Mike, 20140516
//    bool        IsOnFuncSupport;
//
//    // 是否支援 Auto Function       // add by Mike, 20140516
//	bool        IsAutoFuncSupport;
//
//	// AgentType:atRinse是否支援預吐功能  //add by Poni, 20141006
//	bool        IsPreAntiDryDisFuncSupport;
//};
//
//typedef std::deque<strTrackAgentDispenseData>   TTrackAgentDispenseDatas;
//
//
//struct strTrackFindAgentDispenseDataByLocation
//{
//    const int   Location;
//    const int   SubLocation;
//
//
//    strTrackFindAgentDispenseDataByLocation(int ALocation, int ASubLocation)
//        : Location(ALocation), SubLocation(ASubLocation)
//    {   }
//
//    inline bool operator()(const strTrackAgentDispenseData &AValue) const
//    { return AValue.Location == Location && AValue.SubLocation == SubLocation; }
//};
//
//
//struct strTrackFindAgentDispenseDataByAgentId
//{
//    const GUID &AgentId;
//
//
//    strTrackFindAgentDispenseDataByAgentId(const GUID &AAgentId) : AgentId(AAgentId)
//    {   }
//
//    inline bool operator()(const strTrackAgentDispenseData &ADef) const
//    { return !!(AgentId == ADef.AgentId); }
//};



////////////////////////////////////////////////////////
//
//
//typedef std::deque<CACBaseTemperatureController *>  TACBaseTemperatureControllerDeque;
//
//#if 0
//////////////////////////////////////////////////////////
////
////
//#define   VIRTUAL_ITrackEquippedFlowMeter_IsFlowMeterEnabled()              virtual bool IsFlowMeterEnabled(int AFMT) const
//#define IMPLEMENT_ITrackEquippedFlowMeter_IsFlowMeterEnabled(AClass)        bool AClass::IsFlowMeterEnabled(int AFMT) const
//#define  OVERRIDE_ITrackEquippedFlowMeter_IsFlowMeterEnabled                VIRTUAL_ITrackEquippedFlowMeter_IsFlowMeterEnabled
//
//#define   VIRTUAL_ITrackEquippedFlowMeter_EnableFlowMeter()                 virtual LRESULT EnableFlowMeter(int AFMT, bool AValue, CYCCompletionObject *ACompletionObject)
//#define IMPLEMENT_ITrackEquippedFlowMeter_EnableFlowMeter(AClass)           LRESULT AClass::EnableFlowMeter(int AFMT, bool AValue, CYCCompletionObject *ACompletionObject)
//#define  OVERRIDE_ITrackEquippedFlowMeter_EnableFlowMeter                   VIRTUAL_ITrackEquippedFlowMeter_EnableFlowMeter
//
//#define   VIRTUAL_ITrackEquippedFlowMeter_FlowMeterAlarmValue()             virtual double FlowMeterAlarmValue(int AFMT) const
//#define IMPLEMENT_ITrackEquippedFlowMeter_FlowMeterAlarmValue(AClass)       double AClass::FlowMeterAlarmValue(int AFMT) const
//#define  OVERRIDE_ITrackEquippedFlowMeter_FlowMeterAlarmValue               VIRTUAL_ITrackEquippedFlowMeter_FlowMeterAlarmValue
//
//#define   VIRTUAL_ITrackEquippedFlowMeter_SetFlowMeterAlarmValue()          virtual LRESULT SetFlowMeterAlarmValue(int AFMT, WORD AValue, CYCCompletionObject *ACompletionObject)
//#define IMPLEMENT_ITrackEquippedFlowMeter_SetFlowMeterAlarmValue(AClass)    LRESULT AClass::SetFlowMeterAlarmValue(int AFMT, WORD AValue, CYCCompletionObject *ACompletionObject)
//#define  OVERRIDE_ITrackEquippedFlowMeter_SetFlowMeterAlarmValue            VIRTUAL_ITrackEquippedFlowMeter_SetFlowMeterAlarmValue
//
//#define   VIRTUAL_ITrackEquippedFlowMeter_FlowMeterCurrentFlow()            virtual double FlowMeterCurrentFlow(int AFMT) const
//#define IMPLEMENT_ITrackEquippedFlowMeter_FlowMeterCurrentFlow(AClass)      double AClass::FlowMeterCurrentFlow(int AFMT) const
//#define  OVERRIDE_ITrackEquippedFlowMeter_FlowMeterCurrentFlow              VIRTUAL_ITrackEquippedFlowMeter_FlowMeterCurrentFlow
//
//
//__interface ITrackEquippedFlowMeter
//{
//public:
//    VIRTUAL_ITrackEquippedFlowMeter_IsFlowMeterEnabled()    = NULL;
//    VIRTUAL_ITrackEquippedFlowMeter_EnableFlowMeter()       = NULL;
//    VIRTUAL_ITrackEquippedFlowMeter_FlowMeterAlarmValue()   = NULL;
//    VIRTUAL_ITrackEquippedFlowMeter_SetFlowMeterAlarmValue()= NULL;
//    VIRTUAL_ITrackEquippedFlowMeter_FlowMeterCurrentFlow()  = NULL;
//
//};
//#endif
//
//
//////////////////////////////////////////////////////////
////
////
//typedef std::map<CString, CString, strYCStrLessNoCase>        TTrackWaferExtInfos;
//
//
//////////////////////////////////////////////////////////
////
////
//#define ROBOTENDEFFECTOR_Lower              ROBOTENDEFFECTOR_A
//#define ROBOTENDEFFECTOR_Upper              ROBOTENDEFFECTOR_B
//
//
//__interface ITrackObject
//{
//public:
//    STDMETHOD_(CObject* , GetThis        )() PURE;
//};
//
//
//enum enmTempateratureSelectedMode
//{
//    tsmAutoMode = 0,
//    tsmAssignMode,
//};
//
