#include "stdafx.h"

#include "YCException.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//////////////////////////////////////////////////////////////////////////////
// CYCException
//
IMPLEMENT_DYNAMIC(CYCException, CException)


void YCThrowException(WORD ACode, LPCSTR AMsg)
{
    static CYCException    LYCExceptionObj(FALSE);

    LYCExceptionObj.SetCode(ACode);
    LYCExceptionObj.SetMessage(AMsg);

    throw &LYCExceptionObj;
}

void YCThrowExceptionFmt(WORD ACode, LPCSTR AFmt, ...)
{
    CString LStr;

    va_list LArgs;
    va_start(LArgs, AFmt);

    LStr.FormatV(AFmt, LArgs);
    va_end(LArgs);

    YCThrowException(ACode, LStr);
}
//
// CYCException
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// CYCOutOfRangeException
//
IMPLEMENT_DYNAMIC(CYCOutOfRangeException, CYCException)


void YCThrowOutOfRangeException(int AMin, int AMax, int ACurrent)
{
    static CYCOutOfRangeException   LYCOutOfRangeExceptionObj(FALSE);


    LYCOutOfRangeExceptionObj.SetRange(ACurrent, AMax, AMin);

    throw &LYCOutOfRangeExceptionObj;
}
//
// CYCOutOfRangeException
//////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////
// CYCThreadException
//
IMPLEMENT_DYNAMIC(CYCThreadException, CYCComponentException)


void YCThrowThreadException(WORD ACode, LPCSTR AMsg)
{
    static CYCThreadException   LYCThreadExceptionObj(FALSE);


    LYCThreadExceptionObj.SetCode(ACode);
    LYCThreadExceptionObj.SetMessage(AMsg);

    throw &LYCThreadExceptionObj;
}

void YCThrowThreadExceptionFmt(WORD ACode, LPCSTR AFmt, ...)
{
    CString LStr;

    va_list LArgs;
    va_start(LArgs, AFmt);

    LStr.FormatV(AFmt, LArgs);
    va_end(LArgs);

    YCThrowThreadException(ACode, LStr);
}
//
// CYCThreadException
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// CYCComponentException
//
IMPLEMENT_DYNAMIC(CYCComponentException, CYCException)


void YCThrowComponentException(CYCComponent *ASender, WORD ACode, LPCSTR AMsg)
{
    static CYCComponentException    LYCComponentExceptionObj(FALSE);

    LYCComponentExceptionObj.SetCode(ACode);
    LYCComponentExceptionObj.SetMessage(AMsg);
    LYCComponentExceptionObj.SetSender(ASender);

    throw &LYCComponentExceptionObj;
}

void YCThrowComponentExceptionFmt(CYCComponent *ASender, WORD ACode, LPCSTR AFmt, ...)
{
    CString LStr;

    va_list LArgs;
    va_start(LArgs, AFmt);

    LStr.FormatV(AFmt, LArgs);
    va_end(LArgs);

    YCThrowComponentException(ASender, ACode, LStr);
}
//
// CYCComponentException
//////////////////////////////////////////////////////////////////////////////



