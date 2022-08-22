#include "StdAfx.h"


#include "YCObject.h"
#include "YCCompletionObject.h"
#include "YCThread.h"


#include "YCEventLogger.h"


#include "YCUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define __LineEnd       "\r\n"


////////////////////////////////////////////////////////////////////////////////////
// CYCBaseLoggerThread
//
IMPLEMENT_DYNAMIC(CYCBaseLoggerThread, CYCThread)


CYCBaseLoggerThread::CYCBaseLoggerThread()
: CYCThread()
, m_OpenCount(0)
{
    TRACE("CYCBaseLoggerThread::CYCBaseLoggerThread()\n");
}

CYCBaseLoggerThread::~CYCBaseLoggerThread()
{
    TRACE("CYCBaseLoggerThread::~CYCBaseLoggerThread()\n");
}

long CYCBaseLoggerThread::Open(CYCBaseLogger *ALogger)
{
    CSingleLock LLocker(&m_OpenCloseLocker, TRUE);

    strOpenCloseCmd     LCmd;

    LCmd.IsOpen = true;
    LCmd.Logger = ALogger;

    m_OpenCloseCmd.push_back(LCmd);
    m_OpenCloseEvent.SetEvent();

    return InterlockedIncrement(&m_OpenCount);
}

long CYCBaseLoggerThread::Close(CYCBaseLogger *ALogger)
{
    CSingleLock LLocker(&m_OpenCloseLocker, TRUE);

    strOpenCloseCmd     LCmd;
    DEFINE_NEW_CompletionHandle();

    LCmd.IsOpen = false;
    LCmd.Logger = ALogger;
    LCmd.CompletionHandle = LCompletionHandle;

    m_OpenCloseCmd.push_back(LCmd);
    m_OpenCloseEvent.SetEvent();
    LLocker.Unlock();

    LCompletionHandle->WaitForCompletion(0);

    return InterlockedDecrement(&m_OpenCount);
}

IMPLEMENT_CYCThread_Execute(CYCBaseLoggerThread)
{
    TRACE("---->CYCBaseLoggerThread::Execute().\n");

    SetThreadPriority(ThreadHandle(), THREAD_PRIORITY_LOWEST);

    while (!IsTerminated())
    {
        HANDLE  LWaitingHandles[32];

        LWaitingHandles[0] = m_OpenCloseEvent;

        HANDLE  *LWaitingHandle = LWaitingHandles + 1;

        for (std::deque<CYCBaseLogger *>::iterator  LIter = m_OpenLoggers.begin();
            LIter != m_OpenLoggers.end(); LIter ++, LWaitingHandle ++)
        {
            *LWaitingHandle = (*LIter)->m_Event;
        }

        const int LWaitingIdx = WaitForMultipleObjects(1 + static_cast<DWORD>(m_OpenLoggers.size()), LWaitingHandles, FALSE, INFINITE);

        if (LWaitingIdx == WAIT_OBJECT_0)
        {
            MaintainOpenLoggers();
        }
        else if (LWaitingIdx > WAIT_OBJECT_0 && LWaitingIdx < 1 + static_cast<int>(m_OpenLoggers.size()))
        {
            m_OpenLoggers[LWaitingIdx - WAIT_OBJECT_0 - 1]->ThreadWriteToLog();
        }
        else
        {
            TRACE("CYCBaseLoggerThread::WaitForMultipleObjects() out of range.\n");
        }

        if (m_OpenLoggers.size() == 0)
            Terminate();
    }

    TRACE("<----CYCBaseLoggerThread::Execute().\n");

    return 0;
}

void CYCBaseLoggerThread::MaintainOpenLoggers()
{
    for (bool LIsFinish = false; !LIsFinish; )
    {
        CSingleLock LLocker(&m_OpenCloseLocker, TRUE);

        if (m_OpenCloseCmd.size() > 0)
        {
            strOpenCloseCmd LCmd = m_OpenCloseCmd.front();

            m_OpenCloseCmd.pop_front();
            LLocker.Unlock();

            if (LCmd.IsOpen)
            {
                if (std::find(m_OpenLoggers.begin(), m_OpenLoggers.end(), LCmd.Logger) == m_OpenLoggers.end())
                {
                    m_OpenLoggers.push_back(LCmd.Logger);
                    LCmd.Logger->OnOpen();

                    TRACE("Open a logger. Total Loggers %d\n", m_OpenLoggers.size());
                }
            }
            else
            {
                std::deque<CYCBaseLogger *>::iterator  LIter = std::find(m_OpenLoggers.begin(), m_OpenLoggers.end(), LCmd.Logger);

                if (LIter != m_OpenLoggers.end())
                {
                    m_OpenLoggers.erase(LIter);

                    LCmd.Logger->ThreadWriteToLog();
                    LCmd.Logger->OnClose();

                    TRACE("Close a logger. Remaind loggers %d\n", m_OpenLoggers.size());
                }

                if (LCmd.CompletionHandle.IsNotNull())
                    LCmd.CompletionHandle->Complete(0);
            }
        }
        else
        {
            LIsFinish = true;
        }
    }
}
//
// CYCBaseLoggerThread
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
//CYCEventLogger
//
IMPLEMENT_DYNAMIC(CYCBaseLogger, CObject)


CYCBaseLoggerThread *CYCBaseLogger::m_Thread = NULL;
LONG                CYCBaseLogger::m_ThreadRefCount = 0;


CYCBaseLogger::CYCBaseLogger()
: CObject()
, m_IsOpened(false)
, m_Buffer(&m_Buffer1)
{
    if (InterlockedIncrement(&m_ThreadRefCount) == 1)
    {
        // 第一個被立的logger必須建立工作執行緒
        CYCBaseLoggerThread *LThrd = new CYCBaseLoggerThread();

        // 確認m_Thread是null，並把建立的執行緒置入
        while (InterlockedCompareExchangePointer((PVOID *)&m_Thread, LThrd, NULL) != NULL)
            SwitchToThread();
    }
    else
    {
        Sleep(10);
    }
}

CYCBaseLogger::~CYCBaseLogger(void)
{
    Close();

    CYCBaseLoggerThread    *LThrd = m_Thread;

    if (InterlockedDecrement(&m_ThreadRefCount) == 0)
    {
        if (InterlockedCompareExchangePointer((PVOID *)&m_Thread, NULL, LThrd) == LThrd)
        {
            delete LThrd;
        }
        else
        {
            ASSERT(FALSE);
        }
    }
}

bool CYCBaseLogger::IsOpened() const
{
    return m_IsOpened;
}

bool CYCBaseLogger::Open()
{
    ASSERT(m_Thread);

    CSingleLock     LLocker(&m_Locker, TRUE);

    //ASSERT(!m_IsOpened);

    if (!m_IsOpened)
    {
        // Create the second thread
        if (m_Thread->Open(this) == 1)
            m_Thread->Create("YCEventLoggerThread", false);

        m_IsOpened = true;

        Sleep(1);

        return true;
    }

    return false;
}

void CYCBaseLogger::Close()
{
    ASSERT(m_Thread);

    CSingleLock     LLocker(&m_Locker, TRUE);

    if (m_IsOpened)
    {
        m_IsOpened = false;

        LLocker.Unlock();

        if (m_Thread->Close(this) == 0)
            m_Thread->Delete();

        m_Buffer1.Empty();
        m_Buffer2.Empty();
    }
}

void CYCBaseLogger::WriteToBuffer(LPCSTR AMsg)
{
    CSingleLock LLocker(&m_Locker, TRUE);

    if (m_IsOpened)
    {
        m_Buffer->AppendFormat("%s%s", AMsg, __LineEnd);

        m_Event.SetEvent();
    }
}

void CYCBaseLogger::ThreadWriteToLog()
{
    CSingleLock LLocker(&m_Locker, TRUE);

    try
    {
        CString *LBuffer = m_Buffer;

        // 把Buffer中的資料讀進來
        m_Buffer = ((m_Buffer == &m_Buffer1) ? &m_Buffer2 : &m_Buffer1);

        LLocker.Unlock();

        OnWriteToLog(*LBuffer);

        LBuffer->Empty();
    }
    catch (...)
    {
        TRACE("Fail log.\n");
    }
}
//
//CYCBaseLogger
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
//CYCBaseFileLogger
//
IMPLEMENT_DYNAMIC(CYCBaseFileLogger, CYCBaseLogger)


CYCBaseFileLogger::CYCBaseFileLogger()
: CYCBaseLogger()
, m_FirstFileName("")
, m_FileCycleCount(1)
, m_MaxFileSize(8 * 1024 * 1024)
, m_LogFileIdx(0)
{
}

CYCBaseFileLogger::~CYCBaseFileLogger(void)
{
    Close();
}

IMPLEMENT_CYCBaseLogger_OnOpen(CYCBaseFileLogger)
{
    return PrivOpenFile(true);
}

IMPLEMENT_CYCBaseLogger_OnClose(CYCBaseFileLogger)
{
    return PrivCloseFile(true);
}

IMPLEMENT_CYCBaseLogger_OnWriteToLog(CYCBaseFileLogger)
{
    try
    {
        CString LBuffer(AMsg);

        if (m_FileCycleCount == 0)
        {
            m_File.Write(LBuffer.GetBuffer(), LBuffer.GetLength());
        }
        else
        {
            PrivCheckFileSize();

            DWORD LCurrentFileSize = ::GetFileSize(m_File.m_hFile, NULL);
            DWORD LFileRemainderCount     = m_MaxFileSize - LCurrentFileSize;

            if (static_cast<int>(LFileRemainderCount) >= LBuffer.GetLength())
            {
                m_File.Write(LBuffer.GetBuffer(), LBuffer.GetLength());
            }
            else
            {
                LPCSTR  LStrBegin = LBuffer.GetBuffer();
                LPCSTR  LStrEnd   = LStrBegin;

                // 把字串分割以符合最接近設定的案大小
                while (LStrBegin && *LStrBegin)
                {
                    if (strlen(LStrBegin) > LFileRemainderCount)
                    {
                        LStrEnd = LStrBegin + LFileRemainderCount;
                        LStrEnd = strstr(LStrEnd, __LineEnd);

                        if (LStrEnd)
                        {
                            LStrEnd += 2;
                            m_File.Write(LStrBegin, static_cast<UINT>(LStrEnd - LStrBegin));
                            LStrBegin = LStrEnd;
                        }
                        else
                        {
                            m_File.Write(LStrBegin, static_cast<UINT>(strlen(LStrBegin)));
                            LStrBegin = NULL;
                        }

                        PrivCloseFile(false);
                        PrivOpenFile(false);

                        LFileRemainderCount = m_MaxFileSize;
                    }
                    else
                    {
                        m_File.Write(LStrBegin, static_cast<UINT>(strlen(LStrBegin)));
                        LStrBegin = NULL;
                    }
                }
            }
        }

        LBuffer.Empty();
        m_File.Flush();
    }
    catch (...)
    {
        TRACE("Fail log.\n");
    }
}

LPCSTR CYCBaseFileLogger::FirstFileName()
{
    static __declspec(thread)  char    LFirstFileName[MAX_PATH];

    CSingleLock LLocker(&m_Locker, TRUE);

    strcpy_s(LFirstFileName, sizeof(LFirstFileName), m_FirstFileName);

    return LFirstFileName;
}

void CYCBaseFileLogger::SetFirstFileName(LPCSTR AValue)
{
    CSingleLock LLocker(&m_Locker, TRUE);

    if (!IsOpened())
        m_FirstFileName = AValue;
}

DWORD CYCBaseFileLogger::FileCycleCount() const
{
    return m_FileCycleCount;
}

void  CYCBaseFileLogger::SetFileCycleCount(DWORD AValue)
{
    m_FileCycleCount = AValue;
}

DWORD CYCBaseFileLogger::MaxFileSize() const
{
    return m_MaxFileSize;
}

void  CYCBaseFileLogger::SetMaxFileSize(DWORD AValue)
{
    m_MaxFileSize = AValue;
}

void CYCBaseFileLogger::WriteToFile(LPCSTR AMsg)
{
    if (m_File.m_hFile != m_File.hFileNull)
        m_File.Write(AMsg, static_cast<UINT>(strlen(AMsg)));
}

bool CYCBaseFileLogger::PrivOpenFile(bool AIsOpenExist)
{
    const UINT  LCreateFlag = CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyWrite | (AIsOpenExist ? CFile::modeNoTruncate : 0);
    CString     LFileName;

    PrivSeekOpenFileName(!AIsOpenExist, LFileName);

    YCForceDirFromFileName(LFileName);

    m_File.Open(LFileName, LCreateFlag);
    m_File.SeekToEnd();

    return true;
}

void CYCBaseFileLogger::PrivCloseFile(bool AIsNormalClose)
{
    if (m_File.m_hFile != m_File.hFileNull)
        m_File.Close();

    if (m_FileCycleCount != INFINITE && !AIsNormalClose)
    {
        char LFileName[MAX_PATH];

        strcpy_s(LFileName, sizeof(LFileName), m_FirstFileName);

        const CString LFileExt(PathFindExtension(LFileName));

        PathRemoveExtension(LFileName);

        for (int I = (int)m_FileCycleCount; I > 0; I --)
        {
            CString LFileName1, LFileName2;

            LFileName1.Format("%s%d%s", LFileName, I, LFileExt);

            if (I == 1)
                LFileName2 = m_FirstFileName;
            else
                LFileName2.Format("%s%d%s", LFileName, I - 1, LFileExt);


            if (PathFileExists(LFileName2))
            {
                MoveFileEx(LFileName2, LFileName1, MOVEFILE_REPLACE_EXISTING);
                TRACE("MoveFileEx(%s, %s, MOVEFILE_REPLACE_EXISTING)\n", LFileName2, LFileName1);
            }
        }
    }
}

void CYCBaseFileLogger::PrivSeekOpenFileName(bool AIsNewFile, OUT CString &AFileName)
{
    AFileName = m_FirstFileName;

    if (m_FileCycleCount == INFINITE)
    {
        char LFileName[MAX_PATH];

        strcpy_s(LFileName, sizeof(LFileName), m_FirstFileName);

        const CString LFileExt(PathFindExtension(LFileName));

        PathRemoveExtension(LFileName);

        for (int I = 0; I < INT_MAX; I ++)
        {
            CString LTestFileName;

            if (I == 0)
                LTestFileName = m_FirstFileName;
            else
                LTestFileName.Format("%s%d%s", LFileName, I, LFileExt);


            if (PathFileExists(LTestFileName))
            {
                if (!AIsNewFile)
                    AFileName = LTestFileName;
            }
            else
            {
                if (AIsNewFile)
                    AFileName = LTestFileName;

                I = INT_MAX - 1; // 脫離迴圈
            }   
        }
    }
}

void CYCBaseFileLogger::PrivCheckFileSize()
{
    /* 檢查log檔是否已超出預定之大小，如果是，則將它關閉並複製成第二檔名再重新開啟 */
    const DWORD LFileSize = ::GetFileSize(m_File.m_hFile, NULL);

    if (LFileSize > m_MaxFileSize && m_FileCycleCount > 0)
    {
        PrivCloseFile(false);
        PrivOpenFile(false);
    }
}
//
//CYCBaseFileLogger
////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////
//CYCEventLogger
//
IMPLEMENT_DYNAMIC(CYCEventLogger, CYCBaseFileLogger)


LPCSTR CYCEventLogger::FormatLogLevelText(int ALevel)
{
    static const CHAR *LLevelTexts[] =
    {
        "Operation",
        "Operation1",
        "Operation2",
        "Operation3",
        "Operation4",
        "Operation9",
        "Error",
        "Alarm",
        ""
    };


    switch (ALevel)
    {
    case llMin        : return LLevelTexts[0];

    case llOperation1 : return LLevelTexts[1];
    case llOperation2 : return LLevelTexts[2];
    case llOperation3 : return LLevelTexts[3];
    case llOperation4 : return LLevelTexts[4];

    case llOperation9 : return LLevelTexts[5];
    case llError      : return LLevelTexts[6];
    case llAlarm      : return LLevelTexts[7];
    }

    return LLevelTexts[8];
}

LPCSTR CYCEventLogger::FormatLogDirText(int ADir)
{
    static const CHAR *LDirTexts[] =
    {
        "---->",
        "<----",
        "-----"
    };


    switch (ADir)
    {
    case ldForeward : return LDirTexts[0];
    case ldBackward : return LDirTexts[1];
    case ldNone     :
    default         : return LDirTexts[2];
    }
}


CYCEventLogger::CYCEventLogger()
: CYCBaseFileLogger()
, m_LogLevel(llOperation9)
{
}

CYCEventLogger::~CYCEventLogger(void)
{
    Close();
}

BYTE CYCEventLogger::LogLevel() const
{
    return m_LogLevel;
}

void CYCEventLogger::SetLogLevel(BYTE AValue)
{
    m_LogLevel = ((AValue > llAlarm) ? llAlarm : ((AValue < llMin) ? llOperation : AValue));
}

void CYCEventLogger::Write(BYTE ALevel, LPCSTR AMsg)
{
#ifndef _DEBUG
    if (ALevel >= m_LogLevel)
#endif
    {
        Write(ALevel, ldNone, AMsg);
    }
}

void CYCEventLogger::Write(BYTE ALevel, int ADir, LPCSTR AMsg)
{
    CSingleLock LLocker(&m_Locker, TRUE);

#ifdef _DEBUG

    char        LPrependedStr[256];
    SYSTEMTIME  LST;

    GetLocalTime(&LST);

    const int LPrependedStrLen = sprintf_s(LPrependedStr, sizeof(LPrependedStr),
        /**/                               "[%04u-%02u-%02u %02u:%02u:%02u %3u][%8u][%10s] %s ", 
        /**/                               LST.wYear,
        /**/                               LST.wMonth,
        /**/                               LST.wDay,
        /**/                               LST.wHour,
        /**/                               LST.wMinute,
        /**/                               LST.wSecond,
        /**/                               LST.wMilliseconds,
        /**/                               GetCurrentThreadId(),
        /**/                               FormatLogLevelText(ALevel),
        /**/                               FormatLogDirText(ADir));

    TRACE("%s%s\n", LPrependedStr, AMsg);

#endif

    if (ALevel >= m_LogLevel && IsOpened())
    {
        try
        {
#ifndef _DEBUG

            char        LPrependedStr[256];
            SYSTEMTIME  LST;

            GetLocalTime(&LST);

            const int LPrependedStrLen = sprintf_s(LPrependedStr, sizeof(LPrependedStr),
                /**/                               "[%04u-%02u-%02u %02u:%02u:%02u %3u][%8u][%10s] %s ", 
                /**/                               LST.wYear,
                /**/                               LST.wMonth,
                /**/                               LST.wDay,
                /**/                               LST.wHour,
                /**/                               LST.wMinute,
                /**/                               LST.wSecond,
                /**/                               LST.wMilliseconds,
                /**/                               GetCurrentThreadId(),
                /**/                               FormatLogLevelText(ALevel),
                /**/                               FormatLogDirText(ADir));

#endif

            CString LBuffer;

            LBuffer.Format("%s%s", LPrependedStr, AMsg);
            WriteToBuffer(LBuffer);
        }
        catch (...)
        {
            TRACE("Log message failed.\n");
        }
    }
}

void CYCEventLogger::WriteFmt(BYTE ALevel, LPCSTR AFmt, ...)
{
#ifndef _DEBUG
    if (ALevel >= m_LogLevel)
#endif
    {
        va_list LArgs;

        va_start(LArgs, AFmt);

        WriteFmtV(ALevel, AFmt, LArgs);

        va_end(LArgs);
    }
}

void CYCEventLogger::WriteFmt(BYTE ALevel, int ADir, LPCSTR AFmt, ...)
{
#ifndef _DEBUG
    if (ALevel >= m_LogLevel)
#endif
    {
        va_list LArgs;

        va_start(LArgs, AFmt);

        WriteFmtV(ALevel, ADir, AFmt, LArgs);

        va_end(LArgs);
    }
}

void CYCEventLogger::WriteFmtV(BYTE ALevel, LPCSTR AFmt, va_list AArgs)
{
#ifndef _DEBUG
    if (ALevel >= m_LogLevel)
#endif
    {
        CString LStr;

        try
        {
            LStr.FormatV(AFmt, AArgs);
        }
        catch (...)
        {
            LStr = CString("Invalid format format : ") + AFmt;
        }

        Write(ALevel, LStr);
    }
}

void CYCEventLogger::WriteFmtV(BYTE ALevel, int ADir, LPCSTR AFmt, va_list AArgs)
{
#ifndef _DEBUG
    if (ALevel >= m_LogLevel)
#endif
    {
        CString LStr;

        try
        {
            LStr.FormatV(AFmt, AArgs);
        }
        catch (...)
        {
            LStr = CString("Invalid format format : ") + AFmt;
        }

        Write(ALevel, ADir, LStr);
    }
}

void CYCEventLogger::WriteAlarmDayFile(CString AFilePatch, int AIndex,CString AStr)
{
	CString LCountStr;
	LCountStr.Format("%d" , AIndex);
	WritePrivateProfileString("Alarm" ,"Alarm[" + LCountStr + "]" , AStr ,AFilePatch);
}
//
//CYCEventLogger
////////////////////////////////////////////////////////////////////////////////////



