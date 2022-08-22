#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

class CYCMessageOnlyWnd : public CWnd
{
    DECLARE_DYNAMIC(CYCMessageOnlyWnd)

public:
    CYCMessageOnlyWnd(void);
    virtual ~CYCMessageOnlyWnd(void);

    BOOL Create();

    // for child windows, views, panes etc
    virtual BOOL Create(
        LPCTSTR         lpszClassName,
        LPCTSTR         lpszWindowName,
        DWORD           dwStyle,
        const RECT      &rect,
        CWnd            *pParentWnd,
        UINT            nID,
        CCreateContext  *pContext = NULL);

    virtual BOOL CreateEx(
        DWORD           dwExStyle,
        LPCTSTR         lpszClassName,
        LPCTSTR         lpszWindowName,
        DWORD           dwStyle,
        const RECT      &rect,
        CWnd*           pParentWnd,
        UINT            nID,
        LPVOID          lpParam = NULL);
};
