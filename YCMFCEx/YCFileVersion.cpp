#include "StdAfx.h"
#include "YCFileVersion.h"

#pragma comment(lib, "Version.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CYCFileVersion::CYCFileVersion(void)
{
    Open(NULL);
}

CYCFileVersion::CYCFileVersion(LPCSTR AFileName)
{
    Open(AFileName);
}

CYCFileVersion::~CYCFileVersion(void)
{
}

LPCSTR  CYCFileVersion::Comments() const
{
    return m_Comments;
}

LPCSTR  CYCFileVersion::InternalName() const
{
    return m_InternalName;
}

LPCSTR CYCFileVersion::ProductName() const
{
    return m_ProductName;
}

LPCSTR  CYCFileVersion::CompanyName() const
{
    return m_CompanyName;
}

LPCSTR  CYCFileVersion::LegalCopyright() const
{
    return m_LegalCopyright;
}

LPCSTR  CYCFileVersion::ProductVersion() const
{
    return m_ProductVersion;
}

LPCSTR  CYCFileVersion::FileDescription() const
{
    return m_FileDescription;
}

LPCSTR  CYCFileVersion::FileVersion() const
{
    return m_FileVersion;
}

LPCSTR  CYCFileVersion::PrivateBuild() const
{
    return m_PrivateBuild;
}

LPCSTR  CYCFileVersion::OriginalFilename() const
{
    return m_OriginalFilename;
}

bool    CYCFileVersion::Open(LPCSTR AFileName)
{
    m_Comments.Empty();
    m_InternalName.Empty();
    m_ProductName.Empty();
    m_CompanyName.Empty();
    m_LegalCopyright.Empty();
    m_ProductVersion.Empty();
    m_FileDescription.Empty();
    m_FileVersion.Empty();
    m_PrivateBuild.Empty();
    m_OriginalFilename.Empty();


    CHAR    LFileName[MAX_PATH] = {0};

    if (AFileName == NULL)
        ::GetModuleFileName(NULL, LFileName, MAX_PATH);
    else strcpy_s(LFileName, sizeof(LFileName), AFileName);

    INT LVerBufSize = ::GetFileVersionInfoSize(LFileName, NULL);

    if (LVerBufSize <= 0)
    {
        return false;
    }

    CHAR    *LVerBuf = new CHAR[LVerBufSize];

    if (!LVerBuf)
    {  
        return false;
    }

    if (!::GetFileVersionInfo(LFileName, NULL, LVerBufSize, LVerBuf))
    {  
        return false;
    }

    struct LANGANDCODEPAGE
    {  
        WORD   Language;
        WORD   CodePage;
    } *LTranslate;

    //   Read   the   list   of   languages   and   code   pages.  
    UINT   LTranslateCount;

    ::VerQueryValue(LVerBuf, "\\VarFileInfo\\Translation", (LPVOID*)&LTranslate, &LTranslateCount);

    UINT    LReadCount;
    CHAR*   LReadBuffer;
    CHAR    LName[256];

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\Comments", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_Comments = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\InternalName",  LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_InternalName = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\ProductName", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_ProductName = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\CompanyName", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_CompanyName = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\LegalCopyright", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_LegalCopyright = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\ProductVersion", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_ProductVersion = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\FileDescription", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_FileDescription = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\FileVersion", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_FileVersion = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\PrivateBuild", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_PrivateBuild = LReadBuffer;
    }

    _snprintf_s(LName, 256, 256, "\\StringFileInfo\\%04x%04x\\OriginalFilename", LTranslate[0].Language, LTranslate[0].CodePage);

    if (::VerQueryValue(LVerBuf, LName, (LPVOID*)&LReadBuffer, &LReadCount))
    {  
        m_OriginalFilename = LReadBuffer;
    }

    delete [] LVerBuf;

    return true;
}