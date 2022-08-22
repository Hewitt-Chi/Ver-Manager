#include "StdAfx.h"

#include "YCUtils.h"
#include "YCObject.h"
#include "YCData.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////
// CYCData
//
IMPLEMENT_SERIAL(CYCData, CYCObject, 0x01)


CYCData::CYCData()
: CYCObject()
, m_IsValid(false)
{
}

CYCData::CYCData(const CYCData &ASrc)
: CYCObject()
, m_IsValid(ASrc.m_IsValid)
{
    Assign(&ASrc);
}

IMPLEMENT_CObject_Serialize(CYCData)
{
    __super::Serialize(AArchive);

    AArchive || m_IsValid;
}

IMPLEMENT_CYCObject_Assign(CYCData)
{
    if (AValue != this)
    {
        const CYCData *LValue = dynamic_cast<const CYCData *>(AValue);

        if (LValue)
            YCObjectAssignField(m_IsValid);
    }
}

IMPLEMENT_CYCObject_IsEqual(CYCData)
{
    if (AValue != this)
    {
        const CYCData *LValue = dynamic_cast<const CYCData *>(AValue);

        return YCIsObjectFieldEqual(m_IsValid);
    }

    return true;
}

bool CYCData::IsValid() const
{
    return m_IsValid;
}

void CYCData::ResetValid()
{
    m_IsValid = false;
}

void CYCData::SetValid()
{
    m_IsValid = true;
}

IMPLEMENT_CYCData_UpdateValid(CYCData)
{
}
//
// CYCData
////////////////////////////////////////
