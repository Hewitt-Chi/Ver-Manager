#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif



class CYCWaitableTimer : public CSyncObject
{
    DECLARE_DYNAMIC(CYCWaitableTimer)

public:
    CYCWaitableTimer(LPSECURITY_ATTRIBUTES ATimerAttributes = NULL, BOOL AManualReset = FALSE, LPCTSTR ATimerName = NULL);
    CYCWaitableTimer(LPSECURITY_ATTRIBUTES ATimerAttributes, BOOL AManualReset, LPCTSTR ATimerName,
        /**/         LONGLONG ADueTime, DWORD APeriod, BOOL AResume);
    virtual ~CYCWaitableTimer(void);


    using   CSyncObject::Unlock;
    BOOL    Unlock();


    BOOL    SetWaitableTimer(const LARGE_INTEGER* ADueTime, LONG APeriod, BOOL AResume);
    BOOL    SetWaitableTimer(LONGLONG ADueTime, LONG APeriod, BOOL AResume);
    BOOL    CancelWaitableTimer();

};
