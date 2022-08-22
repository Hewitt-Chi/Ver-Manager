// Serial.h
#include <windows.h>

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


#ifndef __SERIAL_H__
#define __SERIAL_H__

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13
//-------------------------------------------------------------//
#define SERIES_PARITY_NONE  0
#define SERIES_PARITY_ODD   1
#define SERIES_PARITY_EVEN  2
#define SERIES_PARITY_MASK  3
#define SERIES_PARITY_SPACE 4
//-------------------------------------------------------------//
#define SERIES_STOPBITS_10  0
#define SERIES_STOPBITS_15  1
#define SERIES_STOPBITS_20  2
//-------------------------------------------------------------//
class CSerial
{

public:
    CSerial();
    ~CSerial();

    // init COM port
    bool Open(int nPort, int nBaud , int nByteSize, int nParity, int nStopBits);

    // close COM port
    bool Close();

    // read a character from COM port
    int ReadSingleChar(char &ch);
    
    // Read string from COM port 
    int ReadData( void *, int );
    
    // Send string to COM port
    int SendData( const char *, int );
    
    // return read buffer number
    int ReadDataWaiting( void );

    // Is open COM port
    bool IsOpened()
    { return m_bOpened; }

    // purge comm
    void PurgeComm(DWORD AFlags = PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

    inline operator HANDLE() const
    { return m_hIDComDev; };

protected:
    // Is set Stop-bit
    bool IsStopBitsOK(int nStopBits);
    
    // Is set parity
    bool IsParityOK(int nParity);
    
    // send character
    bool WriteCommByte( unsigned char );
    
    // Is Set Byte size
    bool IsByteSizeOK(int nByteSize);

    // COM headle
    HANDLE m_hIDComDev;
    
    // Is COM open?
    bool m_bOpened;
    
    OVERLAPPED  m_OverlappedRead;
    OVERLAPPED  m_OverlappedWrite;  

};

#endif
