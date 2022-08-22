#include "StdAfx.h"

#include "YCUtils.h"
#include "YCObject.h"
#include "YCComponent.h"
#include "YCControl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////
// CYCControl : 
//      Base Class of this library
//
IMPLEMENT_DYNAMIC(CYCControl, CYCComponent)


CYCControl::CYCControl(void)
: CYCComponent()
, m_Parent(NULL)
{
    OnPreset();
}

CYCControl::~CYCControl(void)
{
    OnDestroy();
}

IMPLEMENT_CYCComponent_OnDestroy(CYCControl)
{
    while (m_Childs.size() > 0)
        m_Childs.back()->SetParent(NULL);

    SetParent(NULL);
}

IMPLEMENT_CYCComponent_OnPreset(CYCControl)
{
    m_IsOwnChild = false;
}

CYCControl*
/**/    CYCControl::Parent() const
{
    return m_Parent;
}

void    CYCControl::SetParent(CYCControl *AParent)
{
    CYCControl  *LOldParent = m_Parent;

    if (LOldParent)
        LOldParent->RemoveChild(this);

    if (AParent)
        AParent->AddChild(this);
}

bool    CYCControl::IsOwnChild() const
{
    return m_IsOwnChild;
}

void    CYCControl::SetIsOwnChild(bool AValue)
{
    m_IsOwnChild = AValue;
}

INT_PTR CYCControl::ChildCount() const
{
    return m_Childs.size();
}

CYCControl*
/**/    CYCControl::ChildAt(INT_PTR AIdx) const
{
    if (AIdx >= 0 && AIdx < (int)m_Childs.size())
        return m_Childs[AIdx];

    return NULL;
}

bool    CYCControl::IsChildRelationship(const CYCControl* const AControl) const
{
    if (AControl)
        return AControl->IsParentRelationship(this);

    return false;
}

bool    CYCControl::IsParentRelationship(const CYCControl* const AControl) const
{
    if (AControl)
    {
        for (CYCControl *LParent = m_Parent; LParent; LParent = LParent->m_Parent)
        {
            if (LParent == AControl)
                return true;
        }
    }

    return false;
}

bool    CYCControl::QueryChildOf(DWORD AChildId, void **AChild)
{
    for (std::deque<CYCControl *>::const_iterator   LIter = m_Childs.begin();
        LIter != m_Childs.end(); LIter ++)
    {
        CYCControl  *LChild = *LIter;

        if (AChildId == LChild->Id())
        {
            if (AChild)
            {
                *AChild = LChild;
                LChild->AddRef();
            }

            return true;
        }
    }

    if (AChild)
        *AChild = NULL;

    return false;
}

bool    CYCControl::QueryChildOf(LPCSTR AChildName, void **AChild)
{
    for (std::deque<CYCControl *>::const_iterator   LIter = m_Childs.begin();
        LIter != m_Childs.end(); LIter ++)
    {
        CYCControl  *LChild = *LIter;

        if (_stricmp(AChildName, LChild->Name()) == 0)
        {
            if (AChild)
            {
                *AChild = LChild;
                LChild->AddRef();
            }

            return true;
        }
    }

    if (AChild)
        *AChild = NULL;

    return false;
}

bool    CYCControl::QueryChildAt(INT_PTR AIdx, void **AChild)
{
    if (AIdx >= 0 && AIdx < (int)m_Childs.size())
    {
        if (AChild)
        {
            *AChild = m_Childs[AIdx];
            m_Childs[AIdx]->AddRef();
        }

        return true;
    }

    if (AChild)
        *AChild = NULL;

    return false;
}

#if 0
IMPLEMENT_CYCControl_OnChildAddRemove(CYCControl)
{
}
#endif

void    CYCControl::AddChild(CYCControl *AChild)
{
    ASSERT(AChild);
    ASSERT(AChild->m_Parent == NULL);

    if (std::find(m_Childs.begin(), m_Childs.end(), AChild) == m_Childs.end())
    {
        m_Childs.push_back(AChild);

        AChild->m_Parent = this;

#if 0
        OnChildAddRemove(AChild, true);
#endif
    }
}

bool    CYCControl::RemoveChild(CYCControl *AChild)
{
    ASSERT(AChild);
    ASSERT(AChild->m_Parent == this);

    std::deque<CYCControl *>::iterator  LIter = std::find(m_Childs.begin(), m_Childs.end(), AChild);

    if (LIter != m_Childs.end())
    {
        bool LIsOwnChild = m_IsOwnChild;

        m_Childs.erase(LIter);

        if (AChild->m_Parent == this)
            AChild->m_Parent = NULL;

#if 0
        OnChildAddRemove(AChild, false);
#endif
        if (LIsOwnChild && AChild)
            AChild->Free();

        return true;
    }

    return false;
}
//
// CYCControl
////////////////////////////////////////
