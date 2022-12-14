#include "stdafx.h"


#include "DeveloperPublicDefine.h"



#pragma comment(lib, "Version.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*BEGIN_ALARMTEXT_REGISTER(TrackSystem)

ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PlaceStandbyFail                       )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PrePlaceFail                           )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PlaceFail                              )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PostPlaceFail                          )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PickStandbyFail                        )

ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PrePickFail                            )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PickFail                               )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PostPickFail                           )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_WaferExists                            )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_WaferNotExists                         )

ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PrePlaceTimeout                        )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PrePickTimeout                         )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_StillInProcessing                      )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PickCancel                             )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_PlaceCancel                            )

ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_IsOccupied                             )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_WaferStateIsNotValid                   )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_SetCompatibleWaferTypeFail             )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_WaferTypeIsIncompatible                )
ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_InteractivePlaceFail                   )

ALARMTEXT_REGISTER_ENTRY_C(WAFERHOLDER_Alarm_InteractivePickFail                    )

//====================================== PLCModule
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_ReadDataFail                             )
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_StatusFail                               )
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_ReadWarning2Fail                         )
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_ReadError1Fail                           )
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_ReadError2Fail                           )

ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_WriteDataFail                            )
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_WriteCommandFail                         )
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_ThrowWarning2                            )
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_ThrowError1                              )
ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_ThrowError2                              )

ALARMTEXT_REGISTER_ENTRY_C(PLCMODULE_Alarm_ThrowSystemError                         )

//====================================== Process Station
ALARMTEXT_REGISTER_ENTRY_C(PROCESSSTATION_Alarm_ProcessFail                         )
ALARMTEXT_REGISTER_ENTRY_C(PROCESSSTATION_Alarm_ProcessTimeout                      )
ALARMTEXT_REGISTER_ENTRY_C(PROCESSSTATION_Alarm_WaferStateCannotProcess             )
ALARMTEXT_REGISTER_ENTRY_C(PROCESSSTATION_Alarm_WaferStartProcessFail               )
ALARMTEXT_REGISTER_ENTRY_C(PROCESSSTATION_Alarm_WaferIsNotExists                    )

ALARMTEXT_REGISTER_ENTRY_C(PROCESSSTATION_Alarm_WaferRecipeNotCompatible            )

//====================================== Loader/Unloader
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_CassetteHasBeenSet                  )
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_CassetteNotExists                   )
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_ProcessingCassetteDisappear         )
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_UnloaderCassetteIsNotFound          )

#if 0
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_LoadWaferFail                       )
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_UnloadWaferFail                     )
#endif

ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_SlotIsOccupied                      )
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_LoaderUnloaderCassetteSizeNotTheSame)
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_NotOwnWafer                         )
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_WaferSizeIsNotCompatible            )

ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_SlotIdxIsNotValid                   )
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_SlotIdxIsOutOfRange                 )
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_LoaderStatusFailOnPrePick                 )         //add by Tom , 20150515
ALARMTEXT_REGISTER_ENTRY_C(LOADERUNLOADER_Alarm_LoaderStatusFailOnPrePlace                 )         //add by Tom , 20150515

//====================================== Wafer mover
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_PickFail                                )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_PlaceFail                               )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_1StepPickFail                           )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_1StepPlaceFail                          )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_2StepPickFail                           )

ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_2StepPlaceFail                          )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_ExchangeFail                            )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_LoadFail                                )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_UnloadFail                              )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_IncorrectWaferHolder                    )

ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_IncorrectRobotTarget                    )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_NoWaferToPick                           )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_NoWaferToPlace                          )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_TargetIsOccupied                        )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_NoEmptyRobotEndeffector                 )

ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_TargetIsNotProcessStation               )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_TargetIsNotLoader                       )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_TargetIsNotUnloader                     )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_TargetIsNotLoaderOrUnloader             )
ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_RobotUnloadingInfoIsInvalid             )

ALARMTEXT_REGISTER_ENTRY_C(WAFERMOVER_Alarm_WaferIsNotOnRobotEndeffector            )

//====================================== Auto runner
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_NextStepFail                            )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_AnalyzeNextStepFail                     )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_AutoTrackIsNoClear                      )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_PrealignerIsNoClear                     )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_NextRunFail                             )

ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_LoadWaferFail                           )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_UnloadWaferFail                         )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_ClearWafersFail                         )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_MoveWaferFail                           )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_SetTemperatureSetupFail                 )

ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_SetTemperatureSVFail                    )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_SetTemperaturePVOSFail                  )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_SetTemperatureAlarmRangeFail            )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_RecipeCannotRunInSystem                 )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_SystemIsBlocked                         )
ALARMTEXT_REGISTER_ENTRY_C(AUTORUNNER_Alarm_SetupHPTemperatureFail                  )

END_ALARMTEXT_REGISTER()
*/



    struct strDefinition
    {
        GUID    Id;
        CString Name;
        CString ShortName;
    

    typedef std::map<CYCGUID, strDefinition>  TDefinitions;


    //==============================
    TDefinitions    m_Definitions;

	};


//================================= PR function
/*namespace nspTrackPR
{
    //=================================
    CTrackAgentDefinition&
        /**///Definition()
    //{
     //   static CTrackAgentDefinition   LDefinition;

      //  return LDefinition;
    //}


    //=================================
  /*  bool    TrackPRInitialize()
    {
        return Definition().Initialize(nspTrack::TrackDirectoryOf(DID_Config) + "\\PR.def", "PR");
    }

    CString TrackPRTextOf(const GUID &AId, bool AIsShortFormat)
    {
        return Definition().AgentTextOf(AId, AIsShortFormat);
    }

    CString TrackPRTextAt(int AIdx, bool AIsShortFormat)
    {
        return Definition().AgentTextAt(AIdx, AIsShortFormat);
    }

    GUID    TrackPRIdAt(int AIdx)
    {
        return Definition().AgentIdAt(AIdx);
    }

    int     TrackPRIdxOf(const GUID &AId)
    {
        return Definition().AgentIdxOf(AId);
    }

    int     TrackPRCount()
    {
        return Definition().AgentCount();
    }
}

*/
//================================= ER function
//namespace nspTrackER
//{
    //=================================
  //  CTrackAgentDefinition&
        /**///Definition()
    //{
     //   static CTrackAgentDefinition   LDefinition;

     //   return LDefinition;
   // }


    //=================================
//    bool    TrackERInitialize()
//    {
//        return Definition().Initialize(nspTrack::TrackDirectoryOf(DID_Config) + "\\ER.def", "ER");
//    }
//
//    CString TrackERTextOf(const GUID &AId, bool AIsShortFormat)
//    {
//        return Definition().AgentTextOf(AId, AIsShortFormat);
//    }
//
//    CString TrackERTextAt(int AIdx, bool AIsShortFormat)
//    {
//        return Definition().AgentTextAt(AIdx, AIsShortFormat);
//    }
//
//    GUID    TrackERIdAt(int AIdx)
//    {
//        return Definition().AgentIdAt(AIdx);
//    }
//
//    int     TrackERIdxOf(const GUID &AId)
//    {
//        return Definition().AgentIdxOf(AId);
//    }
//
//    int     TrackERCount()
//    {
//        return Definition().AgentCount();
//    }
//    //
//    // ER function
//    ///////////////////////////////
//}
//
//
////================================= BR function
//namespace nspTrackBR
//{
//    //=================================
//    CTrackAgentDefinition&
//        /**/Definition()
//    {
//        static CTrackAgentDefinition   LDefinition;
//
//        return LDefinition;
//    }
//
//
//    //=================================
//    bool    TrackBRInitialize()
//    {
//        return Definition().Initialize(nspTrack::TrackDirectoryOf(DID_Config) + "\\BR.def", "BR");
//    }
//
//    CString TrackBRTextOf(const GUID &AId, bool AIsShortFormat)
//    {
//        return Definition().AgentTextOf(AId, AIsShortFormat);
//    }
//
//    CString TrackBRTextAt(int AIdx, bool AIsShortFormat)
//    {
//        return Definition().AgentTextAt(AIdx, AIsShortFormat);
//    }
//
//    GUID    TrackBRIdAt(int AIdx)
//    {
//        return Definition().AgentIdAt(AIdx);
//    }
//
//    int     TrackBRIdxOf(const GUID &AId)
//    {
//        return Definition().AgentIdxOf(AId);
//    }
//
//    int     TrackBRCount()
//    {
//        return Definition().AgentCount();
//    }
//}
//
//
////================================= Agent function
//namespace nspTrackAgent
//{
//    //=================================
//    CTrackAgentDefinition&
//        /**/AgentDefinition()
//    {
//        static CTrackAgentDefinition   LDefinition;
//
//        return LDefinition;
//    }
//
//
//    //=================================
//    bool    TrackAgentInitialize()
//    {
//        return AgentDefinition().Initialize(nspTrack::TrackFileNameOf(FID_AgentDef), "Agent");
//    }
//
//    CString TrackAgentTextOf(const GUID &AId, bool AIsShortFormat)
//    {
//        return AgentDefinition().AgentTextOf(AId, AIsShortFormat);
//    }
//
//    CString TrackAgentTextAt(int AIdx, bool AIsShortFormat)
//    {
//        return AgentDefinition().AgentTextAt(AIdx, AIsShortFormat);
//    }
//
//    GUID    TrackAgentIdAt(int AIdx)
//    {
//        return AgentDefinition().AgentIdAt(AIdx);
//    }
//
//    int     TrackAgentIdxOf(const GUID &AId)
//    {
//        return AgentDefinition().AgentIdxOf(AId);
//    }
//
//    int     TrackAgentCount()
//    {
//        return AgentDefinition().AgentCount();
//    }
//}


////================================= PLC Module Functions
//namespace nspTrackPLCModule
//{
//    //=================================
//    struct strTrackPLCModuleErrorFile
//    {
//        CYCMemIniFile       *File;
//        CCriticalSection    Locker;
//
//        strTrackPLCModuleErrorFile() : File(NULL)
//        {   }
//    };
//
//
//    //=================================
//    strTrackPLCModuleErrorFile&
//        /**/TrackPLCModuleErrorFile()
//    {
//        static strTrackPLCModuleErrorFile   LFile;
//
//        return LFile;
//    }
//
//    //=================================
//    CString TrackFormatPLCModuleText(LPCSTR AModuleName, LPCSTR AGroupName, DWORD ACode)
//    {
//        strTrackPLCModuleErrorFile
//            /**/        &LFile = TrackPLCModuleErrorFile();
//
//        CSingleLock     LLocker(&LFile.Locker, TRUE);
//        CYCMemIniFile   *LTextFile = LFile.File;
//        CString         LRslt;
//
//        if (LTextFile)
//        {
//#define __NextSection           "NextSection"
//
//            bool                    LIsContinue = true;
//            std::deque<CString>     LBrowseSectionNames;
//            CString                 LSectionName;
//            CString                 LValueName;
//
//
//            LSectionName.Format("%s_%s", AModuleName, AGroupName);
//            LValueName.Format("%u", ACode);
//
//            while (LIsContinue)
//            {
//                if (std::find(LBrowseSectionNames.begin(), LBrowseSectionNames.end(), LSectionName) == LBrowseSectionNames.end())
//                {
//                    LBrowseSectionNames.push_back(LSectionName);
//
//
//                    if (LTextFile->IsValueNameExists(LSectionName, LValueName))
//                    {
//                        // 在指定section中有指定的value值
//                        LRslt       = LTextFile->ReadString(LSectionName, LValueName, NULL, false);
//                        LIsContinue = false;
//                    }
//                    else if (LTextFile->IsValueNameExists(LSectionName, __NextSection))
//
//                    {
//                        // 在指定section中沒有指定的value值，所以找下一個相關的section
//                        LSectionName = LTextFile->ReadString(LSectionName, __NextSection, NULL, false);
//                    }
//                    else
//                    {
//                        // 找不到任何東西，結束
//                        LIsContinue = false;
//                    }
//                }
//                else
//                {
//                    // 指定的section之前已找過了(循環回頭了)
//                    LIsContinue = false;
//                }
//            }
//        }
//
//        if (LRslt.IsEmpty())
//            LRslt.Format("[%s][%s][%u][No message]", AModuleName, AGroupName, ACode);
//
//        return LRslt;
//
//#undef __NextSection
//    }
//
//    void    TrackSetPLCModuleTextFile(CYCMemIniFile *AFile)
//    {
//        strTrackPLCModuleErrorFile
//            /**/        &LFile = TrackPLCModuleErrorFile();
//
//        CSingleLock     LLocker(&LFile.Locker, TRUE);
//
//        LFile.File = AFile;
//    }
//}
//
//
////================================= Temperature Setup Function
//namespace nspTrackTemperatureSetup
//{
//#define __TemperatureSetupDBFileName        nspTrack::TrackDirectoryOf(DID_AppData) + "\\TemperatureSetup.db"
//
//
//    //=================================
//    CTrackTemperatureSetupDB&
//        /**/TrackTemperatureSetupDB()
//    {
//        static CTrackTemperatureSetupDB    LTemperatureSetupDB;
//
//        return LTemperatureSetupDB;
//    }
//
//
//    //=================================
//    void    TrackTemperatureSetupDBInitialize()
//    {
//        CTrackTemperatureSetupDB    &LTemperatureSetupDB = TrackTemperatureSetupDB();
//
//        const CString LFileName = __TemperatureSetupDBFileName;
//
//        CTrackTemperatureSetupDB    *LDB = nspTrackTemperatureSetup::OpenFile(LFileName);
//
//        if (LDB)
//        {
//            LTemperatureSetupDB = *LDB;
//
//            delete LDB;
//        }
//    }
//
//    void    TrackTemperatureSetupDBSaveToFile()
//    {
//        nspTrackTemperatureSetup::SaveFile(__TemperatureSetupDBFileName, &TrackTemperatureSetupDB());
//    }
//
//
//#undef  __TemperatureSetupDBFileName
//}


//================================= Track Functions
namespace nspTrack
{
    //=================================
    std::map<enmTrackDirectoryId, CString>&
        /**/TrackDirectories()
    {
        static std::map<enmTrackDirectoryId, CString>  LTrackDirectories;

        return LTrackDirectories;
    }


    //=================================
    void    TrackInitDirectories()
    {
        std::map<enmTrackDirectoryId, CString>  &LDirectories = TrackDirectories();

        CHAR    LDirName[MAX_PATH + 1];

        GetModuleFileName(NULL, LDirName, sizeof(LDirName));
        PathRemoveFileSpec(LDirName);


        LDirectories[DID_AppDir]            = LDirName;
        LDirectories[DID_Config]            = CString(LDirName)     + "\\" + DID_Config_Text;
        LDirectories[DID_AppData]           = CString(LDirName)     + "\\" + DID_AppData_Text;
        LDirectories[DID_Recipe]            = CString(LDirName)     + "\\" + DID_Recipe_Text;
        LDirectories[DID_Log]               = CString(LDirName)     + "\\" + DID_Log_Text;
        LDirectories[DID_AutoRunAnalyzeLog] = LDirectories[DID_Log] + "\\" + DID_AutoRunAnalyzeLog_Text;
        LDirectories[DID_ProcessLog]        = CString(LDirName)     + "\\" + DID_ProcessLog_Text;
        LDirectories[DID_Temp]              = CString(LDirName)     + "\\" + DID_Temp_Text;
        LDirectories[DID_TestData]          = LDirectories[DID_Temp] + "\\" + DID_TestData_Text;
        LDirectories[DID_Alarm] =LDirectories[DID_Log]+ "\\" + DID_Alarm_Text;  //add by Tom , 20150224 
         LDirectories[DID_FDCLog]            = CString(LDirName)  + "\\" + DID_FDCLog_Text;
        CYCMemIniFile   LFile;

        LFile.Open(LDirectories[DID_Config] + "\\TrackPublicInit.ini");
        LFile.SetSectionName("Directories");

#define IniReadDir(X) \
    /**/    LDirectories[X] = YCRelativeFileNameToAbs(LFile.ReadString(#X, LDirectories[X], true)); \
    /**/                                                                                            \
    /**/    if (!PathFileExists(LDirectories[X]))                                                   \
    /**/        ::CreateDirectory(LDirectories[X], NULL);                                           \

        IniReadDir(DID_AppData);
        IniReadDir(DID_Recipe);
        IniReadDir(DID_Log);
        IniReadDir(DID_AutoRunAnalyzeLog);
        IniReadDir(DID_ProcessLog);
        IniReadDir(DID_Temp);
        IniReadDir(DID_TestData);
        IniReadDir(DID_Alarm);  //add by Tom , 20150224 
        IniReadDir(DID_FDCLog); 
#undef  IniReadDir

        YCRegisterDirectoryVar("AppDir"                 , TrackDirectoryOf(DID_AppDir));
        YCRegisterDirectoryVar("ConfigDir"              , TrackDirectoryOf(DID_Config));
        YCRegisterDirectoryVar("AppDataDir"             , TrackDirectoryOf(DID_AppData));
        YCRegisterDirectoryVar("RecipeDir"              , TrackDirectoryOf(DID_Recipe));
        YCRegisterDirectoryVar("LogDir"                 , TrackDirectoryOf(DID_Log));
        YCRegisterDirectoryVar("AutoRunAnalyzeLogDir"   , TrackDirectoryOf(DID_AutoRunAnalyzeLog));
        YCRegisterDirectoryVar("ProcessLogDir"          , TrackDirectoryOf(DID_ProcessLog));
        YCRegisterDirectoryVar("TempDir"                , TrackDirectoryOf(DID_Temp));
        YCRegisterDirectoryVar("TestDataDir"            , TrackDirectoryOf(DID_TestData));
        YCRegisterDirectoryVar("AlarmDir"            , TrackDirectoryOf(DID_Alarm));  //add by Tom , 20150224 
        YCRegisterDirectoryVar("FDCLog"                 , TrackDirectoryOf(DID_FDCLog));
    }

  


    CString TrackDirectoryOf(enmTrackDirectoryId AId)
    {
        std::map<enmTrackDirectoryId, CString>                  &LDirectories = TrackDirectories();
        std::map<enmTrackDirectoryId, CString>::const_iterator  LIter         = LDirectories.find(AId);

        if (LIter != LDirectories.end())
            return LIter->second;

        return "";
    }

    CString   YearMonthDay()  //add by Tom , 20150224
    {
        SYSTEMTIME  LST;
        GetLocalTime(&LST);
        CString LYearMonthDay="";
        LYearMonthDay.Format("%04u%02u%02u_" ,LST.wYear,LST.wMonth,LST.wDay);
        return LYearMonthDay ;
    }

    CString TrackFileNameOf(enmTrackFileId AId)
    {
        CHAR    LDirName[MAX_PATH + 1];

        GetModuleFileName(NULL, LDirName, sizeof(LDirName));

        switch (AId)
        {
        case FID_App                : return LDirName;
        case FID_System             : return TrackDirectoryOf(DID_Config)  + "\\" + FID_System_Text;
        case FID_HWConfig           : return TrackDirectoryOf(DID_Config)  + "\\" + FID_HWConfig_Text;
        case FID_SWConfig           : return TrackDirectoryOf(DID_AppData) + "\\" + FID_SWConfig_Text;
        case FID_PLCIODef           : return TrackDirectoryOf(DID_Config)  + "\\" + FID_PLCIODef_Text;
        case FID_WaferDef           : return TrackDirectoryOf(DID_Config)  + "\\" + FID_WaferDef_Text;
        case FID_PRDef              : return TrackDirectoryOf(DID_Config)  + "\\" + FID_PRDef_Text;
        case FID_ERDef              : return TrackDirectoryOf(DID_Config)  + "\\" + FID_ERDef_Text;
        case FID_BRDef              : return TrackDirectoryOf(DID_Config)  + "\\" + FID_BRDef_Text;
        case FID_AgentDef           : return TrackDirectoryOf(DID_Config)  + "\\" + FID_AgentDef_Text;
        case FID_InitMacro          : return TrackDirectoryOf(DID_Config)  + "\\" + FID_InitMacro_Text;
        case FID_PLCModuleText      : return TrackDirectoryOf(DID_Config)  + "\\" + FID_PLCModuleText_Text;
        case FID_PLCModuleTextZHTW  : return TrackDirectoryOf(DID_Config)  + "\\" + FID_PLCModuleTextZHTW_Text;
        case FID_Log                : return TrackDirectoryOf(DID_Log)     + "\\" + FID_Log_Text;
            //case FID_AlarmLog           : return TrackDirectoryOf(DID_Log)     + "\\" + FID_AlarmLog_Text;   //mark by Tom , 20150224
        //case FID_AlarmLog           : return TrackDirectoryOf(DID_Alarm)     +"\\" +YearMonthDay()+ FID_AlarmLog_Text;   //add by Tom , 20150224, Alarm以日期做儲存
        case FID_AlarmLog           : return TrackDirectoryOf(DID_Alarm)     +"\\" + FID_AlarmLog_Text;      //add by Tom , 20160802
        case FID_TrackFilter          : return TrackDirectoryOf(DID_Config)  + "\\" +FID_TrackFilter_Text ;  //add by Tom , 20140929
        case FID_AgentStatus          : return TrackDirectoryOf(DID_Config)  + "\\" +FID_AgentStatus_Text ;  //add by Tom , 20150417
        case FID_AlarmDayFile        : return TrackDirectoryOf(DID_AppData) +"\\" +FID_AlarmDayFile_Text ; 

        default                     : return "";
        }
    }

//    LPCSTR  TrackFormatWaferLoadUnloadModeText(enmTrackWaferLoadUnloadMode AValue, bool AIsShortFormat)
//    {
//        static const struct strData
//        {
//            enmTrackWaferLoadUnloadMode
//                /**/    Mode;
//
//            LPCSTR      Text;
//            LPCSTR      ShortText;
//        }
//        LDatas[] =
//        {
//            { LOADUNLOADMODE_ALoadAUnload   , "A load A unload"                 , "A load A unload"                 },
//            { LOADUNLOADMODE_ALoadRAUnload  , "A load A unload reverse"         , "A load A unload reverse"         },
//            { LOADUNLOADMODE_ALoadBUnload   , "A load B unload"                 , "A load B unload"                 },
//            { LOADUNLOADMODE_ALoadBUnloadR  , "A load B unload reverse"         , "A load B unload reverse"         },
//            { LOADUNLOADMODE_ALoadRBUnload  , "A load reverse B unload"         , "A load reverse B unload"         },
//            { LOADUNLOADMODE_ALoadRBUnloadR , "A load reverse B unload reverse" , "A load reverse B unload reverse" },
//            { LOADUNLOADMODE_ALoadAUnload   , NULL, NULL }
//        };
//
//        for (int I = 0; LDatas[I].Text; I ++)
//        {
//            if (LDatas[I].Mode == AValue)
//                return AIsShortFormat ? LDatas[I].ShortText : LDatas[I].Text;
//        }
//
//        return NULL;
//    }
//
//    //2014.12.15 設定操作流程，讀取文字
//    enmSetOperationFlow ReadOperationFlowText(const char* AOperationFlowText)
//    {
//#define MATCH(X) if (strcmp(AOperationFlowText, #X) == 0) return X 
//        MATCH(CIM);
//        MATCH(CIMDoubleCheckLotID);
//        MATCH(SECSGEM);
//        MATCH(CIM001125);               // ECN20160314MIKE01
//        return OperationFlow_count;
//#undef MATCH
//    }
//
} // namespace nspTrack


