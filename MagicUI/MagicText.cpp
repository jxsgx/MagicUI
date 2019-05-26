//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicText.cpp											[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û�������ı�ʵ��
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Include/MagicUI/MagicText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicText,CStatic);

CMagicText::CMagicText()
{
	m_nFontSize=10;//�����С
	m_strFontName="����";//��������
	m_nAlign=DT_LEFT;//���뷽ʽ
	m_nStyle=PS_FIXSIZE;

	//����|б��|�»���|ɾ����
	m_bBold=m_bBoldFocus=m_bBoldSelected=m_bBoldDisabled=FALSE;
	m_bItalic=m_bItalicFocus=m_bItalicSelected=m_bItalicDisabled=FALSE;
	m_bUnderline=m_bUnderlineFocus=m_bUnderlineSelected=m_bUnderlineDisabled=FALSE;
	m_bStrikeOut=m_bStrikeOutFocus=m_bStrikeOutSelected=m_bStrikeOutDisabled=FALSE;

	//�ı���ɫ
	m_textColor=m_textColorFocus=m_textColorSelected=GetSysColor(COLOR_BTNTEXT);
	m_textColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	//�߿���ɫ
	m_borderColor=m_borderColorFocus=m_borderColorSelected=m_borderColorDisabled=-1;

	//ѡ����ʾ
	m_borderColorShow=-1;
	m_textColorShow=GetSysColor(COLOR_BTNTEXT);
	m_bBoldShow=m_bItalicShow=m_bUnderlineShow=m_bStrikeOutShow=FALSE;

	m_bVisible=TRUE;//�ؼ�����
	m_bEnable=TRUE;//�ؼ�����
	m_bMouseOn=FALSE;//���������
	m_bMouseDown=FALSE;//��갴��

	m_hCursor=LoadCursor(NULL,IDC_ARROW);//��ͷ���
}

CMagicText::~CMagicText()
{
}


BEGIN_MESSAGE_MAP(CMagicText, CStatic)
	//{{AFX_MSG_MAP(CMagicText)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicText message handlers

//���ش�������
BOOL CMagicText::Create(LPCTSTR lpszCaption, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(dwStyle & WS_DISABLED)
		m_bEnable=FALSE;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create(lpszCaption,dwStyle,rect,pParentWnd,nID);
}

//�Զ�����
BOOL CMagicText::AutoLoad(UINT nID, CWnd* pParent)
{
	m_nID=nID;
	m_pWnd=pParent;
	CStatic* pPic=(CStatic *)pParent->GetDlgItem(nID);
	
	CRect rect;
	pPic->GetClientRect(&rect);
	pPic->ClientToScreen(&rect);
	pParent->ScreenToClient(&rect);

	CString str;
	pPic->GetWindowText(str);
	pPic->ShowWindow(SW_HIDE);

	DWORD dwStyle=WS_CHILD|WS_VISIBLE;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create(str,dwStyle,rect,pParent,nID);
}

//��������
void CMagicText::SetFont(int nFontSize,CString strFontName,BOOL bBold,BOOL bItalic,
					BOOL bUnderline,BOOL bStrikeOut)
{
	m_nFontSize=nFontSize;
	m_strFontName=strFontName;
	m_bBold=bBold;
	m_bItalic=bItalic;
	m_bUnderline=bUnderline;
	m_bStrikeOut=bStrikeOut;

	Invalidate();
}

//��ȡҪ��������ĸ����ڱ���
void CMagicText::GetBackgndMask()
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
void CMagicText::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

void CMagicText::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//�ж�״̬
	if(m_bEnable)
	{
		if(m_bMouseOn)
		{
			if(m_bMouseDown)
			{
				//Selected
				m_borderColorShow=m_borderColorSelected;
				m_textColorShow=m_textColorSelected;
				m_bBoldShow=m_bBoldSelected;
				m_bItalicShow=m_bItalicSelected;
				m_bUnderlineShow=m_bUnderlineSelected;
				m_bStrikeOutShow=m_bStrikeOutSelected;
			}
			else
			{
				//Focus
				m_borderColorShow=m_borderColorFocus;
				m_textColorShow=m_textColorFocus;
				m_bBoldShow=m_bBoldFocus;
				m_bItalicShow=m_bItalicFocus;
				m_bUnderlineShow=m_bUnderlineFocus;
				m_bStrikeOutShow=m_bStrikeOutFocus;
			}
		}
		else
		{
			//Normal
			m_borderColorShow=m_borderColor;
			m_textColorShow=m_textColor;
			m_bBoldShow=m_bBold;
			m_bItalicShow=m_bItalic;
			m_bUnderlineShow=m_bUnderline;
			m_bStrikeOutShow=m_bStrikeOut;
		}
	}
	else
	{
		//Disabled
		m_borderColorShow=m_borderColorDisabled;
		m_textColorShow=m_textColorDisabled;
		m_bBoldShow=m_bBoldDisabled;
		m_bItalicShow=m_bItalicDisabled;
		m_bUnderlineShow=m_bUnderlineDisabled;
		m_bStrikeOutShow=m_bStrikeOutDisabled;
	}
	//��ȡ���ڴ�С
	CRect rect;
	GetClientRect(&rect);

	//�汳��
	DrawOriginalBitmap(&dc,rect,m_backgndMask);
	if(!m_bVisible) return;

	//���ı�
	CString str;
	GetWindowText(str);

	dc.SetBkMode(TRANSPARENT);

	//��������
	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfWidth=0;//������(Ĭ��)
	lf.lfHeight=-MulDiv(m_nFontSize,GetDeviceCaps(dc.m_hDC,LOGPIXELSY),72);//����߶�
	strcpy(lf.lfFaceName,m_strFontName.GetBuffer(m_strFontName.GetLength()));//��������
	lf.lfWeight=m_bBoldShow?FW_BOLD:FW_NORMAL;//����
	lf.lfItalic=m_bItalicShow;//б��
	lf.lfUnderline=m_bUnderlineShow;//�»���
	lf.lfStrikeOut=m_bStrikeOutShow;//ɾ����

	CFont font;
	font.CreateFontIndirect(&lf);
	dc.SelectObject(&font);

	if(!m_bEnable)
	{
		rect.top+=1;
		rect.left+=1;
		dc.SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
		dc.DrawText(str,rect,m_nAlign);
		rect.top-=1;
		rect.left-=1;
	}
	dc.SetTextColor(m_textColorShow);
	dc.DrawText(str,rect,m_nAlign);
	if(m_borderColorShow!=-1)
	{
		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);
		dc.SelectObject(&brush);
		CPen pen(PS_SOLID,1,m_borderColorShow);
		dc.SelectObject(&pen);
		dc.Rectangle(rect);
	}
	// Do not call CStatic::OnPaint() for painting messages
}

void CMagicText::SetStyle(UINT nStyle)
{
	m_nStyle=nStyle;
	Invalidate();
}

BOOL CMagicText::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();
	return TRUE;
}

//��������ɫ
void CMagicText::SetTextColor(COLORREF textColor)
{
	m_textColor=textColor;
	m_textColorFocus=textColor;
	m_textColorSelected=textColor;

	Invalidate();
}

void CMagicText::SetTextColor(COLORREF textColor,COLORREF textColorFocus,
				COLORREF textColorSelected,COLORREF textColorDisabled)
{
	if(textColor!=-1) m_textColor=textColor;
	if(textColorFocus!=-1) m_textColorFocus=textColorFocus;
	if(textColorSelected!=-1) m_textColorSelected=textColorSelected;
	if(textColorDisabled!=-1) m_textColorDisabled=textColorDisabled;

	Invalidate();
}

//��߿���ɫ
void CMagicText::SetBorderColor(COLORREF borderColor)
{
	m_borderColor=borderColor;
	m_borderColorFocus=borderColor;
	m_borderColorSelected=borderColor;

	Invalidate();
}

void CMagicText::SetBorderColor(COLORREF borderColor,COLORREF borderColorFocus,
				COLORREF borderColorSelected,COLORREF borderColorDisabled)
{
	if(borderColor!=-1) m_borderColor=borderColor;
	if(borderColorFocus!=-1) m_borderColorFocus=borderColorFocus;
	if(borderColorSelected!=-1) m_borderColorSelected=borderColorSelected;
	if(borderColorDisabled!=-1) m_borderColorDisabled=borderColorDisabled;

	Invalidate();
}

//���ô���
void CMagicText::SetBold(BOOL bBold,BOOL bBoldFocus,BOOL bBoldSelected,BOOL bBoldDisabled)
{
	m_bBold=bBold;
	m_bBoldFocus=bBoldFocus;
	m_bBoldSelected=bBoldSelected;
	m_bBoldDisabled=bBoldDisabled;

	Invalidate();
}

//����б��
void CMagicText::SetItalic(BOOL bItalic,BOOL bItalicFocus,BOOL bItalicSelected,BOOL bItalicDisabled)
{
	m_bItalic=bItalic;
	m_bItalicFocus=bItalicFocus;
	m_bItalicSelected=bItalicSelected;
	m_bItalicDisabled=bItalicDisabled;

	Invalidate();
}
//�����»���
void CMagicText::SetUnderline(BOOL bUnderline,BOOL bUnderlineFocus,BOOL bUnderlineSelected,BOOL bUnderlineDisabled)
{
	m_bUnderline=bUnderline;
	m_bUnderlineFocus=bUnderlineFocus;
	m_bUnderlineSelected=bUnderlineSelected;
	m_bUnderlineDisabled=bUnderlineDisabled;

	Invalidate();
}
//����ɾ����
void CMagicText::SetStrikeOut(BOOL bStrikeOut,BOOL bStrikeOutFocus,BOOL bStrikeOutSelected,BOOL bStrikeOutDisabled)
{
	m_bStrikeOut=bStrikeOut;
	m_bStrikeOutFocus=bStrikeOutFocus;
	m_bStrikeOutSelected=bStrikeOutSelected;
	m_bStrikeOutDisabled=bStrikeOutDisabled;

	Invalidate();
}

//���뷽ʽ
void CMagicText::SetAlign(UINT nAlign)
{
	m_nAlign=nAlign;
	Invalidate();
}

void CMagicText::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bMouseOn=TRUE;
	Invalidate();

	//��׽���
	TRACKMOUSEEVENT tme;   
	tme.cbSize=sizeof(tme);   
	tme.hwndTrack=m_hWnd;   
	tme.dwFlags=TME_LEAVE;   
	_TrackMouseEvent(&tme);

	CStatic::OnMouseMove(nFlags, point);
}

LRESULT CMagicText::OnMouseLeave(WPARAM wParam,LPARAM lParam)   
{
	m_bMouseOn=FALSE;
	Invalidate();
	return TRUE;
}

void CMagicText::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bMouseDown=TRUE;
	Invalidate();

	CStatic::OnLButtonDown(nFlags, point);
}

void CMagicText::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bMouseDown=FALSE;
	Invalidate();

	CStatic::OnLButtonUp(nFlags, point);
}

BOOL CMagicText::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(m_hCursor);
	return true;

	//return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CMagicText::SetCursor(HCURSOR hCursor)
{
	if(hCursor)
	{
		m_hCursor=hCursor;
		Invalidate();
	}
}

BOOL CMagicText::EnableWindow(BOOL bEnable)
{
	m_bEnable=bEnable;
	Invalidate();

	if(m_bEnable)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return TRUE;
}

BOOL CMagicText::GetEnable()
{
	return m_bEnable;
}

BOOL CMagicText::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
	{
		m_bVisible=FALSE;

		BOOL m_bOldVisible=m_bEnable;
		EnableWindow(FALSE);
		m_bEnable=m_bOldVisible;
	}
	else
	{
		m_bVisible=TRUE;
		EnableWindow(m_bEnable);
	}

	Invalidate();

	return TRUE;
}

BOOL CMagicText::GetVisible()
{
	return m_bVisible;
}
