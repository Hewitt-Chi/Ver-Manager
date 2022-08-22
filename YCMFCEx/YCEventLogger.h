#pragma once

#include <afxmt.h>

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


/**************************************************************************
class CYCEventLogger

�γ~�G�ΥH�N�T���g�J��log�ɤ��C



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


    // �O�_�}�ҤF
    bool    IsOpened() const;
    bool    Open();
    void    Close();

protected:
    CCriticalSection    m_Locker;


    // �ѥ~�ɩI�s�A�N�T���g�Jbuffer��
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


    // �Ѱ�����I�s�A��buffer�����T��g�X
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


    // �Ĥ@���ɮת��W�r(Log���ɮצW�r�|�Ѧ��o�i�A
    // �Ҧp�GFirstFileName1.log, FirstFileName2.log, FirstFileName3.log ...)
    LPCSTR  FirstFileName();
    void    SetFirstFileName(LPCSTR AValue);


    // �ɮ״`���ϥΪ��ƶq
    // �p�G== INFINITE�A�h�H�ǦC�覡���U�Ӥ��`��
    // �D�n�v�T���̫�(�s)�@���ɮצW��
    // �p��INFINITE�A�̫�(�s)�@���ɮצW�٬�FirstFileName(n).log
    // �_�h��FirstFileName.log
    //
    DWORD   FileCycleCount() const;
    void    SetFileCycleCount(DWORD AValue);


    // �ɮ׳̤j�e�q
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

    // m_FileCycleCount == INFINITE��ܤ��`���@���g�U�h
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
    BYTE    m_LogLevel; // 0~9 ��n�g�J��log��level�j��o�ӭȮɤ~�u���g�J
    //
    // Properties
    /////////////////////////////
};
//
// CYCEventLogger
////////////////////////////////////////////////////////////////////////////////////
