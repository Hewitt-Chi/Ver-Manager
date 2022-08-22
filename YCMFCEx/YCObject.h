#pragma once


#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif



//////////////////////////////////////////////////////////////////////////////
// CYCObject
//
#define   VIRTUAL_CYCObject_Assign()                    virtual void Assign(const CObject *AValue)
#define IMPLEMENT_CYCObject_Assign(AClass)              void AClass::Assign(const CObject *AValue)
#define  OVERRIDE_CYCObject_Assign                      VIRTUAL_CYCObject_Assign

#define   VIRTUAL_CYCObject_IsEqual()                   virtual bool IsEqual(const CObject *AValue) const
#define IMPLEMENT_CYCObject_IsEqual(AClass)             bool AClass::IsEqual(const CObject *AValue) const
#define  OVERRIDE_CYCObject_IsEqual                     VIRTUAL_CYCObject_IsEqual

#define YCObjectAssignField(X)                          X = LValue->X
#define YCIsObjectFieldEqual(X)                         (X == LValue->X)


class CYCObject : public CObject
{
    DECLARE_DYNAMIC(CYCObject)

public:
    // constructor & destructor
    CYCObject();
    virtual ~CYCObject();


    // class Name
    LPCSTR      ClassName() const;


    ///////////////////////////////////////////////////////
    // 把σ璸计竟
    //
    LONG        RefCount() const;
    LONG        AddRef();
    LONG        ReleaseRef();
    //
    // 把σ璸计竟
    ///////////////////////////////////////////////////////

protected:
#ifdef _DEBUG
    // ン嘿
    CString     m_DebugName;
#endif


    VIRTUAL_CYCObject_Assign();
    VIRTUAL_CYCObject_IsEqual();

private:

    LONG        m_RefCount;

};
//
// CYCObject
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//  CYCObjectHandle
//      provides the basis for all other smart pointers
//      The other smartpointers add their own constructors and operators
//
template <class T>
class CYCObjectHandle
{
public:
    typedef     T   _PtrClass;



    CYCObjectHandle() throw()
    {
        m_Object = NULL;
    }

    CYCObjectHandle(T *AValue) throw()
    {
        m_Object = NULL;

        operator=(AValue);
#if 0
        m_Object = AValue;

        if (m_Object != NULL)
            m_Object->AddRef();
#endif
    }

    CYCObjectHandle(const CYCObjectHandle<T> &AValue) throw()
    {
        m_Object = NULL;

        operator=(AValue);
#if 0
        m_Object = AValue;

        if (m_Object != NULL)
            m_Object->AddRef();
#endif
    }

    ~CYCObjectHandle() throw()
    {
        operator=(NULL);
    }

    inline operator T*() const throw()
    {
        return m_Object;
    }

    inline T& operator *() const
    {
        ASSERT(m_Object != NULL);
        return *m_Object;
    }

    //The assert on operator& usually indicates a bug.  If this is really
    //what is needed, however, take the address of the m_Object member explicitly.
    inline T** operator &() throw()
    {
        ASSERT(m_Object == NULL);
        return &m_Object;
    }

    inline T* operator ->() const throw()
    {
        ASSERT(m_Object != NULL);
        return m_Object;
    }

    inline bool operator !() const throw()
    {
        return (m_Object == NULL);
    }

    bool operator ==(T* AValue) const throw()
    {
        return m_Object == AValue;
    }

    inline bool operator !=(T *AValue) const
    {
        return !operator==(AValue);
    }

    inline T* operator =(T *AValue) throw()
    {
        if (m_Object != AValue)
        {
            if (m_Object)
                m_Object->ReleaseRef();

            m_Object = AValue;

            if (m_Object)
                m_Object->AddRef();
        }

        return m_Object;
    }

#if 1
    inline CYCObjectHandle<T>& operator =(const CYCObjectHandle<T> &AValue) throw()
    {
        operator=((T *)AValue);

        return *this;
    }
#endif

    // Release the interface and set to NULL
#if 0
    inline void Release() throw()
    {
        T* LObj = m_Object;

        if (LObj)
        {
            m_Object = NULL;
            LObj->Release();
        }
    }
#endif

#if 0
    // Attach to an existing interface (does not AddRef)
    inline void Attach(T* AValue) throw()
    {
        if (m_Object)
            m_Object->Release();

        m_Object = AValue;
    }

    // Detach the interface (does not Release)
    inline T* Detach() throw()
    {
        T* LObj = m_Object;

        m_Object = NULL;

        return LObj;
    }
#endif

    inline bool CopyTo(T **AValue) throw()
    {
        ASSERT(AValue != NULL);

        if (AValue == NULL)
            return false;

        *AValue = m_Object;

        if (m_Object)
            m_Object->AddRef();

        return true;
    }

    inline bool IsNull() const
    {
        return m_Object == NULL;
    }

    inline bool IsNotNull() const
    {
        return m_Object != NULL;
    }

    inline CYCObjectHandle<T>* HandlePtr()
    {
        return this;
    }

private:
    T   *m_Object;

};
//
//  CYCObjectHandle
//      provides the basis for all other smart pointers
//      The other smartpointers add their own constructors and operators
//////////////////////////////////////////////////////////////////////////////

