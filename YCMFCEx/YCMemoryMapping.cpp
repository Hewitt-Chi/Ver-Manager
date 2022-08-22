
#include "stdafx.h"

#include "YCObject.h"
#include "YCMemoryMapping.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define __EVENT_Text            ".Event"
#define __MUTEX_Text            ".Mutex"
#define __FILEMAPPING_Text      ".FileMapping"


CYCMemoryMapping::CYCMemoryMapping()
: m_Size(0)
, m_Memory(NULL)
, m_MemoryChangedEvent(NULL)
, m_MapFile(NULL)
, m_MemoryLocker(NULL)
{
}

CYCMemoryMapping::~CYCMemoryMapping()
{
    Close();
}

LPCSTR  CYCMemoryMapping::Name() const
{
    return m_Name;
}

SIZE_T  CYCMemoryMapping::Size() const
{
    return m_Size;
}

HANDLE  CYCMemoryMapping::MemoryChangedEvent() const
{
    return m_MemoryChangedEvent;
}

bool    CYCMemoryMapping::Open(LPCSTR AName, SIZE_T ABufferSize)
{
    if (!m_Memory)
    {
        bool LFinish = false;

        for (int LStep = 0; !LFinish; LStep ++)
        {
            switch (LStep)
            {
            case 0 :
                m_MemoryChangedEvent = CreateEvent(NULL,               // default security attributes
                    /**/                           FALSE,              // manual-reset event
                    /**/                           FALSE,              // initial state is nonsignaled
                    /**/                           CString(AName) + __EVENT_Text); 

                break;

            case 1 :
                m_MemoryLocker = CreateMutex(NULL,              // default security attributes
                    /**/                     FALSE,             // initially not owned
                    /**/                     CString(AName) + __MUTEX_Text);             // unnamed mutex


                break;

            case 2 :
                m_Name = CString(AName);    // Add by Mike, 20130821
                // Create File Mapping
                m_MapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, m_Name + __FILEMAPPING_Text);

                if (m_MapFile == NULL)
                    m_MapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, PtrToUint(m_Size), m_Name + __FILEMAPPING_Text);

                break;

            case 3 :
                // Map to memory
                if (m_MapFile != NULL && m_MapFile != INVALID_HANDLE_VALUE)
                    m_Memory = (LPVOID )MapViewOfFile(m_MapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

                break;

            case 4 :
                {
                    MEMORY_BASIC_INFORMATION    LMBI;

                    VirtualQueryEx(GetCurrentProcess(), m_Memory, &LMBI, sizeof(LMBI));

                    m_Size = LMBI.RegionSize;

                    LFinish = true;
                }
            }
        }
    }

    return m_Memory != NULL;
}

void    CYCMemoryMapping::Close()
{
    if (m_Memory)
    {
        UnmapViewOfFile(m_Memory);
        m_Memory = NULL;
    }

    if (m_MapFile)
    {
        CloseHandle(m_MapFile);
        m_MapFile = NULL;
    }

    if (m_MemoryChangedEvent)
    {
        CloseHandle(m_MemoryChangedEvent);
        m_MemoryChangedEvent = NULL;
    }

    if (m_MemoryLocker)
    {
        CloseHandle(m_MemoryLocker);
        m_MemoryLocker = NULL;
    }
}

LPVOID  CYCMemoryMapping::LockMemory()
{
    WaitForSingleObject(m_MemoryLocker, INFINITE);

    return m_Memory;
}

void    CYCMemoryMapping::UnlockMemory(bool AIsSetEvent/* = false*/)
{
    ReleaseMutex(m_MemoryLocker);

    if (AIsSetEvent)
        SetEvent(m_MemoryChangedEvent);
}

SIZE_T  CYCMemoryMapping::WriteMemory(IN LPCVOID ABuffer, SIZE_T ABufferSize)
{
    LPVOID LBuffer = LockMemory();

    memcpy_s(LBuffer, m_Size, ABuffer, min(ABufferSize, m_Size));

    UnlockMemory(true);

    return min(ABufferSize, m_Size);
}

SIZE_T  CYCMemoryMapping::ReadMemory(OUT LPVOID ABuffer, SIZE_T ABufferSize)
{
    LPVOID LBuffer = LockMemory();

    memcpy_s(ABuffer, ABufferSize, LBuffer, min(ABufferSize, m_Size));
    ZeroMemory(LBuffer, min(ABufferSize, m_Size));

    UnlockMemory(false);

    return min(ABufferSize, m_Size);
}

#undef __EVENT_Text
#undef __MUTEX_Text
#undef __FILEMAPPING_Text
