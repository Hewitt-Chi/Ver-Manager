#include "StdAfx.h"

#include "YCMessageOnlyWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CYCMessageOnlyWnd, CWnd)

CYCMessageOnlyWnd::CYCMessageOnlyWnd(void) : CWnd()
{
}

CYCMessageOnlyWnd::~CYCMessageOnlyWnd(void)
{
}

BOOL CYCMessageOnlyWnd::Create()
{
    CString LStr = ::AfxRegisterWndClass(NULL);

    return __super::CreateEx(0, LStr, "CYCMessageOnlyWnd",0 ,0 ,0 ,0 ,0 , HWND_MESSAGE, 0);
}

BOOL CYCMessageOnlyWnd::Create(LPCTSTR          lpszClassName,
                               LPCTSTR          lpszWindowName,
                               DWORD            dwStyle,
                               const RECT       &rect,
                               CWnd             *pParentWnd,
                               UINT             nID,
                               CCreateContext   *pContext/* = NULL*/)
{
    return Create();
}

BOOL CYCMessageOnlyWnd::CreateEx(DWORD          dwExStyle,
                                 LPCTSTR        lpszClassName,
                                 LPCTSTR        lpszWindowName,
                                 DWORD          dwStyle,
                                 const RECT     &rect,
                                 CWnd           *pParentWnd,
                                 UINT           nID,
                                 LPVOID         lpParam/* = NULL*/)
{
    return Create();
}
