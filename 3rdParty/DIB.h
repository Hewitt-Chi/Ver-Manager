// DIB.h

#ifndef __DIB_H__
#define __DIB_H__

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

class CDib
{

public:
    
    CDib();
    ~CDib();

    unsigned char * GetDIB(); // BMP data's headle
    unsigned char * GetDIBRowData();
    BOOL Load( const char * ); // Load BMP file
    BOOL Save( const char * ); // save BMP file
    BOOL Draw( HDC &pDC, int nX = 0, int nY = 0, int nWidth = -1, int nHeight = -1 ); // Draw BMP image
    BOOL SetPalette( CDC * ); // set BMP palette

    bool GetDIBArea(long &Width,long &Height);
private:
    CPalette m_Palette; // BMP palette
    unsigned char *m_pDib, *m_pDibBits; // BMP fubber
    DWORD m_dwDibSize; // Size of data
    BITMAPINFOHEADER *m_pBIH; // Head of BMP
    RGBQUAD *m_pPalette;
    int m_nPaletteEntries;

};

#endif
