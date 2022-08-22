#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif



// Exception code
enum enmYCComponentException
{
    YCCOMPONENT_Exception_ComponentNotCreated = 1,
    YCCOMPONENT_Exception_ComponentCreated,
    YCCOMPONENT_Exception_InvalidParameter,
    YCCOMPONENT_Exception_User = 100
};


//////////////////////////////////////////////////////////////////////////////
// CYCComponent :
//      Base class of YCAutoControlFW
//
//      目的：提供物件生成，消滅及再利用的基本規範類別 
//
//      函式 :
//          Create() : 羅輯建構子，用以初始化所有動態生成之成員變數(如記憶體配置)，
//                     或者是用以設定必要之變數初始值。僅可於尚未呼叫本函式前呼叫
//                     一次，或Destroy()後方可再次呼叫
//          Destroy() : 羅輯解構子，用以清除動態生成之成員變數或重設必要之變數值
//                      至初始狀態。僅可於Create()後呼叫
//          Preset() : 初始化所有必要之變數，可於任何時候呼叫，都其初始化的變數需
//                     考慮是否可於任何時候被初始化，會在Destroy()及預設建構子中
//                     被自動呼叫。
//          Free() : 羅輯上的delete，會呼叫Destroy()
//
//      使用方式：1.建構
//                2.呼叫Create()
//                3.開始使用
//                4.呼叫Free()
//                5.如要再次使用則回第2步
//                6.解構
//
//
#define INVALID_YCCOMPONENTID_VALUE                         ((DWORD)-1)


//===============================
#define   VIRTUAL_CYCComponent_OnCreate()                   virtual bool OnCreate()
#define IMPLEMENT_CYCComponent_OnCreate(AClass)             bool AClass::OnCreate()
#define  OVERRIDE_CYCComponent_OnCreate                     VIRTUAL_CYCComponent_OnCreate


//===============================
#define   VIRTUAL_CYCComponent_OnDestroy()                  virtual void DoOnDestroy(); \
    /**/                                                    void         OnDestroy()    \

#define IMPLEMENT_CYCComponent_OnDestroy(AClass)            void AClass::DoOnDestroy()  \
    /**/                                                    {                           \
    /**/                                                        AClass::OnDestroy();    \
    /**/                                                        __super::DoOnDestroy(); \
    /**/                                                    }                           \
    /**/                                                                                \
    /**/                                                    void AClass::OnDestroy()    \

#define  OVERRIDE_CYCComponent_OnDestroy                    VIRTUAL_CYCComponent_OnDestroy


//===============================
#define   VIRTUAL_CYCComponent_OnPreset()                   virtual void DoOnPreset();  \
    /**/                                                    void         OnPreset()     \

#define IMPLEMENT_CYCComponent_OnPreset(AClass)             void AClass::DoOnPreset()   \
    /**/                                                    {                           \
    /**/                                                        __super::DoOnPreset();  \
    /**/                                                        AClass::OnPreset();     \
    /**/                                                    }                           \
    /**/                                                                                \
    /**/                                                    void AClass::OnPreset()     \

#define  OVERRIDE_CYCComponent_OnPreset                     VIRTUAL_CYCComponent_OnPreset


class CYCComponent : public CYCObject
{
    DECLARE_DYNAMIC(CYCComponent)

public:
    static CYCComponent*
        /**/    FromNamePermanent(LPCSTR AName);
    static CYCComponent*
        /**/    FromIdPermanent(DWORD AId);


    //===============================
    CYCComponent(void);
    virtual ~CYCComponent(void);


    // 配置動態的資源
    bool        Create();

    // 刪除本物件(如果可以的話，保留)
    void        Free();

    // 是否已配置動態資源
    bool        IsCreated() const;

    // 物件識別碼
    DWORD       Id() const;
    void        SetId(DWORD AValue);

    // 物件名稱
    LPCSTR      Name() const;
    void        SetName(LPCSTR AValue);

    // 建立時的Thread Id
    DWORD       CreateThreadId() const;

protected:
#if 0
    // 如果是沒有IsCreated，則丟出一個Exception
    void ThrowIfNotCreated() throw();

    // 如果是IsCreated，則丟出一個Exception
    void ThrowIfCreated() throw();
#endif

    //
    VIRTUAL_CYCComponent_OnCreate();

    // 清除由Create()中所配置的資源
    VIRTUAL_CYCComponent_OnDestroy();

    // 把所有變數還原成未使用狀態
    VIRTUAL_CYCComponent_OnPreset();


private:
    typedef std::map<CString, CYCComponent *, strYCStrLessNoCase>    TPermanentNameControllers;
    typedef std::map<DWORD  , CYCComponent *>                        TPermanentIdControllers;


    //===============================
    static  TPermanentNameControllers
        /**/    m_PermanentNameControllers;

    static  TPermanentIdControllers
        /**/    m_PermanentIdControllers;

    static  CCriticalSection
        /**/    m_PermanentLocker;


    //===============================
    // 物件識別碼
    DWORD       m_Id;

    // 物件名稱
    CString     m_Name;

    // 記錄是否已被Create()過
    bool        m_IsCreated;

    // Create的Thread Id
    DWORD       m_CreateThreadId;

};
//
// CYCComponent 
//////////////////////////////////////////////////////////////////////////////

