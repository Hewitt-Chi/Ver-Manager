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
//      �ت��G���Ѫ���ͦ��A�����ΦA�Q�Ϊ��򥻳W�d���O 
//
//      �禡 :
//          Create() : ù��غc�l�A�ΥH��l�ƩҦ��ʺA�ͦ��������ܼ�(�p�O����t�m)�A
//                     �Ϊ̬O�ΥH�]�w���n���ܼƪ�l�ȡC�ȥi��|���I�s���禡�e�I�s
//                     �@���A��Destroy()���i�A���I�s
//          Destroy() : ù��Ѻc�l�A�ΥH�M���ʺA�ͦ��������ܼƩέ��]���n���ܼƭ�
//                      �ܪ�l���A�C�ȥi��Create()��I�s
//          Preset() : ��l�ƩҦ����n���ܼơA�i�����ɭԩI�s�A�����l�ƪ��ܼƻ�
//                     �Ҽ{�O�_�i�����ɭԳQ��l�ơA�|�bDestroy()�ιw�]�غc�l��
//                     �Q�۰ʩI�s�C
//          Free() : ù��W��delete�A�|�I�sDestroy()
//
//      �ϥΤ覡�G1.�غc
//                2.�I�sCreate()
//                3.�}�l�ϥ�
//                4.�I�sFree()
//                5.�p�n�A���ϥΫh�^��2�B
//                6.�Ѻc
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


    // �t�m�ʺA���귽
    bool        Create();

    // �R��������(�p�G�i�H���ܡA�O�d)
    void        Free();

    // �O�_�w�t�m�ʺA�귽
    bool        IsCreated() const;

    // �����ѧO�X
    DWORD       Id() const;
    void        SetId(DWORD AValue);

    // ����W��
    LPCSTR      Name() const;
    void        SetName(LPCSTR AValue);

    // �إ߮ɪ�Thread Id
    DWORD       CreateThreadId() const;

protected:
#if 0
    // �p�G�O�S��IsCreated�A�h��X�@��Exception
    void ThrowIfNotCreated() throw();

    // �p�G�OIsCreated�A�h��X�@��Exception
    void ThrowIfCreated() throw();
#endif

    //
    VIRTUAL_CYCComponent_OnCreate();

    // �M����Create()���Ұt�m���귽
    VIRTUAL_CYCComponent_OnDestroy();

    // ��Ҧ��ܼ��٭즨���ϥΪ��A
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
    // �����ѧO�X
    DWORD       m_Id;

    // ����W��
    CString     m_Name;

    // �O���O�_�w�QCreate()�L
    bool        m_IsCreated;

    // Create��Thread Id
    DWORD       m_CreateThreadId;

};
//
// CYCComponent 
//////////////////////////////////////////////////////////////////////////////

