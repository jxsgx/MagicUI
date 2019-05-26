//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicGroup.cpp												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û������Ⱥ���ʵ��
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Include/MagicUI/MagicGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicGroup,CStatic);

CMagicGroup::CMagicGroup()
{
	m_textColor=GetSysColor(COLOR_BTNTEXT);
	m_nAlign=SS_LEFT;
	m_bVisible=TRUE;//�ؼ�����
	m_bEnable=TRUE;//�ؼ�����
}

CMagicGroup::~CMagicGroup()
{
}


BEGIN_MESSAGE_MAP(CMagicGroup, CStatic)
	//{{AFX_MSG_MAP(CMagicGroup)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicGroup message handlers

//���ش�������
BOOL CMagicGroup::Create(LPCTSTR lpszCaption, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(dwStyle & WS_DISABLED)
		m_bEnable=FALSE;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD|SS_USERITEM;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create(lpszCaption,dwStyle,rect,pParentWnd,nID);
}

//�Զ�����
BOOL CMagicGroup::AutoLoad(UINT nID, CWnd* pParent)
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

	DWORD dwStyle=WS_CHILD|WS_VISIBLE|SS_USERITEM;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create(str,dwStyle,rect,pParent,nID);
}
HBRUSH CMagicGroup::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	CRect rc;
	GetClientRect(&rc);
	//�汳��
	DrawOriginalBitmap(pDC,rc,m_backgndMask);
	if(!m_bVisible)
		return NULL;

	int y;
	switch(m_nAlign)
	{
	case SS_LEFT:
		y=5;
		break;
	case SS_RIGHT:
		y=rc.Width()-m_szText.cx-5;
		break;
	case SS_CENTER:
		y=(rc.Width()-m_szText.cx)/2;
		break;
	}
	CRect rcText=CRect(CPoint(y,0),m_szText);
	CRect rcBox=rc+CRect(0,-m_szText.cy/2,0,0);

	CString str;
	GetWindowText(str);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_textColor);
	pDC->DrawText(str,rcText,DT_LEFT|DT_TOP);
	pDC->BeginPath();
	pDC->Rectangle(rcText);
	pDC->EndPath();
	pDC->SelectClipPath(RGN_DIFF);
	pDC->DrawEdge(rcBox,EDGE_ETCHED,BF_RECT);
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}

//��������ɫ
void CMagicGroup::SetTextColor(COLORREF textColor)
{
	m_textColor=textColor;

	Invalidate();
}

//���뷽ʽ
void CMagicGroup::SetAlign(UINT nAlign)
{
	m_nAlign=nAlign;

	Invalidate();
}

//��������
void CMagicGroup::SetFont(int nFontSize,CString strFontName,BOOL bBold,BOOL bItalic,
					BOOL bUnderline,BOOL bStrikeOut)
{
	CClientDC dc(this);
	int nHeight=MulDiv(nFontSize,GetDeviceCaps(dc.m_hDC,LOGPIXELSY),72);

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

	Invalidate();
}

//��ȡҪ��������ĸ����ڱ���
void CMagicGroup::GetBackgndMask()
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
void CMagicGroup::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

BOOL CMagicGroup::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();

	CString str;
	GetWindowText(str);
	pDC->SelectObject(&m_font);
	m_szText=pDC->GetTextExtent(str);

	return TRUE;
}

BOOL CMagicGroup::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
		m_bVisible=FALSE;
	else
		m_bVisible=TRUE;

	Invalidate();

	return TRUE;
}

BOOL CMagicGroup::GetVisible()
{
	return m_bVisible;
}
