#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


////////////////////////////////////////////////////////////////////////////////////////////
// CYCCompletionObject
//
class CYCCompletionObject : public CYCObject
{
    DECLARE_DYNAMIC(CYCCompletionObject)

public:
    CYCCompletionObject();
    virtual ~CYCCompletionObject();


    const HANDLE
        /**/    Event() const;
    LRESULT     Result() const;


    void        Complete(LRESULT AResult);
    bool        WaitForCompletion(DWORD ATimeoutMSec, OUT LRESULT *AResult);
    LRESULT     WaitForCompletion(LRESULT ADefaultResult);
    void        Reset(LRESULT ADefaultResult);
private:
#ifdef _DEBUG
    static LONG m_UniqueNoSeed;
    static LONG m_ObjectCount;


    //==========================
    const LONG  m_UniqueNo;


    bool    volatile
        /**/    m_IsSetCompletion;
#endif


    LRESULT volatile
        /**/    m_Result;

    const HANDLE
        /**/    m_Event;
};
//
// CACCompletionHandle
////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////
// CACCompletionHandle
//
typedef CYCObjectHandle<CYCCompletionObject>    CYCCompletionHandle;
typedef std::deque<CYCCompletionHandle>         TYCCompletionHandleDeque;


#define DEFINE_NEW_CompletionHandleName(X)      CYCCompletionHandle X = new CYCCompletionObject(); X->ReleaseRef()
#define DEFINE_NEW_CompletionHandle()           DEFINE_NEW_CompletionHandleName(LCompletionHandle)
#define ASSIGN_NEW_CompletionHandle(X)          X.operator=(new CYCCompletionObject()); X->ReleaseRef()
//
// CACCompletionHandle
///////////////////////////////////////////////////////////////////////////////////////

