#include "StdAfx.h"

#include "YCUtils.h"
#include "YCBitStatic.h"
#include "YCSignalLightStatic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////////
// CYCSignalLightStatic
//
IMPLEMENT_DYNAMIC(CYCSignalLightStatic, CYCBitStatic)

CYCSignalLightStatic::CYCSignalLightStatic()
: CYCBitStatic(), m_IsSignaled(false), m_IsReverseSignal(false)
, m_SignaledBMPResID(0), m_UnsignaledBMPResID(0)
{
    SetBitmapResourceID(m_UnsignaledBMPResID);
}

CYCSignalLightStatic::~CYCSignalLightStatic()
{
}


BEGIN_MESSAGE_MAP(CYCSignalLightStatic, CYCBitStatic)
    //ON_UPDATE_COMMAND_UI_REFLECT(&CYCSignalLightStatic::OnUpdateCommandUI)
END_MESSAGE_MAP()


void CYCSignalLightStatic::OnUpdateCommandUI(CCmdUI *pCmdUI)
{
    //if (pCmdUI->m_pOther->IsWindowVisible())
    //    UpdateDisplay();
}

void CYCSignalLightStatic::SetReverseSignal(bool AValue)
{
    if (m_IsReverseSignal != AValue)
    {
        m_IsReverseSignal = AValue;
        UpdateDisplay();        
    }
}

void CYCSignalLightStatic::SetSignaledBMPResID(WORD AValue)
{
    if (m_SignaledBMPResID != AValue)
    {
        m_SignaledBMPResID = AValue;
        UpdateDisplay();
    }
}

void CYCSignalLightStatic::SetUnsignaledBMPResID(WORD AValue)
{
    if (m_UnsignaledBMPResID != AValue)
    {
        m_UnsignaledBMPResID = AValue;
        UpdateDisplay();
    }
}

void CYCSignalLightStatic::SetBMPResID(WORD ASignaledBMPResID, WORD AUnsignaledBMPResID)
{
    if (m_SignaledBMPResID != ASignaledBMPResID || m_UnsignaledBMPResID != AUnsignaledBMPResID)
    {
        m_SignaledBMPResID = ASignaledBMPResID;
        m_UnsignaledBMPResID = AUnsignaledBMPResID;

        UpdateDisplay();
    }
}

void CYCSignalLightStatic::SetSignaled(bool AValue)
{
    if (m_IsSignaled != AValue)
    {
        m_IsSignaled = AValue;
        UpdateDisplay();
    }
}

void CYCSignalLightStatic::UpdateDisplay()
{
    bool LSignaled = m_IsReverseSignal ? !m_IsSignaled : m_IsSignaled;

    SetBitmapResourceID(LSignaled ? m_SignaledBMPResID : m_UnsignaledBMPResID);
}
//
// CYCSignalLightStatic
////////////////////////////////////////////