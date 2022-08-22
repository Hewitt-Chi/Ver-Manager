#pragma once


#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


class CYCXMLElement;


typedef CYCObjectHandle<CYCXMLElement>      CYCXMLElementHandle;


class CYCXMLElement : public CYCObject
{
    DECLARE_DYNAMIC(CYCXMLElement)

public:
    CYCXMLElement();
    CYCXMLElement(const CYCXMLElement &ASrc);
    virtual ~CYCXMLElement();


    OVERRIDE_CYCObject_Assign();


    LPCSTR  Tag() const;
    void    SetTag(LPCSTR AValue);

    int     AttributeCount() const;
    int     AttributeIndexOf(LPCSTR AName) const;
    LPCSTR  AttributeNameAt(int     AIdx) const;
    LPCSTR  AttributeTextOf(LPCSTR  AName) const;
    LPCSTR  AttributeTextAt(int     AIdx) const;
    bool    RemoveAttributeOf(LPCSTR    AName);
    bool    RemoveAttributeAt(int       AIdx);
    bool    SetAttributeAt(int      AIdx , LPCSTR AValue);
    void    SetAttributeOf(LPCSTR   AName, LPCSTR AValue);
    void    SetAttributeOf(LPCSTR   AName, bool   AValue);
    void    SetAttributeOf(LPCSTR   AName, char   AValue);
    void    SetAttributeOf(LPCSTR   AName, short  AValue);
    void    SetAttributeOf(LPCSTR   AName, int    AValue);
    void    SetAttributeOf(LPCSTR   AName, BYTE   AValue);
    void    SetAttributeOf(LPCSTR   AName, WORD   AValue);
    void    SetAttributeOf(LPCSTR   AName, UINT   AValue);
    void    SetAttributeOf(LPCSTR   AName, long   AValue);
    void    SetAttributeOf(LPCSTR   AName, DWORD  AValue);
    void    SetAttributeOf(LPCSTR   AName, float  AValue, int ADigit);
    void    SetAttributeOf(LPCSTR   AName, double AValue, int ADigit);


    LPCSTR  Text() const;
    void    SetText(LPCSTR AValue);


    int     ElementCount() const;
    bool    QueryElementAt(int AIdx, OUT CYCXMLElementHandle &AResultHandle) const;
    bool    RemoveElementAt(int AIdx);
    bool    SetElementAt(int AIdx , CYCXMLElement *AElement);
    void    PushElementBack(CYCXMLElement *AElement);
    bool    InsertElementAt(int AIdx , CYCXMLElement *AElement);
    bool    AssignElementContentAt(int AIdx , CYCXMLElement *AElement);
    

    CString XMLText() const;
    void    XMLText(OUT CString &AXMLText) const;

    void    SaveToFile(LPCSTR AFileName) const;

private:
    typedef std::pair<CString, CString> TAttributeItem;
    typedef std::deque<TAttributeItem>  TAttributes;

    struct strFindAttributeFunc
    {
        const CString   Name;


        strFindAttributeFunc(LPCSTR AName) : Name(AName)
        {   }

        inline bool operator()(const TAttributeItem &AItem)
        { return !Name.Compare(AItem.first); }
    };

    typedef std::deque<CYCXMLElementHandle> TElements;


    CString     m_Tag;
    TAttributes m_Attributes;
    CString     m_Text;

    TElements   m_Elements;

};
