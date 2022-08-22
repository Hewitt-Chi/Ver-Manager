#include "stdafx.h"


#include "YCUtils.h"


#include "YCListCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CYCListCtrl, CListCtrl)


CYCListCtrl::CYCListCtrl()
: CListCtrl()
, m_RowHeight(-1)
{
    m_LButtonDownCell.x = -1;
    m_LButtonDownCell.y = -1;
    m_FocusedCell.x = -1;
    m_FocusedCell.y = -1;
}

void    CYCListCtrl::PreSubclassWindow()
{

    const LONG LRowHeight = (m_RowHeight == -1) ? ApproximateViewRect(CSize(-1, -1), 2).cy - ApproximateViewRect(CSize(-1, -1), 1).cy : m_RowHeight;

    m_RowHeight = -1;
    SetRowHeight(LRowHeight);

    ModifyStyle(0, LVS_REPORT);

    __super::PreSubclassWindow();
}


BEGIN_MESSAGE_MAP(CYCListCtrl, CListCtrl)

    ON_WM_STYLECHANGING()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_KEYDOWN()
    ON_WM_KEYUP()

    ON_WM_MEASUREITEM_REFLECT()

    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW  , &CYCListCtrl::OnNMCustomDraw)
    ON_NOTIFY_REFLECT(LVN_INSERTITEM , &CYCListCtrl::OnLvnInsertitem)
    ON_NOTIFY_REFLECT(LVN_DELETEITEM , &CYCListCtrl::OnLvnDeleteitem)
    ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CYCListCtrl::OnLvnItemchanged)

END_MESSAGE_MAP()


LRESULT CYCListCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case LVM_INSERTCOLUMN :
        {
            TCellDataDeque  LColumnCellDatas;

            LColumnCellDatas.assign(GetItemCount(), DefaultCellData());
            m_CellDatas.insert(m_CellDatas.begin() + wParam, LColumnCellDatas);
            m_ColCellTypes.insert(m_ColCellTypes.begin() + wParam, ctNormal);
        }
        break;

    case LVM_DELETECOLUMN :
        m_CellDatas.erase(m_CellDatas.begin() + wParam);
        m_ColCellTypes.erase(m_ColCellTypes.begin() + wParam);
        break;

    }

    return __super::WindowProc(message, wParam, lParam);
}

void    CYCListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    TRACE("DrawItem %d\n", GetTickCount());
}

//============================
void    CYCListCtrl::OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
    __super::OnStyleChanging(nStyleType, lpStyleStruct);

    if (nStyleType == GWL_STYLE)
        lpStyleStruct->styleNew |= LVS_REPORT;
}

void    CYCListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    __super::OnLButtonDown(nFlags, point);

    LVHITTESTINFO   LHitTestInfo;

    LHitTestInfo.pt = point;

    m_LButtonDownCell.y = SubItemHitTest(&LHitTestInfo);
    m_LButtonDownCell.x = LHitTestInfo.iSubItem;


    if (m_LButtonDownCell.y != -1)
    {
        const strCellData &LCellData = m_CellDatas[m_LButtonDownCell.x][m_LButtonDownCell.y];

        if (LCellData.IsEnabled)
        {
            SetSelectionMark(m_LButtonDownCell.y);
            SetItemState(m_LButtonDownCell.y, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
            SetFocusedCell(m_LButtonDownCell);


            switch (LCellData.CellType)
            {
            case ctButton :
            case ctCheck :
            case ctCheckButton :
                {
                    SetCapture();

                    RedrawCell(m_LButtonDownCell.x, m_LButtonDownCell.y);
                }
                break;

            default :
                m_LButtonDownCell.y = -1;
                m_LButtonDownCell.x = -1;

            }


            TRACE("OnLButtonDown(%d, %d)\n", m_LButtonDownCell.x, m_LButtonDownCell.y);
        }
        else
        {
            m_LButtonDownCell.x = -1;
            m_LButtonDownCell.y = -1;
        }
    }
    else
    {
        m_LButtonDownCell.x = -1;
        m_LButtonDownCell.y = -1;
    }
}

void    CYCListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
    __super::OnLButtonUp(nFlags, point);

    if (m_LButtonDownCell.x != -1 && m_LButtonDownCell.y != -1)
    {
        ReleaseCapture();

        strCellData &LCellData = m_CellDatas[m_LButtonDownCell.x][m_LButtonDownCell.y];

        if (LCellData.CellType == ctCheck ||
            LCellData.CellType == ctCheckButton)
        {
            LCellData.IsChecked ^= true;
        }

        const POINT LCell = m_LButtonDownCell;

        m_LButtonDownCell.x = -1;
        m_LButtonDownCell.y = -1;

        RedrawCell(LCell.x, LCell.y);
        m_ButtonClickEvent(this, LCell.x, LCell.y);

        TRACE("OnLButtonUp()\n");
    }
    else
    {
        m_LButtonDownCell.x = -1;
        m_LButtonDownCell.y = -1;
    }
}

void    CYCListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: Add your message handler code here and/or call default
    switch (nChar)
    {
    case VK_LEFT :
        OffsetFocusedCell(-1, 0);
        break;

    case VK_UP :
        OffsetFocusedCell(0, -1);
        break;

    case VK_RIGHT :
        OffsetFocusedCell(1, 0);
        break;

    case VK_DOWN :
        OffsetFocusedCell(0, 1);
        break;

    case VK_SPACE :
        {
            const strCellData &LCellData = m_CellDatas[m_FocusedCell.x][m_FocusedCell.y];

            if (m_LButtonDownCell.x == -1 && m_LButtonDownCell.y == -1 && m_FocusedCell.x != -1 && m_FocusedCell.y != -1 &&
                (LCellData.CellType == ctButton ||
                 LCellData.CellType == ctCheck ||
                 LCellData.CellType == ctCheckButton) &&
                LCellData.IsEnabled)
            {
                m_LButtonDownCell = m_FocusedCell;
                RedrawCell(m_FocusedCell.x, m_FocusedCell.y);
            }
        }
        break;
    }


    __super::OnKeyDown(nChar, nRepCnt, nFlags);
}

void    CYCListCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: Add your message handler code here and/or call default
    switch (nChar)
    {
    case VK_SPACE :

        if (m_LButtonDownCell.x != -1 && m_LButtonDownCell.y != -1)
        {
            strCellData &LCellData = m_CellDatas[m_LButtonDownCell.x][m_LButtonDownCell.y];
            
            switch (LCellData.CellType)
            {
            case ctCheck :
            case ctCheckButton :
                LCellData.IsChecked ^= true;
                break;
            }

            const POINT LCell = m_LButtonDownCell;

            m_LButtonDownCell.x = m_LButtonDownCell.y = -1;
            RedrawCell(m_FocusedCell.x, m_FocusedCell.y);

            m_ButtonClickEvent(this, LCell.x, LCell.y);
        }
        break;
    }

    __super::OnKeyUp(nChar, nRepCnt, nFlags);
}

void    CYCListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    lpMeasureItemStruct->itemHeight = m_RowHeight;
}

void    CYCListCtrl::OnNMCustomDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW  pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: Add your control notification handler code here

    NMLVCUSTOMDRAW  *pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

    // Take the default processing unless we 
    // set this to something else below.
    *pResult = CDRF_DODEFAULT;

    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.
    const CPoint LCell(pLVCD->iSubItem, PtrToInt(pLVCD->nmcd.dwItemSpec));

    switch (pLVCD->nmcd.dwDrawStage)
    {
    case CDDS_PREPAINT :
        *pResult = CDRF_NOTIFYITEMDRAW;
        break;

    case CDDS_ITEMPREPAINT :
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
        break;

    case CDDS_ITEMPREPAINT | CDDS_SUBITEM :
        {
            CDC     LDC;

            LDC.Attach(pLVCD->nmcd.hdc);


            CRect   LRect;

            GetThisSubItemRect(LCell.x, LCell.y, LRect);


            // 塗成白色的底色
            LDC.FillRect(LRect, &CBrush(GetBkColor()));

            if (LCell.x < static_cast<int>(m_CellDatas.size()) && LCell.y < static_cast<int>(m_CellDatas[LCell.x].size()))
            {
                const strCellData &LCellData = m_CellDatas[LCell.x][LCell.y];

                switch (LCellData.CellType)
                {
                case ctButton :
                case ctCheckButton :
                    {
                        // 內縮4pixel，塗上按鈕的顏色
                        LRect.DeflateRect(4, 4);
                        LDC.FillRect(LRect, &CBrush(GetSysColor(COLOR_BTNFACE)));


                        // 把字畫出來
                        LDC.SetBkMode(TRANSPARENT);
                        LDC.SetTextColor(GetSysColor(LCellData.IsEnabled ? COLOR_BTNTEXT : COLOR_3DLIGHT));
                        LDC.DrawText(GetItemText(LCell.y, LCell.x), &LRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

                        // 畫出字的陰影
                        if (!LCellData.IsEnabled)
                        {
                            LDC.SetTextColor(GetSysColor(COLOR_3DSHADOW));
                            LRect.OffsetRect(-1, -1);
                            LDC.DrawText(GetItemText(LCell.y, LCell.x), &LRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
                        }


                        // 顯示按鈕邊框
                        UINT    LEdgeType = EDGE_RAISED;

                        if (LCell == m_LButtonDownCell ||
                            (LCellData.CellType == ctCheckButton && LCellData.IsChecked))
                        {
                            LEdgeType = EDGE_SUNKEN;
                        }

                        LDC.DrawEdge(&LRect, LEdgeType, BF_RECT);


                        // 顯示按鈕被focus的框
                        if (LCell == m_FocusedCell)
                        {
                            LRect.DeflateRect(5, 5);
                            LDC.DrawFocusRect(&LRect);
                        }

                        *pResult = CDRF_SKIPDEFAULT;
                    }
                    break;

                case ctCheck :
                    {
                        // 顯示按鈕被focus的框
                        if (LCell == m_FocusedCell)
                        {
                            LRect.DeflateRect(5, 5);
                            LDC.DrawFocusRect(&LRect);
                        }


                        CellRectToCheckBoxItemRect(&LRect, &LRect);

                        // 塗上被disable的顏色
                        if (!LCellData.IsEnabled || LCell == m_LButtonDownCell)
                            LDC.FillRect(&LRect, &CBrush(GetSysColor(COLOR_BTNFACE)));


                        // 畫出邊框
                        LDC.DrawEdge(&LRect, EDGE_SUNKEN, BF_RECT);


                        // 畫出勾
                        if (LCellData.IsChecked)
                        {
                            CPen    LPen(PS_SOLID, 2, GetSysColor(LCellData.IsEnabled ? COLOR_BTNTEXT : COLOR_GRAYTEXT));

                            DECLARE_GdiSelectPen(LDC, &LPen);

                            LDC.MoveTo(LRect.left + 3, LRect.top + 5);
                            LDC.LineTo(LRect.left + 6, LRect.bottom - 4);
                            LDC.MoveTo(LRect.left + 5, LRect.bottom - 4);
                            LDC.LineTo(LRect.right - 3, LRect.top + 3);
                        }

                        *pResult = CDRF_SKIPDEFAULT;
                    }
                    break;

                case ctNormal :
                    {
                        LDC.FillRect(&LRect, &CBrush(LCellData.BkColor));
                        LRect.DeflateRect(5, 5);

                        LDC.SetBkMode(TRANSPARENT);
                        LDC.SetTextColor(LCellData.IsEnabled ? LCellData.TextColor : GetSysColor(COLOR_GRAYTEXT));
                        LDC.DrawText(GetItemText(LCell.y, LCell.x), &LRect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);

                        if (LCell == m_FocusedCell)
                            LDC.DrawFocusRect(&LRect);

                        *pResult = CDRF_SKIPDEFAULT;
                    }
                    break;
                }

                LDC.Detach();
            } // if (LCell.x < m_CellDatas.size() && LCell.y < m_CellDatas[LCell.x].size())
        } // case CDDS_ITEMPREPAINT | CDDS_SUBITEM :
        break;
    }
}

void    CYCListCtrl::OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    // TODO: Add your control notification handler code here
    for (int I = 0; I < GetHeaderCtrl()->GetItemCount(); I ++)
    {
        m_CellDatas[I].insert(m_CellDatas[I].begin() + pNMLV->iItem, DefaultCellData());
        m_CellDatas[I][pNMLV->iItem].CellType = m_ColCellTypes[I];
    }


    if (GetSelectionMark() == -1 && GetItemCount() > 0)
    {
        SetSelectionMark(0);
        SetItemState(0, LVIS_SELECTED  | LVIS_FOCUSED | LVIS_ACTIVATING, LVIS_SELECTED  | LVIS_FOCUSED | LVIS_ACTIVATING);
    }
    else
    {
        if (m_FocusedCell.y >= pNMLV->iItem)
            SetFocusedCell(CPoint(m_FocusedCell.x, m_FocusedCell.y + 1));

        else if (m_FocusedCell.x == -1 || m_FocusedCell.y == -1)
            SetFocusedCell(CPoint(0, 0));
    }

    *pResult = 0;
}

void    CYCListCtrl::OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    // TODO: Add your control notification handler code here
    for (int I = 0; I < GetHeaderCtrl()->GetItemCount(); I ++)
        m_CellDatas[I].erase(m_CellDatas[I].begin() + pNMLV->iItem);

    if (m_FocusedCell.y > pNMLV->iItem)
        SetFocusedCell(CPoint(m_FocusedCell.x, m_FocusedCell.y - 1));

    else if (m_FocusedCell.y == pNMLV->iItem)
        SetFocusedCell(CPoint(-1, -1));

    *pResult = 0;
}

void    CYCListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: Add your control notification handler code here
    if (pNMLV->uNewState & LVIS_SELECTED)
        SetFocusedCell(CPoint((m_FocusedCell.x == -1) ? 0 : m_FocusedCell.x, pNMLV->iItem));

    *pResult = 0;
}

//============================
int     CYCListCtrl::RowHeight() const
{
    return m_RowHeight;
}

void    CYCListCtrl::SetRowHeight(int AValue)
{
    if (m_RowHeight != AValue)
    {
        m_RowHeight = AValue;

        if (m_hWnd)
        {
            ModifyStyle(0, LVS_OWNERDRAWFIXED);

            CRect LRect;

            GetWindowRect(&LRect);
            LRect.bottom -= 1;

            SetWindowPos(NULL, 0, 0, LRect.Width(), LRect.Height(), SWP_NOMOVE);

            LRect.bottom += 1;
            SetWindowPos(NULL, 0, 0, LRect.Width(), LRect.Height(), SWP_NOMOVE);

            ModifyStyle(LVS_OWNERDRAWFIXED, 0);
        }
    }
}

CYCListCtrl::enmCellType
/**/    CYCListCtrl::CellType(int ACellX, int ACellY) const
{
    return m_CellDatas[ACellX][ACellY].CellType;
}

void    CYCListCtrl::SetCellType(int ACellX, int ACellY, enmCellType AValue)
{
    if (m_CellDatas[ACellX][ACellY].CellType != AValue)
    {
        m_CellDatas[ACellX][ACellY].CellType = AValue;

        if (m_hWnd)
            Invalidate();
    }
}

void    CYCListCtrl::SetColumnCellType(int ACellX, enmCellType AValue)
{
    TCellDataDeque  &LDeque = *(m_CellDatas.begin() + ACellX);

    for (TCellDataDeque::iterator   LIter = LDeque.begin();
        LIter != LDeque.end(); LIter ++)
    {
        LIter->CellType = AValue;
    }

    m_ColCellTypes[ACellX] = AValue;

    RedrawColumn(ACellX);
}

void    CYCListCtrl::SetRowCellType(int ACellY, enmCellType AValue)
{
    for (std::deque<TCellDataDeque>::iterator   LIter = m_CellDatas.begin();
        LIter != m_CellDatas.end(); LIter ++)
    {
        TCellDataDeque  &LDeque = *LIter;

        LDeque[ACellY].CellType = AValue;
    }

    RedrawRow(ACellY);
}

bool    CYCListCtrl::IsCellChecked(int ACellX, int ACellY) const
{
    return m_CellDatas[ACellX][ACellY].IsChecked;
}

void    CYCListCtrl::SetIsCellChecked(int ACellX, int ACellY, bool AValue)
{
    if (AValue != m_CellDatas[ACellX][ACellY].IsChecked)
    {
        m_CellDatas[ACellX][ACellY].IsChecked = AValue;

        RedrawCell(ACellX, ACellY);
    }
}

void    CYCListCtrl::SetColumnIsCellChecked(int ACellX, bool AValue)
{
    TCellDataDeque  &LDeque = *(m_CellDatas.begin() + ACellX);

    for (TCellDataDeque::iterator LIter = LDeque.begin();
        LIter != LDeque.end(); LIter ++)
    {
        LIter->IsChecked = AValue;
    }

    RedrawColumn(ACellX);
}

void    CYCListCtrl::SetRowIsCellChecked(int ACellY, bool AValue)
{
    for (std::deque<TCellDataDeque>::iterator   LIter = m_CellDatas.begin();
        LIter != m_CellDatas.end(); LIter ++)
    {
        TCellDataDeque  &LDeque = *LIter;

        LDeque[ACellY].IsChecked = AValue;
    }

    RedrawRow(ACellY);
}

bool    CYCListCtrl::IsCellEnabled(int ACellX, int ACellY) const
{
    return m_CellDatas[ACellX][ACellY].IsEnabled;
}

void    CYCListCtrl::SetIsCellEnabled(int ACellX, int ACellY, bool AValue)
{
    if (AValue != m_CellDatas[ACellX][ACellY].IsEnabled)
    {
        m_CellDatas[ACellX][ACellY].IsEnabled = AValue;

        RedrawCell(ACellX, ACellY);
    }
}

void    CYCListCtrl::SetColumnIsCellEnabled(int ACellX, bool AValue)
{
    TCellDataDeque  &LDeque = *(m_CellDatas.begin() + ACellX);

    for (TCellDataDeque::iterator LIter = LDeque.begin();
        LIter != LDeque.end(); LIter ++)
    {
        LIter->IsEnabled = AValue;
    }

    RedrawColumn(ACellX);
}

void    CYCListCtrl::SetRowIsCellEnabled(int ACellY, bool AValue)
{
    for (std::deque<TCellDataDeque>::iterator   LIter = m_CellDatas.begin();
        LIter != m_CellDatas.end(); LIter ++)
    {
        TCellDataDeque  &LDeque = *LIter;

        LDeque[ACellY].IsEnabled = AValue;
    }

    RedrawRow(ACellY);
}

COLORREF
/**/    CYCListCtrl::CellBkColor(int ACellX, int ACellY) const
{
    return m_CellDatas[ACellX][ACellY].BkColor;
}

void    CYCListCtrl::SetCellBkColor(int ACellX, int ACellY, COLORREF AValue)
{
    if (AValue != m_CellDatas[ACellX][ACellY].BkColor)
    {
        m_CellDatas[ACellX][ACellY].BkColor = AValue;

        RedrawCell(ACellX, ACellY);
    }
}

void    CYCListCtrl::SetColumnCellBkColor(int ACellX, COLORREF AValue)
{
    TCellDataDeque  &LDeque = *(m_CellDatas.begin() + ACellX);

    for (TCellDataDeque::iterator LIter = LDeque.begin();
        LIter != LDeque.end(); LIter ++)
    {
        LIter->BkColor = AValue;
    }

    RedrawColumn(ACellX);
}

void    CYCListCtrl::SetRowCellBkColor(int ACellY, COLORREF AValue)
{
    for (std::deque<TCellDataDeque>::iterator   LIter = m_CellDatas.begin();
        LIter != m_CellDatas.end(); LIter ++)
    {
        TCellDataDeque  &LDeque = *LIter;

        LDeque[ACellY].BkColor = AValue;
    }

    RedrawRow(ACellY);
}

COLORREF
/**/    CYCListCtrl::CellTextColor(int ACellX, int ACellY) const
{
    return m_CellDatas[ACellX][ACellY].TextColor;
}

void    CYCListCtrl::SetCellTextColor(int ACellX, int ACellY, COLORREF AValue)
{
    if (AValue != m_CellDatas[ACellX][ACellY].TextColor)
    {
        m_CellDatas[ACellX][ACellY].TextColor = AValue;

        RedrawCell(ACellX, ACellY);
    }
}

void    CYCListCtrl::SetColumnCellTextColor(int ACellX, COLORREF AValue)
{
    TCellDataDeque  &LDeque = *(m_CellDatas.begin() + ACellX);

    for (TCellDataDeque::iterator LIter = LDeque.begin();
        LIter != LDeque.end(); LIter ++)
    {
        LIter->TextColor = AValue;
    }

    RedrawColumn(ACellX);
}

void    CYCListCtrl::SetRowCellTextColor(int ACellY, COLORREF AValue)
{
    for (std::deque<TCellDataDeque>::iterator   LIter = m_CellDatas.begin();
        LIter != m_CellDatas.end(); LIter ++)
    {
        TCellDataDeque  &LDeque = *LIter;

        LDeque[ACellY].TextColor = AValue;
    }

    RedrawRow(ACellY);
}

//============================
const CYCListCtrl::strCellData&
/**/    CYCListCtrl::DefaultCellData()
{
    static const strCellData  LCD = { ctNormal, true, false, clWhite, GetSysColor(COLOR_BTNTEXT) };

    return LCD;
}

void    CYCListCtrl::CellRectToCheckBoxItemRect(LPCRECT   ACellRect, LPRECT ACheckBoxRect)
{
    const CRect LSubItemRect(ACellRect);

    ACheckBoxRect->left   = LSubItemRect.CenterPoint().x - 7;
    ACheckBoxRect->top    = LSubItemRect.CenterPoint().y - 7;
    ACheckBoxRect->right  = ACheckBoxRect->left + 13;
    ACheckBoxRect->bottom = ACheckBoxRect->top  + 13;
}

void    CYCListCtrl::RedrawCell(int ACellX, int ACellY)
{
    CRect   LRect;

    GetThisSubItemRect(ACellX, ACellY, LRect);

    InvalidateRect(LRect);
    UpdateWindow();
}

void    CYCListCtrl::RedrawColumn(int ACellX)
{
    CRect   LRect;

    GetThisSubItemRect(ACellX, 0, LRect);

    CRect   LClientRect;

    GetClientRect(&LClientRect);

    LRect.top    = LClientRect.top;
    LRect.bottom = LClientRect.bottom;

    InvalidateRect(&LRect);
}

void    CYCListCtrl::RedrawRow(int ACellY)
{
    if (ACellY >= GetTopIndex() && ACellY <= GetTopIndex() + GetCountPerPage())
    {
        POINT   LPnt;

        GetOrigin(&LPnt);

        CRect   LRect;

        GetItemRect(ACellY, LRect, LVIR_BOUNDS);

        CRect   LClientRect;

        GetClientRect(&LClientRect);

        LRect.left  = LClientRect.left;
        LRect.right = LClientRect.right;

        InvalidateRect(&LRect);
    }
}    

void    CYCListCtrl::SetFocusedCell(const POINT &ACell)
{
    if (m_FocusedCell.x != ACell.x || m_FocusedCell.y != ACell.y)
    {
        const POINT LOldCell = m_FocusedCell;

        m_FocusedCell = ACell;

        if (LOldCell.x != -1 && LOldCell.y != -1)
            RedrawCell(LOldCell.x, LOldCell.y);

        if (m_FocusedCell.x != -1 && m_FocusedCell.y != -1)
            RedrawCell(m_FocusedCell.x, m_FocusedCell.y);
    }
}

void    CYCListCtrl::OffsetFocusedCell(int AOffsetX, int AOffsetY)
{
    if (AOffsetX || AOffsetY)
    {
        const int LX = m_FocusedCell.x + AOffsetX;
        const int LY = m_FocusedCell.y + AOffsetY;

        if (LX >= 0 && LX < GetHeaderCtrl()->GetItemCount() &&
            LY >= 0 && LY < GetItemCount())
        {
            SetFocusedCell(CPoint(LX, LY));
        }
    }
}

void    CYCListCtrl::GetThisSubItemRect(int ACellX, int ACellY, OUT CRect &ARect)
{
    CRect   LRect;

    GetSubItemRect(ACellY, ACellX, LVIR_BOUNDS, LRect);

    if (ACellX == 0)
        LRect.right = LRect.left + GetColumnWidth(0);

    ARect = LRect;
}
