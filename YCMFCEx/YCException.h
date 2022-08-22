#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif



//////////////////////////////////////////////////////////////////////////////
// CYCException
//
class CYCException : public CSimpleException
{
    DECLARE_DYNAMIC(CYCException)

public:

    CYCException() : CSimpleException(), m_Code(0) {   }
    explicit CYCException(BOOL bAutoDelete) : CSimpleException(bAutoDelete), m_Code(0) {   }
    virtual ~CYCException() {   }


    inline WORD Code() const                { return m_Code;        }
    inline void SetCode(WORD AValue)        { m_Code = AValue;      }
    inline void SetMessage(LPCSTR AMessage) { strcpy_s(m_szMessage, sizeof(m_szMessage), AMessage); m_bInitialized = TRUE; }
    inline LPCSTR Message() const           { return m_szMessage;   }

private:

    WORD    m_Code;

};


extern void YCThrowException(WORD ACode, LPCSTR AMsg);
extern void YCThrowExceptionFmt(WORD ACode, LPCSTR AFmt, ...);
//
// CYCException
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// CYCOutOfRangeException
//
class CYCOutOfRangeException : public CYCException
{
    DECLARE_DYNAMIC(CYCOutOfRangeException)

public:

    CYCOutOfRangeException() : CYCException(), m_Max(1), m_Min(0) {   }
    explicit CYCOutOfRangeException(BOOL bAutoDelete) : CYCException(bAutoDelete), m_Max(1), m_Min(0) {   }
    virtual ~CYCOutOfRangeException() {   }


    inline int Max() const      { return m_Max;     }
    inline int Min() const      { return m_Min;     }
    inline int Current() const  { return m_Current; }

    inline void SetRange(int ACurrent, int AMax, int AMin)
    {
        CString LStr;

        LStr.Format("%d is out of range(Min : %d, Max : %d).", ACurrent, AMin, AMax);
        SetMessage(LStr);
        m_Max = AMax; m_Min = AMin; m_Current = ACurrent;
    }

private:

    int m_Max;
    int m_Min;
    int m_Current;

};


extern void YCThrowOutOfRangeException(int AMin, int AMax, int ACurrent);
//
// CYCOutOfRangeException
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// CYCThreadException
//
class CYCThreadException : public CYCException
{
    DECLARE_DYNAMIC(CYCThreadException)

public:
    CYCThreadException() : CYCException()   {   }
    explicit CYCThreadException(BOOL bAutoDelete) : CYCException(bAutoDelete)   {   }

};


extern void YCThrowThreadException(WORD ACode, LPCSTR AMsg);
extern void YCThrowThreadExceptionFmt(WORD ACode, LPCSTR AFmt, ...);
//
// CYCThreadException
//////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////
// CYCComponentException
//
class CYCComponent;

class CYCComponentException : public CYCException
{
    DECLARE_DYNAMIC(CYCComponentException)

public:
    CYCComponentException() : CYCException(), m_Sender(NULL)    {    }
    explicit CYCComponentException(BOOL bAutoDelete) : CYCException(bAutoDelete), m_Sender(NULL)    {    }
    virtual ~CYCComponentException()    {    }

    inline CYCComponent* Sender()                   { return m_Sender;      }
    inline void SetSender(CYCComponent *ASender)    { m_Sender = ASender;   }

private:
    CYCComponent    *m_Sender;

};


extern void YCThrowComponentException(CYCComponent *ASender, WORD ACode, LPCSTR AMsg);
extern void YCThrowComponentExceptionFmt(CYCComponent *ASender, WORD ACode, LPCSTR AFmt, ...);
//
// CYCComponentException
//////////////////////////////////////////////////////////////////////////////



