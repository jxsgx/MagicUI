//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicCombo.cpp												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û������������ʵ��
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Include/MagicUI/MagicCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicCombo,CComboBox);

CMagicCombo::CMagicCombo()
{
	m_bVisible=TRUE;//����
	m_bEnable=TRUE;//����
	m_bHover=FALSE;//��ͣ
	m_bFocus=FALSE;//�۽�
	m_hCursor=LoadCursor(NULL,IDC_ARROW);//��ͷ���
	m_pWnd=NULL;//������ָ��
	
	m_bBold=FALSE;//����
	m_bItalic=FALSE;//б��
	m_bUnderline=FALSE;//�»���
	m_bStrikeOut=FALSE;//ɾ����

	m_nFontSize=10;//�����С
	m_strFontName="����";//��������

	//�ı���ɫ
	m_textColor=m_textColorHover=GetSysColor(COLOR_BTNTEXT);
	m_textColorDisabled=GetSysColor(COLOR_GRAYTEXT);
	//������ɫ
	m_backColor=m_backColorHover=m_backColorDisabled=GetSysColor(COLOR_3DHILIGHT);
	//�߿���ɫ
	m_borderColor=GetSysColor(COLOR_GRAYTEXT);
	m_brBkgnd.CreateSolidBrush(COLOR_GRAYTEXT);
	//��ť����
	m_btnColor=GetSysColor(COLOR_3DFACE);
}

CMagicCombo::~CMagicCombo()
{
}


BEGIN_MESSAGE_MAP(CMagicCombo, CComboBox)
	//{{AFX_MSG_MAP(CMagicCombo)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT(CBN_SETFOCUS, OnSetfocus)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillfocus)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicCombo message handlers

//������ť
BOOL CMagicCombo::Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(dwStyle & WS_DISABLED)
		m_bEnable=FALSE;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD;
	dwStyle|=WS_TABSTOP;
	dwStyle|=WS_VSCROLL;
	dwStyle|=CBS_DROPDOWNLIST;
	dwStyle|=CBS_OWNERDRAWVARIABLE;

	return CComboBox::Create(dwStyle,rect,pParentWnd,nID);
}

//�Զ�����
BOOL CMagicCombo::AutoLoad(UINT nID, CWnd* pParent)
{
	m_nID=nID;
	m_pWnd=pParent;
	CComboBox* pCombo=(CComboBox *)pParent->GetDlgItem(nID);
	
	CRect rect;
	pCombo->GetClientRect(&rect);
	pCombo->ClientToScreen(&rect);
	pParent->ScreenToClient(&rect);

	pCombo->ShowWindow(SW_HIDE);

	return CComboBox::Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|CBS_DROPDOWNLIST|CBS_OWNERDRAWVARIABLE, rect, pParent, nID);
}

int CMagicCombo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	
	return 0;
}

void CMagicCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect(lpDrawItemStruct->rcItem);
	UINT nItemID=lpDrawItemStruct->itemID;
	UINT nItemAction=lpDrawItemStruct->itemAction;
	DWORD dwItemData=lpDrawItemStruct->itemData;

	CBrush brush;
	CString str;
	static CRect rcSel(0,0,0,0);
	static CString strSel="";
	pDC->SetBkMode(TRANSPARENT);
	switch(nItemAction)
	{
	case ODA_DRAWENTIRE:
		if(nItemID!=-1)
		{
			if((int)nItemID==GetCurSel())
			{
				pDC->FillSolidRect(rect,m_backColorHover);//����(Hover)
				pDC->SetTextColor(m_textColorHover);//�ı�(Hover)
			}
			else
			{
				pDC->FillSolidRect(rect,m_backColor);//����(Normal)
				pDC->SetTextColor(m_textColor);//�ı�(Normal)
			}
			str=m_strAry.GetAt(nItemID);
			pDC->DrawText(str,rect,DT_LEFT);
		}
		else
		{
			pDC->FillSolidRect(rect,m_backColorHover);//����(Hover)
		}
		break;
	case ODA_SELECT:
		pDC->FillSolidRect(rcSel,m_backColor);//����(Normal)
		pDC->SetTextColor(m_textColor);//�ı�(Normal)
		pDC->DrawText(strSel,rcSel,DT_LEFT);

		str=m_strAry.GetAt(nItemID);
		rcSel=rect;
		strSel=str;
		
		pDC->FillSolidRect(rect,m_backColorHover);//����(Hover)
		pDC->SetTextColor(m_textColorHover);//�ı�(Hover)
		pDC->DrawText(str,rect,DT_LEFT);
		break;
	}
}

void CMagicCombo::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	
}

HBRUSH CMagicCombo::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	CRect rect;
	GetClientRect(&rect);

	if(!m_bVisible)
	{
		//�汳��
		DrawOriginalBitmap(pDC,rect,m_backgndMask);
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH hbr=(HBRUSH)GetStockObject(NULL_BRUSH);
		return hbr;
	}
	//���������߿�
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	pDC->FillRect(rect,&brush);
	pDC->Draw3dRect(rect,m_borderColor,m_borderColor);
	//����ť
	rect-=CRect(rect.Width()-17,2,2,2);
	CBrush brBtn;
	brBtn.CreateSolidBrush(m_btnColor);
	pDC->FillRect(rect,&brBtn);//��ť����
	pDC->Draw3dRect(rect,m_borderColor,m_borderColor);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(102,102,102));
	pDC->DrawText("v",rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	if(m_bHover|m_bFocus)
		return (HBRUSH)m_brBkgnd.m_hObject;

	return NULL;
}

int CMagicCombo::AddString( LPCTSTR lpszString )
{
	m_strAry.Add(lpszString);
	return CComboBox::AddString(lpszString);
}
int CMagicCombo::InsertString(int nIndex, LPCTSTR lpszString)
{
	m_strAry.InsertAt(nIndex,lpszString);
	return CComboBox::InsertString(nIndex,lpszString);
}

int CMagicCombo::DeleteString(UINT nIndex)
{
	m_strAry.RemoveAt(nIndex);
	return CComboBox::DeleteString(nIndex);
}

void CMagicCombo::ResetContent()
{
	m_strAry.RemoveAll();
	CComboBox::ResetContent();
}

void CMagicCombo::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	//��׽���
	TRACKMOUSEEVENT tme;   
	tme.cbSize=sizeof(tme);   
	tme.hwndTrack=m_hWnd;   
	tme.dwFlags=TME_LEAVE;   
	_TrackMouseEvent(&tme);

	m_bHover=TRUE;
	Invalidate();

	CComboBox::OnMouseMove(nFlags, point);
}

LRESULT CMagicCombo::OnMouseLeave(WPARAM wParam,LPARAM lParam)   
{
	m_bHover=FALSE;
	Invalidate();

	return TRUE;
}

BOOL CMagicCombo::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bHover)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return CComboBox::OnSetCursor(pWnd, nHitTest, message);
}

//�豳��ɫ
void CMagicCombo::SetBackColor(COLORREF backColor)
{
	m_backColor=backColor;
	m_backColorHover=backColor;
	m_backColorDisabled=backColor;

	Invalidate();
}

void CMagicCombo::SetBackColor(COLORREF backColor,
							   COLORREF backColorHover,COLORREF backColorDisabled)
{
	if(backColor!=-1) m_backColor=backColor;
	if(backColorHover!=-1) m_backColorHover=backColorHover;
	if(backColorDisabled!=-1) m_backColorDisabled=backColorDisabled;

	Invalidate();
}

//��������ɫ
void CMagicCombo::SetTextColor(COLORREF textColor)
{
	m_textColor=textColor;
	m_textColorHover=textColor;
	m_textColorDisabled=textColor;

	Invalidate();
}

void CMagicCombo::SetTextColor(COLORREF textColor,
				COLORREF textColorHover,COLORREF textColorDisabled)
{
	if(textColor!=-1) m_textColor=textColor;
	if(textColorHover!=-1) m_textColorHover=textColorHover;
	if(textColorDisabled!=-1) m_textColorDisabled=textColorDisabled;

	Invalidate();
}

//��߿�ɫ
void CMagicCombo::SetBorderColor(COLORREF borderColor)
{
	m_borderColor=borderColor;
	if(m_brBkgnd.m_hObject)
		m_brBkgnd.DeleteObject();
	m_brBkgnd.CreateSolidBrush(m_borderColor);

	Invalidate();
}

//�谴ť����ɫ
void CMagicCombo::SetBtnColor(COLORREF btnColor)
{
	m_btnColor=btnColor;

	Invalidate();
}

void CMagicCombo::SetCursor(HCURSOR hCursor)
{
	m_hCursor=hCursor;
	Invalidate();
}

//��ȡҪ��������ĸ����ڱ���
void CMagicCombo::GetBackgndMask()
{
		CWnd *pParentWnd=GetParent();
		CClientDC pdc(pParentWnd);

		CRect rc;
		GetClientRect(&rc);
		ClientToScreen(&rc);
		pParentWnd->ScreenToClient(&rc);

		CClientDC dc(this);
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		if(m_backgndMask.m_hObject)
			m_backgndMask.DeleteObject();
		m_backgndMask.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
		memDC.SelectObject(&m_backgndMask);
		memDC.BitBlt(0,0,rc.Width(),rc.Height(),&pdc,rc.left,rc.top,SRCCOPY);
}

//����ͨλͼ
void CMagicCombo::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

BOOL CMagicCombo::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();

	CRect rect;
	GetClientRect(&rect);
	//�汳��
	DrawOriginalBitmap(pDC,rect,m_backgndMask);

	return TRUE;
}

//��������
void CMagicCombo::SetFont(int nFontSize,CString strFontName,BOOL bBold,BOOL bItalic,
					BOOL bUnderline,BOOL bStrikeOut)
{
	m_nFontSize=nFontSize;
	m_strFontName=strFontName;
	m_bBold=bBold;
	m_bItalic=bItalic;
	m_bUnderline=bUnderline;
	m_bStrikeOut=bStrikeOut;

	
	CClientDC dc(this);
	DWORD dwStyle=GetStyle();

	int nHeight=MulDiv(nFontSize,GetDeviceCaps(dc.m_hDC,LOGPIXELSY),72);
	if(!(dwStyle&ES_MULTILINE))
	if(nHeight>16) nHeight=16;

	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfWidth=0;//������(Ĭ��)
	lf.lfHeight=nHeight;//����߶�
	strcpy(lf.lfFaceName,strFontName.GetBuffer(strFontName.GetLength()));//��������
	lf.lfWeight=bBold?FW_BOLD:FW_NORMAL;//����
	lf.lfItalic=bItalic;//б��
	lf.lfUnderline=bUnderline;//�»���
	lf.lfStrikeOut=bStrikeOut;//ɾ����

	if(m_font.m_hObject)
		m_font.DeleteObject();
	m_font.CreateFontIndirect(&lf);

	CComboBox::SetFont(&m_font);

	Invalidate();
}

void CMagicCombo::OnSetfocus() 
{
	// TODO: Add your control notification handler code here
	m_bFocus=TRUE;
	Invalidate();
}

void CMagicCombo::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
	m_bFocus=FALSE;
	Invalidate();
}

BOOL CMagicCombo::EnableWindow(BOOL bEnable)
{
	m_bEnable=bEnable;
	return CComboBox::EnableWindow(bEnable);
}

BOOL CMagicCombo::GetEnable()
{
	return m_bEnable;
}

BOOL CMagicCombo::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
	{
		m_bVisible=FALSE;
		CComboBox::EnableWindow(FALSE);
	}
	else
	{
		m_bVisible=TRUE;
		EnableWindow(m_bEnable);
	}

	Invalidate();

	return TRUE;
}

BOOL CMagicCombo::GetVisible()
{
	return m_bVisible;
}