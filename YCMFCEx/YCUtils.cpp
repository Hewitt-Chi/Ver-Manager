#include "stdafx.h"

#include "YCUtils.h"

#include <afxpriv.h >
#include <shlwapi.h>
#include <shlobj.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString YCColorToStr(COLORREF   AColor)
{
#define CaseReturn(X)   case X : return #X

    switch (AColor)
    {
        CaseReturn(clAliceBlue);
        CaseReturn(clAntiqueWhite);
        CaseReturn(clAqua);
        CaseReturn(clAquaMarine);
        CaseReturn(clAzure);
        CaseReturn(clBeige);
        CaseReturn(clBisque);
        CaseReturn(clBlack);
        CaseReturn(clBlanchedAlmond);
        CaseReturn(clBlue);
        CaseReturn(clBlueViolet);
        CaseReturn(clBrown);
        CaseReturn(clBurlyWood);
        CaseReturn(clCadetBlue);
        CaseReturn(clChartreuse);
        CaseReturn(clChocolate);
        CaseReturn(clCoral);
        CaseReturn(clCornflowerBlue);
        CaseReturn(clCornsilk);
        CaseReturn(clCrimson);
        //CaseReturn(clCyan);
        CaseReturn(clDarkBlue);
        CaseReturn(clDarkCyan);
        CaseReturn(clDarkGoldenRod);
        CaseReturn(clDarkGray);
        CaseReturn(clDarkGreen);
        CaseReturn(clDarkKhaki);
        CaseReturn(clDarkMagenta);
        CaseReturn(clDarkOliveGreen);
        CaseReturn(clDarkOrange);
        CaseReturn(clDarkOrchid);
        CaseReturn(clDarkRed);
        CaseReturn(clDarkSalmon);
        CaseReturn(clDarkSeaGreen);
        CaseReturn(clDarkSlateBlue);
        CaseReturn(clDarkSlateGray);
        CaseReturn(clDarkTurquoise);
        CaseReturn(clDarkViolet);
        CaseReturn(clDeepPink);
        CaseReturn(clDeepSkyBlue);
        CaseReturn(clDimGray);
        CaseReturn(clDodgerBlue);
        CaseReturn(clFireBrick);
        CaseReturn(clFloralWhite);
        CaseReturn(clForestGreen);
        CaseReturn(clFuchsia);
        CaseReturn(clGainsboro);
        CaseReturn(clGhostWhite);
        CaseReturn(clGold);
        CaseReturn(clGoldenRod);
        CaseReturn(clGray);
        CaseReturn(clGreen);
        CaseReturn(clGreenYellow);
        CaseReturn(clHoneyDew);
        CaseReturn(clHotPink);
        CaseReturn(clIndianRed);
        CaseReturn(clIndigo);
        CaseReturn(clIvory);
        CaseReturn(clKhaki);
        CaseReturn(clLavender);
        CaseReturn(clLavenderBlush);
        CaseReturn(clLawnGreen);
        CaseReturn(clLemonChiffon);
        CaseReturn(clLightBlue);
        CaseReturn(clLightCoral);
        CaseReturn(clLightCyan);
        CaseReturn(clLightGoldenRodYellow);
        CaseReturn(clLightGreen);
        CaseReturn(clLightGrey);
        CaseReturn(clLightPink);
        CaseReturn(clLightSalmon);
        CaseReturn(clLightSeaGreen);
        CaseReturn(clLightSkyBlue);
        CaseReturn(clLightSlateGray);
        CaseReturn(clLightSteelBlue);
        CaseReturn(clLightYellow);
        CaseReturn(clLime);
        CaseReturn(clLimeGreen);
        CaseReturn(clLinen);
        //CaseReturn(clMagenta);
        CaseReturn(clMaroon);
        CaseReturn(clMediumAquaMarine);
        CaseReturn(clMediumBlue);
        CaseReturn(clMediumOrchid);
        CaseReturn(clMediumPurple);
        CaseReturn(clMediumSeaGreen);
        CaseReturn(clMediumSlateBlue);
        CaseReturn(clMediumSpringGreen);
        CaseReturn(clMediumTurquoise);
        CaseReturn(clMediumVioletRed);
        CaseReturn(clMidnightBlue);
        CaseReturn(clMintCream);
        CaseReturn(clMistyRose);
        CaseReturn(clMoccasin);
        CaseReturn(clNavajoWhite);
        CaseReturn(clNavy);
        CaseReturn(clOldLace);
        CaseReturn(clOlive);
        CaseReturn(clOliveDrab);
        CaseReturn(clOrange);
        CaseReturn(clOrangeRed);
        CaseReturn(clOrchid);
        CaseReturn(clPaleGoldenRod);
        CaseReturn(clPaleGreen);
        CaseReturn(clPaleTurquoise);
        CaseReturn(clPaleVioletRed);
        CaseReturn(clPapayaWhip);
        CaseReturn(clPeachPuff);
        CaseReturn(clPeru);
        CaseReturn(clPink);
        CaseReturn(clPlum);
        CaseReturn(clPowderBlue);
        CaseReturn(clPurple);
        CaseReturn(clRed);
        CaseReturn(clRosyBrown);
        CaseReturn(clRoyalBlue);
        CaseReturn(clSaddleBrown);
        CaseReturn(clSalmon);
        CaseReturn(clSandyBrown);
        CaseReturn(clSeaGreen);
        CaseReturn(clSeaShell);
        CaseReturn(clSienna);
        CaseReturn(clSilver);
        CaseReturn(clSkyBlue);
        CaseReturn(clSlateBlue);
        CaseReturn(clSlateGray);
        CaseReturn(clSnow);
        CaseReturn(clSpringGreen);
        CaseReturn(clSteelBlue);
        CaseReturn(clTan);
        CaseReturn(clTeal);
        CaseReturn(clThistle);
        CaseReturn(clTomato);
        CaseReturn(clTurquoise);
        CaseReturn(clViolet);
        CaseReturn(clWheat);
        CaseReturn(clWhite);
        CaseReturn(clWhiteSmoke);
        CaseReturn(clYellow);
        CaseReturn(clYellowGreen);
    }

#undef  CaseReturn


    CString LRslt;

    LRslt.Format("0x%X", AColor);

    return LRslt;
}

COLORREF
/**/    YCStrToColor(LPCSTR     AColorText)
{
#define EqualReturn(X)      if (!CString(AColorText).Trim().CompareNoCase(#X)) return X

    EqualReturn(clAliceBlue);
    EqualReturn(clAntiqueWhite);
    EqualReturn(clAqua);
    EqualReturn(clAquaMarine);
    EqualReturn(clAzure);
    EqualReturn(clBeige);
    EqualReturn(clBisque);
    EqualReturn(clBlack);
    EqualReturn(clBlanchedAlmond);
    EqualReturn(clBlue);
    EqualReturn(clBlueViolet);
    EqualReturn(clBrown);
    EqualReturn(clBurlyWood);
    EqualReturn(clCadetBlue);
    EqualReturn(clChartreuse);
    EqualReturn(clChocolate);
    EqualReturn(clCoral);
    EqualReturn(clCornflowerBlue);
    EqualReturn(clCornsilk);
    EqualReturn(clCrimson);
    //EqualReturn(clCyan);
    EqualReturn(clDarkBlue);
    EqualReturn(clDarkCyan);
    EqualReturn(clDarkGoldenRod);
    EqualReturn(clDarkGray);
    EqualReturn(clDarkGreen);
    EqualReturn(clDarkKhaki);
    EqualReturn(clDarkMagenta);
    EqualReturn(clDarkOliveGreen);
    EqualReturn(clDarkOrange);
    EqualReturn(clDarkOrchid);
    EqualReturn(clDarkRed);
    EqualReturn(clDarkSalmon);
    EqualReturn(clDarkSeaGreen);
    EqualReturn(clDarkSlateBlue);
    EqualReturn(clDarkSlateGray);
    EqualReturn(clDarkTurquoise);
    EqualReturn(clDarkViolet);
    EqualReturn(clDeepPink);
    EqualReturn(clDeepSkyBlue);
    EqualReturn(clDimGray);
    EqualReturn(clDodgerBlue);
    EqualReturn(clFireBrick);
    EqualReturn(clFloralWhite);
    EqualReturn(clForestGreen);
    EqualReturn(clFuchsia);
    EqualReturn(clGainsboro);
    EqualReturn(clGhostWhite);
    EqualReturn(clGold);
    EqualReturn(clGoldenRod);
    EqualReturn(clGray);
    EqualReturn(clGreen);
    EqualReturn(clGreenYellow);
    EqualReturn(clHoneyDew);
    EqualReturn(clHotPink);
    EqualReturn(clIndianRed);
    EqualReturn(clIndigo);
    EqualReturn(clIvory);
    EqualReturn(clKhaki);
    EqualReturn(clLavender);
    EqualReturn(clLavenderBlush);
    EqualReturn(clLawnGreen);
    EqualReturn(clLemonChiffon);
    EqualReturn(clLightBlue);
    EqualReturn(clLightCoral);
    EqualReturn(clLightCyan);
    EqualReturn(clLightGoldenRodYellow);
    EqualReturn(clLightGreen);
    EqualReturn(clLightGrey);
    EqualReturn(clLightPink);
    EqualReturn(clLightSalmon);
    EqualReturn(clLightSeaGreen);
    EqualReturn(clLightSkyBlue);
    EqualReturn(clLightSlateGray);
    EqualReturn(clLightSteelBlue);
    EqualReturn(clLightYellow);
    EqualReturn(clLime);
    EqualReturn(clLimeGreen);
    EqualReturn(clLinen);
    //EqualReturn(clMagenta);
    EqualReturn(clMaroon);
    EqualReturn(clMediumAquaMarine);
    EqualReturn(clMediumBlue);
    EqualReturn(clMediumOrchid);
    EqualReturn(clMediumPurple);
    EqualReturn(clMediumSeaGreen);
    EqualReturn(clMediumSlateBlue);
    EqualReturn(clMediumSpringGreen);
    EqualReturn(clMediumTurquoise);
    EqualReturn(clMediumVioletRed);
    EqualReturn(clMidnightBlue);
    EqualReturn(clMintCream);
    EqualReturn(clMistyRose);
    EqualReturn(clMoccasin);
    EqualReturn(clNavajoWhite);
    EqualReturn(clNavy);
    EqualReturn(clOldLace);
    EqualReturn(clOlive);
    EqualReturn(clOliveDrab);
    EqualReturn(clOrange);
    EqualReturn(clOrangeRed);
    EqualReturn(clOrchid);
    EqualReturn(clPaleGoldenRod);
    EqualReturn(clPaleGreen);
    EqualReturn(clPaleTurquoise);
    EqualReturn(clPaleVioletRed);
    EqualReturn(clPapayaWhip);
    EqualReturn(clPeachPuff);
    EqualReturn(clPeru);
    EqualReturn(clPink);
    EqualReturn(clPlum);
    EqualReturn(clPowderBlue);
    EqualReturn(clPurple);
    EqualReturn(clRed);
    EqualReturn(clRosyBrown);
    EqualReturn(clRoyalBlue);
    EqualReturn(clSaddleBrown);
    EqualReturn(clSalmon);
    EqualReturn(clSandyBrown);
    EqualReturn(clSeaGreen);
    EqualReturn(clSeaShell);
    EqualReturn(clSienna);
    EqualReturn(clSilver);
    EqualReturn(clSkyBlue);
    EqualReturn(clSlateBlue);
    EqualReturn(clSlateGray);
    EqualReturn(clSnow);
    EqualReturn(clSpringGreen);
    EqualReturn(clSteelBlue);
    EqualReturn(clTan);
    EqualReturn(clTeal);
    EqualReturn(clThistle);
    EqualReturn(clTomato);
    EqualReturn(clTurquoise);
    EqualReturn(clViolet);
    EqualReturn(clWheat);
    EqualReturn(clWhite);
    EqualReturn(clWhiteSmoke);
    EqualReturn(clYellow);
    EqualReturn(clYellowGreen);

#undef  EqualReturn

    int LColor = 0;

    if (StrToIntEx(AColorText, STIF_SUPPORT_HEX, &LColor))
        return LColor;

    return RGB(0, 0, 0);
}

CString YCStrName(LPCSTR AStr)
{
    char LBuffer[1024] = { 0, };
    const char *LChar = strchr(AStr, '=');

    if (LChar)
        strncpy_s(LBuffer, sizeof(LBuffer), AStr, LChar - AStr);

    return LBuffer;
}

CString YCStrValue(LPCSTR AStr)
{
    char LBuffer[1024] = { 0, };
    const char *LChar = strchr(AStr, '=');

    if (LChar)
        strcpy_s(LBuffer, sizeof(LBuffer), LChar + 1);

    return LBuffer;
}

void    YCLastErrorText(OUT CString &ARslt)
{
    LPVOID      LMsgBuf    = NULL;
    const DWORD LLastError = GetLastError();

    ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        /**/        NULL,
        /**/        LLastError,
        /**/        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        /**/        (LPTSTR)&LMsgBuf,
        /**/        0, NULL );

    ARslt = (LPCSTR)LMsgBuf;

    LocalFree(LMsgBuf);
}

void    YCShowLastErrorText(bool AIsOnlyTrace)
{
    CString   LStr;

    YCLastErrorText(LStr);

    TRACE("%s\n", LStr);

    if (!AIsOnlyTrace)
        AfxMessageBox(LStr, MB_ICONERROR);
}

int     YCStrToIntDef(LPCSTR AStr, int ADef)
{
    LPTSTR P = NULL;

    int LResult = strtol(AStr, &P, 0);

    if (P && *P != NULL)
        return ADef;
    else
        return LResult;
}

DWORD   YCStrToUINTDef(LPCSTR AStr, DWORD ADef)
{
    LPTSTR P = NULL;

    DWORD LResult = strtoul(AStr, &P, 0);

    if (P && *P != NULL)
        return ADef;
    else return LResult;
}

double  YCStrToFloatDef(LPCSTR AStr, double ADef)
{
    LPTSTR P = NULL;

    double LResult = strtod(AStr, &P);

    if (P && *P != NULL)
        return ADef;
    else return LResult;
}

int     YCRound(double AValue)
{
    if (AValue - floor(AValue) >= 0.50000)
        return (int)ceil(AValue);
    else return (int)floor(AValue);
}

bool    YCWaitForSignalObjectsAndHandleMessage(DWORD &ASignalObj, DWORD AObjCount, HANDLE *AHandles, 
                                               DWORD ATimeoutMSec)
{
    /*
    進行等待物件的動作，並且在等待中處理視窗訊息(Windows Message)
    流程：處理一個視窗訊息，進行一次等待，如果沒有視窗訊息，則指定等侍時間為參數時間，否則為0
    */

    // DWORD LRslt = AObjCount;
    DWORD LStartTC = GetTickCount();

    do
    {
        MSG     LMsg;
        DWORD   LWaitTime = ATimeoutMSec;

        if (::PeekMessage(&LMsg, 0, 0, 0, PM_REMOVE))
        {
            if (LMsg.message == WM_QUIT)
            {
                PostQuitMessage((int)LMsg.wParam);
                return false;
            }
            else
            {
                // 先處理queue中的訊息
                ::TranslateMessage(&LMsg);
                ::DispatchMessage(&LMsg);

                // 如果queue有訊息的話，把等待的時間設為0，以便繼續處理下個訊息
                LWaitTime = 0;
            }
        }
        else 
        {
            // 如果queue沒有訊息的話，把時間設為要等待的時間
            LWaitTime = ATimeoutMSec - YCMinTickCountBetween(GetTickCount(), LStartTC);

            if (LWaitTime < 0)
                LWaitTime = 10;
        }

        ASignalObj = ::MsgWaitForMultipleObjects(AObjCount, AHandles, FALSE, LWaitTime, QS_ALLINPUT);

        if ((ASignalObj >= WAIT_OBJECT_0 && ASignalObj < WAIT_OBJECT_0 + AObjCount) ||
            (ASignalObj >= WAIT_ABANDONED_0 && ASignalObj < WAIT_ABANDONED_0 + AObjCount))
        {
            // 等到物件被觸發了
            return true;
        }
        else if (ASignalObj == WAIT_TIMEOUT)
        {
            if (LWaitTime != 0)
                return true;
        }
    }
    while (YCMinTickCountBetween(GetTickCount(), LStartTC) < ATimeoutMSec);

    ASignalObj = WAIT_TIMEOUT;

    return true;
}

DWORD   YCMsgWaitForSingleObject(HANDLE AHandle, DWORD AMilliseconds, DWORD AWakeMask)
{
    return MsgWaitForMultipleObjects(1, &AHandle, FALSE, AMilliseconds, AWakeMask);
}

DWORD   YCMsgWaitForSingleObjectEx(HANDLE AHandle, DWORD AMilliseconds, DWORD AWakeMask,
                               BOOL AIsAlertable, BOOL AIsInputAvailable)
{
    DWORD LFlag = ((AIsAlertable ? MWMO_ALERTABLE : 0) | (AIsInputAvailable ? MWMO_INPUTAVAILABLE : 0));

    return MsgWaitForMultipleObjectsEx(1, &AHandle, AMilliseconds, AWakeMask, LFlag);
}

void    YCWinMsgQueueNeeded()
{
    MSG LMsg;

    PeekMessage(&LMsg, NULL, 0, 0, PM_NOREMOVE);
}

CString YCSeperateWords(LPCSTR AText, char ASeperateChar)
{
    CString LStr = AText;

    bool    LIsUpperCase = false;

    for (int I = LStr.GetLength() - 2; I >= 0; I --)
    {
        if (LStr[I] >= 'A' && LStr[I] <= 'Z')
        {
            LIsUpperCase = true;
        }
        else //if (LStr[I] >= 'a' && LStr[I] <= 'z')
        {
            if (LIsUpperCase)
            {
                LStr.Insert(I + 1, ASeperateChar);
            }

            LIsUpperCase = false;
        }
    }

    return LStr;
}

bool    YCIsValidName(LPCSTR AName)
{
    class CIsValidChar
    {
    public:
        static bool IsValidChar(char AValue, bool AIsFirstChar)
        {
            if ((AValue >= 'A' && AValue <= 'Z') ||
                (AValue == '_') ||
                (AValue >= 'a' && AValue <= 'z'))
            {
                return true;
            }
            else if (!AIsFirstChar)
            {
                return AValue >= '0' && AValue <= '9';
            }

            return false;
        }
    };

    if (AName && strlen(AName) > 1)
    {
        if (CIsValidChar::IsValidChar(AName[0], true))
        {
            for (int I = 1; I < (int)strlen(AName); I ++)
            {
                if (!CIsValidChar::IsValidChar(AName[I], false))
                    return false;
            }

            return true;
        }
    }

    return false;
}

bool    YCAdjRectToInsideAnother(RECT &AChild, const RECT &AParent, bool AIntersectionOp)
{
    bool    LRslt = false;
    CRect   LChild(AChild),
        LParent(AParent);

    LChild.NormalizeRect();
    LParent.NormalizeRect();

    if (AIntersectionOp)
    {
        LChild &= LParent;

        if (LChild != CRect(AChild))
            LRslt = true;
    }
    else
    {
        if (LChild.Width() > LParent.Width())
        {
            LChild.left = LParent.left;
            LChild.right = LParent.right;

            LRslt = true;
        }
        else
        {
            if (LChild.left < LParent.left)
                LChild.MoveToX(LParent.left);
            else if (LChild.right > LParent.right)
                LChild.MoveToX(LParent.right - LChild.Width());
        }

        if (LChild.Height() > LParent.Height())
        {
            LChild.top = LParent.top;
            LChild.bottom = LParent.bottom;

            LRslt = true;
        }
        else
        {
            if (LChild.top < LParent.top)
                LChild.MoveToY(LParent.top);
            else if (LChild.bottom > LParent.bottom)
                LChild.MoveToY(LParent.bottom - LChild.Height());
        }  
    }

    AChild = LChild;

    return LRslt;
}

bool    YCAdjLineToInsideAnother(CYCLine &ALine, const RECT &AParent, bool AIntersectionOp)
{
    bool    LRslt = false;
    CRect   LParent(AParent);
    CYCLine LLine(ALine.Point1, ALine.Point2);

    if (!LParent.PtInRect(LLine.Point1))
    {
        if (!LParent.PtInRect(LLine.Point2))   
        {
            if (AIntersectionOp)
            {
                LLine.SetLineEmpty();

                LRslt = true;
            }
            else
            {
            }
        }
        else
        {

        }
    }
    else
    {
        if (!LParent.PtInRect(LLine.Point2))   
        {
            if (AIntersectionOp)
            {
                LLine.SetLineEmpty();

                LRslt = true;
            }
            else
            {
            }
        }
        else
        {

        }
    }

    ALine = LLine;

    return LRslt;
}

CWnd*   YCGetTopModalDialog(CWnd *AWnd)
{
    for (CWnd *LWnd = AWnd; LWnd; LWnd = LWnd->GetParent())
    {
        if ((LWnd->GetStyle() & WS_CHILD) == 0)
            return LWnd;
    }

    return NULL;
}

void    YCSetDlgItemText(CDialog *ADlg, WORD AItemId, LPCSTR AText)
{
    CString LOldStr;

    ADlg->GetDlgItemText(AItemId, LOldStr);

    if (LOldStr != AText)
        ADlg->SetDlgItemText(AItemId, AText);
}

void    YCSetDlgItemFloat(CDialog *ADlg, WORD AItemId, double AValue, int ADigit/* = 1*/)
{
    CString LStr;

    LStr.Format("%.*f", ADigit, AValue);

    YCSetDlgItemText(ADlg, AItemId, LStr);
}

double  YCGetDlgItemFloatDef(CDialog *ADlg, WORD AItemId, double ADef/* = 0.0*/)
{
    CString LStr;

    ADlg->GetDlgItemText(AItemId, LStr);

    return YCStrToFloatDef(LStr, ADef);
}


//////////////////////////////////////////
//
//
class CYCAfxMessageBox : public CDialog
{
public:
    static HHOOK
        /**/    m_CBTHook;

    static CYCAfxMessageBox
        /**/    *m_ActiveMessageBox;


    static LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam);


    CYCAfxMessageBox(CFont *AFont);
    virtual ~CYCAfxMessageBox(void);


    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

private:
    IN CFont    *m_Font;

};


HHOOK   CYCAfxMessageBox::m_CBTHook             = NULL;

CYCAfxMessageBox
/**/    *CYCAfxMessageBox::m_ActiveMessageBox   = NULL;


LRESULT CALLBACK CYCAfxMessageBox::CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)  // do not process message 
        return CallNextHookEx(m_CBTHook, nCode, wParam, lParam); 


    if (nCode == HCBT_CREATEWND)
    {
        // TODO: write error handler
        char LClassName[256];

        GetClassName((HWND)wParam, LClassName, sizeof(LClassName));

        if (m_ActiveMessageBox && !_stricmp(LClassName, "#32770"))
            m_ActiveMessageBox->SubclassWindow((HWND)wParam);
    }


    return CallNextHookEx(m_CBTHook, nCode, wParam, lParam); 
}


CYCAfxMessageBox::CYCAfxMessageBox(CFont *AFont) : CDialog(), m_Font(AFont)
{
}

CYCAfxMessageBox::~CYCAfxMessageBox(void)
{
}

BOOL    CYCAfxMessageBox::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

    if (message == WM_INITDIALOG)
    {
        if (m_Font && m_Font->m_hObject)
        {
            CStatic LStatic;

            if (LStatic.Attach(::GetDlgItem(m_hWnd, 0xFFFF)))
            {
                int     LScaleXNumerator   = 1;
                int     LScaleXDenominator = 1;
                int     LScaleYNumerator   = 1;
                int     LScaleYDenominator = 1;
                CRect   LWinRect;

                {
                    CRect   LStaticOldRect(0, 0, 0, 0);
                    CRect   LStaticNewRect(0, 0, 0, 0);
                    CString LStaticText;


                    LStatic.GetWindowText(LStaticText);


                    //==========================================找出字串顯示於字型改變前後的畫面大小
                    CClientDC   LStaticDC(&LStatic);


                    // 計算出字型改變前要顯示的字串所需的顯示畫面尺吋
                    LStaticDC.DrawText(LStaticText, &LStaticOldRect, DT_CALCRECT);

                    // 計算出字型改變前要顯示的字串所需的顯示畫面尺吋
                    DECLARE_GdiSelectFont(LStaticDC, m_Font);

                    LStaticDC.DrawText(LStaticText, &LStaticNewRect, DT_CALCRECT);


                    //==========================================找出基準畫面大小
                    // 取出目前顯示的畫面尺吋
                    LStatic.GetClientRect(&LWinRect);

                    // 找出最小的畫面，以此為放大基準
                    LStaticOldRect &= LWinRect;


                    //==========================================
                    LScaleXNumerator   = LStaticNewRect.Width();
                    LScaleXDenominator = LStaticOldRect.Width();
                    LScaleYNumerator   = LStaticNewRect.Height();
                    LScaleYDenominator = LStaticOldRect.Height();
                }

                LStatic.Detach();


                SetFont(m_Font);


                //==========================================調整視窗的尺吋
                GetClientRect(&LWinRect);

                LWinRect.right  = LWinRect.left + LWinRect.Width()  * LScaleXNumerator / LScaleXDenominator;
                LWinRect.bottom = LWinRect.top  + LWinRect.Height() * LScaleYNumerator / LScaleYDenominator;
                AdjustWindowRect(&LWinRect, GetStyle(), FALSE);
                
                MoveWindow(&LWinRect, FALSE);


                //==========================================調整所有子控項的尺吋
                for (CWnd *LChild = GetWindow(GW_CHILD); LChild; LChild = LChild->GetWindow(GW_HWNDNEXT))
                {
                    LChild->SetFont(m_Font);
                    LChild->GetWindowRect(&LWinRect);
                    ScreenToClient(&LWinRect);

                    // 設定控項位置尺吋
                    LChild->MoveWindow(LWinRect.left     * LScaleXNumerator / LScaleXDenominator,
                        /**/           LWinRect.top      * LScaleYNumerator / LScaleYDenominator,
                        /**/           LWinRect.Width()  * LScaleXNumerator / LScaleXDenominator,
                        /**/           LWinRect.Height() * LScaleYNumerator / LScaleYDenominator);
                }

                CenterWindow();

            } // if (LStatic.Attach(::GetDlgItem(m_hWnd, 0xFFFF)))

        } // if (m_Font && m_Font->m_hObject)

        UnhookWindowsHookEx(CYCAfxMessageBox::m_CBTHook);
        m_CBTHook          = NULL;
        m_ActiveMessageBox = NULL;

    } // if (message == WM_INITDIALOG)

    return __super::OnWndMsg(message, wParam, lParam, pResult);
}

int     YCAfxMessageBox(LPCTSTR AText, UINT AType/* = MB_OK*/, UINT AIDHelp/* = 0*/, IN CFont *AFont/* = NULL*/)
{
    if (!AFont)
    {
        return AfxMessageBox(AText, AType, AIDHelp);
    }
    else
    {
        CYCAfxMessageBox    LAfxMessageBox(AFont);


        CYCAfxMessageBox::m_ActiveMessageBox = &LAfxMessageBox;
        CYCAfxMessageBox::m_CBTHook          = SetWindowsHookEx(WH_CBT, &CYCAfxMessageBox::CBTProc, NULL, GetCurrentThreadId());


        return AfxMessageBox(AText, AType, AIDHelp);
    }
}
//
//
//////////////////////////////////////////


DWORD   YCMinTickCountBetween(DWORD AMSecond1, DWORD AMSecond2)
{
    if (AMSecond1 > AMSecond2)
        return (AMSecond1 - AMSecond2 > ULONG_MAX / 2) ? (ULONG_MAX - AMSecond1 + AMSecond2) : (AMSecond1 - AMSecond2);
    else 
        return (AMSecond2 - AMSecond1 > ULONG_MAX / 2) ? (ULONG_MAX - AMSecond2 + AMSecond1) : (AMSecond2 - AMSecond1);
}

DWORD   YCMSecBetween(const SYSTEMTIME &ATime1, const SYSTEMTIME &ATime2)
{
    return (DWORD)abs(YCSystemTimeDifferenceMSec(ATime1, ATime2));
}

LONG    YCSystemTimeDifferenceMSec(const SYSTEMTIME &ATime1, const SYSTEMTIME &ATime2)
{
    const CTimeSpan LTimeSpan = CTime(ATime1, 0) - CTime(ATime2, 0);

    return (LONG)(LTimeSpan.GetTotalSeconds() * 1000 + ((LONG)ATime1.wMilliseconds - (LONG)ATime2.wMilliseconds));
}

void    YCSystemTimeAdd(SYSTEMTIME &ATime, int ATimeMSec)
{
    union
    {
        FILETIME        LTempTime;
        ULARGE_INTEGER  LTemp;
    };

    SystemTimeToFileTime(&ATime, &LTempTime);

    LTemp.QuadPart += ((LONGLONG)ATimeMSec * 1000 * 10);

    FileTimeToSystemTime(&LTempTime, &ATime);
}

LONG    YCSystemTimeCompare(const SYSTEMTIME &ATime1, const SYSTEMTIME &ATime2)
{
    return YCSystemTimeDifferenceMSec(ATime1, ATime2);
}

CString YCFormatCurrentTimeText(LPCSTR AFormat)
{
    SYSTEMTIME  LST;

    GetLocalTime(&LST);

    return YCFormatSystemTimeText(LST, AFormat);
}

CString YCFormatSystemTimeText(const SYSTEMTIME &ATime, LPCSTR AFormat)
{
    CString LRslt;

    LRslt.Format("%04u-%02u-%02u %02u:%02u:%02u %3u", ATime.wYear, ATime.wMonth, ATime.wDay, ATime.wHour, ATime.wMinute, ATime.wSecond, ATime.wMilliseconds);

    return LRslt;
}

SYSTEMTIME
/**/    YCGetBaseLocalTime()
{
    SYSTEMTIME LST;

    GetLocalTime(&LST);

    LST.wHour         = 0;
    LST.wMinute       = 0;
    LST.wSecond       = 0;
    LST.wMilliseconds = 0;

    return LST;
}

SYSTEMTIME
/**/    YCGetLocalTime()
{
    SYSTEMTIME LST;

    GetLocalTime(&LST);

    return LST;
}


//void YCSystemTimeAdd(SYSTEMTIME &ATime1, SYSTEMTIME &ATime2)
//{
//}
//
//void YCSystemTimeAdd(SYSTEMTIME &ATime1, const CTime &ATime2)
//{
//}
//
//void YCSystemTimeAdd(SYSTEMTIME &ATime1, const CTimeSpan &ATime2)
//{
//}

double  YCAverage(int ACount, double AValues[])
{
    double LTotal = 0;

    for (int I = 0; I < ACount; I++) 
        LTotal += AValues[I];

    return LTotal / ACount;
}

double  YCAverage(int ACount, int ASkipFront, int ASkipBack, double AValues[])
{
    std::vector<double> LValues;

    LValues.reserve(ACount);

    for (int I = 0; I < ACount; I ++)
    {
        // 插入排序
        for (int J = 0; J < (LONGLONG)LValues.size(); J ++)
        {
            if (AValues[I] <= LValues[J])
            {
                LValues.insert(LValues.begin() + J, AValues[I]);
                break;
            }
        }

        if ((I + 1) != LValues.size())
            LValues.push_back(AValues[I]);
    }

    ACount = 0;
    double LRslt = 0;

    for (int I = ASkipFront; I < (int)LValues.size() - ASkipBack - 1; I ++)
    {
        LRslt += LValues[I];
        ACount ++;
    }

    if (ACount != 0)
        return LRslt / ACount;

    return LRslt;
}

double  YCMiddle(int ACount, double AValues[])
{
    std::vector<double> LValues;

    for (int I = 0; I < ACount; I ++)
    {
        // 插入排序
        for (int J = 0; J < (LONGLONG)LValues.size(); J ++)
        {
            if (AValues[I] <= LValues[J])
            {
                LValues.insert(LValues.begin() + J, AValues[I]);
                break;
            }
        }

        if ((I + 1) != LValues.size())
            LValues.push_back(AValues[I]);
    }

    return LValues[LValues.size() / 2];
}

bool    YCSaveBMPToFileBMPBW8(LPCSTR AFileName, BITMAPINFO* ABitmapInfo, const BYTE *ABMP)
{
    ASSERT(AFileName);
    ASSERT(ABitmapInfo);
    ASSERT(ABMP);

    if (!AFileName || !ABitmapInfo || !ABMP)
        return false;


    YCForceDirFromFileName(AFileName);

    CFile LFile;

    if (LFile.Open(AFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
    {
        // long LSize = 0, LBMPLineWidth = 0;
        int                 LPaletteSize = 0;
        BITMAPFILEHEADER    LBitmapFileHeader;

        //Get LPaletteSize
        switch (ABitmapInfo->bmiHeader.biBitCount)
        {
        case 1  : LPaletteSize = 2;   break;
        case 4  : LPaletteSize = 16;  break;
        case 8  : LPaletteSize = 256; break;
        case 16 :
        case 24 : LPaletteSize = 0;   break;
        }

        //Get Bytes of each line
        /*LBMPLineWidth = (ABitmapInfo->bmiHeader.biWidth * ABitmapInfo->bmiHeader.biBitCount + 7)/8;
        LBMPLineWidth = (LBMPLineWidth + 3) / 4;
        LBMPLineWidth = LBMPLineWidth*4;*/

        const LONG LBMPLineWidth = YCWidthToBmpWidth(ABitmapInfo->bmiHeader.biWidth);

        //Get Size of Bmp Data 
        const LONG LSize = LBMPLineWidth * ABitmapInfo->bmiHeader.biHeight;

        //Write BMP File Header
        LBitmapFileHeader.bfType        = 0x4d42;
        LBitmapFileHeader.bfReserved1   = LBitmapFileHeader.bfReserved2 = 0;
        LBitmapFileHeader.bfOffBits     = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + LPaletteSize * sizeof(RGBQUAD);
        LBitmapFileHeader.bfSize        = LBitmapFileHeader.bfOffBits + LSize;

        //Do Write
        LFile.Write(&LBitmapFileHeader, sizeof(BITMAPFILEHEADER));
        LFile.Write(ABitmapInfo, sizeof(BITMAPINFOHEADER) + LPaletteSize * sizeof(RGBQUAD));
        LFile.Write(ABMP, LSize);
        LFile.Close();

        return true;

    } // if (LFile.Open(AFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))

    return false;
}

bool    YCSaveBMPToFileRawBW8(LPCSTR AFileName, const BYTE *AImage, int AWidth, int AHeight)
{
    if (!AFileName)
        return false;

    BITMAPINFO*    ABitmapInfo = NULL;
    short BitsPerPixel = 8;
    int PaletteSize = 256, bytes_per_line=0;
    int I, index=0;
    long size = 0;

    if (BitsPerPixel==24)
        PaletteSize=0;

    ABitmapInfo = (BITMAPINFO*)new char[(sizeof(BITMAPINFOHEADER) + PaletteSize*sizeof(RGBQUAD))];
    if (!ABitmapInfo)        return false;

    //Get Bytes of each line
    bytes_per_line = (AWidth * 8 + 7)/8;
    bytes_per_line = (bytes_per_line + 3) / 4;
    bytes_per_line = bytes_per_line*4;

    //Get Size of Bmp Data 
    size = bytes_per_line * AHeight;
    ABitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ABitmapInfo->bmiHeader.biWidth = AWidth;
    ABitmapInfo->bmiHeader.biHeight = AHeight;
    ABitmapInfo->bmiHeader.biPlanes = 1;
    ABitmapInfo->bmiHeader.biBitCount = BitsPerPixel;
    ABitmapInfo->bmiHeader.biCompression = BI_RGB;
    ABitmapInfo->bmiHeader.biSizeImage = size;
    ABitmapInfo->bmiHeader.biXPelsPerMeter = 
        ABitmapInfo->bmiHeader.biYPelsPerMeter = 120;
    ABitmapInfo->bmiHeader.biClrUsed = PaletteSize;
    ABitmapInfo->bmiHeader.biClrImportant = PaletteSize;

    for (I=0;I<PaletteSize;I++)
    {
        ABitmapInfo->bmiColors[I].rgbRed = I;
        ABitmapInfo->bmiColors[I].rgbGreen = I;
        ABitmapInfo->bmiColors[I].rgbBlue = I;
        ABitmapInfo->bmiColors[I].rgbReserved = 0;
    }


    BYTE *Image=new BYTE[bytes_per_line*AHeight];

    for (I=0;I<AHeight;I++)
    {
        //memcpy(&Image[I*bytes_per_line], &AImage[(AHeight-I-1)*AWidth], AWidth);
        memcpy(&Image[I*bytes_per_line], &AImage[(I)*AWidth], AWidth);
    }


    bool ok;
    ok=YCSaveBMPToFileBMPBW8(AFileName, ABitmapInfo, Image);

    delete[] Image;
    delete[] ABitmapInfo;

    if (ok==false) return false;

    return true;
}

bool    YCSaveBMPToFileBMPBW8(LPCSTR AFileName, const BYTE *AImage, int AWidth, int AHeight)
{
    bool LRslt = false;

    if (AFileName)
    {
        short   LBitsPerPixel   = 8;
        int     LPaletteSize    = 256;

        if (LBitsPerPixel == 24)
            LPaletteSize = 0;

        BITMAPINFO  *LBitmapInfo = (BITMAPINFO*)new char[(sizeof(BITMAPINFOHEADER) + LPaletteSize * sizeof(RGBQUAD))];

        ASSERT(LBitmapInfo);

        if (LBitmapInfo)
        {
            try
            {
                LBitmapInfo->bmiHeader.biSize   = sizeof(BITMAPINFOHEADER);
                LBitmapInfo->bmiHeader.biWidth  = AWidth;
                LBitmapInfo->bmiHeader.biHeight = AHeight;
                LBitmapInfo->bmiHeader.biPlanes = 1;
                LBitmapInfo->bmiHeader.biBitCount    = LBitsPerPixel;
                LBitmapInfo->bmiHeader.biCompression = BI_RGB;
                LBitmapInfo->bmiHeader.biSizeImage   = YCWidthToBmpWidth(AWidth) * AHeight;
                LBitmapInfo->bmiHeader.biXPelsPerMeter  = 
                    LBitmapInfo->bmiHeader.biYPelsPerMeter  = 120;
                LBitmapInfo->bmiHeader.biClrUsed        = LPaletteSize;
                LBitmapInfo->bmiHeader.biClrImportant   = LPaletteSize;

                for (int I = 0; I < LPaletteSize; I ++)
                {
                    LBitmapInfo->bmiColors[I].rgbRed        = I;
                    LBitmapInfo->bmiColors[I].rgbGreen      = I;
                    LBitmapInfo->bmiColors[I].rgbBlue       = I;
                    LBitmapInfo->bmiColors[I].rgbReserved   = 0;
                }

                LRslt = YCSaveBMPToFileBMPBW8(AFileName, LBitmapInfo, AImage);
            }
            catch (...)
            {
                LRslt = false;
            }

            delete[] LBitmapInfo;
        }
    }

    return LRslt;
}

bool    YCOpenBMPFromFileRawBW8(LPCSTR AFileName, OUT SIZE &ABmpSize, OUT BYTE **ABmpRaw)
{
    /*****************************************************************
    ******************************************************************
    ******************************************************************
    ***   第一部份：
    ***   bmp檔案的開頭為一BITMAPFILEHEADER結構
    ***   BITMAPFILEHEADER結構其大小為14 bytes
    ***   第0~1 byte 為識別碼 "BM" 我們可以透過前兩個bytes來判斷這個檔案是否為bmp檔
    ***   第2~5 byte 儲存了這個檔案的大小
    ***   接下來中間有兩個WORD沒有用
    ***   第10~13 byte 儲存點陣資料(RAW DATA)距離檔頭的位移
    ***   
    ***   第二部份：
    ***   接下來是BITMAPINFO結構 分為兩個部分
    ***   前面為BITMAPINFOHEADER結構 後面為調色盤(pallete)
    ***   BITMAPINFOHEADER結構 儲存了一些有用的資訊
    ***   如圖片 寬 高 位元深度
    ***   另外還有 biXPelsPerMeter 跟 biYPelsPerMeter
    ***   這紀錄了每公尺有多少像素 
    ***   這兩個數值是給印表機用的(PowerPoint 也會用到) 
    ***   當印表機要印出這張圖時 便會將這兩個值跟寬高相乘 便可得到印出來長幾公分寬幾公分
    ***   
    ***   第三部份：
    ***   調色盤資訊 只有古早顏色很少的圖片才會用到 新的圖片都用不到
    ***
    ***   第四部份：
    ***   最後是點陣圖資料 這部分只要把bitmap的 DIB_Bits填進去就OK了
    ***   其起始位置為BITMAPFILEHEADER結構中bfOffBits所指定
    ***   
    ***   
    ***   最後列出相關的結構宣告
    ***   typedef struct tagBITMAPFILEHEADER
    ***   {
    ***       WORD    bfType;
    ***       DWORD   bfSize;
    ***       WORD    bfReserved1;
    ***       WORD    bfReserved2;
    ***       DWORD   bfOffBits;
    ***   } BITMAPFILEHEADER, *PBITMAPFILEHEADER;
    ***
    ***   typedef struct tagBITMAPINFO
    ***   {
    ***       BITMAPINFOHEADER bmiHeader;
    ***       RGBQUAD          bmiColors[1];
    ***   } BITMAPINFO, *PBITMAPINFO;
    ***
    ***   typedef struct tagBITMAPINFOHEADER
    ***   {
    ***       DWORD  biSize;
    ***       LONG   biWidth;
    ***       LONG   biHeight;
    ***       WORD   biPlanes;
    ***       WORD   biBitCount;
    ***       DWORD  biCompression;
    ***       DWORD  biSizeImage;
    ***       LONG   biXPelsPerMeter;
    ***       LONG   biYPelsPerMeter;
    ***       DWORD  biClrUsed;
    ***       DWORD  biClrImportant;
    ***   } BITMAPINFOHEADER, *PBITMAPINFOHEADER;
    ******************************************************************
    ******************************************************************
    *****************************************************************/

    if (!PathFileExists(AFileName))
        return false;


    CFile   LFile;

    if (LFile.Open(AFileName, CFile::modeRead))
    {

        ////////////////////////////////////////
        // Bitmap File Header
        BITMAPFILEHEADER    LBitmapFileHeader;

        if (LFile.GetLength() - LFile.GetPosition() >= sizeof(LBitmapFileHeader))
            LFile.Read(&LBitmapFileHeader, sizeof(LBitmapFileHeader));
        else
            return false;

        if (LBitmapFileHeader.bfType != 0x4D42)
            return false;

        ////////////////////////////////////////
        // Bitmap Info Header
        BITMAPINFOHEADER    LBitmapInfoHeader;

        if (LFile.GetLength() - LFile.GetPosition() >= sizeof(LBitmapInfoHeader))
            LFile.Read(&LBitmapInfoHeader, sizeof(LBitmapInfoHeader));
        else
            return false;

        ////////////////////////////////////////
        // Bitmap Color Table
        ULARGE_INTEGER  LFileSize;
        ULARGE_INTEGER  LFilePosition;

        LFile.Seek(LBitmapFileHeader.bfOffBits, CFile::begin);

        ////////////////////////////////////////
        // Bitmap Data
        ASSERT(ABmpRaw);
        ASSERT(!(*ABmpRaw));

        if (ABmpRaw && !(*ABmpRaw))
        {
            const int LBMPBMPWidth = ((LBitmapInfoHeader.biWidth % 4) ? ((LBitmapInfoHeader.biWidth / 4) + 1) * 4 : LBitmapInfoHeader.biWidth);

            *ABmpRaw = (BYTE *)malloc(LBitmapInfoHeader.biWidth * LBitmapInfoHeader.biHeight);

            for (int LY = 0; LY < LBitmapInfoHeader.biHeight; LY ++)
            {
                for (int LX = 0; LX < LBMPBMPWidth; LX ++)
                {
                    BYTE LPixelData = 0;

                    switch (LBitmapInfoHeader.biBitCount)
                    {
                        //case 1 : break;
                        //case 4 : break;
                    case  8 :
                        LFile.Read(&LPixelData, sizeof(LPixelData));
                        break;

                    case 16 :
                        {
                            WORD LPixelData16;

                            VERIFY(LFile.Read(&LPixelData16, sizeof(LPixelData16)) == sizeof(LPixelData16));
                            LPixelData = (LPixelData16 * 255 / 0xFFFF);
                        }
                        break;

                    case 24 :
                        {
                            DWORD LPixelData24 = 0;

                            VERIFY(LFile.Read(&LPixelData24, 3) == 3);
                            LPixelData = (BYTE)((LPixelData24 * 255 / 0xFFFFFF));
                        }
                        break;

                    case 32 :
                        {
                            DWORD LPixelData32;

                            VERIFY(LFile.Read(&LPixelData32, sizeof(LPixelData32)) == sizeof(LPixelData32));
                            LPixelData = (BYTE)(((LPixelData32 & 0xFFFFFF) * 255 / 0xFFFFFF));
                        }
                        break;

                    default : ASSERT(FALSE);

                    }

                    if (LX < LBitmapInfoHeader.biWidth)
                    {
                        (*ABmpRaw)[LY * LBitmapInfoHeader.biWidth + LX] = LPixelData;
                    }
                }
            }

            ABmpSize.cx = LBitmapInfoHeader.biWidth;
            ABmpSize.cy = LBitmapInfoHeader.biHeight;

            LFileSize.QuadPart     = LFile.GetLength();
            LFilePosition.QuadPart = LFile.GetPosition();
            TRACE("LFile.Position : %d, Size : %d\n", LFilePosition.LowPart, LFileSize.LowPart);

            return true;

        } // if (ABmpRaw && !(*ABmpRaw))

    } // if (LFile.Open(AFileName, CFile::modeRead))

    return false;
}

bool    YCAnalyzeLine(const std::vector<strYCDoublePoint> &APoints, int AFromIdx, int AEndIdx, OUT double *AA, OUT double *AB)
{
    if (AEndIdx > (int)APoints.size() - 1)
        AEndIdx = (int)APoints.size() - 1;

    const int LPointsCount = AEndIdx - AFromIdx + 1;

    if (LPointsCount <= 1)
        return false;

    double SXY = 0, SX = 0, SY = 0, SX2 = 0;

    for (int I = AFromIdx; I <= AEndIdx; I ++)
    {
        SX += APoints[I].X;
        SY += APoints[I].Y;
        SXY += (APoints[I].X * APoints[I].Y);
        SX2 += (APoints[I].X * APoints[I].X);
    }

    double LA, LB;

    if ((LPointsCount * SX2 - SX * SX) != 0)
        LA = (LPointsCount * SXY - SX * SY) / (LPointsCount * SX2 - SX * SX);
    else LA = 0;

    LB = SY / LPointsCount - LA * (SX / LPointsCount);

    if (AA)
        *AA = LA;

    if (AB)
        *AB = LB;

    return true;
}

void    YCAnalyzeLine(int APointsCount, const strYCDoublePoint *APoints, OUT double *AA, OUT double *AB)
{
    double SXY = 0, SX = 0, SY = 0, SX2 = 0;

    for (int I = 0; I < APointsCount; I ++)
    {
        SX += APoints[I].X;
        SY += APoints[I].Y;
        SXY += (APoints[I].X * APoints[I].Y);
        SX2 += (APoints[I].X * APoints[I].X);
    }

    double LA, LB;

    if ((APointsCount * SX2 - SX * SX) != 0)
        LA = (APointsCount * SXY - SX * SY) / (APointsCount * SX2 - SX * SX);
    else LA = 0;

    LB = SY / APointsCount - LA * (SX / APointsCount);

    if (AA)
        *AA = LA;

    if (AB)
        *AB = LB;

    /**AA = (APointsCount * SXY - SX * SY) / (APointsCount * SX2 - SX * SX);
    *AB = SY / APointsCount - *AA * (SX / APointsCount);*/
}

void    YCAnalyzeCircle(int ACount, strYCDoublePoint *APoints, OUT strYCDoublePoint &AOrg, OUT double &ARadius)
{
    double a1, a2, b1, b2, c1, c2;
    double S_Xi = 0, S_Yi = 0,
        S_Xi2 = 0, S_Yi2 = 0, S_XiYi = 0,
        S_Xi3 = 0, S_Yi3 = 0,
        S_XiYi2 = 0, S_Xi2Yi = 0;

    for (int I = 0; I < ACount; I ++)
    {
        S_Xi += APoints[I].X; 
        S_Yi += APoints[I].Y;

        double LTmp = APoints[I].X * APoints[I].X;

        S_Xi2 += LTmp;
        S_Xi3 += LTmp * APoints[I].X;
        S_Xi2Yi += LTmp * APoints[I].Y;

        LTmp = APoints[I].Y * APoints[I].Y;
        S_Yi2 += LTmp;
        S_Yi3 += LTmp * APoints[I].Y;
        S_XiYi2 += APoints[I].X * LTmp;

        S_XiYi += APoints[I].X * APoints[I].Y;
    }

    a1 = 2 * (S_Xi * S_Xi - ACount * S_Xi2);
    b1 = 2 * (S_Xi * S_Yi - ACount * S_XiYi);
    a2 = b1;
    b2 = 2 * (S_Yi * S_Yi - ACount * S_Yi2);
    c1 = S_Xi2 * S_Xi - ACount * S_Xi3 + S_Xi * S_Yi2 - ACount * S_XiYi2;
    c2 = S_Xi2 * S_Yi - ACount * S_Yi3 + S_Yi * S_Yi2 - ACount * S_Xi2Yi;

    AOrg.X = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
    AOrg.Y = (c2 * a1 - c1 * a2) / (a1 * b2 - a2 * b1);

    ARadius = 0;

    for (int I = 0; I < ACount; I ++)
    {
        ARadius += pow(pow(APoints[I].X - AOrg.X, 2.0) + pow(APoints[I].Y - AOrg.Y, 2.0), 0.5);
    }

    ARadius /= ACount;
}

void    YCBMPToRaw(const SIZE ASize, OUT BYTE *ADst, const BYTE *ASrc)
{
    if (YCWidthToBmpWidth(ASize.cx) == ASize.cx)
        memcpy_s(ADst, ASize.cx * ASize.cy, ASrc, ASize.cx * ASize.cy);
    else
    {
        for (int I = 0; I < ASize.cy; I ++)
        {
            memcpy_s(ADst, ASize.cx, ASrc, ASize.cx);

            ADst += ASize.cx;
            ASrc += YCWidthToBmpWidth(ASize.cx);
        }
    }
}

void    YCRawToBMP(const SIZE ASize, OUT BYTE *ADst, const BYTE *ASrc)
{
    if (YCWidthToBmpWidth(ASize.cx) == ASize.cx)
        memcpy_s(ADst, ASize.cx * ASize.cy, ASrc, ASize.cx * ASize.cy);
    else
    {
        ZeroMemory(ADst, YCWidthToBmpWidth(ASize.cx) * ASize.cy);

        for (int I = 0; I < ASize.cy; I ++)
        {
            memcpy_s(ADst, ASize.cx, ASrc, ASize.cx);

            ASrc += ASize.cx;
            ADst += YCWidthToBmpWidth(ASize.cx);
        }
    }
}

void    YCReverseCopyBMP(const SIZE &ASize, BYTE *ADst, const BYTE *ASrc)
{
#ifdef _DEBUG
    static DWORD LMaxSpendTime = 0;
    DWORD LTC = GetTickCount();
#endif           

    if (ADst == ASrc)
    {
        BYTE    *LBuffer = new BYTE[ASize.cx];
        BYTE    *LSrc    = ADst;
        BYTE    *LDst    = ADst + (ASize.cx * ASize.cy - ASize.cx);

        try
        {
            for (int I = 0; LDst > LSrc; I ++)
            {
                memcpy_s(LBuffer, ASize.cx, LDst    , ASize.cx);
                memcpy_s(LDst   , ASize.cx, LSrc    , ASize.cx);
                memcpy_s(LSrc   , ASize.cx, LBuffer , ASize.cx);

                LSrc += ASize.cx;
                LDst -= ASize.cx;
            }
        }
        catch (...)
        {
        }

        delete [] LBuffer;
    }
    else
    {
        const BYTE  *LSrc = ASrc;
        BYTE        *LDst = ADst + (ASize.cx * ASize.cy - ASize.cx);

        for (int I = 0; I < ASize.cy; I ++)
        {
            memcpy_s(LDst, ASize.cx, LSrc, ASize.cx);

            LSrc += ASize.cx;
            LDst -= ASize.cx;
        }
    }

#ifdef _DEBUG
    LTC = GetTickCount() - LTC;
    LMaxSpendTime = LTC > LMaxSpendTime ? LTC : LMaxSpendTime;
    TRACE("YCReverseCopyBMP({%d, %d}) Spend time : %d, Max Spend time : %d\n", ASize.cx, ASize.cy, LTC, LMaxSpendTime);
#endif

}

bool    YCPumpMessageAndWaitFor(HANDLE AHandle, DWORD ATimeoutMSec/* = INFINITE*/)
{
    bool    LRslt = false;
    MSG     LMsg;
    int     LIdleCount = 0;
    bool    LIsDoIdle = false;
    DWORD   LMilliseconds = ATimeoutMSec;
    DWORD   LTC = GetTickCount();
#ifdef _DEBUG
    bool    LIsForceExit = false;
#endif

    do
    {
        // 如果訊息佇列有訊息，則執行它
        if (::PeekMessage(&LMsg, NULL, 0, 0, PM_NOREMOVE))
        {
            LIdleCount = 0;
            LIsDoIdle = true;

            //if (!AfxGetThread()->PumpMessage())
            if (!AfxPumpMessage())
                break; // WM_QUIT;
            else
                LMilliseconds = 0;
        }
        else
        {
            // 算出進入本程序後已經過的時間
            LMilliseconds = YCMinTickCountBetween(LTC, GetTickCount());

            if (LMilliseconds > ATimeoutMSec)
                LMilliseconds = 0;
            else if (ATimeoutMSec != INFINITE)
                LMilliseconds = ATimeoutMSec - LMilliseconds;
            else
                LMilliseconds = INFINITE;

            // 檢查是否要DoIdle()
            if (LIsDoIdle)
            {
                HWND LTopHwnd = ::GetForegroundWindow();

                if (LTopHwnd && (::GetWindowThreadProcessId(LTopHwnd, NULL) == AfxGetApp()->m_nThreadID))
                {
                    ::SendMessage(LTopHwnd, WM_KICKIDLE, MSGF_DIALOGBOX, LIdleCount ++);
                    LIsDoIdle = false;

                    LMilliseconds = 0;
                }
            }
        }

#ifdef _DEBUG
        if (LIsForceExit)
            break;
#endif
        // 執行待待並取得結果
        LRslt = (MsgWaitForMultipleObjects(1, &AHandle, FALSE, LMilliseconds, QS_ALLINPUT) == WAIT_OBJECT_0);
    }
    while (!LRslt && (YCMinTickCountBetween(LTC, GetTickCount()) < ATimeoutMSec));

    return LRslt;
}

void    YCEnableThisWndIncludeParent(CWnd *AWnd, bool AAllParent, BOOL AEnabled)
{
    ASSERT(AWnd);

    if (AWnd)
    {
        AWnd->EnableWindow(AEnabled);

        if (AAllParent)
        {
            for (CWnd *LParent = AWnd->GetParent(); LParent; LParent = LParent->GetParent())
                LParent->EnableWindow(AEnabled);
        }
    }
}

CString YCComputerName()
{
    char    LBuf[MAX_PATH];
    DWORD   LSize = sizeof(LBuf);

    ::GetComputerName(LBuf, &LSize);

    if (LSize < MAX_PATH)
        LBuf[LSize] = 0;

    return LBuf;
}

CString YCApplicationFileName()
{
    char LBuf[MAX_PATH];

    ::GetModuleFileName(NULL, LBuf, sizeof(LBuf));

    return LBuf;
}

CString YCApplicationDir()
{
    char LBuf[MAX_PATH];

    ::GetModuleFileName(NULL, LBuf, sizeof(LBuf));
    PathRemoveFileSpec(LBuf);

    return LBuf;
}

bool    YCSSEAddImage(long AWidth, long AHeight, BYTE *Image1, BYTE *Image2)
{
    long  iCount;

    //if (IsBMPFormat==true)
    //{
    char AddShift = (char)(((int)(AWidth / 4) + 1) * 4 - AWidth);

    if (AddShift == 4) 
        AddShift=0;

    iCount = (AWidth + AddShift) * AHeight;
    //}
    //else iCount = AWidth * AHeight;

    // we assume all data in the register is not used by others
    __asm
    {
        // Assign pointers to register
        mov            esi, [Image1]        ;put src addr to esi reg
            mov            edi, [Image2]        ;put dest addr to edi reg
            mov            ecx, [iCount]        ;put count to ecx reg
            shr            ecx, 3                ;divide count with 8 by shifting 3 bits to right

codeloop:
        movq        mm0, [esi]            ;mov 8 bytes of src data to mmx reg 0
            movq        mm2, [edi]            ;mov 8 bytes of dest data to mmx reg 1
            PADDUSB        mm0, mm2            ;Add unsigned 8bit saturated to mmx reg 0
            movq        [esi], mm0            ;dump back the added 8 bytes of data to dest memory
            add            esi, 8                ;add src pointer by 8 bytes
            add            edi, 8                ;add dest pointer by 8 bytes

            dec            ecx                    ;decrement count by 1
            jnz            codeloop            ;jump to codeloop if not Zero
            emms                            ;Restore FPU state to normal
    }

    // For end of image
    if ((iCount % 8 ) !=0)
    {
        long i, value;

        i = iCount - (iCount % 8);
        for ( ; i < iCount; i ++)
        {
            value = Image1[i] + Image2[i];

            if (value > 255) 
                Image1[i] = 255;
            else Image1[i] = (BYTE)value;

        }
    }

    return true;
}

bool    YCSSEAddImage(long AWidth, long AHeight, BYTE *Image1, BYTE Value)
{
    if (Image1 == NULL)
        return false;

    long  iCount;

    //if(IsBMPFormat==true)
    //{
    char AddShift=(char) (((int) (AWidth/4)+1)*4-AWidth);
    if(AddShift==4) AddShift=0;
    iCount=(AWidth+AddShift)*AHeight;
    //}
    //else iCount=AWidth*AHeight;

    BYTE *Buffer=new BYTE[8];
    memset(Buffer, Value, sizeof(BYTE)*8);


    // we assume all data in the register is not used by others
    __asm
    {
        // Assign pointers to register
        mov            esi, [Image1]        ;put src addr to esi reg
            mov            edi, [Buffer]        ;put dest addr to edi reg
            mov            ecx, [iCount]        ;put count to ecx reg
            shr            ecx, 3                ;divide count with 8 by shifting 3 bits to right

            movq        mm2, [edi]

codeloop:
        movq        mm0, [esi]            ;mov 8 bytes of src data to mmx reg 0
            PADDUSB        mm0, mm2            ;Add unsigned 8bit saturated to mmx reg 0
            movq        [esi], mm0            ;dump back the added 8 bytes of data to dest memory
            add            esi, 8                ;add src pointer by 8 bytes

            dec            ecx                    ;decrement count by 1
            jnz            codeloop            ;jump to codeloop if not Zero
            emms                            ;Restore FPU state to normal

    }

    // For end of image
    if( (iCount % 8 ) !=0)
    {
        long i, value;
        i=iCount-(iCount % 8);
        for( ; i < iCount; i ++)
        {
            value=Image1[i]+Value;
            if(value > 255) 
                Image1[i]=255;
            else Image1[i]=(BYTE)value;

        }
    }

    delete[] Buffer;

    return true;
}

void    YCHightContrastRaw(IN OUT BYTE *ABmp, const RECT& ASize, int AFactor)
{
    YCHightContrastRaw(ABmp, ASize.right - ASize.left, ASize.bottom - ASize.top, AFactor);
}

void    YCHightContrastRaw(IN OUT BYTE *ABmp, int AWidth, int AHeight, int AFactor)
{
    // TODO: Add your control notification handler code here
    long    LLowPixelValue,
        LHighPixelValue,
        LMinPixelCount = 100;
    std::vector<BYTE>   LHistogram;

    LHistogram.resize(256);
    ZeroMemory(&LHistogram[0], 256);

    for (int LRow = 0; LRow < AHeight; LRow ++)
    {
        for (int LCol = 0; LCol < AWidth; LCol ++)
        {
            BYTE LValue = ABmp[LCol + LRow * AWidth];

            LHistogram[LValue] ++;
        }
    }

    for (int LPixelValue = 0; LPixelValue < 256; LPixelValue ++)
    {
        if (LHistogram[LPixelValue] >= LMinPixelCount)
        {
            LLowPixelValue = LPixelValue - 10;

            if (LLowPixelValue < 0)
                LLowPixelValue = 0;

            break;
        }
    }

    for (int LPixelValue = 240; LPixelValue >=0 ; LPixelValue --)
    {
        if (LHistogram[LPixelValue] >= LMinPixelCount)
        {
            LHighPixelValue = LPixelValue + 10;

            if (LHighPixelValue > 255)
                LHighPixelValue = 255;

            break;
        }
    }

    float LFactor = 255.0f / (LHighPixelValue - LLowPixelValue);

    for (int LRow = 0; LRow < AHeight; LRow ++)
    {
        for (int LCol = 0; LCol < AWidth; LCol ++)
        {
            if (ABmp[LCol + LRow * AWidth] > LHighPixelValue)
            {
                ABmp[LCol + LRow * AWidth] = 255;
            }
            else if (ABmp[LCol + LRow * AWidth] < LLowPixelValue)
            {
                ABmp[LCol + LRow * AWidth] = 0;
            }
            else
            {
                ABmp[LCol + LRow * AWidth] = (BYTE)(LFactor * (ABmp[LCol + LRow * AWidth] - LLowPixelValue));
            }
        }
    }
}

void    YCImageGainOffset(IN OUT BYTE *ABmp, const SIZE &ASize, double AGain, int AOffset)
{
    YCImageGainOffset(ABmp, ASize.cx, ASize.cy, AGain, AOffset);
}

void    YCImageGainOffset(IN OUT BYTE *ABmp, int AWidth, int AHeight, double AGain, int AOffset)
{
    YCImageGainOffset(ABmp, AWidth, AHeight, 0, 0, AWidth, AHeight, AGain, AOffset);
}

void    YCImageGainOffset(IN OUT BYTE *ABmp, const SIZE &ASize, const RECT &AEffectiveArea, double AGain, int AOffset)
{
    YCImageGainOffset(
        ABmp,
        ASize.cx,
        ASize.cy,
        AEffectiveArea.left,
        AEffectiveArea.top,
        AEffectiveArea.right - AEffectiveArea.left,
        AEffectiveArea.bottom- AEffectiveArea.top,
        AGain,
        AOffset);
}

void    YCImageGainOffset(IN OUT BYTE    *ABmp,
                         int            AWidth              , int AHeight,
                         int            AEffectiveAreaX     , int AEffectiveAreaY,
                         int            AEffectiveAreaWidth , int AEffectiveAreaHeight,
                         double         AGain               , int AOffset)
{
    ///////////////////////////////
    // 影像Gain/Offset處理
    //
    const int LGain10XInt = (int)(AGain * 10);

    if (LGain10XInt != 10 || AOffset != 0)
    {
        if (AEffectiveAreaX < 0)
            AEffectiveAreaX = 0;

        if (AEffectiveAreaY < 0)
            AEffectiveAreaY = 0;

        if (AEffectiveAreaX + AEffectiveAreaWidth > AWidth)
            AEffectiveAreaWidth = AWidth - AEffectiveAreaX;

        if (AEffectiveAreaY + AEffectiveAreaHeight > AHeight)
            AEffectiveAreaHeight = AHeight - AEffectiveAreaY;


        for (int LRow = AEffectiveAreaY; LRow < AEffectiveAreaY + AEffectiveAreaHeight; LRow ++)
        {
            for (int LCol = AEffectiveAreaX; LCol < AEffectiveAreaX + AEffectiveAreaWidth; LCol ++)
            {
#define LSrcPel     ABmp[LCol + LRow * AWidth]

                int LPel = (LGain10XInt * LSrcPel) / 10 + AOffset;

                if (LPel > 240)
                    LPel = 240;
                else if (LPel < 15)
                    LPel = 15;

                LSrcPel = LPel;

#undef LSrcPel
            }
        }
    }
    //
    // 影像Gain/Offset處理
    ///////////////////////////////
}

void*   YCmalloc(size_t ASize)
{
    return (ASize > 0) ? malloc(ASize) : NULL;
}

void    YCfree(void *AMemBlock)
{
    if (AMemBlock)
        free(AMemBlock);
}

void*   YCrealloc(void *AMemBlock, size_t ANewSize)
{
    return (!AMemBlock && (ANewSize == 0)) ? AMemBlock : realloc(AMemBlock, ANewSize);
}

void    YCForceDir(LPCSTR ADir)
{
    SHCreateDirectoryEx(NULL, ADir, NULL);
}

void    YCForceDirFromFileName(LPCSTR AFileName)
{
    CString     LFileName = AFileName;
    const int   I         = LFileName.ReverseFind('\\');

    if (I >= 0)
        LFileName.Delete(I, MAX_PATH);

    if (!LFileName.IsEmpty())
        YCForceDir(LFileName);
}


typedef std::map<CString, CString, strYCStrLessNoCase>    TYCDirectoryVar;


TYCDirectoryVar&
/**/    YCDirectoryVar()
{
    static TYCDirectoryVar LDirectoryVar;

    return LDirectoryVar;
}

CString YCRelativeFileNameToAbs(LPCSTR AFileName)
{
    TStringDeque    LStrings;
    LPCSTR          LBegin = AFileName;
    LPCSTR          LScan  = AFileName;

    const TYCDirectoryVar &LDirectoryVar = YCDirectoryVar();

    for ( ; *LScan; LScan ++)
    {
        if (*LScan == '$')
        {
            LPCSTR  LLeft = strchr(LScan, '(');

            if (LLeft)
            {
                LPCSTR  LRight = strchr(LLeft, ')');

                if (LRight)
                {
                    const CString LVar(LLeft + 1, static_cast<int>(LRight - LLeft - 1));

                    TYCDirectoryVar::const_iterator LIter = LDirectoryVar.find(LVar);

                    if (LIter != LDirectoryVar.end())
                    {
                        LStrings.push_back(CString(LBegin   , static_cast<int>(LScan - LBegin)));
                        LStrings.push_back(LIter->second);

                        LScan  = LRight;
                        LBegin = LRight + 1;
                    }
                }
            }
        }
    }

    LStrings.push_back(CString(LBegin, static_cast<int>(LScan - LBegin)));


    CString LRslt;

    for (TStringDeque::const_iterator   LIter = LStrings.begin();
        LIter != LStrings.end(); LIter ++)
    {
        LRslt.Append(*LIter);
    }

    if (!LRslt.IsEmpty() && PathIsRelative(LRslt))
    {
        char LPath[MAX_PATH];

        GetModuleFileName(NULL, LPath, sizeof(LPath));
        PathRemoveFileSpec(LPath);
        PathAppend(LPath, LRslt);

        LRslt = LPath;
    }


    return LRslt;
}

void    YCRegisterDirectoryVar(LPCSTR AVarName, LPCSTR ADirectory)
{
    TYCDirectoryVar &LDirectoryVar = YCDirectoryVar();

    LDirectoryVar[AVarName] = ADirectory;
}

void    YCShowApplication()
{
    CWnd *LpMainWnd = AfxGetApp()->m_pMainWnd;

    if (LpMainWnd)
    {
        ASSERT_VALID(LpMainWnd);

        // hide the application's windows before closing all the documents
        LpMainWnd->ShowWindow(SW_SHOW);
        LpMainWnd->ShowOwnedPopups(TRUE);

        // put the window at the bottom of zorder, so it isn't activated
        LpMainWnd->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
        LpMainWnd->BringWindowToTop();
    }
}

void    YCHideApplication()
{
    // 隱藏Application
    AfxGetApp()->HideApplication();
}

double  YCMin(const std::deque<double>& AValues)
{
    if (AValues.size() > 0)
    {
        double LRslt = AValues[0];

        for (int I = 1; I < (int)AValues.size(); I ++)
        {
            if (LRslt > AValues[I])
                LRslt = AValues[I];
        }

        return LRslt;
    }

    return 0;
}

double  YCMax(const std::deque<double>& AValues)
{
    if (AValues.size() > 0)
    {
        double LRslt = AValues[0];

        for (int I = 1; I < (int)AValues.size(); I ++)
        {
            if (LRslt < AValues[I])
                LRslt = AValues[I];
        }

        return LRslt;
    }

    return 0;
}

double  YCMin(const std::vector<double>& AValues)
{
    if (AValues.size() > 0)
    {
        double LRslt = AValues[0];

        for (int I = 1; I < (int)AValues.size(); I ++)
        {
            if (LRslt > AValues[I])
                LRslt = AValues[I];
        }

        return LRslt;
    }

    return 0;
}

double  YCMax(const std::vector<double>& AValues)
{
    if (AValues.size() > 0)
    {
        double LRslt = AValues[0];

        for (int I = 1; I < (int)AValues.size(); I ++)
        {
            if (LRslt < AValues[I])
                LRslt = AValues[I];
        }

        return LRslt;
    }

    return 0;
}

void    YCDifferentiation(IN const std::vector<strYCDoublePoint> &AValue, int ALineSpan, OUT std::vector<strYCDoublePoint> *ADiffValue/* = NULL*/)
{
    std::vector<strYCDoublePoint>   LdDatas;

    LdDatas.resize(AValue.size());

    if (AValue.size() >= 7)
    {
        for (int LIdx = ALineSpan / 2; LIdx < (int)AValue.size() - ALineSpan / 2; LIdx ++)
        {
            std::vector<strYCDoublePoint> LPoints;

            for (int J = LIdx - ALineSpan / 2; J <= LIdx + ALineSpan / 2; J ++)
            {
                LPoints.push_back(AValue[J]);
            }

            double LA;

            YCAnalyzeLine(LPoints, 0, (int)LPoints.size() - 1, &LA, NULL);

            LdDatas[LIdx].Y = LA;
            LdDatas[LIdx].X = AValue[LIdx].X;

            TRACE("LdDatas[%d] = %.3f\n", LIdx, LA);
        } // for (size_t LIdx = 2; LIdx < AValue.size() - 2; LIdx ++)

        for (int LIdx = 0; LIdx < ALineSpan / 2; LIdx ++)
        {
            LdDatas[LIdx].Y = LdDatas[ALineSpan / 2].Y;
            LdDatas[LIdx].X = AValue[LIdx].X;
        }

        for (int LIdx = (int)AValue.size() - ALineSpan / 2; LIdx < (int)AValue.size(); LIdx ++)
        {
            LdDatas[LIdx].Y = LdDatas[LdDatas.size() - ALineSpan / 2 - 1].Y;
            LdDatas[LIdx].X = AValue[LIdx].X;
        }

        if (ADiffValue)
            *ADiffValue = LdDatas;
    }
}

void    YCAppendTextToEditControl(CEdit   *AEdit, LPCSTR AMessage)
{
    ASSERT(AEdit);
    ASSERT(AEdit->m_hWnd);

    int LLineIdx = AEdit->LineIndex(AEdit->GetLineCount() - 1);
    int LInsertIdx = LLineIdx + AEdit->LineLength(LLineIdx);
    AEdit->SetSel(LInsertIdx, LInsertIdx);

    CString LMessage(AMessage);

    if (LMessage.Right(2) != "\r\n")
        LMessage.Append("\r\n");

    AEdit->ReplaceSel(LMessage);
}

//=================== MSXML functions
HRESULT YCXMLDOMCreateDocument(bool AIsOpen, IXMLDOMDocument **AXMLDoc, LPCSTR ARootEleName/* = NULL*/, IXMLDOMElement **ARootXMLEle/* = NULL*/, LPCSTR AEncoding/* = NULL*/)
{
    //ASSERT(AXMLDoc);

    HRESULT     LCoRslt = AXMLDoc ? S_OK : E_POINTER;


    //==================== 建立XML文件
    CComPtr<IXMLDOMDocument>
        /**/    LXMLDoc;

    if (SUCCEEDED(LCoRslt))
    {
        LCoRslt = LXMLDoc.CoCreateInstance(__uuidof(DOMDocument30), NULL, CLSCTX_INPROC);

        if (SUCCEEDED(LCoRslt) && !LXMLDoc)
            LCoRslt = E_OUTOFMEMORY;
    }


    if (SUCCEEDED(LCoRslt) && !AIsOpen)
    {
        //==================== 建立XML處理指令並加入文件中
        CComPtr<IXMLDOMProcessingInstruction>
            /**/    LXMLPI;

        CString     LXMLPIData = "version='1.0'";

        if (AEncoding && strlen(AEncoding))
            LXMLPIData.AppendFormat(" encoding='%s'", AEncoding);

        LCoRslt = LXMLDoc->createProcessingInstruction(_bstr_t(L"xml"), _bstr_t(LXMLPIData), &LXMLPI);

        if (SUCCEEDED(LCoRslt))
            LCoRslt = LXMLDoc->appendChild(LXMLPI, NULL);


        //==================== 建立XML根元素並加入文件中
        if (ARootEleName && strlen(ARootEleName))
        {
            CComPtr<IXMLDOMElement>
                /**/    LRootXMLEle;

            if (SUCCEEDED(LCoRslt))
                LCoRslt = LXMLDoc->createElement(_bstr_t(ARootEleName), &LRootXMLEle);

            if (SUCCEEDED(LCoRslt))
                LCoRslt = LXMLDoc->appendChild(LRootXMLEle, NULL);

            if (SUCCEEDED(LCoRslt) && ARootXMLEle)
                LCoRslt = LRootXMLEle.CopyTo(ARootXMLEle);
        }
    }


    if (SUCCEEDED(LCoRslt))
        LCoRslt = LXMLDoc.CopyTo(AXMLDoc);

    return LCoRslt;
}

HRESULT YCXMLDOMDocumentLoad(IXMLDOMDocument *AXMLDoc, LPCSTR AFileName)
{
    //ASSERT(AXMLDoc);


    HRESULT     LCoRslt = AXMLDoc ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        VARIANT_BOOL
            /**/    LIsLoadSucc = VARIANT_FALSE;

        LCoRslt = AXMLDoc->load(_variant_t(AFileName), &LIsLoadSucc);

        if (SUCCEEDED(LCoRslt) && LIsLoadSucc == VARIANT_FALSE)
            LCoRslt = E_FAIL;
    }

    return LCoRslt;
}

HRESULT YCXMLDOMDocumentSave(IXMLDOMDocument *AXMLDoc, LPCSTR AFileName)
{
    //ASSERT(AXMLDoc);

    HRESULT     LCoRslt = AXMLDoc ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = AXMLDoc->save(_variant_t(AFileName));

    return LCoRslt;
}

HRESULT YCXMLDOMGetRootElement(IXMLDOMDocument *AXMLDoc, IXMLDOMElement **ARslt)
{
    //ASSERT(AXMLDoc);


    HRESULT LCoRslt = AXMLDoc ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        CComPtr<IXMLDOMElement>
            /**/    LRootXMLEle;

        LCoRslt = AXMLDoc->get_documentElement(&LRootXMLEle);

        if (SUCCEEDED(LCoRslt) && !LRootXMLEle)
            LCoRslt = E_UNEXPECTED;

        if (SUCCEEDED(LCoRslt) && ARslt)
            LCoRslt = LRootXMLEle.CopyTo(ARslt);
    }

    return LCoRslt;
}

HRESULT YCXMLDOMGetRootElement(IXMLDOMElement  *AXMLEle, IXMLDOMElement **ARslt)
{
    //ASSERT(AXMLEle);

    CComPtr<IXMLDOMDocument>
        /**/    LXMLDoc;

    HRESULT     LCoRslt = YCXMLDOMGetDocument(AXMLEle, &LXMLDoc);

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMGetRootElement(LXMLDoc, ARslt);

    return LCoRslt;
}

HRESULT YCXMLDOMGet1stChildNode(IXMLDOMElement  *AParentXMLEle, IXMLDOMNode **ARslt)
{
    //ASSERT(AParentXMLEle);

    HRESULT     LCoRslt = AParentXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        CComPtr<IXMLDOMNode>
            /**/    L1stChildXMLNod;

        LCoRslt = AParentXMLEle->get_firstChild(&L1stChildXMLNod);

        if (SUCCEEDED(LCoRslt) && !L1stChildXMLNod)
            LCoRslt = E_UNEXPECTED;

        if (SUCCEEDED(LCoRslt) && ARslt)
            LCoRslt = L1stChildXMLNod.CopyTo(ARslt);
    }

    return LCoRslt;
}

HRESULT YCXMLDOMGet1stChildNode(IXMLDOMNode *AParentXMLNod, IXMLDOMNode **ARslt)
{
    //ASSERT(AParentXMLNod);

    HRESULT     LCoRslt = AParentXMLNod ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        CComPtr<IXMLDOMNode>
            /**/    L1stChildXMLNod;

        LCoRslt = AParentXMLNod->get_firstChild(&L1stChildXMLNod);

        if (SUCCEEDED(LCoRslt) && !L1stChildXMLNod)
            LCoRslt = E_UNEXPECTED;

        if (SUCCEEDED(LCoRslt) && ARslt)
            LCoRslt = L1stChildXMLNod.CopyTo(ARslt);
    }

    return LCoRslt;
}

HRESULT YCXMLDOMGetNextSiblingChildNode(IXMLDOMNode  *AXMLNod, IXMLDOMNode **ARslt)
{
    //ASSERT(AXMLNod);

    HRESULT     LCoRslt = AXMLNod ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        CComPtr<IXMLDOMNode>
            /**/    LNextSiblingChildXMLNod;

        LCoRslt = AXMLNod->get_nextSibling(&LNextSiblingChildXMLNod);

        if (SUCCEEDED(LCoRslt) && !LNextSiblingChildXMLNod)
            LCoRslt = E_UNEXPECTED;

        if (SUCCEEDED(LCoRslt) && ARslt)
            LCoRslt = LNextSiblingChildXMLNod.CopyTo(ARslt);
    }

    return LCoRslt;
}

HRESULT YCXMLDOMGetDocument(IXMLDOMElement  *AXMLEle, IXMLDOMDocument **ARslt)
{
    //ASSERT(AXMLEle);

    HRESULT     LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        CComPtr<IXMLDOMDocument>
            /**/    LXMLDoc;

        LCoRslt = AXMLEle->get_ownerDocument(&LXMLDoc);

        if (SUCCEEDED(LCoRslt) && !LXMLDoc)
            LCoRslt = E_UNEXPECTED;

        if (SUCCEEDED(LCoRslt) && ARslt)
            LCoRslt = LXMLDoc.CopyTo(ARslt);
    }

    return LCoRslt;
}

HRESULT YCXMLDOMCreateElement(IXMLDOMElement  *AXMLEle, LPCSTR AEleName, IXMLDOMElement **ARslt)
{
    //ASSERT(AXMLEle);
    
    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    CComPtr<IXMLDOMDocument>
        /**/    LXMLDoc;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMGetDocument(AXMLEle, &LXMLDoc);

    CComPtr<IXMLDOMElement>
        /**/    LXMLEle;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = LXMLDoc->createElement(_bstr_t(AEleName), ARslt);

    return LCoRslt;
}

HRESULT YCXMLDOMCreateAppendElement(IXMLDOMElement  *AParentXMLEle, LPCSTR AEleName, IXMLDOMElement **ARslt)
{
    //ASSERT(AParentXMLEle);
    
    HRESULT LCoRslt = AParentXMLEle ? S_OK : E_INVALIDARG;

    CComPtr<IXMLDOMElement>
        /**/    LChildXMLEle;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMCreateElement(AParentXMLEle, AEleName, &LChildXMLEle);

    if (SUCCEEDED(LCoRslt))
        LCoRslt = AParentXMLEle->appendChild(LChildXMLEle, NULL);

    if (SUCCEEDED(LCoRslt) && ARslt)
        LCoRslt = LChildXMLEle.CopyTo(ARslt);

    return LCoRslt;
}

HRESULT YCXMLDOMSelectSingleNode(IXMLDOMElement  *AParentXMLEle, LPCSTR AEleName, IXMLDOMNode **ARslt)
{
    //ASSERT(AParentXMLEle);
    
    HRESULT LCoRslt = AParentXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = AParentXMLEle->selectSingleNode(_bstr_t(AEleName), ARslt);

    if (SUCCEEDED(LCoRslt) && ARslt && !*ARslt)
        LCoRslt = E_UNEXPECTED;

    return LCoRslt;
}

HRESULT YCLoadObjectFromXMLFile(LPCSTR AFileName, LPCSTR ARootEleName, CObject **ARslt)
{
    const CYCCoInitialize
        /**/    LCoInitialize;

    HRESULT     LCoRslt = LCoInitialize.m_CoInitializeResult;


    //==================== 建立XML文件
    CComPtr<IXMLDOMDocument>
        /**/    LXMLDoc;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMCreateDocument(true, &LXMLDoc);


    //==================== 載入檔案
    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMDocumentLoad(LXMLDoc, AFileName);


    //==================== 取得根元素
    CComPtr<IXMLDOMElement>
        /**/    LRootXMLEle;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMGetRootElement(LXMLDoc, &LRootXMLEle);


    //==================== 載入物件
    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCLoadObjectFromXML(LRootXMLEle, ARootEleName, ARslt);


    return LCoRslt;
}

HRESULT YCSaveObjectToXMLFile2(LPCSTR AFileName, CObject *AObject, LPCSTR ARootEleName)
{
    const CYCCoInitialize
        /**/    LCoInitialize;

    HRESULT     LCoRslt = LCoInitialize.m_CoInitializeResult;


    //==================== 建立XML文件
    CComPtr<IXMLDOMDocument>
        /**/    LXMLDoc;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMCreateDocument(false, &LXMLDoc, ARootEleName);


    //==================== 取出XML文件的根元素
    CComPtr<IXMLDOMElement>
        /**/    LRootXMLEle;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMGetRootElement(LXMLDoc, &LRootXMLEle);


    //==================== 把物件寫入XML根元素中
    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCSaveObjectToXML2(LRootXMLEle, AObject);


    //==================== 儲存XML文件
    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMDocumentSave(LXMLDoc, AFileName);


    return LCoRslt;
}

HRESULT YCLoadObjectFromXML(IXMLDOMElement *AXMLEle, LPCSTR AEleName, CObject **ARslt)
{
    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt) && AEleName && strlen(AEleName))
    {
        _bstr_t    LEleName;

        LCoRslt = AXMLEle->get_tagName(LEleName.GetAddress());

        if (SUCCEEDED(LCoRslt) && strcmp(LEleName, AEleName))
            LCoRslt = E_UNEXPECTED;
    }


    //==================== 取得物件類別名稱
    CString LClassName;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMAttributeReadString(AXMLEle, "ClassName", LClassName, "");


    //==================== 建立物件
    if (SUCCEEDED(LCoRslt) && !LClassName.IsEmpty())
    {
        CObject* const
            /**/    LRslt = CRuntimeClass::CreateObject(LClassName);

        if (LRslt)
        {
            *ARslt = LRslt;


            //==================== 讀取物件資料
            IYCXMLPersist* const
                /**/    LXMLPersist = dynamic_cast<IYCXMLPersist *>(LRslt);

            if (LXMLPersist)
                LXMLPersist->LoadFromXML(AXMLEle);
        }
    }


    return LCoRslt;
}

HRESULT YCSaveObjectToXML2(IXMLDOMElement *AXMLEle, CObject *AObject)
{
    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;


    //==================== 寫入物件類別名稱
    if (SUCCEEDED(LCoRslt) && AObject && AObject->GetRuntimeClass())
        LCoRslt = YCXMLDOMAttributeWriteNameString(AXMLEle, "ClassName", AObject->GetRuntimeClass()->m_lpszClassName);


    //==================== 儲存物件資料
    if (SUCCEEDED(LCoRslt))
    {
        IYCXMLPersist* const
            /**/    LXMLPersist = dynamic_cast<IYCXMLPersist *>(AObject);

        if (LXMLPersist)
            LXMLPersist->SaveToXML(AXMLEle); 
    }


    return LCoRslt;
}

HRESULT YCSaveObjectToXMLChild2(IXMLDOMElement *AParentXMLEle, LPCSTR AChildEleName, CObject *AObject, IXMLDOMElement **AChildXMLEle/* = NULL*/)
{
    //ASSERT(AParentXMLEle);

    HRESULT     LCoRslt = AParentXMLEle ? S_OK : E_INVALIDARG;


    //==================== 取出element的document
    CComPtr<IXMLDOMDocument>
        /**/    LXMLDoc;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMGetDocument(AParentXMLEle, &LXMLDoc);


    //==================== 建立子element
    CComPtr<IXMLDOMElement>
        /**/    LChildXMLEle;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = LXMLDoc->createElement(_bstr_t(AChildEleName), &LChildXMLEle);


    //==================== 把子element加入document中
    if (SUCCEEDED(LCoRslt))
        LCoRslt = AParentXMLEle->appendChild(LChildXMLEle, NULL);


    //==================== 把物件寫入子element
    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCSaveObjectToXML2(LChildXMLEle, AObject);


    if (SUCCEEDED(LCoRslt) && AChildXMLEle)
        LCoRslt = LChildXMLEle.CopyTo(AChildXMLEle);


    return LCoRslt;
}

HRESULT YCDumpObjectInfoToXMLFile2(LPCSTR AFileName, CObject *AObject, LPCSTR ARootEleName)
{
    const CYCCoInitialize
        /**/    LCoInitialize;

    HRESULT     LCoRslt = LCoInitialize.m_CoInitializeResult;


    //==================== 建立XML文件
    CComPtr<IXMLDOMDocument>
        /**/    LXMLDoc;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMCreateDocument(false, &LXMLDoc, ARootEleName);


    //==================== 取回XML根元素
    CComPtr<IXMLDOMElement>
        /**/    LRootXMLEle;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMGetRootElement(LXMLDoc, &LRootXMLEle);


    //==================== 把物件寫入XML Root element中
    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCDumpObjectInfoToXML2(LRootXMLEle, AObject);


    //==================== 儲存文件
    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMDocumentSave(LXMLDoc, AFileName);

    return LCoRslt;
}

HRESULT YCDumpObjectInfoToXML2(IXMLDOMElement *AXMLEle, CObject *AObject)
{
    // ASSERT(AXMLEle);


    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    //==================== 寫入物件型態
    if (SUCCEEDED(LCoRslt) && AObject && AObject->GetRuntimeClass())
        LCoRslt = YCXMLDOMAttributeWriteNameString(AXMLEle, "Type", AObject->GetRuntimeClass()->m_lpszClassName + 1);


    //==================== 寫入物件資料
    if (SUCCEEDED(LCoRslt))
    {
        IYCXMLDumpInfo* const
            /**/    LXMLDumpInfo = dynamic_cast<IYCXMLDumpInfo *>(AObject);

        if (LXMLDumpInfo)
            LXMLDumpInfo->DumpInfoToXML(AXMLEle); 
    }

    return LCoRslt;
}

HRESULT YCDumpObjectInfoToXMLChild2(IXMLDOMElement *AParentXMLEle, LPCSTR AChildEleName, CObject *AObject, IXMLDOMElement **AChildXMLEle/* = NULL*/)
{
    //ASSERT(AParentXMLEle);


    HRESULT     LCoRslt = AParentXMLEle ? S_OK : E_INVALIDARG;


    //==================== 取出element的document
    CComPtr<IXMLDOMDocument>
        /**/    LXMLDoc;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMGetDocument(AParentXMLEle, &LXMLDoc);


    //==================== 建立子element
    CComPtr<IXMLDOMElement>
        /**/    LChildXMLEle;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = LXMLDoc->createElement(_bstr_t(AChildEleName), &LChildXMLEle);


    //==================== 把子element加入父元素中
    if (SUCCEEDED(LCoRslt))
        LCoRslt = AParentXMLEle->appendChild(LChildXMLEle, NULL);


    //==================== 把物件寫入子element
    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCDumpObjectInfoToXML2(LChildXMLEle, AObject);


    if (SUCCEEDED(LCoRslt) && AChildXMLEle)
        LCoRslt = LChildXMLEle.CopyTo(AChildXMLEle);

    return LCoRslt;
}

HRESULT YCXMLDOMAttributeReadString(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, OUT CString &ARslt, LPCSTR ADefault)
{
    ASSERT(AXMLEle);

    ARslt = ADefault;

    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    _variant_t   LVar;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = AXMLEle->getAttribute(_bstr_t(AAttName), &LVar);

    if (SUCCEEDED(LCoRslt) && (LCoRslt == S_OK) && LVar.vt != VT_NULL)
        ARslt = static_cast<LPCSTR>(_bstr_t(LVar));


    return LCoRslt;
}


HRESULT YCXMLDOMAttributeReadGUID(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, OUT GUID &ARslt, const GUID &ADefault)
{
    ASSERT(AXMLEle);

    ARslt = ADefault;

    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        _variant_t   LVar;

        LCoRslt = AXMLEle->getAttribute(_bstr_t(AAttName), &LVar);

        if (SUCCEEDED(LCoRslt) && (LCoRslt == S_OK) && LVar.vt != VT_NULL)
            ARslt = YCStrToGUID(static_cast<LPCSTR>(_bstr_t(LVar)));
    }

    return LCoRslt;
}

HRESULT YCXMLDOMAttributeWriteGUID(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, const GUID &AValue)
{
    ASSERT(AXMLEle);

    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = AXMLEle->setAttribute(_bstr_t(AAttName), _variant_t(YCGUIDToStr(AValue)));

    return LCoRslt;
}



HRESULT YCXMLDOMAttributeReadSystemTime(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, OUT SYSTEMTIME &ARslt, const SYSTEMTIME &ADefault)
{
    ASSERT(AXMLEle);

    ARslt = ADefault;

    CString LStr = "0 0";
    HRESULT LCoRslt = YCXMLDOMAttributeReadString(AXMLEle, AAttName, LStr, LStr);

    if (SUCCEEDED(LCoRslt) && (LCoRslt == S_OK))
    {
        FILETIME    LFT = { 0, 0 };

        sscanf_s(LStr, "%u %u", &LFT.dwLowDateTime, &LFT.dwHighDateTime);
        FileTimeToSystemTime(&LFT, &ARslt);
    }

    return LCoRslt;
}

HRESULT YCXMLDOMAttributeWriteSystemTime(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, const SYSTEMTIME &AValue)
{
    ASSERT(AXMLEle);

    CFileTime   LFT;

    SystemTimeToFileTime(&AValue, &LFT);

    CString LStr;

    LStr.Format("%u %u", LFT.dwLowDateTime, LFT.dwHighDateTime);

    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = YCXMLDOMAttributeWrite(AXMLEle, AAttName, LStr);

    return LCoRslt;
}
