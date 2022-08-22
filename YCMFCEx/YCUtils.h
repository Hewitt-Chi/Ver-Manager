#pragma once

#include <comdef.h>
#include <msxml2.h>

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

#define YCWidthToBmpWidth(X)                            (((X) / 4 + ((X) % 4 == 0 ? 0 : 1)) * 4)
#define PI                                              3.1415926535
#define YCRadToDeg(X)                                   (360.0 * (X) / (2 * PI))
#define YCDegToRad(X)                                   (2 * PI * (X) / 360.0)
#define YCRoundI(X)                                     YCRound(X)
#define YCRoundL(X)                                     ((long)YCRound(X))
#define YCHypotenuseLength(X, Y)                        (pow((pow((X), 2.0) + pow((Y), 2.0)), 0.5))
#define YCPressureToWeightN(__Pressure, R)              (__Pressure * pow(R * 2.54, 2) * 3.14)
#define YCWeightNToPressure(__Weight, R)                (__Weight / (pow(R * 2.54, 2) * 3.14))
#define YCBoolText(X)                                   ((X) ? "true" : "false")


#define __LINETEXT3__(X)                                #X
#define __LINETEXT2__(X)                                __LINETEXT3__(X)
#define __LINETEXT__                                    "Line : "__LINETEXT2__(__LINE__)
#define __OUTPUT_LOCATE__                               __FILE__ "(" __LINETEXT2__(__LINE__) ")"


// S-->Set, SS-->SubSet
// S是否包含SS
#define IsIncluded(S, SS)                               (((S) & (SS)) == (SS))

// S1與S2是否有交集
#define IsIntersected(S1, S2)                           (((S1) & (S2)) != 0)

// S1與S2是否互斥
#define IsExcluded(S1, S2)                              (((S1) & (S2)) == 0)

// 把SS放入S
#define Include(S, SS)                                  S |= (SS)

// 把SS自S中移除
#define Exclude(S, SS)                                  S &= ~(SS)

//
#define BitSet(X, __Idx)                                (X |= (0x01 << __Idx))

//
#define BitReset(X, __Idx)                              (X &= ~(0x01 << __Idx))

//
#define IsBitSet(X, __Idx)                              (((X >> __Idx) & 1) != 0)

//
#define IsBitReset(X, __Idx)                            (((X >> __Idx) & 1) == 0)


//
#define YCShowDlgItem2(__Dialog, __WndId, __IsShow)         __Dialog->GetDlgItem(__WndId)->ShowWindow(__IsShow ? SW_SHOW : SW_HIDE)
#define YCShowThisDlgItem2(__WndId, __IsShow)               YCShowDlgItem2(this, __WndId, __IsShow)

#define YCShowDlgItem(__Dialog, __WndId)                    __Dialog->GetDlgItem(__WndId)->ShowWindow(SW_SHOW)
#define YCShowThisDlgItem(__WndId)                          YCShowDlgItem(this, __WndId)

#define YCHideDlgItem(__Dialog, __WndId)                    __Dialog->GetDlgItem(__WndId)->ShowWindow(SW_HIDE)
#define YCHideThisDlgItem(__WndId)                          YCHideDlgItem(this, __WndId)

#define YCEnableDlgItem2(__Dialog, __WndId, __IsEnabled)    __Dialog->GetDlgItem(__WndId)->EnableWindow(__IsEnabled)
#define YCEnableThisDlgItem2(__WndId, __IsEnabled)          YCEnableDlgItem2(this, __WndId, __IsEnabled)

#define YCEnableDlgItem(__Dialog, __WndId)                  YCEnableDlgItem2(__Dialog, __WndId, TRUE)
#define YCEnableThisDlgItem(__WndId)                        YCEnableDlgItem(this, __WndId)

#define YCDisableDlgItem(__Dialog, __WndId)                 YCEnableDlgItem2(__Dialog, __WndId, FALSE)
#define YCDisableThisDlgItem(__WndId)                       YCDisableDlgItem(this, __WndId)

#define YCIsDlgItemEnabled(__Dialog, __WndId)               __Dialog->GetDlgItem(__WndId)->IsWindowEnabled()
#define YCIsThisDlgItemEnabled(__WndId)                     YCIsDlgItemEnabled(this, __WndId)

#define YCIsDlgItemEnabled(__Dialog, __WndId)               __Dialog->GetDlgItem(__WndId)->IsWindowEnabled()
#define YCIsThisDlgItemEnabled(__WndId)                     YCIsDlgItemEnabled(this, __WndId)

#define YCIsDlgEditModified(__Dialog, __WndId)              __Dialog->GetDlgItem(__WndId)->IsModified()
#define YCIsThisDlgEditModified(__WndId)                    YCIsDlgItemEnabled(this, __WndId)

#define YCboolToBOOL(X)                                     ((X) ? TRUE : FALSE)

#define YCFontSizeToLogFontHeight(__Size, __dc)             (- __Size * GetDeviceCaps(__dc, LOGPIXELSY) / 72)

#define  OVERRIDE_CObject_Serialize()                       virtual void Serialize(CArchive &AArchive)
#define IMPLEMENT_CObject_Serialize(AClass)                 void AClass::Serialize(CArchive &AArchive)



enum enmYCLayout
{
    loLeftTop,
    loTop,
    loRightTop,
    loLeft,
    loCenter,
    loRight,
    loLeftBottom,
    loBottom,
    loRightBottom
};



// See "Color Table"
enum enmYCColor
{
    clAliceBlue                   = 0xFFF8F0,
    clAntiqueWhite                = 0xD7EBFA,
    clAqua                        = 0xFFFF00,
    clAquaMarine                  = 0xD4FF7F,
    clAzure                       = 0xFFFFF0,
    clBeige                       = 0xDCF5F5,
    clBisque                      = 0xC4E4FF,
    clBlack                       = 0x000000,
    clBlanchedAlmond              = 0xCDEBFF,
    clBlue                        = 0xFF0000,
    clBlueViolet                  = 0xE22B8A,
    clBrown                       = 0x2A2AA5,
    clBurlyWood                   = 0x87B8DE,
    clCadetBlue                   = 0xA09E5F,
    clChartreuse                  = 0x00FF7F,
    clChocolate                   = 0x1E69D2,
    clCoral                       = 0x507FFF,
    clCornflowerBlue              = 0xED9564,
    clCornsilk                    = 0xDCF8FF,
    clCrimson                     = 0x3C14DC,
    // clCyan                        = 0xFFFF00,
    clDarkBlue                    = 0x8B0000,
    clDarkCyan                    = 0x8B8B00,
    clDarkGoldenRod               = 0x0B86B8,
    clDarkGray                    = 0xA9A9A9,
    clDarkGreen                   = 0x006400,
    clDarkKhaki                   = 0x6BB7BD,
    clDarkMagenta                 = 0x8B008B,
    clDarkOliveGreen              = 0x2F6B55,
    clDarkOrange                  = 0x008CFF,
    clDarkOrchid                  = 0xCC3299,
    clDarkRed                     = 0x00008B,
    clDarkSalmon                  = 0x7A96E9,
    clDarkSeaGreen                = 0x8BBC8F,
    clDarkSlateBlue               = 0x8B3D48,
    clDarkSlateGray               = 0x4F4F2F,
    clDarkTurquoise               = 0xD1CE00,
    clDarkViolet                  = 0xD30094,
    clDeepPink                    = 0x9314FF,
    clDeepSkyBlue                 = 0xFFBF00,
    clDimGray                     = 0x696969,
    clDodgerBlue                  = 0xFF901E,
    clFireBrick                   = 0x2222B2,
    clFloralWhite                 = 0xF0FAFF,
    clForestGreen                 = 0x228B22,
    clFuchsia                     = 0xFF00FF,
    clGainsboro                   = 0xDCDCDC,
    clGhostWhite                  = 0xFFF8F8,
    clGold                        = 0x00D7FF,
    clGoldenRod                   = 0x20A5DA,
    clGray                        = 0x808080,
    clGreen                       = 0x008000,
    clGreenYellow                 = 0x2FFFAD,
    clHoneyDew                    = 0xF0FFF0,
    clHotPink                     = 0xB469FF,
    clIndianRed                   = 0x5C5CCD,
    clIndigo                      = 0x82004B,
    clIvory                       = 0xF0FFFF,
    clKhaki                       = 0x8CE6F0,
    clLavender                    = 0xFAE6E6,
    clLavenderBlush               = 0xF5F0FF,
    clLawnGreen                   = 0x00FC7C,
    clLemonChiffon                = 0xCDFAFF,
    clLightBlue                   = 0xE6D8AD,
    clLightCoral                  = 0x8080F0,
    clLightCyan                   = 0xFFFFE0,
    clLightGoldenRodYellow        = 0xD2FAFA,
    clLightGreen                  = 0x90EE90,
    clLightGrey                   = 0xD3D3D3,
    clLightPink                   = 0xC1B6FF,
    clLightSalmon                 = 0x7AA0FF,
    clLightSeaGreen               = 0xAAB220,
    clLightSkyBlue                = 0xFACE87,
    clLightSlateGray              = 0x998877,
    clLightSteelBlue              = 0xDEC4B0,
    clLightYellow                 = 0xE0FFFF,
    clLime                        = 0x00FF00,
    clLimeGreen                   = 0x32CD32,
    clLinen                       = 0xE6F0FA,
    //clMagenta                     = 0xFF00FF,
    clMaroon                      = 0x000080,
    clMediumAquaMarine            = 0xAACD66,
    clMediumBlue                  = 0xCD0000,
    clMediumOrchid                = 0xD355BA,
    clMediumPurple                = 0xDB7093,
    clMediumSeaGreen              = 0x71B33C,
    clMediumSlateBlue             = 0xEE687B,
    clMediumSpringGreen           = 0x9AFA00,
    clMediumTurquoise             = 0xCCD148,
    clMediumVioletRed             = 0x8515C7,
    clMidnightBlue                = 0x701919,
    clMintCream                   = 0xFAFFF5,
    clMistyRose                   = 0xE1E4FF,
    clMoccasin                    = 0xB5E4FF,
    clNavajoWhite                 = 0xADDEFF,
    clNavy                        = 0x800000,
    clOldLace                     = 0xE6F5FD,
    clOlive                       = 0x008080,
    clOliveDrab                   = 0x238E6B,
    clOrange                      = 0x00A5FF,
    clOrangeRed                   = 0x0045FF,
    clOrchid                      = 0xD670DA,
    clPaleGoldenRod               = 0xAAE8EE,
    clPaleGreen                   = 0x98FB98,
    clPaleTurquoise               = 0xEEEEAF,
    clPaleVioletRed               = 0x9370DB,
    clPapayaWhip                  = 0xD5EFFF,
    clPeachPuff                   = 0xB9DAFF,
    clPeru                        = 0x3F85CD,
    clPink                        = 0xCBC0FF,
    clPlum                        = 0xDDA0DD,
    clPowderBlue                  = 0xE6E0B0,
    clPurple                      = 0x800080,
    clRed                         = 0x0000FF,
    clRosyBrown                   = 0x8F8FBC,
    clRoyalBlue                   = 0xE16941,
    clSaddleBrown                 = 0x1213458B,
    clSalmon                      = 0x7280FA,
    clSandyBrown                  = 0x60A4F4,
    clSeaGreen                    = 0x578B2E,
    clSeaShell                    = 0xEEF5FF,
    clSienna                      = 0x2D52A0,
    clSilver                      = 0xC0C0C0,
    clSkyBlue                     = 0xEBCE87,
    clSlateBlue                   = 0xCD5A6A,
    clSlateGray                   = 0x908070,
    clSnow                        = 0xFAFAFF,
    clSpringGreen                 = 0x7FFF00,
    clSteelBlue                   = 0xB48246,
    clTan                         = 0x8CB4D2,
    clTeal                        = 0x808000,
    clThistle                     = 0xD8BFD8,
    clTomato                      = 0x4763FF,
    clTurquoise                   = 0xD0E040,
    clViolet                      = 0xEE82EE,
    clWheat                       = 0xB3DEF5,
    clWhite                       = 0xFFFFFF,
    clWhiteSmoke                  = 0xF5F5F5,
    clYellow                      = 0x00FFFF,
    clYellowGreen                 = 0x32CD9A,
	clDarkGray2					  = 0X202020,
};


extern CString  YCColorToStr(COLORREF   AColor);
extern COLORREF YCStrToColor(LPCSTR     AColorText);


#pragma pack(1)

struct strYCCommonDataHeader
{
    char            IDText[128];
    int             Id;

    union
    {
        DWORD       Version;

        struct
        {
            WORD    MajorVer;
            WORD    MinorVer;
        };
    };
};


class CYCCommonDataHeader : public strYCCommonDataHeader
{
public:
    inline CYCCommonDataHeader()
    {
        ZeroMemory(IDText, sizeof(IDText));
        Id      = 0;
        Version = 0;
    }

    inline CYCCommonDataHeader(LPCSTR AIDText, int AId, DWORD AVersion)
    {
        ASSERT(AIDText && strlen(AIDText) > 0);

        if (AIDText && strlen(AIDText) > 0)
        {
            strcpy_s(IDText, sizeof(IDText), AIDText);
            Id      = AId;
            Version = AVersion;
        }
    }

    inline CYCCommonDataHeader(LPCSTR AIDText, int AId, WORD AMajorVer, WORD AMinorVer)
    {
        ASSERT(AIDText && strlen(AIDText) > 0);

        if (AIDText && strlen(AIDText) > 0)
        {
            strcpy_s(IDText, sizeof(IDText), AIDText);
            Id       = AId;
            MajorVer = AMajorVer;
            MinorVer = AMinorVer;
        }
    }

    inline CYCCommonDataHeader(const strYCCommonDataHeader &AValue)
    {
        operator=(AValue);
    }

    virtual ~CYCCommonDataHeader()
    {
    }

    inline CYCCommonDataHeader& operator =(const strYCCommonDataHeader &AValue)
    {
        memcpy_s(IDText, sizeof(IDText), AValue.IDText, sizeof(AValue.IDText));
        Id      = AValue.Id;
        Version = AValue.Version;

        return *this;
    }

    inline bool operator ==(const strYCCommonDataHeader &AValue)
    {
        return
            Id == AValue.Id &&
            Version == AValue.Version &&
            strcmp(IDText, AValue.IDText) == 0;
    }

    inline bool operator !=(const strYCCommonDataHeader &AValue)
    {
        return !operator ==(AValue);
    }

};

#pragma pack()



#define strCommonFileHeader                             strYCCommonDataHeader
#define CYCCommonFileHeader                             CYCCommonDataHeader


//============================ Line
struct strYCLine
{
    CPoint  Point1;
    CPoint  Point2;
};

class CYCLine : public strYCLine
{
public:
    CYCLine()
    { Point1.SetPoint(0, 0); Point2.SetPoint(0, 0); }

    CYCLine(const CPoint &APoint1, const CPoint &APoint2)
    { SetLine(APoint1, APoint2);                    }


    inline void   SetPoint1(const CPoint &AValue)                   { Point1 = AValue;                              }
    inline void   SetPoint2(const CPoint &AValue)                   { Point2 = AValue;                              }
    inline void   SetLineEmpty()                                    { Point1 = Point2 = CPoint(0, 0);               }
    inline void   SetLine(const CPoint &APoint1, const CPoint &APoint2) { Point1 = APoint1; Point2 = APoint2;       }
    inline double Length() const                                    { return YCHypotenuseLength(DeltaX() * 1.0, DeltaY() * 1.0); }
    inline long   DeltaX() const                                    { return Point1.x - Point2.x;                   }
    inline long   DeltaY() const                                    { return Point1.y - Point2.y;                   }
    inline bool   IsLineEmpty() const                               { return (Point1 == Point2) == TRUE;            }
    inline bool   IsLineNull() const                                { return ((Point1 == CPoint(0, 0)) == TRUE) && ((Point2 == CPoint(0, 0)) == TRUE); }
};



//============================ Double Point
struct strYCDoublePoint
{
    double X;
    double Y;
};

class CYCDoublePoint : public strYCDoublePoint
{
public :
    CYCDoublePoint()                                                { X = 0; Y = 0;                                     }
    CYCDoublePoint(double AX, double AY)                            { X = AX; Y = AY;                                   }


    inline void SetPoint(double AX, double AY)                      { X = AX; Y = AY;                                   }
    inline void operator+=(const strYCDoublePoint &AValue)            { X += AValue.X; Y += AValue.Y;                     }
    inline CYCDoublePoint& operator=(const strYCDoublePoint &AValue)  { X = AValue.X; Y = AValue.Y; return *this;         }
    inline CYCDoublePoint operator+(const strYCDoublePoint &AValue)   { return CYCDoublePoint(X + AValue.X, Y + AValue.Y); }
    inline bool operator==(const strYCDoublePoint &AValue) const      { return X == AValue.X && Y == AValue.Y;            }
    inline bool operator!=(const strYCDoublePoint &AValue) const      { return !(*this == AValue);                        }

};



//============================ Double Range
struct strYCDoubleRange
{
    double Low;
    double High;
};



//============================ CYCVector
template<class _Ty, class _Ax = std::allocator<_Ty> >
class CYCVector : public std::vector<_Ty, _Ax>
{
public:
    inline INT_PTR  IndexOf(const _Ty &AValue) const
    {
        if (size() > 0)
        {
            for (INT_PTR I = 0; I < (INT_PTR)size(); I ++)
            {
                if ((*this)[I] == AValue)
                    return I;
            }
        }

        return -1;
    }

    inline bool     Remove(const _Ty &AValue)
    {
        INT_PTR I = IndexOf(AValue);

        if (I != -1)
        {
            erase(begin() + I);

            return true;
        }

        return false;
    }
};


//============================ CYCThreadVector
template<class _Ty, class _Ax = std::allocator<_Ty> >
class CYCThreadVector : public CYCVector<_Ty, _Ax>
{
public:

    inline INT_PTR  ThreadIndexOf(void *AValue)     { CSingleLock LLocker(&m_Locker, TRUE); return __super::IndexOf(AValue);    }
    inline bool     ThreadRemove(void *AValue)      { CSingleLock LLocker(&m_Locker, TRUE); return __super::Remove(AValue);     }
    inline void     ThreadPushback(void *AValue)    { CSingleLock LLocker(&m_Locker, TRUE); __super::push_back(AValue);         }

    inline std::vector<_Ty, _Ax>*
        /**/        LockVector()                    { m_Locker.Lock(); return this;                                             }

    inline void     Unlock()                        { m_Locker.Unlock();                                                        }


private:
    CCriticalSection    m_Locker;

};


//============================ CYCDeque
template<class _Ty, class _Ax = std::allocator<_Ty> >
class CYCDeque : public std::deque<_Ty, _Ax>
{
public:

    CYCDeque() : std::deque<_Ty, _Ax>()
    {
    }

    CYCDeque(int ASize) : std::deque<_Ty, _Ax>(ASize)
    {
    }

    inline INT_PTR  IndexOf(const _Ty &AValue) const
    {
        if (size() > 0)
        {
            for (INT_PTR I = 0; I < (INT_PTR)size(); I ++)
            {
                if ((*this)[I] == AValue)
                    return I;
            }
        }

        return -1;
    }

    inline bool     Remove(const _Ty &AValue)
    {
        INT_PTR I = IndexOf(AValue);

        if (I != -1)
        {
            erase(begin() + I);

            return true;
        }

        return false;
    }

};



//============================ CYCThreadDeque
template<class _Ty, class _Ax = std::allocator<_Ty> >
class CYCThreadDeque : public CYCDeque<_Ty, _Ax>
{
public:

    CYCThreadDeque() : CYCDeque()
    {
    }

    CYCThreadDeque(int ASize) : CYCDeque(ASize)
    {
    }

    inline INT_PTR  ThreadIndexOf(const _Ty &AValue)
    {
        CSingleLock LLocker(&m_Locker, TRUE);
        return __super::IndexOf(AValue);
    }

    inline bool     ThreadRemove(const _Ty &AValue)
    {
        CSingleLock LLocker(&m_Locker, TRUE);
        return __super::Remove(AValue);
    }

    inline void     ThreadPushFront(const _Ty &AValue)
    {
        CSingleLock LLocker(&m_Locker, TRUE);
        __super::push_front(AValue);
    }

    inline void     ThreadPushBack(const _Ty &AValue)
    {
        CSingleLock LLocker(&m_Locker, TRUE);
        __super::push_back(AValue);
    }


    inline _Ty      ThreadPopFront(bool AIsRemove)
    {
        CSingleLock LLocker(&m_Locker, TRUE);

        _Ty LRslt = front();

        __super::pop_front();

        return LRslt;
    }

    inline _Ty      ThreadPopBack(bool AIsRemove)
    {
        CSingleLock LLocker(&m_Locker, TRUE);

        _Ty LRslt = back();

        __super::pop_back();

        return LRslt;
    }

    inline std::deque<_Ty, _Ax>*
        /**/        LockDeque()
    {
        m_Locker.Lock();
        return this;
    }

    inline void     UnlockDeque()
    {
        m_Locker.Unlock();
    }


private:
    CCriticalSection    m_Locker;

};



//============================ CYCAverageComputer
template<class _Ty>
class CYCAverageComputer
{
public:
    CYCAverageComputer()
        : m_IsAutoCompute(false)
        , m_MaxCount(5)
        , m_IsDefaultValueValid(false)
    {
    }


    inline void Clear()
    {
        m_Datas.clear();
        Recompute();
    }

    inline int  MaxCount()
    {
        return m_MaxCount;
    }

    inline void SetMaxCount(int AValue)
    {
        ASSERT(AValue >= 1);
        m_MaxCount = AValue;

        if (static_cast<int>(m_Datas.size()) > m_MaxCount)
            m_Datas.erase(m_Datas.begin(), m_Datas.begin() + m_Datas.size() - m_MaxCount);

        Recompute();
    }

    inline bool IsAutoCompute()
    {
        return m_IsAutoCompute;
    }

    inline void SetIsAutoCompute(bool AValue)
    {
        m_IsAutoCompute = AValue;
    }

    inline void SetDefaultValue(const _Ty &AData)
    {
        m_DefaultValue = AData;
    }

    inline void PushData(const _Ty &AData)
    {
        m_Datas.push_back(AData);

        if (static_cast<int>(m_Datas.size()) > m_MaxCount)
            m_Datas.erase(m_Datas.begin(), m_Datas.begin() + m_Datas.size() - m_MaxCount);

        if (m_IsAutoCompute)
            Recompute();
    }

    inline const _Ty&
        /**/    Recompute()
    {
        if (m_Datas.size() > 0)
        {
            _Ty LTotalValue = m_Datas[0];

            for (int I = 1; I < static_cast<int>(m_Datas.size()); I ++)
            {
                LTotalValue += m_Datas[I];
            }

            m_AverageValue = LTotalValue / static_cast<int>(m_Datas.size());
        }
        else
        {
            m_AverageValue = m_DefaultValue;
        }

        return m_AverageValue;
    }

    inline const _Ty&
        /**/    AverageValue() const
    {
        return (m_Datas.size() > 0) ? m_AverageValue : m_DefaultValue;
    }

private:
    bool                m_IsAutoCompute;
    int                 m_MaxCount;
    _Ty                 m_AverageValue;
    _Ty                 m_DefaultValue;
    bool                m_IsDefaultValueValid;

    std::vector<_Ty>    m_Datas;

};


//============================

typedef std::vector<BYTE>       TByteVector;
typedef std::vector<WORD>       TWordVector;
typedef std::vector<DWORD>      TDWordVector;
typedef std::vector<char>       TCharVector;
typedef std::vector<short>      TShortVector;
typedef std::vector<long>       TLongVector;
typedef std::vector<int>        TIntVector;
typedef std::vector<float>      TFloatVector;
typedef std::vector<double>     TDoubleVector;
typedef std::vector<CString>    TStringVector;
typedef std::vector<bool>       TBoolVector;
typedef std::vector<GUID>       TGUIDVector;
typedef std::vector<CObject *>  TObjectVector;

typedef std::deque<BYTE>        TByteDeque;
typedef std::deque<WORD>        TWordDeque;
typedef std::deque<DWORD>       TDWordDeque;
typedef std::deque<char>        TCharDeque;
typedef std::deque<short>       TShortDeque;
typedef std::deque<long>        TLongDeque;
typedef std::deque<int>         TIntDeque;
typedef std::deque<float>       TFloatDeque;
typedef std::deque<double>      TDoubleDeque;
typedef std::deque<CString>     TStringDeque;
typedef std::deque<bool>        TBoolDeque;
typedef std::deque<GUID>        TGUIDDeque;
typedef std::deque<CObject *>   TObjectDeque;


template<class _Ty, class _Ax>
inline int  YCIndexOf(_Ty &AList, _Ax &AValue)
{
#if 0
    int LIdx = 0;

    for (_Ty::const_iterator LIter = AList.begin();
        LIter != AList.end(); LIter ++, LIdx ++)
    {
        if ((*LIter) == AValue)
            return LIdx;
    }
#else
    _Ty::const_iterator LIter = std::find(AList.begin(), AList.end(), AValue);

    if (LIter != AList.end())
        return static_cast<int>(LIter - AList.begin());
#endif

    return -1;
}


// 把Name=Value格式的字串分離出Name和Value兩個字串
extern CString  YCStrName(LPCSTR AStr);
extern CString  YCStrValue(LPCSTR AStr);
extern void     YCLastErrorText(OUT CString &ARslt);
extern void     YCShowLastErrorText(bool AIsOnlyTrace);
#define         YCTraceLastErrorText()      YCShowLastErrorText(true)

extern int      YCStrToIntDef(LPCSTR AStr, int ADef);
extern DWORD    YCStrToUINTDef(LPCSTR AStr, DWORD ADef);
extern double   YCStrToFloatDef(LPCSTR AStr, double ADef);
extern int      YCRound(double AValue);

extern DWORD    YCMinTickCountBetween(DWORD AMSecond1, DWORD AMSecond2);
extern DWORD    YCMSecBetween(const SYSTEMTIME &ATime1, const SYSTEMTIME &ATime2);
extern LONG     YCSystemTimeDifferenceMSec(const SYSTEMTIME &ATime1, const SYSTEMTIME &ATime2);
extern void     YCSystemTimeAdd(SYSTEMTIME &ATime, int ATimeMSec);
extern LONG     YCSystemTimeCompare(const SYSTEMTIME &ATime1, const SYSTEMTIME &ATime2);
extern CString  YCFormatCurrentTimeText(LPCSTR AFormat = NULL);
extern CString  YCFormatSystemTimeText(const SYSTEMTIME &ATime, LPCSTR AFormat = NULL);

extern SYSTEMTIME
/**/            YCGetBaseLocalTime();

extern SYSTEMTIME
/**/            YCGetLocalTime();

extern double   YCAverage(int ACount, double AValues[]);
extern double   YCAverage(int ACount, int ASkipFront, int ASkipBack, double AValues[]);
extern double   YCMiddle(int ACount, double AValues[]);
extern double   YCMin(const std::deque<double>& AValues);
extern double   YCMax(const std::deque<double>& AValues);
extern double   YCMin(const std::vector<double>& AValues);
extern double   YCMax(const std::vector<double>& AValues);
extern bool     YCAnalyzeLine(const std::vector<strYCDoublePoint> &APoints, int AFromIdx, int AEndIdx, OUT double *AA, OUT double *AB);
extern void     YCAnalyzeLine(int APointsCount, const strYCDoublePoint *APoints, OUT double *AA, OUT double *AB);
extern void     YCAnalyzeCircle(int ACount, strYCDoublePoint *APoints, OUT strYCDoublePoint &AOrg, OUT double &ARadius);
extern void     YCDifferentiation(IN const std::vector<strYCDoublePoint> &AValue, int ALineSpan, OUT std::vector<strYCDoublePoint> *ADiffValue = NULL);
extern void     YCAppendTextToEditControl(CEdit   *AEdit, LPCSTR AMessage);

extern bool     YCSaveBMPToFileBMPBW8(LPCSTR AFileName, BITMAPINFO* ABitmapInfo, const BYTE *ABMP);
extern bool     YCSaveBMPToFileBMPBW8(LPCSTR AFileName, const BYTE *AImage, int AWidth, int AHeight);
extern bool     YCSaveBMPToFileRawBW8(LPCSTR AFileName, const BYTE *AImage, int AWidth, int AHeight);
extern bool     YCOpenBMPFromFileRawBW8(LPCSTR AFileName, OUT SIZE &ABmpSize, OUT BYTE **ABmpRaw);
extern void     YCBMPToRaw(const SIZE ASize, OUT BYTE *ADst, const BYTE *ASrc);
extern void     YCRawToBMP(const SIZE ASize, OUT BYTE *ADst, const BYTE *ASrc);
extern void     YCReverseCopyBMP(const SIZE &ASize, OUT BYTE *ADst, const BYTE *ASrc);
extern bool     YCSSEAddImage(long AWidth, long AHeight, BYTE *Image1, BYTE *Image2);
extern bool     YCSSEAddImage(long AWidth, long AHeight, BYTE *Image1, BYTE Value);
extern void     YCHightContrastRaw(IN OUT BYTE *ABmp, const RECT& ASize, int AFactor);
extern void     YCHightContrastRaw(IN OUT BYTE *ABmp, int AWidth, int AHeight, int AFactor);

extern void     YCImageGainOffset(IN OUT BYTE *ABmp, const SIZE &ASize, double AGain, int AOffset);
extern void     YCImageGainOffset(IN OUT BYTE *ABmp, int AWidth, int AHeight, double AGain, int AOffset);
extern void     YCImageGainOffset(IN OUT BYTE *ABmp, const SIZE &ASize, const RECT &AEffectiveArea, double AGain, int AOffset);
extern void     YCImageGainOffset(IN OUT BYTE *ABmp,
                                int AWidth              , int AHeight,
                                int AEffectiveAreaX     , int AEffectiveAreaY,
                                int AEffectiveAreaWidth , int AEffectiveAreaHeight,
                                double AGain            , int AOffset);




extern bool     YCAdjRectToInsideAnother(RECT &AChild, const RECT &AParent, bool AIntersectionOp);
extern bool     YCAdjLineToInsideAnother(CYCLine &ALine, const RECT &AParent, bool AIntersectionOp);

extern CWnd*    YCGetTopModalDialog(CWnd *AWnd);
extern void     YCSetDlgItemText(CDialog *ADlg, WORD AItemId, LPCSTR AText);
extern void     YCSetDlgItemFloat(CDialog *ADlg, WORD AItemId, double AValue, int ADigit = 1);
extern double   YCGetDlgItemFloatDef(CDialog *ADlg, WORD AItemId, double ADef = 0.0);


#define         YCSetThisDlgItemText(__ItemId, __Text)              YCSetDlgItemText(this, __ItemId, __Text)
#define         YCSetThisDlgItemFloat(__ItemId, __Value, __Digit)   YCSetDlgItemFloat(this, __ItemId, __Value, __Digit)
#define         YCGetThisDlgItemFloatDef(__ItemId, __Def)           YCGetDlgItemFloatDef(this, __ItemId, __Def);




extern int      YCAfxMessageBox(LPCTSTR AText, UINT AType = MB_OK, UINT AIDHelp = 0, IN CFont *AFont = NULL);

//////////////////////////////////////////
// YCWaitForSignalObjectsAndHandleMessage : 
//     如果收到WM_QUIT訊息則傳回false，其它則傳回true
extern bool     YCWaitForSignalObjectsAndHandleMessage(DWORD &ASignalObj, DWORD AObjCount, HANDLE *AHandles, DWORD ATimeoutMSec = 1000);
extern void     YCWinMsgQueueNeeded();
extern bool     YCPumpMessageAndWaitFor(HANDLE AHandle, DWORD ATimeoutMSec = INFINITE);
extern void     YCEnableThisWndIncludeParent(CWnd *AWnd, bool AAllParent, BOOL AEnabled);
extern DWORD    YCMsgWaitForSingleObject(HANDLE AHandle, DWORD AMilliseconds, DWORD AWakeMask);
extern DWORD    YCMsgWaitForSingleObjectEx(HANDLE AHandle, DWORD AMilliseconds, DWORD AWakeMask, BOOL AIsAlertable, BOOL AIsInputAvailable);




extern void*    YCmalloc(size_t ASize);
extern void     YCfree(void *AMemBlock);
extern void*    YCrealloc(void *AMemBlock, size_t ANewSize);



extern CString  YCComputerName();
extern CString  YCApplicationFileName();
extern CString  YCApplicationDir();
extern void     YCForceDir(LPCSTR ADir);
extern void     YCForceDirFromFileName(LPCSTR AFileName);
extern CString  YCRelativeFileNameToAbs(LPCSTR AFileName);
extern void     YCRegisterDirectoryVar(LPCSTR AVarName, LPCSTR ADirectory);
extern void     YCShowApplication();
extern void     YCHideApplication();



////////////////////////////////////////
// YCSeperateWords() :
//     把一個字串，分離出各個單字
//      1. 遇大寫則分離
//      2. 遇ASeperateChar字元則分離
//     回傳：把分離的位置插入一個'\n'
//
extern CString  YCSeperateWords(LPCSTR AText, char ASeperateChar);
//
////////////////////////////////////////




////////////////////////////////////////
// YCIsValidName() :
//     檢查AName是否是有效的
//      1. 長度 > 1
//      2. 符合C++的識別字格式
//     回傳：合格true，反之false
extern bool     YCIsValidName(LPCSTR AName);
//
////////////////////////////////////////


////////////////////////////////////////
// Archive 相關函式：
//
extern CArchive& operator||(CArchive &AArchive, BYTE       &AValue);
extern CArchive& operator||(CArchive &AArchive, WORD       &AValue);
extern CArchive& operator||(CArchive &AArchive, DWORD      &AValue);
extern CArchive& operator||(CArchive &AArchive, LONG       &AValue);
extern CArchive& operator||(CArchive &AArchive, float      &AValue);
extern CArchive& operator||(CArchive &AArchive, double     &AValue);
extern CArchive& operator||(CArchive &AArchive, LONGLONG   &AValue);
extern CArchive& operator||(CArchive &AArchive, ULONGLONG  &AValue);
extern CArchive& operator||(CArchive &AArchive, int        &AValue);
extern CArchive& operator||(CArchive &AArchive, short      &AValue);
extern CArchive& operator||(CArchive &AArchive, char       &AValue);
#ifdef _NATIVE_WCHAR_T_DEFINED
extern CArchive& operator||(CArchive &AArchive, wchar_t    &AValue);
#endif
extern CArchive& operator||(CArchive &AArchive, bool       &AValue);
extern CArchive& YCArchiveRaw(CArchive &AArchive, void *AValue, UINT AValueSize);
extern CArchive& operator||(CArchive &AArchive, strYCCommonDataHeader &AValue);
extern CArchive& operator||(CArchive &AArchive, strYCDoublePoint &AValue);
extern CArchive& operator||(CArchive &AArchive, CString& AValue);
extern CArchive& operator||(CArchive &AArchive, GUID& AValue);
//
// Archive 相關函式：
////////////////////////////////////////




////////////////////////////////////////
// GUID相關函式
//
class CYCGUID : public GUID
{
public:
    CYCGUID();
    CYCGUID(const GUID &AGUID);

    bool    operator>(const GUID &AValue) const;
    bool    operator==(const GUID &AValue) const;
    bool    operator<(const GUID &AValue) const;
    bool    operator>=(const GUID &AValue) const;
    bool    operator<=(const GUID &AValue) const;
    bool    operator!=(const GUID &AValue) const;
    CYCGUID&  operator=(const GUID &AValue);

    void NewGUID();
};

extern CString  YCGUIDToStr(const GUID &AGUID);
extern bool     YCStrToGUID(LPCSTR AGUIDStr, OUT GUID &AResultValue);
extern GUID     YCStrToGUID(LPCSTR AGUIDStr);
//
// GUID相關函式
////////////////////////////////////////


////////////////////////////////////////
// 事件相關宣告
//
//================================
// TNotifyEvent(CObject *ASender)
//
typedef void (CObject::*TNotifyEvent)(CObject *ASender);

struct strYCNotifyEvent
{
    CObject         *Handler;
    TNotifyEvent    HandlerFunc;

    strYCNotifyEvent() : Handler(NULL), HandlerFunc(NULL)
    {   }

    strYCNotifyEvent(CObject  *AHandler, TNotifyEvent AHandlerFunc)
    { Handler = AHandler, HandlerFunc = AHandlerFunc; }

    strYCNotifyEvent(const strYCNotifyEvent &ASrc)
    { operator =(ASrc); }

    inline strYCNotifyEvent& operator =(const strYCNotifyEvent &ASrc)
    { Handler = ASrc.Handler, HandlerFunc = ASrc.HandlerFunc; return *this; }

    inline bool operator ==(const strYCNotifyEvent &ASrc) const
    { return Handler == ASrc.Handler && HandlerFunc == ASrc.HandlerFunc; }

    inline void operator()(CObject *ASender)
    { if (Handler && HandlerFunc) (Handler->*HandlerFunc)(ASender); }
};

#define __NULL_NotifyEvent                      strYCNotifyEvent()
#define __NotifyEvent(__Object, __Func)          strYCNotifyEvent(__Object, static_cast<TNotifyEvent>(__Func))
//
// 事件相關宣告
////////////////////////////////////////


////////////////////////////////////////
// 事件相關宣告
//
//================================
// TNotifyEventEx(CObject *ASender)
//
typedef LRESULT (CObject::*TNotifyEventEx)(CObject *ASender);

struct strYCNotifyEventEx
{
    CObject         *Handler;
    TNotifyEventEx  HandlerFunc;

    strYCNotifyEventEx() : Handler(NULL), HandlerFunc(NULL)
    {   }

    strYCNotifyEventEx(CObject  *AHandler, TNotifyEventEx AHandlerFunc)
    { Handler = AHandler, HandlerFunc = AHandlerFunc; }

    strYCNotifyEventEx(const strYCNotifyEventEx &ASrc)
    { operator =(ASrc); }

    inline strYCNotifyEventEx& operator =(const strYCNotifyEventEx &ASrc)
    { Handler = ASrc.Handler, HandlerFunc = ASrc.HandlerFunc; return *this; }

    inline bool operator ==(const strYCNotifyEventEx &ASrc) const
    { return Handler == ASrc.Handler && HandlerFunc == ASrc.HandlerFunc; }

    inline LRESULT operator()(CObject *ASender)
    { if (Handler && HandlerFunc) return (Handler->*HandlerFunc)(ASender); return 0; }
};

#define __NULL_NotifyEventEx                      strYCNotifyEventEx()
#define __NotifyEventEx(__Handler, __Func)        strYCNotifyEventEx(__Handler, static_cast<TNotifyEventEx>(__Func))
//
// 事件相關宣告
////////////////////////////////////////


struct strYCStrLessNoCase : public std::binary_function<CString, CString, bool>
{
    // functor for operator<
    inline bool operator()(const CString &ALeft, const CString &ARight) const
    {
        // apply operator< to operands
        return (ALeft.CompareNoCase(ARight) < 0);
    }
};


struct strYCStrLess : public std::binary_function<CString, CString, bool>
{
    // functor for operator<
    inline bool operator()(const CString &ALeft, const CString &ARight) const
    {
        // apply operator< to operands
        return (ALeft.Compare(ARight) < 0);
    }
};


struct strYCStrEqualNoCase : public std::binary_function<CString, CString, bool>
{
    // functor for operator==
    inline bool operator()(const CString &ALeft, const CString &ARight) const
    {
        // apply operator< to operands
        return !ALeft.CompareNoCase(ARight);
    }
};


struct strYCStrEqual : public std::binary_function<CString, CString, bool>
{
    // functor for operator==
    inline bool operator()(const CString &ALeft, const CString &ARight) const
    {
        // apply operator== to operands
        return !ALeft.Compare(ARight);
    }
};



class CYCSetThreadPriority
{
public:
    explicit CYCSetThreadPriority(int ANewPriority)
        : m_OrgPriority(GetThreadPriority(GetCurrentThread()))
        , m_OrgThreadId(GetCurrentThreadId())
    {
        SetThreadPriority(GetCurrentThread(), ANewPriority);
    }

    ~CYCSetThreadPriority()
    {
        Reset();
    }

    inline void Reset()
    {
        if (GetCurrentThreadId() == m_OrgThreadId)
        {
            SetThreadPriority(GetCurrentThread(), m_OrgPriority);
        }
        else
        {
            HANDLE  LThrdHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, m_OrgThreadId);

            if (LThrdHandle)
            {
                SetThreadPriority(LThrdHandle, m_OrgPriority);
                CloseHandle(LThrdHandle);
            }
        }
    }

private:
    const int   m_OrgPriority;
    const DWORD m_OrgThreadId;

};


typedef std::deque<CObject *>       CObjectDeque;


class CYCBoolLock
{
public:
    CYCBoolLock(bool *AFlag) : m_Flag(AFlag), m_OldFlag(AFlag ? *AFlag : false)
    {
        //ASSERT(m_Flag);
        if (m_Flag)
            *m_Flag = true;
    }

    ~CYCBoolLock()
    {
        //ASSERT(m_Flag);
        if (m_Flag)
            *m_Flag = m_OldFlag;
    }

private:
    bool* const m_Flag;
    const bool  m_OldFlag;

};


class CYCCountLock
{
public:
    CYCCountLock(LONG   *AFlag) : m_Flag(AFlag), m_IsLocked(false)
    {
        ASSERT(m_Flag);

        if (!m_IsLocked)
        {
            (*m_Flag) ++;
            m_IsLocked = true;
        }
    }

    ~CYCCountLock()
    {
        ASSERT(m_Flag);

        if (m_IsLocked)
        {
            (*m_Flag) --;
            m_IsLocked = false;
        }
    }

private:
    LONG    *m_Flag;
    bool    m_IsLocked;

};


//==============================
#if 0
struct strYCXMLElement
{
    CString     Tag;

    std::map<CString, CString>
        /**/    Attributes;

    CString     Data;

    std::deque<strYCXMLElement *>
        /**/    Elements;


    ~strYCXMLElement();
};

extern CString  YCFormatXMLElementText(const strYCXMLElement &AXMLElement);
extern void     YCFormatXMLElementText(const strYCXMLElement &AXMLElement, OUT CString &ARslt);
#endif


template<class __ObjectClass>
class CYCGdiSelectObject
{
public:
	CYCGdiSelectObject(CDC *ADC, __ObjectClass *AObject)
	    : m_DC(ADC), m_OldObject((__ObjectClass *)ADC->SelectObject(AObject)), m_IsOldObjectValid(true)
	{
	    ASSERT(ADC);
	}

    ~CYCGdiSelectObject()
    {
        Restore();
    }

    inline void Restore()
    {
        if (m_IsOldObjectValid)
        {
            m_DC->SelectObject(m_OldObject);
            m_OldObject = NULL;
            m_IsOldObjectValid = false;
        }
    }

private:
    CDC             *m_DC;
    __ObjectClass   *m_OldObject;
    bool            m_IsOldObjectValid;

};


typedef CYCGdiSelectObject<CPen>        CYCGdiSelectPen;
typedef CYCGdiSelectObject<CBrush>      CYCGdiSelectBrush;
typedef CYCGdiSelectObject<CBitmap>     CYCGdiSelectBitmap;
typedef CYCGdiSelectObject<CFont>       CYCGdiSelectFont;


#define DECLARE_GdiSelectPen(__DCObj, __Object)             const CYCGdiSelectPen       L##__DCObj##SelectPen(&__DCObj, __Object)
#define DECLARE_GdiSelectPenPtr(__DCPtr, __Object)          const CYCGdiSelectPen       L##__DCPtr##SelectPen(__DCPtr , __Object)
#define DECLARE_GdiSelectBrush(__DCObj, __Object)           const CYCGdiSelectBrush     L##__DCObj##SelectBrush(&__DCObj, __Object)
#define DECLARE_GdiSelectBrushPtr(__DCPtr, __Object)        const CYCGdiSelectBrush     L##__DCPtr##SelectBrush(__DCPtr , __Object)
#define DECLARE_GdiSelectBitmap(__DCObj, __Object)          const CYCGdiSelectBitmap    L##__DCObj##SelectBitmap(&__DCObj, __Object)
#define DECLARE_GdiSelectBitmapPtr(__DCPtr, __Object)       const CYCGdiSelectBitmap    L##__DCPtr##SelectBitmap(__DCPtr , __Object)
#define DECLARE_GdiSelectFont(__DCObj, __Object)            const CYCGdiSelectFont      L##__DCObj##SelectFont(&__DCObj, __Object)
#define DECLARE_GdiSelectFontPtr(__DCPtr, __Object)         const CYCGdiSelectFont      L##__DCPtr##SelectFont(__DCPtr , __Object)



class CYCIconInfo
{
public:
    CYCIconInfo(HICON   AIcon)
    {
        ::GetIconInfo(AIcon, &m_IconInfo);
    }

    ~CYCIconInfo()
    {
        if (m_IconInfo.hbmColor)
            ::DeleteObject(m_IconInfo.hbmColor);

        if (m_IconInfo.hbmMask)
            ::DeleteObject(m_IconInfo.hbmMask);

    }

    inline const ICONINFO* operator->() const
    {
        return &m_IconInfo;
    }

private:
    ICONINFO    m_IconInfo;

};


//GROUP:============================== IYCGetThis
__interface IYCGetThis
{
public:
    STDMETHOD_(CObject*, GetThis)(void) PURE;
};


template<class __Ty>
class CYCGetThisTmpl : public __Ty
{
public:
    STDMETHOD_(CObject*, GetThis)(void)
    { return this; }
};


//GROUP:============================== XML DOM function
__interface IYCXMLPersist : public IYCGetThis
{
public:
    STDMETHOD_(bool, LoadFromXML)(IXMLDOMElement *AXMLEle)  PURE;
    STDMETHOD_(bool, SaveToXML  )(IXMLDOMElement *AXMLEle)  PURE;
};


__interface IYCXMLDumpInfo : public IYCGetThis
{
public:
    STDMETHOD_(bool, DumpInfoToXML)(IXMLDOMElement *AXMLEle) PURE;
};



extern HRESULT YCXMLDOMCreateDocument(bool AIsOpen, IXMLDOMDocument **AXMLDoc, LPCSTR ARootEleName = NULL, IXMLDOMElement **ARootXMLEle = NULL, LPCSTR AEncoding = NULL);
extern HRESULT YCXMLDOMDocumentLoad(IXMLDOMDocument *AXMLDoc, LPCSTR AFileName);
extern HRESULT YCXMLDOMDocumentSave(IXMLDOMDocument *AXMLDoc, LPCSTR AFileName);
extern HRESULT YCXMLDOMGetRootElement(IXMLDOMDocument *AXMLDoc, IXMLDOMElement **ARslt);
extern HRESULT YCXMLDOMGetRootElement(IXMLDOMElement  *AXMLEle, IXMLDOMElement **ARslt);
extern HRESULT YCXMLDOMGet1stChildNode(IXMLDOMElement  *AParentXMLEle, IXMLDOMNode **ARslt);
extern HRESULT YCXMLDOMGet1stChildNode(IXMLDOMNode  *AParentXMLNod, IXMLDOMNode **ARslt);
extern HRESULT YCXMLDOMGetNextSiblingChildNode(IXMLDOMNode  *AXMLNod, IXMLDOMNode **ARslt);
extern HRESULT YCXMLDOMGetDocument(IXMLDOMElement  *AXMLEle, IXMLDOMDocument **ARslt);
extern HRESULT YCXMLDOMCreateElement(IXMLDOMElement  *AXMLEle, LPCSTR AEleName, IXMLDOMElement **ARslt);
extern HRESULT YCXMLDOMCreateAppendElement(IXMLDOMElement  *AParentXMLEle, LPCSTR AEleName, IXMLDOMElement **ARslt);
extern HRESULT YCXMLDOMSelectSingleNode(IXMLDOMElement  *AParentXMLEle, LPCSTR AEleName, IXMLDOMNode **ARslt);

extern HRESULT YCLoadObjectFromXMLFile(LPCSTR AFileName, LPCSTR ARootEleName, CObject **ARslt);
extern HRESULT YCSaveObjectToXMLFile2 (LPCSTR AFileName, CObject *AObject, LPCSTR ARootEleName);
extern HRESULT YCLoadObjectFromXML    (IXMLDOMElement *AXMLEle, LPCSTR AEleName, CObject **ARslt);
extern HRESULT YCSaveObjectToXML2     (IXMLDOMElement *AXMLEle, CObject *AObject);
extern HRESULT YCSaveObjectToXMLChild2(IXMLDOMElement *AParentXMLEle, LPCSTR AChildEleName, CObject *AObject, IXMLDOMElement **AChildXMLEle = NULL);

extern HRESULT YCDumpObjectInfoToXMLFile2  (LPCSTR AFileName, CObject *AObject, LPCSTR ARootEleName);
extern HRESULT YCDumpObjectInfoToXML2      (IXMLDOMElement *AXMLEle, CObject *AObject);
extern HRESULT YCDumpObjectInfoToXMLChild2 (IXMLDOMElement *AParentXMLEle, LPCSTR AChildEleName, CObject *AObject, IXMLDOMElement **AChildXMLEle = NULL);


template<class __Ty>
inline HRESULT              YCXMLDOMAttributeRead(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, OUT __Ty &ARslt, const __Ty &ADefault)
{
    ASSERT(AXMLEle);

    ARslt = ADefault;

    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        _variant_t   LVar;

        LCoRslt = AXMLEle->getAttribute(_bstr_t(AAttName), &LVar);

        if (SUCCEEDED(LCoRslt) && (LCoRslt == S_OK) && LVar.vt != VT_NULL)
            ARslt = static_cast<__Ty>(LVar);
    }

    return LCoRslt;
}

template<class __Ty>
inline HRESULT              YCXMLDOMAttributeWrite(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, const __Ty &AValue)
{
    ASSERT(AXMLEle);

    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = AXMLEle->setAttribute(_bstr_t(AAttName), _variant_t(AValue));

    return LCoRslt;
}

template<class __Ty>
inline HRESULT              YCXMLDOMAttributeReadEnum(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, OUT __Ty &ARslt, const __Ty &ADefault)
{
    ASSERT(AXMLEle);

    ARslt = ADefault;

    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
    {
        _variant_t   LVar;

        LCoRslt = AXMLEle->getAttribute(_bstr_t(AAttName), &LVar);

        if (SUCCEEDED(LCoRslt) && (LCoRslt == S_OK) && LVar.vt != VT_NULL)
            ARslt = static_cast<__Ty>(static_cast<int>(LVar));
    }

    return LCoRslt;
}

template<class __Ty>
inline HRESULT              YCXMLDOMAttributeWriteEnum(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, const __Ty &AValue)
{
    ASSERT(AXMLEle);

    HRESULT LCoRslt = AXMLEle ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(LCoRslt))
        LCoRslt = AXMLEle->setAttribute(_bstr_t(AAttName), _variant_t(static_cast<int>(AValue)));

    return LCoRslt;
}

extern HRESULT YCXMLDOMAttributeReadString(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, OUT CString &ARslt, LPCSTR ADefault);
extern HRESULT YCXMLDOMAttributeReadGUID(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, OUT GUID &ARslt, const GUID &ADefault);
extern HRESULT YCXMLDOMAttributeWriteGUID(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, const GUID &AValue);
extern HRESULT YCXMLDOMAttributeReadSystemTime(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, OUT SYSTEMTIME &ARslt, const SYSTEMTIME &ADefault);
extern HRESULT YCXMLDOMAttributeWriteSystemTime(IXMLDOMElement  *AXMLEle, LPCSTR AAttName, const SYSTEMTIME &AValue);


#define YCXMLDOMAttributeReadNameBool(__XMLEle, __AttName, __Var)                           YCXMLDOMAttributeRead(__XMLEle, __AttName, __Var, __Var)
#define YCXMLDOMAttributeReadNameInt(__XMLEle, __AttName, __Var)                            YCXMLDOMAttributeRead(__XMLEle, __AttName, __Var, __Var)
#define YCXMLDOMAttributeReadNameEnum(__XMLEle, __AttName, __Var)                           YCXMLDOMAttributeReadEnum(__XMLEle, __AttName, __Var, __Var)
#define YCXMLDOMAttributeReadNameDouble(__XMLEle, __AttName, __Var)                         YCXMLDOMAttributeRead(__XMLEle, __AttName, __Var, __Var)
#define YCXMLDOMAttributeReadNameGUID(__XMLEle, __AttName, __Var)                           YCXMLDOMAttributeReadGUID(__XMLEle, __AttName, __Var, __Var)
#define YCXMLDOMAttributeReadNameString(__XMLEle, __AttName, __Var)                         YCXMLDOMAttributeReadString(__XMLEle, __AttName, __Var, __Var)

#define YCXMLDOMAttributeReadMemberVarBool(__XMLEle, __Var)                                 YCXMLDOMAttributeReadNameBool(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeReadMemberVarInt(__XMLEle, __Var)                                  YCXMLDOMAttributeReadNameInt(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeReadMemberVarEnum(__XMLEle, __Var)                                 YCXMLDOMAttributeReadNameEnum(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeReadMemberVarDouble(__XMLEle, __Var)                               YCXMLDOMAttributeReadNameDouble(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeReadMemberVarGUID(__XMLEle, __Var)                                 YCXMLDOMAttributeReadNameGUID(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeReadMemberVarString(__XMLEle, __Var)                               YCXMLDOMAttributeReadNameString(__XMLEle, #__Var, __Var)

#define YCXMLDOMAttributeWriteNameBool(__XMLEle, __AttName, __Var)                          YCXMLDOMAttributeWrite(__XMLEle, __AttName, __Var)
#define YCXMLDOMAttributeWriteNameInt(__XMLEle, __AttName, __Var)                           YCXMLDOMAttributeWrite(__XMLEle, __AttName, __Var)
#define YCXMLDOMAttributeWriteNameEnum(__XMLEle, __AttName, __Var)                          YCXMLDOMAttributeWriteEnum(__XMLEle, __AttName, __Var)
#define YCXMLDOMAttributeWriteNameDouble(__XMLEle, __AttName, __Var)                        YCXMLDOMAttributeWrite(__XMLEle, __AttName, __Var)
#define YCXMLDOMAttributeWriteNameGUID(__XMLEle, __AttName, __Var)                          YCXMLDOMAttributeWriteGUID(__XMLEle, __AttName, __Var)
#define YCXMLDOMAttributeWriteNameString(__XMLEle, __AttName, __Var)                        YCXMLDOMAttributeWrite(__XMLEle, __AttName, __Var)

#define YCXMLDOMAttributeWriteMemberVarBool(__XMLEle, __Var)                                YCXMLDOMAttributeWriteNameBool(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeWriteMemberVarInt(__XMLEle, __Var)                                 YCXMLDOMAttributeWriteNameInt(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeWriteMemberVarEnum(__XMLEle, __Var)                                YCXMLDOMAttributeWriteNameEnum(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeWriteMemberVarDouble(__XMLEle, __Var)                              YCXMLDOMAttributeWriteNameDouble(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeWriteMemberVarGUID(__XMLEle, __Var)                                YCXMLDOMAttributeWriteNameGUID(__XMLEle, #__Var, __Var)
#define YCXMLDOMAttributeWriteMemberVarString(__XMLEle, __Var)                              YCXMLDOMAttributeWriteNameString(__XMLEle, #__Var, __Var)


// #define YCXMLDOMAttributeWriteMemberVarInfo(__XMLEle, __VarInfo)                            YCXMLDOMAttributeWrite(__XMLEle, #__VarInfo, m_##__VarInfo)
// #define YCXMLDOMAttributeWriteMemberVarInfoString(__XMLEle, __VarInfo, __VarStr)            YCXMLDOMAttributeWriteNameString(__XMLEle, #__VarInfo, __VarStr)

#define YCVERIFY_XMLDOM(X)  if (SUCCEEDED(LCoRslt)) LCoRslt = (X)


//GROUP:============================== CYCCoInitialize
class CYCCoInitialize
{
public:
    const HRESULT
        /**/    m_CoInitializeResult;

    const DWORD m_ThreadId;


    CYCCoInitialize(DWORD AInit = COINIT_MULTITHREADED)
        : m_CoInitializeResult(::CoInitializeEx(NULL, AInit))
        , m_ThreadId(::GetCurrentThreadId())
    {
        
    }

    ~CYCCoInitialize()
    {
        ASSERT(m_ThreadId == ::GetCurrentThreadId());

        if (m_ThreadId == ::GetCurrentThreadId() && SUCCEEDED(m_CoInitializeResult))
            ::CoUninitialize();
    }

};