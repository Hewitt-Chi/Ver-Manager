#pragma once

#include <afxmt.h>

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


/**************************************************************************
class CYCEventLogger

用途：用以將訊息寫入至log檔中。



**************************************************************************/


class CYCBaseLogger;


////////////////////////////////////////////////////////////////////////////////////
// CYCBaseLoggerThread
//
class CYCBaseLoggerThread : public CYCThread
{
    friend class CYCBaseLogger;

    DECLARE_DYNAMIC(CYCBaseLoggerThread)

public:
    CYCBaseLoggerThread();
    virtual ~CYCBaseLoggerThread();


    long Open(CYCBaseLogger *ALogger);
    long Close(CYCBaseLogger *ALogger);

protected:
    OVERRIDE_CYCThread_Execute();

private:
    struct strOpenCloseCmd
    {
        bool                IsOpen;
        CYCBaseLogger       *Logger;
        CYCCompletionHandle CompletionHandle;
    };


    std::deque<strOpenCloseCmd>     m_OpenCloseCmd;
    CEvent                          m_OpenCloseEvent;
    CCriticalSection                m_OpenCloseLocker;
    std::deque<CYCBaseLogger *>     m_OpenLoggers;
    LONG                            m_OpenCount;


    void MaintainOpenLoggers();
};
//
// CYCBaseLoggerThread
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
// CYCBaseLogger
//
#define   VIRTUAL_CYCBaseLogger_OnOpen()                    virtual bool OnOpen()
#define IMPLEMENT_CYCBaseLogger_OnOpen(AClass)              bool AClass::OnOpen()
#define  OVERRIDE_CYCBaseLogger_OnOpen                      VIRTUAL_CYCBaseLogger_OnOpen

#define   VIRTUAL_CYCBaseLogger_OnClose()                   virtual void OnClose()
#define IMPLEMENT_CYCBaseLogger_OnClose(AClass)             void AClass::OnClose()
#define  OVERRIDE_CYCBaseLogger_OnClose                     VIRTUAL_CYCBaseLogger_OnClose

#define   VIRTUAL_CYCBaseLogger_OnWriteToLog()              virtual void OnWriteToLog(LPCSTR AMsg)
#define IMPLEMENT_CYCBaseLogger_OnWriteToLog(AClass)        void AClass::OnWriteToLog(LPCSTR AMsg)
#define  OVERRIDE_CYCBaseLogger_OnWriteToLog                VIRTUAL_CYCBaseLogger_OnWriteToLog


class CYCBaseLogger : public CObject
{
    friend class CYCBaseLoggerThread;

    DECLARE_DYNAMIC(CYCBaseLogger)

public:

    CYCBaseLogger();
    virtual ~CYCBaseLogger(void);


    // 是否開啟了
    bool    IsOpened() const;
    bool    Open();
    void    Close();

protected:
    CCriticalSection    m_Locker;


    // 由外界呼叫，將訊息寫入buffer中
    void    WriteToBuffer(LPCSTR AMsg);


    VIRTUAL_CYCBaseLogger_OnOpen()       = NULL;
    VIRTUAL_CYCBaseLogger_OnClose()      = NULL;
    VIRTUAL_CYCBaseLogger_OnWriteToLog() = NULL;

private:
    static CYCBaseLoggerThread  *m_Thread;
    static LONG                 m_ThreadRefCount;


    /////////////////////////////
    // Work Data
    //
    bool                m_IsOpened;
    CString             *m_Buffer;
    CString             m_Buffer1;
    CString             m_Buffer2;
    CEvent              m_Event;
    //
    // Work Data
    /////////////////////////////


    // 由執行緒呼叫，把buffer中的訊邊寫出
    void    ThreadWriteToLog();

};
//
// CYCBaseLogger
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
// CYCBaseFileLogger
//
class CYCBaseFileLogger : public CYCBaseLogger
{

    DECLARE_DYNAMIC(CYCBaseFileLogger)

public:

    CYCBaseFileLogger();
    virtual ~CYCBaseFileLogger(void);


    // 第一個檔案的名字(Log的檔案名字會由此發展，
    // 例如：FirstFileName1.log, FirstFileName2.log, FirstFileName3.log ...)
    LPCSTR  FirstFileName();
    void    SetFirstFileName(LPCSTR AValue);


    // 檔案循環使用的數量
    // 如果== INFINITE，則以序列方式往下而不循環
    // 主要影響為最後(新)一個檔案名稱
    // 如為INFINITE，最後(新)一個檔案名稱為FirstFileName(n).log
    // 否則為FirstFileName.log
    //
    DWORD   FileCycleCount() const;
    void    SetFileCycleCount(DWORD AValue);


    // 檔案最大容量
    DWORD   MaxFileSize() const;
    void    SetMaxFileSize(DWORD AValue);


protected:

    OVERRIDE_CYCBaseLogger_OnOpen();
    OVERRIDE_CYCBaseLogger_OnClose();
    OVERRIDE_CYCBaseLogger_OnWriteToLog();

    void    WriteToFile(LPCSTR AMsg);

private:
    /////////////////////////////
    // Properties
    //
    CString     m_FirstFileName;

    // m_FileCycleCount == INFINITE表示不循環一直寫下去
    DWORD       m_FileCycleCount;
    DWORD       m_MaxFileSize;
    //
    // Properties
    /////////////////////////////


    /////////////////////////////
    // Work Data
    //
    DWORD       m_LogFileIdx;
    CFile       m_File;
    //
    // Work Data
    /////////////////////////////


    bool    PrivOpenFile(bool AIsOpenExist);
    void    PrivCloseFile(bool AIsNormalClose);
    void    PrivSeekOpenFileName(bool AIsNewFile, OUT CString &AFileName);
    void    PrivCheckFileSize();

};
//
// CYCBaseFileLogger
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
// CYCEventLogger
//
class CYCEventLogger : public CYCBaseFileLogger
{

    DECLARE_DYNAMIC(CYCEventLogger)

public:
    enum enmLogDir
    {
        ldNone      = 0,
        ldForeward  = 1,
        ldBackward  = -1
    };


    enum enmLogLevel
    {
        llMin = 0,

        llOperation1,
        llOperation2,
        llOperation3,
        llOperation4,

        llOperation9 = 7,
        llError,
        llAlarm,
    };

#define llMax           llAlarm
#define llOperation     llOperation1
#define llAll           llMin


    static LPCSTR FormatLogLevelText(int ALevel);
    static LPCSTR FormatLogDirText(int ADir);


    CYCEventLogger();
    virtual ~CYCEventLogger(void);


    // Log Level
    BYTE    LogLevel() const;
    void    SetLogLevel(BYTE AValue);


    void    Write(BYTE ALevel, LPCSTR AMsg);
    void    Write(BYTE ALevel, int ADir, LPCSTR AMsg);
    void    WriteFmt(BYTE ALevel, LPCSTR AFmt, ...);
    void    WriteFmt(BYTE ALevel, int ADir, LPCSTR AFmt, ...);
    void    WriteFmtV(BYTE ALevel, LPCSTR AFmt, va_list AArgs);
    void    WriteFmtV(BYTE ALevel, int ADir, LPCSTR AFmt, va_list AArgs);
	void	WriteAlarmDayFile(CString AFilePatch , int AIndex ,CString AStr);  //add by Tom , 20150711


private:
    /////////////////////////////
    // Properties
    //
    BYTE    m_LogLevel; // 0~9 當要寫入的log之level大於這個值時才真的寫入
    //
    // Properties
    /////////////////////////////
};
//
// CYCEventLogger
////////////////////////////////////////////////////////////////////////////////////
