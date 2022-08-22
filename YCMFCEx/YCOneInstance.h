#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


class CYCOneInstance
{
public:
    CYCOneInstance(LPTSTR AName);
    virtual ~CYCOneInstance(void);

    bool    TestAndActivatePreInstance();

private:

    static  LONG m_ReferenceCount;

    CString m_Name;
    HANDLE  m_Mutex;
    bool    m_IsPreInstanceExists;

};
