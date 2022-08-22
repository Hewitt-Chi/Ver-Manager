#include "stdafx.h"

#include "YCDefine.h"
#include "YCUtils.h"
#include "YCObject.h"
#include "YCComponent.h"
#include "YCException.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////
// CYCComponent
//
// Exception message
#define RS_ComponentCreated                 "This component is created."
#define RS_ComponentNotCreated              "This component is not created."



CYCComponent::TPermanentNameControllers     CYCComponent::m_PermanentNameControllers;
CYCComponent::TPermanentIdControllers       CYCComponent::m_PermanentIdControllers;
CCriticalSection                            CYCComponent::m_PermanentLocker;


CYCComponent* CYCComponent::FromNamePermanent(LPCSTR AName)
{
    CSingleLock LLocker(&m_PermanentLocker, TRUE);

    TPermanentNameControllers::iterator    LIter = m_PermanentNameControllers.find(AName);

    if (LIter != m_PermanentNameControllers.end())
        return LIter->second;

    return NULL;
}

CYCComponent* CYCComponent::FromIdPermanent(DWORD AId)
{
    CSingleLock LLocker(&m_PermanentLocker, TRUE);


    TPermanentIdControllers::iterator    LIter = m_PermanentIdControllers.find(AId);

    if (LIter != m_PermanentIdControllers.end())
        return LIter->second;

    return NULL;
}


IMPLEMENT_DYNAMIC(CYCComponent, CYCObject)


CYCComponent::CYCComponent(void)
: CYCObject()
, m_Id(INVALID_YCCOMPONENTID_VALUE)
, m_Name("")
, m_IsCreated(false)
, m_CreateThreadId((DWORD)-1)
{
    OnPreset();
}

CYCComponent::~CYCComponent(void)
{
#ifdef _DEBUG
    const CString LName = m_DebugName;

    OnDestroy();

    TRACE("%s(%s).Destructor().\n", ClassName(), LName);
#else
    OnDestroy();
#endif
}

bool    CYCComponent::Create()
{ 
    ASSERT(!m_IsCreated);

#ifdef _DEBUG
    CString LName = m_Name;
#endif

    if (!m_IsCreated)
    {
        if (m_Id == INVALID_YCCOMPONENTID_VALUE)
        {
#define __AUTOID_Begin      0x8000

            static DWORD LObjectID = __AUTOID_Begin;

            InterlockedCompareExchange((LONG *)&LObjectID, (LONG)__AUTOID_Begin, (LONG)INVALID_YCCOMPONENTID_VALUE);

            SetId((DWORD)InterlockedIncrement((LONG *)&LObjectID));

#undef __AUTOID_Begin
        }

        if (m_Name.IsEmpty())
        {
            CString LStr;

            LStr.Format("%s%d", ClassName(), m_Id);

            if (LStr[0] == 'C')
                LStr.Delete(0, 1);

            SetName(LStr);
        }

        m_IsCreated      = true;
        m_CreateThreadId = GetCurrentThreadId();


#ifdef _DEBUG
        LName = m_Name;
#endif

        if (OnCreate())
        {
#ifdef _DEBUG
            TRACE("Create a new %s object which is named \"%s\" succ.\n", ClassName(), LName);
#endif
            return true;
        }
        else
        {
            Free();
        }
    }

#ifdef _DEBUG
    TRACE("Create a new %s object which is named \"%s\" fail.\n", ClassName(), LName);
#endif

    return false;
}

void    CYCComponent::Free()
{
    if (m_IsCreated)
    {
#if 0
        OnDestroy();
        OnPreset();
#else
        DoOnDestroy();
        DoOnPreset();
#endif

        {
            CSingleLock LLocker(&m_PermanentLocker, TRUE);

            {
                TPermanentIdControllers::iterator    LIter = m_PermanentIdControllers.find(m_Id);

                if (LIter != m_PermanentIdControllers.end())
                    m_PermanentIdControllers.erase(LIter);
            }

            {
                TPermanentNameControllers::iterator    LIter = m_PermanentNameControllers.find(m_Name);

                if (LIter != m_PermanentNameControllers.end())
                    m_PermanentNameControllers.erase(LIter);
            }
        }


        const CString LName = m_Name;

        m_IsCreated      = false;
        m_CreateThreadId = DWORD(-1);
        m_Name           = "";
        m_Id             = INVALID_YCCOMPONENTID_VALUE;

        TRACE("%s object %s is Destroyed.\n", ClassName(), LName);
    }
}

bool    CYCComponent::IsCreated() const
{
    return m_IsCreated;
}

DWORD   CYCComponent::Id() const
{
    return m_Id;
}

void    CYCComponent::SetId(DWORD AValue)
{
    ASSERT(AValue != INVALID_YCCOMPONENTID_VALUE);
    ASSERT(m_Id == INVALID_YCCOMPONENTID_VALUE);

    if (AValue != INVALID_YCCOMPONENTID_VALUE &&
        m_Id == INVALID_YCCOMPONENTID_VALUE)
    {
        CSingleLock LLocker(&m_PermanentLocker, TRUE);

        if (m_PermanentIdControllers.find(AValue) == m_PermanentIdControllers.end())
        {
            m_Id = AValue;
            m_PermanentIdControllers[AValue] = this;
        }
        else
        {
            ASSERT(FALSE);
        }
    }
}

LPCSTR  CYCComponent::Name() const
{
    return m_Name;
}

void    CYCComponent::SetName(LPCSTR AValue)
{
    ASSERT(strlen(AValue) > 0);
    ASSERT(m_Name.IsEmpty());

    if (strlen(AValue) > 0 && m_Name.IsEmpty())
    {
        CSingleLock LLocker(&m_PermanentLocker, TRUE);

        if (m_PermanentNameControllers.find(AValue) == m_PermanentNameControllers.end())
        {
            m_Name = AValue;
#ifdef _DEBUG
            m_DebugName = AValue;
#endif
            m_PermanentNameControllers[AValue] = this;
        }
    }
}

DWORD   CYCComponent::CreateThreadId() const
{
    return m_CreateThreadId;
}

#if 0
void    CYCComponent::ThrowIfNotCreated() throw()
{
    ASSERT(m_IsCreated);

    if (!m_IsCreated)
        YCThrowComponentException(this, YCCOMPONENT_Exception_ComponentNotCreated, RS_ComponentNotCreated);
}

void    CYCComponent::ThrowIfCreated() throw()
{
    ASSERT(!m_IsCreated);

    if (m_IsCreated)
        YCThrowComponentException(this, YCCOMPONENT_Exception_ComponentCreated, RS_ComponentCreated);
}
#endif

IMPLEMENT_CYCComponent_OnCreate(CYCComponent)
{
    return true;
}

void    CYCComponent::DoOnDestroy()
{
    CYCComponent::OnDestroy();
}

void    CYCComponent::OnDestroy()
{
}

void    CYCComponent::DoOnPreset()
{
    CYCComponent::OnPreset();
}

void    CYCComponent::OnPreset()
{
}
//
// CYCComponent
////////////////////////////////////////
