#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif



//////////////////////////////////////////////////////////////////////////////
// CYCMemoryBuffer
//
class CYCMemoryBuffer
{
public:
    CYCMemoryBuffer();
    CYCMemoryBuffer(const CYCMemoryBuffer &ASrc);
    virtual ~CYCMemoryBuffer();


    LPCVOID Buffer() const;
    int     BufferSize() const;

    int     WriteFront(LPCVOID  ABuff, int ABuffSize);
    int     WriteBack(LPCVOID  ABuff, int ABuffSize);
    int     ReadFront(OUT LPVOID ABuff, int ABuffSize, bool AIsRemove);
    int     ReadBack(OUT LPVOID ABuff, int ABuffSize, bool AIsRemove);
    void    RemoveFront(int ACount);
    void    RemoveBack(int ACount);
    void    Clear();

    /**/    operator LPCVOID() const;

    CYCMemoryBuffer&
            operator =(const CYCMemoryBuffer &AValue);
    bool    operator ==(const CYCMemoryBuffer &AValue) const;
    bool    operator !=(const CYCMemoryBuffer &AValue) const;

private:
    LPVOID  m_Buffer;
    int     m_BufferSize;
    int     m_BufferCapacity;


    void    GrowBuffer(int ANewCapacity);
};
//
// CYCMemoryBuffer
//////////////////////////////////////////////////////////////////////////////
