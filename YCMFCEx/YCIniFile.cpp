#include "StdAfx.h"

#include "YCUtils.h"

#include "YCIniFile.h"
#include <shlwapi.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define __BOOLTEXT_False     "False"
#define __BOOLTEXT_True      "True"


void YCParseNameValue(LPCSTR ANameValue, OUT CString *AName, OUT CString *AValue)
{
    CString     LNameValue = ANameValue;
    const int   I          = LNameValue.Find('=');

    if (I == -1)
    {
        if (AName)
            *AName = LNameValue.Trim(' ');

        if (AValue)
            *AValue = "";
    }
    else
    {
        if (AName)
            *AName = LNameValue.Left(I).Trim(' ');

        if (AValue)
            *AValue = LNameValue.Mid(I + 1).Trim(' ').Trim('"');
    }
}


///////////////////////////////////////////////////////////////////////////
// CYCBaseIniFile
//
IMPLEMENT_DYNAMIC(CYCBaseIniFile, CObject)


CString CYCBaseIniFile::GetValueName(LPCSTR AText)
{
    CString LStr = AText;
    int     LTokenIdx = 0;

    return LStr.Tokenize("=", LTokenIdx);
}

CString CYCBaseIniFile::GetValueValue(LPCSTR AText)
{
    CString LStr      = AText;
    int     LTokenIdx = 0;

    LStr.Tokenize("=", LTokenIdx);

    if (LTokenIdx != -1)
        return LStr.Mid(LTokenIdx);

    return "";
}

CYCBaseIniFile::CYCBaseIniFile()
: CObject()
, m_FileName("")
, m_SectionName("")
{
}

CYCBaseIniFile::~CYCBaseIniFile(void)
{
}

bool    CYCBaseIniFile::IsOpened() const
{
    return !m_FileName.IsEmpty();
}

bool    CYCBaseIniFile::Open(LPCSTR    AFileName)
{
    if (IsOpened())
    {
        ASSERT(FALSE);
    }
    else if (AFileName && strlen(AFileName))
    {
        if (OnOpen(AFileName))
        {
            m_FileName = AFileName;
            return true;
        }
    }
    else
    {
        ASSERT(FALSE);    
    }

    return false;
}

void    CYCBaseIniFile::Close()
{
    if (IsOpened())
    {
        OnClose();

        m_FileName = "";
    }
}

LPCSTR  CYCBaseIniFile::FileName() const
{
    return m_FileName;
}

LPCSTR  CYCBaseIniFile::SectionName() const
{
    return m_SectionName;
}

void    CYCBaseIniFile::SetSectionName(LPCSTR AValue)
{
    ASSERT(AValue);
    ASSERT(strlen(AValue) > 0);
    ASSERT(IsOpened());

    if (IsOpened() && AValue && strlen(AValue) > 0)
        m_SectionName = AValue;
}

void    CYCBaseIniFile::ReadSectionNames(OUT TYCIniFileStrings &ANames) const
{
    OnReadSectionNames(ANames);
}

void    CYCBaseIniFile::ReadValueNames(LPCSTR ASectionName, OUT TYCIniFileStrings &ANames) const
{
    ASSERT(ASectionName && strlen(ASectionName));

    if (ASectionName && strlen(ASectionName))
        OnReadValueNames(ASectionName, ANames);
}

void    CYCBaseIniFile::ReadValueNames(OUT TYCIniFileStrings &ANames) const
{
    ReadValueNames(m_SectionName, ANames);
}

void    CYCBaseIniFile::ReadSectionContent(LPCSTR ASectionName, OUT TYCIniFileStrings &AContent) const
{
    ASSERT(ASectionName);

    if (ASectionName && strlen(ASectionName))
        OnReadSectionContent(ASectionName, AContent);
}

void    CYCBaseIniFile::ReadSectionContent(OUT TYCIniFileStrings &AContent) const
{
    ReadSectionContent(m_SectionName, AContent);
}

bool    CYCBaseIniFile::IsSectionNameExists(LPCSTR ASectionName) const
{
    ASSERT(ASectionName && strlen(ASectionName));

    if (ASectionName && strlen(ASectionName))
    {
        TYCIniFileStrings   LNames;

        ReadSectionNames(LNames);

        for (TYCIniFileStrings::const_iterator LIter = LNames.begin();
            LIter != LNames.end(); LIter ++)
        {
            if (!LIter->CompareNoCase(ASectionName))
                return true;
        }
    }

    return false;
}

bool    CYCBaseIniFile::IsValueNameExists(LPCSTR ASectionName, LPCSTR AValueName) const
{
    ASSERT(ASectionName && strlen(ASectionName));

    if (ASectionName && strlen(ASectionName))
    {
        TYCIniFileStrings   LNames;

        ReadValueNames(ASectionName, LNames);

        for (TYCIniFileStrings::const_iterator LIter = LNames.begin();
            LIter != LNames.end(); LIter ++)
        {
            if (!LIter->CompareNoCase(AValueName))
                return true;
        }
    }

    return false;
}

CString CYCBaseIniFile::ReadString(LPCSTR ASectionName, LPCSTR AValueName, LPCSTR  ADefault, bool AIsCreateIfNotExist)
{
    ASSERT(IsOpened());
    ASSERT(ASectionName && strlen(ASectionName));
    ASSERT(AValueName   && strlen(AValueName));

    if (IsOpened() &&
        ASectionName && strlen(ASectionName) &&
        AValueName   && strlen(AValueName))
    {
        CString LRslt = ADefault;

        if (!OnReadString(m_SectionName = ASectionName, AValueName, LRslt) && AIsCreateIfNotExist)
            WriteString(ASectionName, AValueName, ADefault);

        return LRslt;
    }

    return "";
}

CString CYCBaseIniFile::ReadString(LPCSTR AValueName, LPCSTR ADefault/* = ""*/, bool AIsCreateIfNotExist/* = false*/)
{
    return ReadString(m_SectionName, AValueName, ADefault, AIsCreateIfNotExist);
}

int     CYCBaseIniFile::ReadInt(LPCSTR ASectionName, LPCSTR AValueName, int ADefault, bool AIsCreateIfNotExist)
{
    CString LStr;

    LStr.Format("%d", ADefault);
    LStr = ReadString(ASectionName, AValueName, LStr, AIsCreateIfNotExist);

    return YCStrToIntDef(LStr, ADefault);
}

int     CYCBaseIniFile::ReadInt(LPCSTR AValueName, int ADefault/* = 0*/,  bool AIsCreateIfNotExist/* = false*/)
{
    return ReadInt(m_SectionName, AValueName, ADefault, AIsCreateIfNotExist);
}

double  CYCBaseIniFile::ReadFloat(LPCSTR ASectionName, LPCSTR AValueName, double ADefault, bool AIsCreateIfNotExist)
{
    CString LStr;

    LStr.Format("%f", ADefault);

    LStr = ReadString(ASectionName, AValueName, LStr, AIsCreateIfNotExist);

    return YCStrToFloatDef(LStr, ADefault);
}

double  CYCBaseIniFile::ReadFloat(LPCSTR AValueName, double ADefault/* = 0*/, bool AIsCreateIfNotExist/* = false*/)
{
    return ReadFloat(m_SectionName, AValueName, ADefault, AIsCreateIfNotExist);
}

bool    CYCBaseIniFile::ReadBool(LPCSTR ASectionName, LPCSTR AValueName, bool ADefault, bool AIsCreateIfNotExist)
{
    const CString LStr = ReadString(ASectionName, AValueName, ADefault ? __BOOLTEXT_True : __BOOLTEXT_False, AIsCreateIfNotExist);

    return !LStr.CompareNoCase(__BOOLTEXT_True);
}

bool    CYCBaseIniFile::ReadBool(LPCSTR AValueName, bool ADefault/* = false*/, bool AIsCreateIfNotExist/* = false*/)
{
    return ReadBool(m_SectionName, AValueName, ADefault, AIsCreateIfNotExist);
}

void    CYCBaseIniFile::WriteString(LPCSTR ASectionName, LPCSTR AValueName, LPCSTR AValue)
{
    ASSERT(IsOpened());
    ASSERT(ASectionName && strlen(ASectionName));
    ASSERT(AValueName   && strlen(AValueName));

    if (IsOpened() &&
        ASectionName && strlen(ASectionName) &&
        AValueName   && strlen(AValueName))
    {
        OnWriteString(m_SectionName = ASectionName, AValueName, AValue);
    }
}

void    CYCBaseIniFile::WriteString(LPCSTR AValueName, LPCSTR AValue)
{
    WriteString(m_SectionName, AValueName, AValue);
}

void    CYCBaseIniFile::WriteInt(LPCSTR ASectionName, LPCSTR AValueName, int AValue)
{
    CString LStr;

    LStr.Format("%d", AValue);
    WriteString(ASectionName, AValueName, LStr);
}

void    CYCBaseIniFile::WriteInt(LPCSTR AValueName, int AValue)
{
    WriteInt(m_SectionName, AValueName, AValue);
}

void    CYCBaseIniFile::WriteFloat(LPCSTR ASectionName, LPCSTR AValueName, double AValue)
{
    CString LStr;

    LStr.Format("%f", AValue);
    WriteString(ASectionName, AValueName, LStr);
}

void    CYCBaseIniFile::WriteFloat(LPCSTR AValueName, double AValue)
{
    WriteFloat(m_SectionName, AValueName, AValue);
}

void    CYCBaseIniFile::WriteBool(LPCSTR ASectionName, LPCSTR AValueName, bool AValue)
{
    WriteString(ASectionName, AValueName, CString(AValue ? __BOOLTEXT_True : __BOOLTEXT_False));
}

void    CYCBaseIniFile::WriteBool(LPCSTR AValueName, bool AValue)
{
    WriteBool(m_SectionName, AValueName, AValue);
}
//
// CYCBaseIniFile
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// CYCIniFile
//
IMPLEMENT_DYNAMIC(CYCIniFile, CYCBaseIniFile)


CYCIniFile::CYCIniFile()
: CYCBaseIniFile()
{
}

CYCIniFile::~CYCIniFile(void)
{
    Close();
}

IMPLEMENT_CYCBaseIniFile_OnOpen(CYCIniFile)
{
    return true;
}

IMPLEMENT_CYCBaseIniFile_OnClose(CYCIniFile)
{
}

IMPLEMENT_CYCBaseIniFile_OnReadSectionNames(CYCIniFile)
{
    if (!PathFileExists(m_FileName))
        return ;

    ANames.clear();

    int LSize = 1024;

    LPTSTR LBuf = (LPTSTR)YCmalloc(LSize);

    while (true)
    {
        if (GetPrivateProfileSectionNames(LBuf, LSize, m_FileName) != LSize - 2)
        {
            LPCTSTR P = LBuf;

            while (P && *P != 0)
            {
                ANames.push_back(P);

                P += (strlen(P) + 1);
            }            

            break;
        }

        LSize += 1024;

        LBuf = (LPTSTR)YCrealloc(LBuf, LSize);
    }

    YCfree(LBuf);

}

IMPLEMENT_CYCBaseIniFile_OnReadValueNames(CYCIniFile)
{
    if (!PathFileExists(m_FileName))
        return ;

    ANames.clear();

    int LSize = 1024;

    LPTSTR LBuf = (LPTSTR)YCmalloc(LSize);

    while (true)
    {
        if (GetPrivateProfileString(ASectionName, NULL, NULL, LBuf, LSize, m_FileName) != LSize - 2)
        {
            LPCTSTR P = LBuf;

            while (P && *P != 0)
            {
                ANames.push_back(P);

                P += (strlen(P) + 1);
            }            

            break;
        }

        LSize += 1024;

        LBuf = (LPTSTR)YCrealloc(LBuf, LSize);
    }

    YCfree(LBuf);

}

IMPLEMENT_CYCBaseIniFile_OnReadSectionContent(CYCIniFile)
{
    if (!PathFileExists(m_FileName))
        return ;

    AContent.clear();
    int LSize = 1024;

    LPTSTR LBuf = (LPTSTR)YCmalloc(LSize);

    while (true)
    {
        if (GetPrivateProfileSection(ASectionName, LBuf, LSize, m_FileName) != LSize - 2)
        {
            LPCTSTR P = LBuf;

            while (P && *P != 0)
            {
                // TODO: Check memory
                AContent.push_back(CString(P));

                P += (strlen(P) + 1);
            }            

            break;
        }

        LSize += 1024;

        LBuf = (LPTSTR)YCrealloc(LBuf, LSize);
    }

    YCfree(LBuf);

}

IMPLEMENT_CYCBaseIniFile_OnReadString(CYCIniFile)
{
    GUID    LGUID;

    CoCreateGuid(&LGUID);

    const CString   LDefault   = YCGUIDToStr(LGUID);
    char            LBuf[512];
    const DWORD     LReadCount = GetPrivateProfileString(ASectionName, AValueName, LDefault, LBuf, sizeof(LBuf) - 1, m_FileName);

    LBuf[LReadCount] = 0;

    if (!LDefault.Compare(LBuf))
        return false;

    ARslt = LBuf;

    return true;
}

IMPLEMENT_CYCBaseIniFile_OnWriteString(CYCIniFile)
{
    WritePrivateProfileString(ASectionName, AValueName, AValue, m_FileName);
}
//
// CYCIniFile
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
// CYCMemIniFile
//
IMPLEMENT_DYNAMIC(CYCMemIniFile, CYCBaseIniFile)


CYCMemIniFile::CYCMemIniFile()
: CYCBaseIniFile()
, m_IsModified(false)
{
}

CYCMemIniFile::~CYCMemIniFile(void)
{
    OnClose();
}

IMPLEMENT_CYCBaseIniFile_OnOpen(CYCMemIniFile)
{
    if (!AFileName || !strlen(AFileName))
        return false;


    CStdioFile  LFile;

    if (LFile.Open(AFileName, CFile::modeRead))
    {
        CString             LStr;
        CSection            LSection;
        TYCIniFileStrings   LComment;

        while (LFile.ReadString(LStr))
        {
            LStr.Trim();

            if (!LStr.IsEmpty())
            {
                // Comment
                if (LStr[0] == ';')
                {
                    LComment.push_back(LStr);
                }
                // 新的Section，Section Name
                else if (LStr[0] == '[' && LStr.Right(1) == "]")
                {
                    // 儲存前一個Section
                    if (!LSection.m_Name.IsEmpty())
                        m_Sections[LSection.m_Name] = LSection;

                    // 設定目前的Section
                    LSection.m_Comment = LComment;
                    LSection.m_Name    = LStr.Trim("[] ");
                    LSection.m_Values.clear();

                    LComment.clear();
                }
                // Value
                else
                {
                    CValue  LValueItem;

                    YCParseNameValue(LStr, &LValueItem.m_Name, &LValueItem.m_Value);
                    LValueItem.m_Comment = LComment;
                    LComment.clear();

                    LSection.m_Values[LValueItem.m_Name] = LValueItem;
                }

            } // if (!LStr.IsEmpty())

        } // while (LFile.ReadString(LStr))

        if (!LSection.m_Name.IsEmpty())
        {
            m_Sections[LSection.m_Name] = LSection;
            LSection.m_Values.clear();
        }

    } // if (LFile.Open(AFileName, CFile::modeRead))

    return true;
}

IMPLEMENT_CYCBaseIniFile_OnClose(CYCMemIniFile)
{
    Flush();
    m_Sections.clear();
}

IMPLEMENT_CYCBaseIniFile_OnReadSectionNames(CYCMemIniFile)
{
    ANames.clear();

    for (CSections::const_iterator  LSectionIterator = m_Sections.begin();
        LSectionIterator != m_Sections.end(); LSectionIterator ++)
    {
        ANames.push_back(LSectionIterator->first);
    }
}

IMPLEMENT_CYCBaseIniFile_OnReadValueNames(CYCMemIniFile)
{
    ANames.clear();

    // 找出本身是否有相同Section
    CSections::const_iterator   LSectionIterator = m_Sections.find(ASectionName);

    // 如果有相同的Section
    if (LSectionIterator != m_Sections.end())
    {
        const CValues &LValues = LSectionIterator->second.m_Values;

        for (CValues::const_iterator LValueIterator = LValues.begin();
            LValueIterator != LValues.end(); LValueIterator ++)
        {
            ANames.push_back(LValueIterator->first);
        }
    }
}

IMPLEMENT_CYCBaseIniFile_OnReadSectionContent(CYCMemIniFile)
{
    AContent.clear();

    // 找出本身是否有相同Section
    CSections::const_iterator   LSectionIterator = m_Sections.find(ASectionName);

    // 如果有相同的Section
    if (LSectionIterator != m_Sections.end())
    {
        const CValues &LValues = LSectionIterator->second.m_Values;

        for (CValues::const_iterator LValueIterator = LValues.begin();
            LValueIterator != LValues.end(); LValueIterator ++)
        {
            AContent.push_back(LValueIterator->first + "=" + LValueIterator->second.m_Value);
        }
    }
}

IMPLEMENT_CYCBaseIniFile_OnReadString(CYCMemIniFile)
{
    // 找出本身是否有相同Section
    CSections::const_iterator   LSectionIter = m_Sections.find(ASectionName);

    // 如果有相同的Section
    if (LSectionIter != m_Sections.end())
    {
        CValues::const_iterator     LValueIter = LSectionIter->second.m_Values.find(AValueName);

        // 如果有找到Value則回傳
        if (LValueIter != LSectionIter->second.m_Values.end())
        {
            ARslt = LValueIter->second.m_Value;

            return true;
        }
    }

    return false;
}

IMPLEMENT_CYCBaseIniFile_OnWriteString(CYCMemIniFile)
{
    // 設定Section
    if (m_Sections.find(ASectionName) == m_Sections.end())
    {
        CSection    LSection;

        LSection.m_Name = ASectionName;
        m_Sections[ASectionName] = LSection;
    }

    // 設定Value
    CValue LValue;

    LValue.m_Name  = AValueName;
    LValue.m_Value = AValue;

    m_Sections[ASectionName].m_Values[AValueName] = LValue;
    m_IsModified = true;
}

void CYCMemIniFile::Flush()
{
    if (IsOpened() && m_IsModified)
    {
        const CString   LFileName = YCRelativeFileNameToAbs(m_FileName);

        YCForceDirFromFileName(LFileName);

        CStdioFile  LFile;

        if (LFile.Open(LFileName, CFile::modeCreate | CFile::modeWrite))
        {
            for (CSections::const_iterator    LSectionIter = m_Sections.begin();
                LSectionIter != m_Sections.end(); LSectionIter ++)
            {
                if (LSectionIter != m_Sections.begin())
                    LFile.WriteString("\n");


                // 把Section Comment寫入
                for (TYCIniFileStrings::const_iterator  LCommentIter = LSectionIter->second.m_Comment.begin();
                    LCommentIter != LSectionIter->second.m_Comment.end(); LCommentIter ++)
                {
                    LFile.WriteString(*LCommentIter);
                    LFile.WriteString("\n");
                }


                // 寫入Section Name
                {
                    CString LStr;

                    LStr.Format("[%s]\n", LSectionIter->second.m_Name);
                    LFile.WriteString(LStr);
                }


                bool LIsLastItemHasComment = false;

                // 寫入Section 值
                for (CValues::const_iterator    LValueIter = LSectionIter->second.m_Values.begin();
                    LValueIter != LSectionIter->second.m_Values.end(); LValueIter ++)
                {
                    if (LValueIter->second.m_Comment.size() > 0/* || LIsLastItemHasComment*/)
                    {
                        LFile.WriteString("\n");
                    }


                    // 把Value Comment寫入
                    for (TYCIniFileStrings::const_iterator  LCommentIter = LValueIter->second.m_Comment.begin();
                        LCommentIter != LValueIter->second.m_Comment.end(); LCommentIter ++)
                    {
                        LFile.WriteString(*LCommentIter);
                        LFile.WriteString("\n");
                    }


                    // 寫入Value Name&Value
                    {
                        CString LStr;

                        LStr.Format("%s=%s\n", LValueIter->second.m_Name, LValueIter->second.m_Value);
                        LFile.WriteString(LStr);
                    }

                    LIsLastItemHasComment = !!LValueIter->second.m_Comment.size();
                }

            } // for (CSections::const_iterator    LSectionIter = m_Sections.begin();
            //       LSectionIter != m_Sections.end(); LSectionIter ++)

            m_IsModified = false;

        } // if (LFile.Open(LFileName, CFile::modeCreate | CFile::modeWrite))
    }
}
//
// CYCMemIniFile
///////////////////////////////////////////////////////////////////////////
