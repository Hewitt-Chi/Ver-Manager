#include "stdafx.h"

#include "YCUtils.h"
#include "YCObject.h"
#include "YCMemoryBuffer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////
// CYCMemoryBuffer
//
CYCMemoryBuffer::CYCMemoryBuffer()
: m_Buffer(NULL)
, m_BufferSize(0)
, m_BufferCapacity(0)
{
    GrowBuffer(4096);
}

CYCMemoryBuffer::CYCMemoryBuffer(const CYCMemoryBuffer &ASrc)
: m_Buffer(NULL)
, m_BufferSize(0)
{
    operator =(ASrc);
}

CYCMemoryBuffer::~CYCMemoryBuffer()
{
    Clear();
}

LPCVOID CYCMemoryBuffer::Buffer() const
{
    return m_Buffer;
}

int     CYCMemoryBuffer::BufferSize() const
{
    return m_BufferSize;
}

int     CYCMemoryBuffer::WriteFront(LPCVOID  ABuff, int ABuffSize)
{
    if (ABuff && ABuffSize > 0)
    {
        GrowBuffer(m_BufferSize + ABuffSize);

        ASSERT(m_BufferCapacity >= m_BufferSize + ABuffSize);

        memmove_s((char *)m_Buffer + ABuffSize, m_BufferCapacity - m_BufferSize, m_Buffer, m_BufferSize);

        memcpy_s(m_Buffer, ABuffSize, ABuff, ABuffSize);

        m_BufferSize += ABuffSize;

        return ABuffSize;
    }

    return 0;
}

int     CYCMemoryBuffer::WriteBack(LPCVOID  ABuff, int ABuffSize)
{
    if (ABuff && ABuffSize > 0)
    {
        GrowBuffer(m_BufferSize + ABuffSize);

        ASSERT(m_BufferCapacity >= m_BufferSize + ABuffSize);

        memcpy_s((char *)m_Buffer + m_BufferSize, m_BufferCapacity - m_BufferSize, ABuff, ABuffSize);

        m_BufferSize += ABuffSize;

        return ABuffSize;
    }

    return 0;
}

int     CYCMemoryBuffer::ReadFront(OUT LPVOID ABuff, int ABuffSize, bool AIsRemove)
{
    ASSERT(ABuffSize == 0 || ABuff);

    if (ABuff && ABuffSize > 0 && m_BufferSize > 0)
    {
        ABuffSize = min(m_BufferSize, ABuffSize);

        memcpy_s(ABuff, ABuffSize, m_Buffer, ABuffSize);

        if (AIsRemove)
            RemoveFront(ABuffSize);

        return ABuffSize;
    }

    return 0;
}

int     CYCMemoryBuffer::ReadBack(OUT LPVOID ABuff, int ABuffSize, bool AIsRemove)
{
    ASSERT(ABuffSize == 0 || ABuff);

    if (ABuff && ABuffSize > 0 && m_BufferSize > 0)
    {
        ABuffSize = min(m_BufferSize, ABuffSize);

        memcpy_s(ABuff, ABuffSize, (char *)m_Buffer + (m_BufferSize - ABuffSize), ABuffSize);

        if (AIsRemove)
            RemoveBack(ABuffSize);

        return ABuffSize;
    }

    return 0;
}

void    CYCMemoryBuffer::RemoveFront(int ACount)
{
    if (ACount > 0)
    {
        if (ACount < m_BufferSize)
            m_BufferSize -= ACount;
        else
            m_BufferSize = 0;


        if (m_BufferSize > 0)
            memcpy_s(m_Buffer, m_BufferSize, (char *)m_Buffer + ACount, m_BufferSize);
    }
}

void    CYCMemoryBuffer::RemoveBack(int ACount)
{
    if (ACount > 0)
    {
        if (ACount < m_BufferSize)
            m_BufferSize -= ACount;
        else
            m_BufferSize = 0;
    }
}

void    CYCMemoryBuffer::Clear()
{
    m_BufferSize     = 0;
    m_Buffer         = YCrealloc(m_Buffer, m_BufferSize);
    m_BufferCapacity = 0;
}

/**/    CYCMemoryBuffer::operator LPCVOID() const
{
    return m_Buffer;
}

CYCMemoryBuffer&
/**/    CYCMemoryBuffer::operator =(const CYCMemoryBuffer &AValue)
{
    if (this != &AValue)
    {
        GrowBuffer(AValue.m_BufferCapacity);

        m_BufferSize = AValue.m_BufferSize;

        if (m_BufferSize > 0)
            memcpy_s(m_Buffer, m_BufferSize, AValue.m_Buffer, AValue.m_BufferSize);
    }

    return *this;
}

bool    CYCMemoryBuffer::operator ==(const CYCMemoryBuffer &AValue) const
{
    if (&AValue == this)
        return true;


    if (AValue.m_BufferSize == m_BufferSize)
        return memcmp(m_Buffer, AValue.m_Buffer, m_BufferSize) == 0;


    return false;
}

bool    CYCMemoryBuffer::operator !=(const CYCMemoryBuffer &AValue) const
{
    return !(operator ==(AValue));
}

void    CYCMemoryBuffer::GrowBuffer(int ANewCapacity)
{
    ANewCapacity = (ANewCapacity / 4096 + ((ANewCapacity % 4096) ? 1 : 0)) * 4096;

    if (ANewCapacity > m_BufferCapacity)
    {
        m_BufferCapacity = ANewCapacity;
        m_Buffer = YCrealloc(m_Buffer, m_BufferCapacity);
    }
}
//
// CYCMemoryBuffer
////////////////////////////////////////
