//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicFillRegion.cpp											[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û�����������ʵ��
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Include/MagicUI/MagicFillRegion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicFillRegion,CStatic);

CMagicFillRegion::CMagicFillRegion()
{
	m_bVisible=TRUE;//�ؼ�����
	m_nAlpha=0;//͸����
	m_backColor=RGB(236,243,246);//����ɫ
	m_borderColor=RGB(0,136,228);//�߿�ɫ
	m_borderWidth=2;//�߿��
	m_nCorner=10;//Բ�Ǵ�С
}

CMagicFillRegion::~CMagicFillRegion()
{
}


BEGIN_MESSAGE_MAP(CMagicFillRegion, CStatic)
	//{{AFX_MSG_MAP(CMagicFillRegion)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicFillRegion message handlers

//���ش�������
BOOL CMagicFillRegion::Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD|SS_USERITEM;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create("",dwStyle,rect,pParentWnd,nID);
}
HBRUSH CMagicFillRegion::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	CRect rc;
	GetClientRect(&rc);
	if(!m_bVisible)
	{
		//�汳��
		DrawOriginalBitmap(pDC,rc,m_backgndMask);
		return NULL;
	}

	int clr=(int)(2.55*m_nAlpha);

	//��͸��DC
	CDC alphaNDC;
	alphaNDC.CreateCompatibleDC(pDC);
	//��ɫλͼ
	CBitmap bmpAlphaN;
	bmpAlphaN.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
	alphaNDC.SelectObject(&bmpAlphaN);
	//��ɻҶ�ͼ
	alphaNDC.FillSolidRect(rc,RGB(255-clr,255-clr,255-clr));

	//����ͼDC
	CDC backDC;
	backDC.CreateCompatibleDC(&alphaNDC);
	//��ɱ���ͼ
	backDC.SelectObject(&m_backgndMask);

	//͸��DC
	CDC alphaDC;
	alphaDC.CreateCompatibleDC(pDC);
	//��ɫλͼ
	CBitmap bmpAlpha;
	bmpAlpha.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
	alphaDC.SelectObject(&bmpAlpha);
	//��ɻҶ�ͼ
	alphaDC.FillSolidRect(rc,RGB(clr,clr,clr));

	//ԭͼDC
	CDC srcDC;
	srcDC.CreateCompatibleDC(&alphaDC);
	//��ɫλͼ
	CBitmap bmpSrc;
	bmpSrc.CreateCompatibleBitmap(&alphaDC,rc.Width(),rc.Height());
	srcDC.SelectObject(&bmpSrc);
	//ԭͼ��ˢ
	CBrush brSrc;
	brSrc.CreateSolidBrush(m_backColor);
	srcDC.SelectObject(&brSrc);
	//ԭͼ����
	CPen penSrc;
	penSrc.CreatePen(PS_SOLID,m_borderWidth,m_borderColor);
	srcDC.SelectObject(&penSrc);
	//���ԭͼ
	srcDC.RoundRect(rc,CPoint(m_nCorner,m_nCorner));

	//DC����=>(alphaNDC OR backDC) AND (alphaDC OR srcDC)
	alphaNDC.BitBlt(0,0,rc.Width(),rc.Height(),&backDC,0,0,SRCPAINT);
	alphaDC.BitBlt(0,0,rc.Width(),rc.Height(),&srcDC,0,0,SRCPAINT);

	pDC->BeginPath();
	pDC->RoundRect(rc,CPoint(m_nCorner,m_nCorner));
	pDC->EndPath();
	pDC->SelectClipPath(RGN_AND);

	pDC->BitBlt(0,0,rc.Width(),rc.Height(),&alphaNDC,0,0,SRCCOPY);
	pDC->BitBlt(0,0,rc.Width(),rc.Height(),&alphaDC,0,0,SRCAND);
	
	return NULL;
}

//��ȡҪ��������ĸ����ڱ���
void CMagicFillRegion::GetBackgndMask()
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
void CMagicFillRegion::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

BOOL CMagicFillRegion::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();

	return TRUE;
}

BOOL CMagicFillRegion::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
		m_bVisible=FALSE;
	else
		m_bVisible=TRUE;

	Invalidate();

	return TRUE;
}

BOOL CMagicFillRegion::GetVisible()
{
	return m_bVisible;
}

//�豳����ɫ
void CMagicFillRegion::SetBackColor(COLORREF backColor)
{
	m_backColor=backColor;
	Invalidate();
}

//��߿���ɫ
void CMagicFillRegion::SetBorderColor(COLORREF borderColor)
{
	m_borderColor=borderColor;
	Invalidate();
}

//��߿���
void CMagicFillRegion::SetBorderWidth(int nWidth)
{
	m_borderWidth=nWidth;
	Invalidate();
}

//��Բ�Ǵ�С
void CMagicFillRegion::SetCorner(int nSize)
{
	m_nCorner=nSize;
	Invalidate();
}

//��͸����
void CMagicFillRegion::SetAlpha(int nAlpha)
{
	m_nAlpha=nAlpha;
	Invalidate();
}