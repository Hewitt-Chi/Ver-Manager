#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

class CYCSignalLightStatic : public CYCBitStatic
{
    DECLARE_DYNAMIC(CYCSignalLightStatic)

public:
    CYCSignalLightStatic();
    virtual ~CYCSignalLightStatic();

    // �O�_��ܤϦV���T��
    inline bool IsReverseSignal() const
    { return m_IsReverseSignal; };

    void SetReverseSignal(bool AValue);

    // �E�A���ϥܸ귽
    inline WORD SignaledBMPResID() const
    { return m_SignaledBMPResID; };
   
    void SetSignaledBMPResID(WORD AValue);

    // �]�w��A���ϥܸ귽
    inline WORD UnsignaledBMPResID() const
    { return m_UnsignaledBMPResID; };

    void SetUnsignaledBMPResID(WORD AValue);

    // �]�w�ϥܸ귽
    void SetBMPResID(WORD ASignaledBMPResID, WORD AUnsignaledBMPResID);

    // �O�_�O�E�A�H
    inline bool IsSignaled() const
    { return m_IsSignaled; };

    void SetSignaled(bool AValue);

protected:
    bool    m_IsReverseSignal;
    bool    m_IsSignaled;
    WORD    m_SignaledBMPResID;
    WORD    m_UnsignaledBMPResID;

    virtual afx_msg void OnUpdateCommandUI(CCmdUI* pCmdUI);

    void UpdateDisplay();

    DECLARE_MESSAGE_MAP()

};
