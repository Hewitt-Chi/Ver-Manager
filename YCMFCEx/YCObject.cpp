#include "StdAfx.h"

#include <typeinfo.h>
#include "YCUtils.h"
#include "YCObject.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////
// CYCObject
//
IMPLEMENT_DYNAMIC(CYCObject, CObject)


CYCObject::CYCObject()
: CObject()
, m_RefCount(1)
{
}

CYCObject::~CYCObject()
{
    ASSERT(m_RefCount <= 1);
    ASSERT(m_RefCount >= 0);
}

LPCSTR CYCObject::ClassName() const
{
    CRuntimeClass   *LRC = GetRuntimeClass();

    if (LRC)
        return LRC->m_lpszClassName;

    return NULL;
}

LONG CYCObject::RefCount() const
{
    return m_RefCount;
}

LONG CYCObject::AddRef()
{
    return InterlockedIncrement(&m_RefCount);
}

LONG CYCObject::ReleaseRef()
{
    const LONG LRefCount = InterlockedDecrement(&m_RefCount);

    if (LRefCount > 0)
        return LRefCount;
    else
        delete this;

    return 0;
}

IMPLEMENT_CYCObject_Assign(CYCObject)
{
    ASSERT(FALSE);
}

IMPLEMENT_CYCObject_IsEqual(CYCObject)
{
    if (AValue == this || (AValue && GetRuntimeClass() == AValue->GetRuntimeClass()))
        return true;

    return false;
}
//
// CYCObject
////////////////////////////////////////
