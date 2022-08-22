#include "StdAfx.h"


#include "YCObject.h"


#include "YCXml.h"


#include "YCUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CYCXMLElement, CYCObject)


CYCXMLElement::CYCXMLElement() : CYCObject()
{
}

CYCXMLElement::CYCXMLElement(const CYCXMLElement &ASrc) : CYCObject()
{
    Assign(&ASrc);
}

CYCXMLElement::~CYCXMLElement()
{
    m_Elements.clear();
}

IMPLEMENT_CYCObject_Assign(CYCXMLElement)
{
    if (this != AValue)
    {
        // __super::Assign(AValue);

        const CYCXMLElement *LValue = dynamic_cast<const CYCXMLElement *>(AValue);

        if (LValue)
        {
            YCObjectAssignField(m_Tag);
            YCObjectAssignField(m_Attributes);
            YCObjectAssignField(m_Text);

            m_Elements.clear();

            for (TElements::const_iterator    LIter = LValue->m_Elements.begin();
                LIter != LValue->m_Elements.end(); LIter ++)
            {
                CYCXMLElement   *LElement = new CYCXMLElement(**LIter);

                m_Elements.push_back(LElement);
                LElement->ReleaseRef();
            }
        }
    }
}

LPCSTR  CYCXMLElement::Tag() const
{
    return m_Tag;
}

void    CYCXMLElement::SetTag(LPCSTR AValue)
{
    m_Tag = AValue;
}

int     CYCXMLElement::AttributeCount() const
{
    return static_cast<int>(m_Attributes.size());
}

int     CYCXMLElement::AttributeIndexOf(LPCSTR AName) const
{
    int LRslt = 0;

    for (TAttributes::const_iterator   LIter = m_Attributes.begin();
        LIter != m_Attributes.end(); LIter ++, LRslt ++)
    {
        if (!LIter->first.Compare(AName))
            return LRslt;
    }

    return -1;
}

LPCSTR  CYCXMLElement::AttributeNameAt(int     AIdx) const
{
    if (AIdx >= 0 && AIdx < static_cast<int>(m_Attributes.size()))
        return m_Attributes[AIdx].first;

    return NULL;
}

LPCSTR  CYCXMLElement::AttributeTextOf(LPCSTR  AName) const
{
    TAttributes::const_iterator   LIter = std::find_if(m_Attributes.begin(), m_Attributes.end(), strFindAttributeFunc(AName));

    if (LIter != m_Attributes.end())
        return LIter->second;

    return NULL;
}

LPCSTR  CYCXMLElement::AttributeTextAt(int     AIdx) const
{
    if (AIdx >= 0 && AIdx < static_cast<int>(m_Attributes.size()))
        return m_Attributes[AIdx].second;

    return NULL;
}

bool    CYCXMLElement::RemoveAttributeOf(LPCSTR    AName)
{
    TAttributes::iterator   LIter = std::find_if(m_Attributes.begin(), m_Attributes.end(), strFindAttributeFunc(AName));

    if (LIter != m_Attributes.end())
    {
        m_Attributes.erase(LIter);

        return true;
    }

    return false;
}

bool    CYCXMLElement::RemoveAttributeAt(int       AIdx)
{
    if (AIdx >= 0 && AIdx < static_cast<int>(m_Attributes.size()))
    {
        m_Attributes.erase(m_Attributes.begin() + AIdx);

        return true;
    }

    return false;
}

bool    CYCXMLElement::SetAttributeAt(int      AIdx , LPCSTR AValue)
{
    if (AIdx >= 0 && AIdx < static_cast<int>(m_Attributes.size()))
    {
        m_Attributes[AIdx].second = AValue;

        return true;
    }

    return false;
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, LPCSTR AValue)
{
    TAttributes::iterator   LIter = std::find_if(m_Attributes.begin(), m_Attributes.end(), strFindAttributeFunc(AName));

    if (LIter != m_Attributes.end())
    {
        LIter->second = AValue;
    }
    else
    {
        TAttributeItem  LItem(AName, AValue);

        m_Attributes.push_back(LItem);
    }
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, bool   AValue)
{
    SetAttributeOf(AName, YCBoolText(AValue));
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, char   AValue)
{
    CString LStr;

    LStr.Format("%c", AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, short  AValue)
{
    CString LStr;

    LStr.Format("%d", AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, int    AValue)
{
    CString LStr;

    LStr.Format("%d", AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, BYTE   AValue)
{
    CString LStr;

    LStr.Format("%u", AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, WORD   AValue)
{
    CString LStr;

    LStr.Format("%u", AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, UINT   AValue)
{
    CString LStr;

    LStr.Format("%u", AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, long   AValue)
{
    CString LStr;

    LStr.Format("%d", AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, DWORD  AValue)
{
    CString LStr;

    LStr.Format("%u", AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, float  AValue, int ADigit)
{
    CString LStr;

    LStr.Format("%.*f", ADigit, AValue);
    SetAttributeOf(AName, LStr);
}

void    CYCXMLElement::SetAttributeOf(LPCSTR   AName, double AValue, int ADigit)
{
    CString LStr;

    LStr.Format("%.*f", ADigit, AValue);
    SetAttributeOf(AName, LStr);
}

LPCSTR  CYCXMLElement::Text() const
{
    return m_Text;
}

void    CYCXMLElement::SetText(LPCSTR AValue)
{
    m_Text = AValue;
}

int     CYCXMLElement::ElementCount() const
{
    return static_cast<int>(m_Elements.size());
}

bool    CYCXMLElement::QueryElementAt(int AIdx, OUT CYCXMLElementHandle &AResultHandle) const
{
    if (AIdx >= 0 && AIdx < static_cast<int>(m_Elements.size()))
    {
        AResultHandle = m_Elements[AIdx];

        return true;
    }

    return false;
}

bool    CYCXMLElement::RemoveElementAt(int AIdx)
{
    if (AIdx >= 0 && AIdx < static_cast<int>(m_Elements.size()))
    {
        m_Elements.erase(m_Elements.begin() + AIdx);

        return true;
    }

    return false;
}

bool    CYCXMLElement::SetElementAt(int AIdx , CYCXMLElement *AElement)
{
    if (AIdx >= 0 && AIdx < static_cast<int>(m_Elements.size()))
    {
        m_Elements[AIdx] = AElement;

        return true;
    }

    return false;
}

void    CYCXMLElement::PushElementBack(CYCXMLElement *AElement)
{
    m_Elements.push_back(AElement);
}

bool    CYCXMLElement::InsertElementAt(int AIdx , CYCXMLElement *AElement)
{
    if (AIdx >= 0 && AIdx <= static_cast<int>(m_Elements.size()))
    {
        m_Elements.insert(m_Elements.begin() + AIdx, AElement);

        return true;
    }

    return false;
}

bool    CYCXMLElement::AssignElementContentAt(int AIdx , CYCXMLElement *AElement)
{
    if (AIdx >= 0 && AIdx < static_cast<int>(m_Elements.size()))
    {
        m_Elements[AIdx]->Assign(AElement);

        return true;
    }

    return false;
}

CString CYCXMLElement::XMLText() const
{
    CString LStr;

    XMLText(LStr);

    return LStr;
}

void    CYCXMLElement::XMLText(OUT CString &ARslt) const
{
    if (!m_Tag.IsEmpty())
    {
        // 有屬性
        if (m_Attributes.size())
        {
            ARslt.AppendFormat("<%s", m_Tag);

            for (TAttributes::const_iterator   LIter = m_Attributes.begin();
                LIter != m_Attributes.end(); LIter ++)
            {
                if (!LIter->first.IsEmpty())
                {
                    CString LSecond = LIter->second;

                    LSecond.Trim('\"');
                    LSecond.Replace("<", "&lt;");
                    LSecond.Replace(">", "&gt;");
                    LSecond.Replace("&", "&amp;");
                    LSecond.Replace("'", "&apos;");
                    LSecond.Replace("\"", "&quot;");

                    ARslt.AppendFormat(" %s=\"%s\"", LIter->first, LSecond);
                }
            }

            //     沒有資料                且      沒有子元素
            if (m_Text.IsEmpty() && !m_Elements.size())
            {
                ARslt.Append("/>");
                return;
            }

            ARslt.AppendChar('>');
        }
        // 沒有屬性
        else
        {
            //     沒有資料                且      沒有子元素
            if (m_Text.IsEmpty() && !m_Elements.size())
            {
                ARslt.AppendFormat("<%s/>", m_Tag);
                return;
            }

            ARslt.AppendFormat("<%s>", m_Tag);
        }

        CString LData = m_Text;

        LData.Replace("<", "&lt;");
        LData.Replace(">", "&gt;");
        LData.Replace("&", "&amp;");
        LData.Replace("'", "&apos;");
        LData.Replace("\"", "&quot;");

        ARslt.Append(LData);

        for (TElements::const_iterator    LIter = m_Elements.begin();
            LIter != m_Elements.end(); LIter ++)
        {
            (*LIter)->XMLText(ARslt);
        }

        ARslt.AppendFormat("</%s>", m_Tag);
    }
}

void    CYCXMLElement::SaveToFile(LPCSTR AFileName) const
{
    try
    {
        YCForceDirFromFileName(AFileName);

        CStdioFile  LFile;

        if (LFile.Open(AFileName, CFile::modeCreate | CFile::modeWrite))
        {
            LFile.WriteString("<?xml version=\"1.0\" encoding=\"Big5\"?>");     // add by Mike, 20140210, 會造成中文字亂碼
            //LFile.WriteString("<?xml version=\"1.0\" encoding=\"utf-8\"?>");  // Mark by Mike, 20140210, 會造成中文字亂碼
            LFile.WriteString(XMLText());
        }
    }
    catch (...)
    {
        TRACE("Save to xml file %s fail.\n", AFileName);
    }
}
