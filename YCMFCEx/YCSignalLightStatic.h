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

    // 是否顯示反向的訊號
    inline bool IsReverseSignal() const
    { return m_IsReverseSignal; };

    void SetReverseSignal(bool AValue);

    // 激態的圖示資源
    inline WORD SignaledBMPResID() const
    { return m_SignaledBMPResID; };
   
    void SetSignaledBMPResID(WORD AValue);

    // 設定基態的圖示資源
    inline WORD UnsignaledBMPResID() const
    { return m_UnsignaledBMPResID; };

    void SetUnsignaledBMPResID(WORD AValue);

    // 設定圖示資源
    void SetBMPResID(WORD ASignaledBMPResID, WORD AUnsignaledBMPResID);

    // 是否是激態？
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
