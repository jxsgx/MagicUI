//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicEdit.cpp												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û������༭��ʵ��
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Include/MagicUI/MagicEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicEdit,CEdit);

CMagicEdit::CMagicEdit()
{
	//������ɫ
	m_textColor=m_textColorFocus=m_textColorHover=GetSysColor(COLOR_BTNTEXT);
	m_textColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	//������ɫ
	m_backColor=m_backColorFocus=m_backColorHover=m_backColorDisabled=GetSysColor(COLOR_3DHIGHLIGHT);

	//�߿���ɫ
	m_borderColor=m_borderColorFocus=m_borderColorHover=m_borderColorDisabled=GetSysColor(COLOR_BTNTEXT);
	
	m_bVisible=TRUE;//����
	m_bEnable=TRUE;//����
	m_bHover=FALSE;//��ͣ
	m_bFocus=FALSE;//�۽�

	m_hCursor=LoadCursor(NULL,IDC_IBEAM);//I�͹��
}

CMagicEdit::~CMagicEdit()
{
}

BEGIN_MESSAGE_MAP(CMagicEdit, CEdit)
	//{{AFX_MSG_MAP(CMagicEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicEdit message handlers

//���ش�������
BOOL CMagicEdit::Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(dwStyle & WS_DISABLED)
		m_bEnable=FALSE;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD;
	dwStyle|=WS_TABSTOP;

	return CEdit::Create(dwStyle,rect,pParentWnd,nID);
}

//�Զ�����
BOOL CMagicEdit::AutoLoad(UINT nID, CWnd* pParent)
{
	m_nID=nID;
	m_pWnd=pParent;
	CStatic* pPic=(CStatic *)pParent->GetDlgItem(nID);
	
	CRect rect;
	pPic->GetClientRect(&rect);
	pPic->ClientToScreen(&rect);
	pParent->ScreenToClient(&rect);

	pPic->ShowWindow(SW_HIDE);
	DWORD dwStyle=WS_CHILD|WS_VISIBLE|WS_TABSTOP;

	return CEdit::Create(dwStyle,rect,pParent,nID);
}

HBRUSH CMagicEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	if(!m_bVisible)
	{
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH hbr=(HBRUSH)GetStockObject(NULL_BRUSH);
		return hbr;
	}

	CRect rect;
	GetClientRect(&rect);
	rect+=CRect(1,1,1,1);

	COLORREF textColor;
	COLORREF backColor;
	COLORREF borderColor;
	if(m_bEnable)
	{
		if(m_bHover)//��ͣ
		{
			textColor=m_textColorHover;
			backColor=m_backColorHover;
			borderColor=m_borderColorHover;
		}
		else
		{
			if(m_bFocus)//�۽�
			{
				textColor=m_textColorFocus;
				backColor=m_backColorFocus;
				borderColor=m_borderColorFocus;
			}
			else//����
			{
				textColor=m_textColor;
				backColor=m_backColor;
				borderColor=m_borderColor;
			}
		}
	}
	else//ʧЧ
	{
		textColor=m_textColorDisabled;
		backColor=m_backColorDisabled;
		borderColor=m_borderColorDisabled;
	}

	//����
	if(m_brBkgnd.m_hObject)
		m_brBkgnd.DeleteObject();
	m_brBkgnd.CreateSolidBrush(backColor);
	//ǰ��
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(textColor);
	//�߿�
	if(m_borderColor!=-1)
	{
		pDC->Draw3dRect(rect,borderColor,borderColor);
	}
	return (HBRUSH)m_brBkgnd.m_hObject;

	//return NULL;
}

void CMagicEdit::OnMouseMove(UINT nFlags, CPoint point) 
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

	CEdit::OnMouseMove(nFlags, point);
}

LRESULT CMagicEdit::OnMouseLeave(WPARAM wParam,LPARAM lParam)   
{
	m_bHover=FALSE;
	Invalidate();

	return TRUE;
}

void CMagicEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_bFocus=TRUE;
	Invalidate();
}

void CMagicEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	m_bFocus=FALSE;
	Invalidate();
}

BOOL CMagicEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(m_hCursor);
	return true;

	//return CEdit::OnSetCursor(pWnd, nHitTest, message);
}

void CMagicEdit::SetCursor(HCURSOR hCursor)
{
	if(hCursor)
	{
		m_hCursor=hCursor;
		Invalidate();
	}
}

//��ȡҪ��������ĸ����ڱ���
void CMagicEdit::GetBackgndMask()
{
		CWnd *pParentWnd=GetParent();
		CClientDC pdc(pParentWnd);

		CRect rc;
		GetClientRect(&rc);
		ClientToScreen(&rc);
		pParentWnd->ScreenToClient(&rc);
		rc+=CRect(1,1,1,1);

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
void CMagicEdit::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

BOOL CMagicEdit::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();

	CRect rect;
	GetClientRect(&rect);
	rect+=CRect(1,1,1,1);
	//�汳��
	DrawOriginalBitmap(pDC,rect,m_backgndMask);

	return TRUE;
}

//��������ɫ
void CMagicEdit::SetTextColor(COLORREF textColor)
{
	m_textColor=textColor;
	m_textColorHover=textColor;
	m_textColorFocus=textColor;
	m_textColorDisabled=textColor;

	Invalidate();
}

void CMagicEdit::SetTextColor(COLORREF textColor,COLORREF textColorHover,
				COLORREF textColorFocus,COLORREF textColorDisabled)
{
	if(textColor!=-1) m_textColor=textColor;
	if(textColorHover!=-1) m_textColorHover=textColorHover;
	if(textColorFocus!=-1) m_textColorFocus=textColorFocus;
	if(textColorDisabled!=-1) m_textColorDisabled=textColorDisabled;

	Invalidate();
}

//�豳����ɫ
void CMagicEdit::SetBackColor(COLORREF backColor)
{
	m_backColor=backColor;
	m_backColorHover=backColor;
	m_backColorFocus=backColor;
	m_backColorDisabled=backColor;

	Invalidate();
}

void CMagicEdit::SetBackColor(COLORREF backColor,COLORREF backColorHover,
				COLORREF backColorFocus,COLORREF backColorDisabled)
{
	if(backColor!=-1) m_backColor=backColor;
	if(backColorHover!=-1) m_backColorHover=backColorHover;
	if(backColorFocus!=-1) m_backColorFocus=backColorFocus;
	if(backColorDisabled!=-1) m_backColorDisabled=backColorDisabled;

	Invalidate();
}

//��߿���ɫ
void CMagicEdit::SetBorderColor(COLORREF borderColor)
{
	m_borderColor=borderColor;
	m_borderColorHover=borderColor;
	m_borderColorFocus=borderColor;
	m_borderColorDisabled=borderColor;

	Invalidate();
}

void CMagicEdit::SetBorderColor(COLORREF borderColor,COLORREF borderColorHover,
				COLORREF borderColorFocus,COLORREF borderColorDisabled)
{
	m_borderColor=borderColor;
	m_borderColorHover=borderColorHover;
	m_borderColorFocus=borderColorFocus;
	m_borderColorDisabled=borderColorDisabled;

	Invalidate();
}

BOOL CMagicEdit::EnableWindow(BOOL bEnable)
{
	m_bEnable=bEnable;
	return CEdit::EnableWindow(bEnable);
}

BOOL CMagicEdit::GetEnable()
{
	return m_bEnable;
}

BOOL CMagicEdit::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
	{
		m_bVisible=FALSE;
		GetWindowText(m_strText);
		SetWindowText("");
		CEdit::EnableWindow(FALSE);
	}
	else
	{
		m_bVisible=TRUE;
		SetWindowText(m_strText);
		EnableWindow(m_bEnable);
	}

	Invalidate();

	return TRUE;
}

BOOL CMagicEdit::GetVisible()
{
	return m_bVisible;
}

//��������
void CMagicEdit::SetFont(int nFontSize,CString strFontName,BOOL bBold,BOOL bItalic,
					BOOL bUnderline,BOOL bStrikeOut)
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	DWORD dwStyle=GetStyle();

	int nHeight=MulDiv(nFontSize,GetDeviceCaps(dc.m_hDC,LOGPIXELSY),72);
	if(!(dwStyle&ES_MULTILINE))
	if(nHeight>rect.Height()) nHeight=rect.Height();

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

	CEdit::SetFont(&m_font);

	Invalidate();
}

//���뷽ʽ
void CMagicEdit::SetAlign(UINT nAlign)
{
	ModifyStyle(0,nAlign);
}

void CMagicEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CMagicEdit::SetPassword(BOOL bPassword)
{
	DWORD dwStyle=GetClassLong(m_hWnd,GCL_STYLE);
	if(bPassword)
	{
		dwStyle|=ES_PASSWORD;
		SetPasswordChar('*');
	}
	else
		dwStyle&=~ES_PASSWORD;
	SetClassLong(m_hWnd,GCL_STYLE,dwStyle);
}