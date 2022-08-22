// Author:      SFr frydaysoft@gmx.de

#ifndef AFX_COLOR_H__9FC7D36B_FC88_42FD_8DAA_2F70016038BA__INCLUDED_
#define AFX_COLOR_H__9FC7D36B_FC88_42FD_8DAA_2F70016038BA__INCLUDED_

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

    typedef enum 
    {   
        DEF_BACKGROUND=0, DEF_TEXT, DEF_SELBACKGROUND, DEF_SELTEXT, DEF_DESELBACKGROUND,DEF_DESELTEXT,BBLACK,
        BBLUE,GGREEN,CYAN,RRED,    MANGENTA,
        YELLOW,    WWHITE,    DARKBLUE,    DARKGREEN, BLUEGREEN,
        BROWN,PURPUR,OLIV,DARKGRAY,
        
        LIGHTGRAY,LLIGHTBLUE,DARKWHITE,
        MIDDLEGRAY,    DARKRED,LLIGHTRED,    LightPink
        
    }
    ITEM_COLOR;

    typedef struct 
    {
        char        str[50];
        ITEM_COLOR      col;
    } ColorList;

    #define COLLIST_MAX 28

    extern ColorList colList[COLLIST_MAX];

    COLORREF GetColorRef(ITEM_COLOR lParam);

#endif