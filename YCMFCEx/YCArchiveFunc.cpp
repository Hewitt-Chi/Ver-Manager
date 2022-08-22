#include "stdafx.h"

#include "YCUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////////////////////////////////////////////////////////
// Archive Functions
//
CArchive& operator||(CArchive &AArchive, BYTE& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, WORD& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, DWORD& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, LONG& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, float& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, double& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, LONGLONG& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, ULONGLONG& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, int& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, short& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& operator||(CArchive &AArchive, char& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

#ifdef _NATIVE_WCHAR_T_DEFINED
CArchive& operator||(CArchive &AArchive, wchar_t& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

#endif
CArchive& operator||(CArchive &AArchive, bool& AValue)
{
    if (AArchive.IsLoading())
        return (AArchive >> AValue);
    else return (AArchive << AValue);
}

CArchive& YCArchiveRaw(CArchive &AArchive, void *AValue, UINT AValueSize)
{
    if (AArchive.IsLoading())
    {
        AArchive.EnsureRead(AValue, AValueSize);
    }
    else
    {
        AArchive.Write(AValue, AValueSize);
    }

    return AArchive;
}

CArchive& operator||(CArchive &AArchive, strYCCommonDataHeader &AValue)
{
    YCArchiveRaw(AArchive, &AValue, sizeof(AValue));

    return AArchive;
}

CArchive& operator||(CArchive &AArchive, strYCDoublePoint &AValue)
{
    YCArchiveRaw(AArchive, &AValue, sizeof(AValue));

    return AArchive;
}

CArchive& operator||(CArchive &AArchive, CString& AValue)
{
    if (AArchive.IsLoading())
        AArchive >> AValue;
    else AArchive << AValue;

    return AArchive;
}

CArchive& operator||(CArchive &AArchive, GUID& AValue)
{
    YCArchiveRaw(AArchive, &AValue, sizeof(AValue));

    return AArchive;
}
//
// Archive Functions
////////////////////////////////////////////////////////////////////////////////////////////
