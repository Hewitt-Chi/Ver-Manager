#pragma once


#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


class CYCMemoryMapping
{
public:

    CYCMemoryMapping();
    virtual ~CYCMemoryMapping();


    LPCSTR  Name() const;
    SIZE_T  Size() const;
    HANDLE  MemoryChangedEvent() const;


    bool    Open(LPCSTR AName, SIZE_T ABufferSize);
    void    Close();


    LPVOID  LockMemory();    
    void    UnlockMemory(bool AIsSetEvent = false);
    SIZE_T  WriteMemory(IN LPCVOID ABuffer, SIZE_T ABufferSize);
    SIZE_T  ReadMemory(OUT LPVOID ABuffer, SIZE_T ABufferSize);

protected:
    CString m_Name;
    SIZE_T  m_Size;
    LPVOID  m_Memory;
    HANDLE  m_MemoryChangedEvent;
    HANDLE  m_MapFile;
    HANDLE  m_MemoryLocker;

};
