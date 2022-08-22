#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


///////////////////////////////////////////////////////
// TYCTrayIconMouseActionEvent(CObject *ASender, LPARAM ATrayIconMouseAction);
//
typedef void (CObject::*TYCTrayIconMouseActionEvent)(CObject *ASender, LPARAM ATrayIconMouseAction);


struct strYCTrayIconMouseActionEvent
{
    CObject                         *Handler;
    TYCTrayIconMouseActionEvent     HandlerFunc;

    strYCTrayIconMouseActionEvent() : Handler(NULL), HandlerFunc(NULL)
    {   }

    strYCTrayIconMouseActionEvent(CObject  *AHandler, TYCTrayIconMouseActionEvent AHandlerFunc)
    { Handler = AHandler, HandlerFunc = AHandlerFunc; }

    strYCTrayIconMouseActionEvent(const strYCTrayIconMouseActionEvent &ASrc)
    { operator =(ASrc); }

    inline strYCTrayIconMouseActionEvent& operator =(const strYCTrayIconMouseActionEvent &ASrc)
    { Handler = ASrc.Handler, HandlerFunc = ASrc.HandlerFunc; return *this; }

    inline bool operator ==(const strYCTrayIconMouseActionEvent &ASrc) const
    { return Handler == ASrc.Handler && HandlerFunc == ASrc.HandlerFunc; }

    inline void operator()(CObject *ASender, LPARAM ATrayIconMouseAction)
    { if (Handler && HandlerFunc) (Handler->*HandlerFunc)(ASender, ATrayIconMouseAction); }
};

#define NULL_YCTrayIconMouseActionEvent             strYCTrayIconMouseActionEvent()
#define YCTrayIconMouseActionEvent(X, Y)            strYCTrayIconMouseActionEvent(X, static_cast<TYCTrayIconMouseActionEvent>(Y))
//
// TYCTrayIconMouseActionEvent(CObject *ASender, LPARAM ATrayIconMouseAction);
///////////////////////////////////////////////////////




class CYCTrayIcon : public CWnd
{
    DECLARE_DYNAMIC(CYCTrayIcon)

public:
    enum enmDefaultAction
    {
        daNone                  = 0x00,
        daClickShowHideApp      = 0x01,
        daDoubleClickShowHideApp= 0x02,
        daHideTrayWhenShowApp   = 0x04,
        daAll                   = 0xFF,
    };

    typedef DWORD   enmDefaultActions;



    CYCTrayIcon();
    virtual ~CYCTrayIcon();

    // 建立trayicon
    bool Create(bool AIsInitShow);
    void Free();

    // 預設的動作
    inline enmDefaultActions    DefaultActions() const                          { return m_DefaultActions;          }
    inline void                 SetDefaultActions(enmDefaultActions AValue)     { m_DefaultActions = AValue;        }


    // 提示字串
    inline LPCSTR TipText() const                   { return m_TipText;                                             }
    inline void   SetTipText(LPCSTR AValue)         { m_TipText = AValue; UpdateTrayIcon(NIM_MODIFY);       }


    // 圖示
    inline HICON Icon() const                       { return m_Icon;                                                }
    inline bool  SetIconResID(UINT AValue)          { return SetIcon(AfxGetApp()->LoadIcon(AValue));                }
    inline bool  SetIcon(HICON AValue)              { m_Icon = AValue; return UpdateTrayIcon(NIM_MODIFY);   }
    inline bool  SetIconResName(LPCTSTR AValue)     { return SetIcon(AValue ? AfxGetApp()->LoadIcon(AValue) : NULL); }
    inline bool  SetStandardIcon(LPCTSTR AValue)    { return SetIcon(::LoadIcon(NULL, AValue));                     }

    // 是否是可顯示的
    inline bool IsVisible() const                   { return m_IsVisible;                                           }
    inline void SetIsVisible(bool AValue)           { if (m_IsVisible != AValue) { m_IsVisible = AValue; UpdateTrayIcon(NIM_MODIFY); } }

    // Pop menu
    inline CMenu* PopupMenu()                       { return m_PopupMenu;                                           }
    inline void   SetPoppuMenu(CMenu *AValue)       { m_PopupMenu = AValue;                                         }


    // Tray icon mouse evetn
    inline const strYCTrayIconMouseActionEvent& OnTrayIconMouseAction()
    { return m_OnTrayIconMouseAction; }

    inline void SetOnTrayIconMouseAction(const strYCTrayIconMouseActionEvent &AValue)
    { m_OnTrayIconMouseAction = AValue; }



    // 顯示Application
    void ShowApplication();

    // 隱藏Application
    void HideApplication();

    void Show();
    void Hide();

protected:
    enum enmMessage
    {
        CM_TrayIconNotification = (WM_USER + 923),
        CM_ShowHideApplication
    };


    afx_msg LRESULT CMTrayIconNotification(WPARAM ATrayIconID, LPARAM ATrayIconAction);
    afx_msg LRESULT CMShowHideApplication(WPARAM AIsShowApp, LPARAM lParam);

    DECLARE_MESSAGE_MAP()

private:

    strYCTrayIconMouseActionEvent   m_OnTrayIconMouseAction;

    CString             m_TipText;
    HICON               m_Icon;
    bool                m_IsVisible;
    enmDefaultActions   m_DefaultActions;

    CMenu               *m_PopupMenu;
    bool                m_IsAdded;
    

    bool    UpdateTrayIcon(DWORD AMessage);

public:
    afx_msg void OnDestroy();
};


// 最重要的地方：m_NID.uCallbackMessage = uCbMsg;