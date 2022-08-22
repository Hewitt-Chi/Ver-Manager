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
//      �ت��G���Ѫ���Child-Parent���Y���޲z
//
//      �禡�G
//          SetParent() : �]�w���󪺤���
//          ChildCount() : �ثe�Ҿ֦����l���ƶq
//          ChildAt() : �b���w���ަ�m�W���l��
//          OnChildAddRemove() : �ƥ�A���@�l���Q�[�J�β����ɦ۰ʩI�s���禡�C
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

    // ��ܬO�_�֦��l�����Aif true�h�bRemoveChild��delete Child
    bool        IsOwnChild() const;
    void        SetIsOwnChild(bool AValue);

    // �l�����ƶq
    INT_PTR     ChildCount() const;

    // ���޽s���Ҧb���l��
    CYCControl* ChildAt(INT_PTR AIdx) const;

    // �p�GAControl�O������Child���Y�^��true
    bool        IsChildRelationship(const CYCControl* const AControl) const;

    // �p�GAControl�O������Parent���Y�^��true
    bool        IsParentRelationship(const CYCControl* const AControl) const;

    // �d�ߤl����
    bool        QueryChildOf(DWORD      AChildId  , OUT void **AChild);
    bool        QueryChildOf(LPCSTR     AChildName, OUT void **AChild);
    bool        QueryChildAt(INT_PTR    AIdx      , OUT void **AChild);

protected:

    OVERRIDE_CYCComponent_OnDestroy();
    OVERRIDE_CYCComponent_OnPreset();

#if 0
    // ��@�Ӫ���Q�[�J�������Φۥ����󲾰���ɩI�s
    VIRTUAL_CYCControl_OnChildAddRemove();
#endif

private:
    // ������
    CYCControl  *m_Parent;

    // �l����
    std::deque<CYCControl *>
        /**/    m_Childs;

    // �O�_�֦��l����
    bool        m_IsOwnChild;



    //// �[�J�@�Ӥl����
    void        AddChild(CYCControl *AChild);

    //// �����@�Ӥl����
    bool        RemoveChild(CYCControl *AChild);

};
//
// CYCControl
//////////////////////////////////////////////////////////////////////////////
