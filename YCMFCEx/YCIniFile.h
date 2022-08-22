#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

///////////////////////////////////////////////////////////////////////////
// CYCBaseIniFile
//
#define   VIRTUAL_CYCBaseIniFile_OnOpen()                       virtual bool OnOpen(LPCSTR     AFileName)
#define IMPLEMENT_CYCBaseIniFile_OnOpen(AClass)                 bool AClass::OnOpen(LPCSTR     AFileName)
#define  OVERRIDE_CYCBaseIniFile_OnOpen                         VIRTUAL_CYCBaseIniFile_OnOpen

#define   VIRTUAL_CYCBaseIniFile_OnClose()                      virtual void OnClose()
#define IMPLEMENT_CYCBaseIniFile_OnClose(AClass)                void AClass::OnClose()
#define  OVERRIDE_CYCBaseIniFile_OnClose                        VIRTUAL_CYCBaseIniFile_OnClose


//****************************** ReadSectionNames()
#define   VIRTUAL_CYCBaseIniFile_OnReadSectionNames() \
    virtual void OnReadSectionNames(OUT TYCIniFileStrings &ANames) const

#define IMPLEMENT_CYCBaseIniFile_OnReadSectionNames(AClass) \
    void AClass::OnReadSectionNames(OUT TYCIniFileStrings &ANames) const

#define  OVERRIDE_CYCBaseIniFile_OnReadSectionNames \
    VIRTUAL_CYCBaseIniFile_OnReadSectionNames


//****************************** ReadValueNames()
#define   VIRTUAL_CYCBaseIniFile_OnReadValueNames() \
    virtual void OnReadValueNames(LPCSTR ASectionName, OUT TYCIniFileStrings &ANames) const

#define IMPLEMENT_CYCBaseIniFile_OnReadValueNames(AClass) \
    void AClass::OnReadValueNames(LPCSTR ASectionName, OUT TYCIniFileStrings &ANames) const

#define  OVERRIDE_CYCBaseIniFile_OnReadValueNames \
    VIRTUAL_CYCBaseIniFile_OnReadValueNames


//****************************** ReadSectionContent()
#define   VIRTUAL_CYCBaseIniFile_OnReadSectionContent() \
    virtual void OnReadSectionContent(LPCSTR ASectionName, OUT TYCIniFileStrings &AContent) const

#define IMPLEMENT_CYCBaseIniFile_OnReadSectionContent(AClass) \
    void AClass::OnReadSectionContent(LPCSTR ASectionName, OUT TYCIniFileStrings &AContent) const

#define  OVERRIDE_CYCBaseIniFile_OnReadSectionContent \
    VIRTUAL_CYCBaseIniFile_OnReadSectionContent


//****************************** ReadString()
#define   VIRTUAL_CYCBaseIniFile_OnReadString() \
    virtual bool OnReadString(LPCSTR ASectionName, LPCSTR AValueName, OUT CString &ARslt)

#define IMPLEMENT_CYCBaseIniFile_OnReadString(AClass) \
    bool AClass::OnReadString(LPCSTR ASectionName, LPCSTR AValueName, OUT CString &ARslt)

#define  OVERRIDE_CYCBaseIniFile_OnReadString \
    VIRTUAL_CYCBaseIniFile_OnReadString


//****************************** WriteString()
#define   VIRTUAL_CYCBaseIniFile_OnWriteString() \
    virtual void OnWriteString(LPCSTR ASectionName, LPCSTR AValueName, LPCSTR AValue)

#define IMPLEMENT_CYCBaseIniFile_OnWriteString(AClass) \
    void AClass::OnWriteString(LPCSTR ASectionName, LPCSTR AValueName, LPCSTR AValue)

#define  OVERRIDE_CYCBaseIniFile_OnWriteString \
    VIRTUAL_CYCBaseIniFile_OnWriteString



class CYCBaseIniFile : public CObject
{
    DECLARE_DYNAMIC(CYCBaseIniFile)

public:
    typedef std::vector<CString>    TYCIniFileStrings;


    static CString  GetValueName(LPCSTR AText);
    static CString  GetValueValue(LPCSTR AText);


    CYCBaseIniFile();
    virtual ~CYCBaseIniFile(void);


    // 是否開啟檔案
    bool    IsOpened() const;

    // 開啟檔案
    bool    Open(LPCSTR    AFileName);
    void    Close();

    // 檔案名稱
    LPCSTR  FileName() const;


    // 資料段落名稱
    LPCSTR  SectionName() const;
    void    SetSectionName(LPCSTR AValue) throw();


    // 讀出所有section的name
    void    ReadSectionNames(OUT TYCIniFileStrings &ANames) const;

    //讀出指定section的所有key的name
    void    ReadValueNames(LPCSTR ASectionName, OUT TYCIniFileStrings &ANames) const;
    void    ReadValueNames(OUT TYCIniFileStrings &ANames) const;

    // 讀出指定section的內容(包含name=value)
    void    ReadSectionContent(LPCSTR ASectionName, OUT TYCIniFileStrings &AContent) const;
    void    ReadSectionContent(OUT TYCIniFileStrings &AContent) const;

    // 資料區段是否存在？
    bool    IsSectionNameExists(LPCSTR ASectionName) const;

    // 資料是否存在？
    bool    IsValueNameExists(LPCSTR ASectionName, LPCSTR AValueName) const;

    // 讀寫資料操作
    CString ReadString (LPCSTR ASectionName, LPCSTR AValueName, LPCSTR ADefault        , bool AIsCreateIfNotExist        );
    CString ReadString (                     LPCSTR AValueName, LPCSTR ADefault = ""   , bool AIsCreateIfNotExist = false);
    int     ReadInt    (LPCSTR ASectionName, LPCSTR AValueName, int    ADefault        , bool AIsCreateIfNotExist        );
    int     ReadInt    (                     LPCSTR AValueName, int    ADefault = 0    , bool AIsCreateIfNotExist = false);
    double  ReadFloat  (LPCSTR ASectionName, LPCSTR AValueName, double ADefault        , bool AIsCreateIfNotExist        );
    double  ReadFloat  (                     LPCSTR AValueName, double ADefault = 0    , bool AIsCreateIfNotExist = false);
    bool    ReadBool   (LPCSTR ASectionName, LPCSTR AValueName, bool   ADefault        , bool AIsCreateIfNotExist        );
    bool    ReadBool   (                     LPCSTR AValueName, bool   ADefault = false, bool AIsCreateIfNotExist = false);

    void    WriteString(LPCSTR ASectionName, LPCSTR AValueName, LPCSTR AValue);
    void    WriteString(                     LPCSTR AValueName, LPCSTR AValue);
    void    WriteInt   (LPCSTR ASectionName, LPCSTR AValueName, int    AValue);
    void    WriteInt   (                     LPCSTR AValueName, int    AValue);
    void    WriteFloat (LPCSTR ASectionName, LPCSTR AValueName, double AValue);
    void    WriteFloat (                     LPCSTR AValueName, double AValue);
    void    WriteBool  (LPCSTR ASectionName, LPCSTR AValueName, bool   AValue);
    void    WriteBool  (                     LPCSTR AValueName, bool   AValue);

protected:

    CString     m_FileName;
    CString     m_SectionName;


    VIRTUAL_CYCBaseIniFile_OnOpen()             = NULL;
    VIRTUAL_CYCBaseIniFile_OnClose()            = NULL;
    VIRTUAL_CYCBaseIniFile_OnReadSectionNames() = NULL;
    VIRTUAL_CYCBaseIniFile_OnReadValueNames()   = NULL;
    VIRTUAL_CYCBaseIniFile_OnReadSectionContent()= NULL;
    VIRTUAL_CYCBaseIniFile_OnReadString()       = NULL;
    VIRTUAL_CYCBaseIniFile_OnWriteString()      = NULL;

};


#define YCIniReadStr(__IniFile, X, __IsCreated)                 X = (__IniFile)->ReadString(#X, X, __IsCreated)
#define YCIniReadInt(__IniFile, X, __IsCreated)                 X = (__IniFile)->ReadInt(#X, X, __IsCreated)
#define YCIniReadIntCast(__IniFile, X, __Type, __IsCreated)     X = (__Type)((__IniFile)->ReadInt(#X, X, __IsCreated))
#define YCIniReadDouble(__IniFile, X, __IsCreated)              X = (__IniFile)->ReadFloat(#X, X, __IsCreated)
#define YCIniReadFloatF(__IniFile, X, __IsCreated)              X = (float)(__IniFile)->ReadFloat(#X, X, __IsCreated)
#define YCIniReadBool(__IniFile, X, __IsCreated)                X = (__IniFile)->ReadBool(#X, X, __IsCreated)

#define YCIniReadStrDef(__IniFile, X, __Def, __IsCreated)       X = (__IniFile)->ReadString(#X, __Def, __IsCreated)
#define YCIniReadIntDef(__IniFile, X, __Def, __IsCreated)       X = (__IniFile)->ReadInt(#X, __Def, __IsCreated)
#define YCIniReadDoubleDef(__IniFile, X, __Def, __IsCreated)    X = (__IniFile)->ReadFloat(#X, __Def, __IsCreated)
#define YCIniReadFloatDef(__IniFile, X, __Def, __IsCreated)     X = (float)(__IniFile)->ReadFloat(#X, __Def, __IsCreated)
#define YCIniReadBoolDef(__IniFile, X, __Def, __IsCreated)      X = (__IniFile)->ReadBool(#X, __Def, __IsCreated)

#define YCIniWriteStr(__IniFile, X)                             (__IniFile)->WriteString(#X, X)
#define YCIniWriteInt(__IniFile, X)                             (__IniFile)->WriteInt(#X, X)
#define YCIniWriteDouble(__IniFile, X)                          (__IniFile)->WriteFloat(#X, X)
#define YCIniWriteFloat(__IniFile, X)                           (__IniFile)->WriteFloat(#X, X)
#define YCIniWriteBool(__IniFile, X)                            (__IniFile)->WriteBool(#X, X)

#define YCIniSecWriteStr(__IniFile, Y, X)                             (__IniFile)->WriteString(Y,#X, X)
#define YCIniSecWriteInt(__IniFile, Y, X)                             (__IniFile)->WriteInt(Y,#X, X)
#define YCIniSecWriteDouble(__IniFile, Y, X)                          (__IniFile)->WriteFloat(Y,#X, X)
#define YCIniSecWriteFloat(__IniFile, Y, X)                           (__IniFile)->WriteFloat(Y,#X, X)
#define YCIniSecWriteBool(__IniFile, Y, X)                            (__IniFile)->WriteBool(Y,#X, X)
//
// CYCBaseIniFile
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
// CYCIniFile
//
class CYCIniFile : public CYCBaseIniFile
{
    DECLARE_DYNAMIC(CYCIniFile)

public:

    CYCIniFile();
    virtual ~CYCIniFile(void);

protected:
    // 開啟檔案
    OVERRIDE_CYCBaseIniFile_OnOpen();
    OVERRIDE_CYCBaseIniFile_OnClose();
    OVERRIDE_CYCBaseIniFile_OnReadSectionNames();
    OVERRIDE_CYCBaseIniFile_OnReadValueNames();
    OVERRIDE_CYCBaseIniFile_OnReadSectionContent();
    OVERRIDE_CYCBaseIniFile_OnReadString();
    OVERRIDE_CYCBaseIniFile_OnWriteString();


};
//
// CYCIniFile
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
// CYCMemIniFile
//
class CYCMemIniFile : public CYCBaseIniFile
{
    DECLARE_DYNAMIC(CYCMemIniFile)

public:
    CYCMemIniFile();
    virtual ~CYCMemIniFile(void);


    // flush
    void Flush();

protected:
    class CValue;
    class CSection;


    class CBaseItem
    {
    public:
        TYCIniFileStrings   m_Comment;
        CString             m_Name;


        CBaseItem()
        {   }

        CBaseItem(const CBaseItem &ASrc)
        { operator=(ASrc); }


        inline CBaseItem& operator=(const CBaseItem &ASrc)
        {
            if (&ASrc != this)
            {
                m_Comment = ASrc.m_Comment;
                m_Name    = ASrc.m_Name;
            }

            return *this;
        }


        inline bool operator==(const CBaseItem &ASrc) const
        {
            if (&ASrc != this)
            {
                return m_Name == ASrc.m_Name &&
                    m_Comment == ASrc.m_Comment;
            }

            return true;
        }


        inline bool operator!=(const CBaseItem &ASrc) const
        { return !(this->operator==(ASrc)); }

    };


    class CValue : public CBaseItem
    {
    public:
        CString     m_Value;


        CValue()
        {   }

        CValue(const CValue &ASrc)
        { operator=(ASrc); }


        inline CValue& operator=(const CValue &ASrc)
        {
            if (&ASrc != this)
            {
                __super::operator =(ASrc);

                m_Value = ASrc.m_Value;
            }

            return *this;
        }


        inline bool operator==(const CValue &ASrc) const
        {
            if (&ASrc != this)
            {
                return __super::operator==(ASrc) &&
                    m_Value == ASrc.m_Value;
            }

            return true;
        }


        inline bool operator!=(const CValue &ASrc) const
        { return !(this->operator ==(ASrc)); }

    };


    typedef std::map<CString, CValue, strYCStrLessNoCase>   CValues;


    class CSection : public CBaseItem
    {
    public:
        CValues     m_Values;



        CSection()
        {   }

        CSection(const CSection &ASrc)
        { operator=(ASrc); }


        inline CSection& operator=(const CSection &ASrc)
        {
            if (&ASrc != this)
            {
                __super::operator =(ASrc);

                m_Values = ASrc.m_Values;
            }

            return *this;
        }


        inline bool operator==(const CSection &ASrc) const
        {
            if (&ASrc != this)
            {
                return __super::operator==(ASrc) &&
                    m_Values == ASrc.m_Values;
            }

            return true;
        }


        inline bool operator!=(const CSection &ASrc) const
        { return !(this->operator==(ASrc)); }

    };


    typedef std::map<CString, CSection, strYCStrLessNoCase>   CSections;


    //===========================
    CSections   m_Sections;
    bool        m_IsModified;


    //===========================
    OVERRIDE_CYCBaseIniFile_OnOpen();
    OVERRIDE_CYCBaseIniFile_OnClose();
    OVERRIDE_CYCBaseIniFile_OnReadSectionNames();
    OVERRIDE_CYCBaseIniFile_OnReadValueNames();
    OVERRIDE_CYCBaseIniFile_OnReadSectionContent();
    OVERRIDE_CYCBaseIniFile_OnReadString();
    OVERRIDE_CYCBaseIniFile_OnWriteString();

};
//
// CYCMemIniFile
///////////////////////////////////////////////////////////////////////////
