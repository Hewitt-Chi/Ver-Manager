#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

class CYCFileVersion
{
public:
    CYCFileVersion(void);
    CYCFileVersion(LPCSTR AFileName);
    virtual ~CYCFileVersion(void);

    LPCSTR  Comments() const;
    LPCSTR  InternalName() const;
    LPCSTR  ProductName() const;
    LPCSTR  CompanyName() const;
    LPCSTR  LegalCopyright() const;
    LPCSTR  ProductVersion() const;
    LPCSTR  FileDescription() const;
    LPCSTR  FileVersion() const;
    LPCSTR  PrivateBuild() const;
    LPCSTR  OriginalFilename() const;

    bool    Open(LPCSTR AFileName);

private:
    CString  m_Comments;
    CString  m_InternalName;
    CString  m_ProductName;
    CString  m_CompanyName;
    CString  m_LegalCopyright;
    CString  m_ProductVersion;
    CString  m_FileDescription;
    CString  m_FileVersion;
    CString  m_PrivateBuild;
    CString  m_OriginalFilename;

};
