#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

// Exception code
enum enmYCControlException
{
    YCC_Exception_Base = 200,
    YCC_Exception_User = YCC_Exception_Base + 100
};

/*////////////////////////////////////////////////////////////////////////////
// CYCControl : 
//      Base Class of this library
//
//      目的：提供物件Child-Parent關係的管理
//
//      函式：
//          SetParent() : 設定物件的父項
//          ChildCount() : 目前所擁有的子項數量
//          ChildAt() : 在指定索引位置上的子項
//          OnChildAddRemove() : 事件，當有一子項被加入或移除時自動呼叫此函式。
*/
#if 0
#define   VIRTUAL_CYCControl_OnChildAddRemove()                    virtual void OnChildAddRemove(CYCControl *AChild, bool AIsAdded)
#define IMPLEMENT_CYCControl_OnChildAddRemove(AClass)              void AClass::OnChildAddRemove(CYCControl *AChild, bool AIsAdded)
#define  OVERRIDE_CYCControl_OnChildAddRemove                      VIRTUAL_CYCControl_OnChildAddRemove
#endif

class CYCControl : public CYCComponent
{
    DECLARE_DYNAMIC(CYCControl)

public:

    CYCControl(void);
    virtual ~CYCControl(void);


    // parent
    CYCControl* Parent() const;
    void        SetParent(CYCControl *AParent);

    // 表示是否擁有子控項，if true則在RemoveChild時delete Child
    bool        IsOwnChild() const;
    void        SetIsOwnChild(bool AValue);

    // 子項的數量
    INT_PTR     ChildCount() const;

    // 索引編號所在的子項
    CYCControl* ChildAt(INT_PTR AIdx) const;

    // 如果AControl是本物件的Child關係回傳true
    bool        IsChildRelationship(const CYCControl* const AControl) const;

    // 如果AControl是本物件的Parent關係回傳true
    bool        IsParentRelationship(const CYCControl* const AControl) const;

    // 查詢子物件
    bool        QueryChildOf(DWORD      AChildId  , OUT void **AChild);
    bool        QueryChildOf(LPCSTR     AChildName, OUT void **AChild);
    bool        QueryChildAt(INT_PTR    AIdx      , OUT void **AChild);

protected:

    OVERRIDE_CYCComponent_OnDestroy();
    OVERRIDE_CYCComponent_OnPreset();

#if 0
    // 當一個物件被加入本物件後或自本物件移除後時呼叫
    VIRTUAL_CYCControl_OnChildAddRemove();
#endif

private:
    // 父物件
    CYCControl  *m_Parent;

    // 子物件
    std::deque<CYCControl *>
        /**/    m_Childs;

    // 是否擁有子物件
    bool        m_IsOwnChild;



    //// 加入一個子物件
    void        AddChild(CYCControl *AChild);

    //// 移除一個子物件
    bool        RemoveChild(CYCControl *AChild);

};
//
// CYCControl
//////////////////////////////////////////////////////////////////////////////
