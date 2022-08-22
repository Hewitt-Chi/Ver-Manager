#include "stdafx.h"

#include "YCUtils.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CYCGUID::CYCGUID()
{
    NewGUID();
}

CYCGUID::CYCGUID(const GUID &AGUID)
{
    operator=(AGUID);
}

bool CYCGUID::operator>(const GUID &AValue) const
{
    for (int I = 7; I > -1; I --)
    {
        if (Data4[I] - AValue.Data4[I])
            return Data4[I] > AValue.Data4[I];
    }

    if (Data3 - AValue.Data3)
        return Data3 > AValue.Data3;

    if (Data2 - AValue.Data2)
        return Data2 > AValue.Data2;

    if (Data1 - AValue.Data1)
        return Data1 > AValue.Data1;

    return false;
}

bool CYCGUID::operator<(const GUID &AValue) const
{
    return !operator>=(AValue);
}

bool CYCGUID::operator==(const GUID &AValue) const
{
    return !!InlineIsEqualGUID(*this, AValue);
}

bool CYCGUID::operator>=(const GUID &AValue) const
{
    return operator>(AValue) || operator==(AValue);
}

bool CYCGUID::operator<=(const GUID &AValue) const
{
    return operator<(AValue) || operator==(AValue);
}

bool CYCGUID::operator!=(const GUID &AValue) const
{
    return !operator==(AValue);
}

CYCGUID& CYCGUID::operator=(const GUID &AValue)
{
    Data1    = AValue.Data1;
    Data2    = AValue.Data2;
    Data3    = AValue.Data3;
    Data4[0] = AValue.Data4[0];
    Data4[1] = AValue.Data4[1];
    Data4[2] = AValue.Data4[2];
    Data4[3] = AValue.Data4[3];
    Data4[4] = AValue.Data4[4];
    Data4[5] = AValue.Data4[5];
    Data4[6] = AValue.Data4[6];
    Data4[7] = AValue.Data4[7];

    return *this;
}

void CYCGUID::NewGUID()
{
    CoCreateGuid((GUID *)this);
}



////////////////////////////////////////////////////////////////////////////////////////////
// GUID 相關函式
//
//規範
//	
//
//input 參數的格式
//
//N
//	
//
//32 位數字：
//
//00000000000000000000000000000000
//
//D
//	
//
//以連字號分隔的 32 位數字：
//
//00000000-0000-0000-0000-000000000000
//
//B
//	
//
//以連字號分隔並以括號括起來的 32 位數字：
//
//{00000000-0000-0000-0000-000000000000}
//
//P
//	
//
//以連字號分隔並以括號括起來的 32 位數字：
//
//(00000000-0000-0000-0000-000000000000)
//
//X
//	
//
//括號中包含四個十六進位值，其中第四個值是八個十六進位值的子集，同樣包含在括號中：
//
//{0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}

CString     YCGUIDToStr(const GUID &AGUID)
{
    CString LRslt;

    LRslt.Format(
        "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
        AGUID.Data1,
        AGUID.Data2,
        AGUID.Data3,
        AGUID.Data4[0], 
        AGUID.Data4[1],
        AGUID.Data4[2],
        AGUID.Data4[3],
        AGUID.Data4[4],
        AGUID.Data4[5],
        AGUID.Data4[6],
        AGUID.Data4[7]);

    return LRslt;
}

bool    YCStrToGUID(LPCSTR AGUIDStr, OUT GUID &AResultValue)
{
    CString LStr;
    GUID    LRslt;

    for (int I = 0; AGUIDStr[I] != 0; I ++)
    {
        switch (AGUIDStr[I])
        {
        case ' ' :
        case '(' :
        case ')' :
        case '{' :
        case '}' :
        case '-' :
        case ',' :
            break;

        case '0' :
            if (AGUIDStr[I + 1] == 'x' || AGUIDStr[I + 1] == 'X')
                I ++;
            else
                LStr.AppendChar(AGUIDStr[I]);

            break;

        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
        case 'a' :
        case 'b' :
        case 'c' :
        case 'd' :
        case 'e' :
        case 'f' :
        case 'A' :
        case 'B' :
        case 'C' :
        case 'D' :
        case 'E' :
        case 'F' :
            LStr.AppendChar(AGUIDStr[I]);
            break;

        default :
            ASSERT(FALSE);

            return false;
        }
    }

    //ASSERT(LStr.GetLength() == 32);

    if (LStr.GetLength() == 32)
    {
        CString LField;

        LField = "0x" + LStr.Mid(0, 8);
        LRslt.Data1 = strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(8, 4);
        LRslt.Data2 = (unsigned short)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(12, 4);
        LRslt.Data3 = (unsigned short)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(16, 2);
        LRslt.Data4[0] = (unsigned char)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(18, 2);
        LRslt.Data4[1] = (unsigned char)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(20, 2);
        LRslt.Data4[2] = (unsigned char)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(22, 2);
        LRslt.Data4[3] = (unsigned char)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(24, 2);
        LRslt.Data4[4] = (unsigned char)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(26, 2);
        LRslt.Data4[5] = (unsigned char)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(28, 2);
        LRslt.Data4[6] = (unsigned char)strtoul(LField, NULL, 16);

        LField = "0x" + LStr.Mid(30, 2);
        LRslt.Data4[7] = (unsigned char)strtoul(LField, NULL, 16);

        AResultValue = LRslt;

        return true;
    }

    AResultValue = GUID_NULL;

    return false;
}

GUID    YCStrToGUID(LPCSTR AGUIDStr)
{
    GUID LRslt = GUID_NULL;

    YCStrToGUID(AGUIDStr, LRslt);

    return LRslt;
}
//
// GUID 相關函式
////////////////////////////////////////////////////////////////////////////////////////////
