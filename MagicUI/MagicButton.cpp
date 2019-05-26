//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicButton.cpp												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û�����ⰴťʵ��
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Include/MagicUI/MagicButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicButton,CButton);

CMagicButton::CMagicButton()
{
	m_bVisible=TRUE;//�ؼ�����
	m_bEnable=TRUE;//�ؼ�����
	m_bMask=TRUE;//��������
	m_maskColor=RGB(255,0,255);//����ɫ
	m_bMouseOn=FALSE;//��겻������
	m_bPressed=FALSE;//δ������
	m_bBorder=TRUE;//�б߿�
	m_nStyle=BS_CLICK;//��ʾ��ʽ
	m_hCursor=LoadCursor(NULL,MAKEINTRESOURCE(32649));//���ι��
	m_pWnd=NULL;//������ָ��
	m_nDrawMode=DRAW_MODE_COLOR;//������ɫ
	m_nFontSize=10;//�����С
	m_strFontName="����";//��������
	m_nAlign=DT_CENTER|DT_VCENTER;//���뷽ʽ

	//����|б��|�»���|ɾ����
	m_bBold=m_bBoldFocus=m_bBoldSelected=m_bBoldDisabled=FALSE;
	m_bItalic=m_bItalicFocus=m_bItalicSelected=m_bItalicDisabled=FALSE;
	m_bUnderline=m_bUnderlineFocus=m_bUnderlineSelected=m_bUnderlineDisabled=FALSE;
	m_bStrikeOut=m_bStrikeOutFocus=m_bStrikeOutSelected=m_bStrikeOutDisabled=FALSE;

	//��ť��ɫ��ʼֵ
	m_backColor=m_backColorFocus=m_backColorSelected=m_backColorDisabled=GetSysColor(COLOR_3DFACE);
	m_foreColor=m_foreColorFocus=m_foreColorSelected=GetSysColor(COLOR_BTNTEXT);
	m_foreColorDisabled=GetSysColor(COLOR_GRAYTEXT);
}

CMagicButton::~CMagicButton()
{
}


BEGIN_MESSAGE_MAP(CMagicButton, CButton)
	//{{AFX_MSG_MAP(CMagicButton)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicButton message handlers

//������ť
BOOL CMagicButton::Create(LPCTSTR lpszCaption, DWORD dwStyle,
				const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(dwStyle & WS_DISABLED)
		m_bEnable=FALSE;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD;
	dwStyle|=WS_TABSTOP;
	dwStyle|=BS_OWNERDRAW;

	return CButton::Create(lpszCaption,dwStyle,rect,pParentWnd,nID);
}

//�Զ�����
BOOL CMagicButton::AutoLoad(UINT nID, CWnd* pParent)
{
	m_nID=nID;
	m_pWnd=pParent;
	CButton* pBtn=(CButton *)pParent->GetDlgItem(nID);
	
	CRect rect;
	pBtn->GetClientRect(&rect);
	pBtn->ClientToScreen(&rect);
	pParent->ScreenToClient(&rect);

	CString str;
	pBtn->GetWindowText(str);
	pBtn->ShowWindow(SW_HIDE);

	return CButton::Create(str, WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_OWNERDRAW, rect, pParent, nID);
}

int CMagicButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	
	return 0;
}

//����DrawItem����
void CMagicButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);//��ȡһ��CDCָ��
	CRect rect(lpDrawItemStruct->rcItem);//���尴ť���򲢳�ʼ��
	UINT state = lpDrawItemStruct->itemState;//��ʼ����ť״̬

	//��������
	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfWidth=0;//������(Ĭ��)
	lf.lfHeight=-MulDiv(m_nFontSize,GetDeviceCaps(pDC->m_hDC,LOGPIXELSY),72);//����߶�
	strcpy(lf.lfFaceName,m_strFontName.GetBuffer(m_strFontName.GetLength()));//��������

	//���ñ���ģʽ
	pDC->SetBkMode(TRANSPARENT);
	CString strText;
	GetWindowText(strText);

	//�汳��
	DrawOriginalBitmap(pDC,rect,m_backgndMask);
	if(!m_bVisible) return;

	if (state & ODS_DISABLED)//��ť�û�
	{
		switch(m_nDrawMode)
		{
		case DRAW_MODE_IMAGE:
			DrawImage(pDC,rect,m_backgndPath,INDEX_DISABLED);
			break;
		case DRAW_MODE_BITMAP:
			if(m_bMask)
				DrawTransparentBitmap(pDC,rect,m_backgroundDisabled,m_maskColor);
			else
				DrawOriginalBitmap(pDC,rect,m_backgroundDisabled);
			break;
		case DRAW_MODE_COLOR:
			if(m_backColorDisabled!=-1)
				DrawColor(pDC,rect,m_backColorDisabled);
			break;
		}

		if(m_bBorder)
			pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
		
		lf.lfWeight=m_bBoldDisabled?FW_BOLD:FW_NORMAL;//����
		lf.lfItalic=m_bItalicDisabled;//б��
		lf.lfUnderline=m_bUnderlineDisabled;//�»���
		lf.lfStrikeOut=m_bStrikeOutDisabled;//ɾ����
		
		CFont font;
		font.CreateFontIndirect(&lf);
		pDC->SelectObject(&font);

		if(strText!="")
		{

			CSize sz = pDC->GetTextExtent(strText);
			int x = rect.left + (rect.Width() - sz.cx)/2;
			int y = rect.top + (rect.Height() - sz.cy)/2;

			rect.top += 2;
			rect.left += 2;
			pDC->SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
			pDC->DrawText(strText, rect, m_nAlign);

			rect.top -= 2;
			rect.left -= 2;
			pDC->SetTextColor(m_foreColorDisabled);
			pDC->DrawText(strText, rect, m_nAlign);
		}
	}
	else
	{
		if (m_bMouseOn||m_bPressed)//����ڰ�ť��
		{
			if (state & ODS_SELECTED||m_bPressed)//����
			{
				switch(m_nDrawMode)
				{
				case DRAW_MODE_IMAGE:
					DrawImage(pDC,rect,m_backgndPath,INDEX_SELECTED);
					break;
				case DRAW_MODE_BITMAP:
					if(m_bMask)
						DrawTransparentBitmap(pDC,rect,m_backgroundSelected,m_maskColor);
					else
						DrawOriginalBitmap(pDC,rect,m_backgroundSelected);
					break;
				case DRAW_MODE_COLOR:
					if(m_backColorSelected!=-1)
						DrawColor(pDC,rect,m_backColorSelected);
					break;
				}

				if(m_bBorder)
					pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
						
				lf.lfWeight=m_bBoldSelected?FW_BOLD:FW_NORMAL;//����
				lf.lfItalic=m_bItalicSelected;//б��
				lf.lfUnderline=m_bUnderlineSelected;//�»���
				lf.lfStrikeOut=m_bStrikeOutSelected;//ɾ����
				
				CFont font;
				font.CreateFontIndirect(&lf);
				pDC->SelectObject(&font);

				pDC->SetTextColor(m_foreColorSelected);
			}
			else//δ����
			{
				switch(m_nDrawMode)
				{
				case DRAW_MODE_IMAGE:
					DrawImage(pDC,rect,m_backgndPath,INDEX_FOCUS);
					break;
				case DRAW_MODE_BITMAP:
					if(m_bMask)
						DrawTransparentBitmap(pDC,rect,m_backgroundFocus,m_maskColor);
					else
						DrawOriginalBitmap(pDC,rect,m_backgroundFocus);
					break;
				case DRAW_MODE_COLOR:
					if(m_backColorFocus!=-1)
						DrawColor(pDC,rect,m_backColorFocus);
					break;
				}

				if(m_bBorder)
					pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
						
				lf.lfWeight=m_bBoldFocus?FW_BOLD:FW_NORMAL;//����
				lf.lfItalic=m_bItalicFocus;//б��
				lf.lfUnderline=m_bUnderlineFocus;//�»���
				lf.lfStrikeOut=m_bStrikeOutFocus;//ɾ����
				
				CFont font;
				font.CreateFontIndirect(&lf);
				pDC->SelectObject(&font);

				pDC->SetTextColor(m_foreColorFocus);
			}
		}
		else//��겻�ڰ�ť��
		{
			switch(m_nDrawMode)
			{
			case DRAW_MODE_IMAGE:
				DrawImage(pDC,rect,m_backgndPath,INDEX_NORMAL);
				break;
			case DRAW_MODE_BITMAP:
				if(m_bMask)
					DrawTransparentBitmap(pDC,rect,m_background,m_maskColor);
				else
					DrawOriginalBitmap(pDC,rect,m_background);
				break;
			case DRAW_MODE_COLOR:
				if(m_backColor!=-1)
					DrawColor(pDC,rect,m_backColor);
				break;
			}

			if(m_bBorder)
				pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
					
			lf.lfWeight=m_bBold?FW_BOLD:FW_NORMAL;//����
			lf.lfItalic=m_bItalic;//б��
			lf.lfUnderline=m_bUnderline;//�»���
			lf.lfStrikeOut=m_bStrikeOut;//ɾ����
			
			CFont font;
			font.CreateFontIndirect(&lf);
			pDC->SelectObject(&font);

			pDC->SetTextColor(m_foreColor);
		}

		if(strText!="")
			pDC->DrawText(strText, rect, m_nAlign);
	}
}

void CMagicButton::OnMouseMove(UINT nFlags, CPoint point) 
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

	CButton::OnMouseMove(nFlags, point);
}

LRESULT CMagicButton::OnMouseLeave(WPARAM wParam,LPARAM lParam)   
{
	m_bMouseOn=FALSE;
	Invalidate();
	return TRUE;
}

void CMagicButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_nStyle==BS_PRESS)
		m_bPressed=!m_bPressed;

	CButton::OnLButtonUp(nFlags, point);
}

BOOL CMagicButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bMouseOn)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return CButton::OnSetCursor(pWnd, nHitTest, message);
}

void CMagicButton::SetBackColor(COLORREF backColor)
{
	m_backColor=backColor;
	m_backColorFocus=backColor;
	m_backColorSelected=backColor;

	m_nDrawMode=DRAW_MODE_COLOR;
	Invalidate();
}

void CMagicButton::SetBackColor(COLORREF backColor,COLORREF backColorFocus,
				COLORREF backColorSelected,COLORREF backColorDisabled)
{
	m_backColor=backColor;
	m_backColorFocus=backColorFocus;
	m_backColorSelected=backColorSelected;
	m_backColorDisabled=backColorDisabled;

	m_nDrawMode=DRAW_MODE_COLOR;
	Invalidate();
}

void CMagicButton::SetForeColor(COLORREF foreColor)
{
	m_foreColor=foreColor;
	m_foreColorFocus=foreColor;
	m_foreColorSelected=foreColor;
	Invalidate();
}

void CMagicButton::SetForeColor(COLORREF foreColor,COLORREF foreColorFocus,
				COLORREF foreColorSelected,COLORREF foreColorDisabled)
{
	if(foreColor!=-1) m_foreColor=foreColor;
	if(foreColorFocus!=-1) m_foreColorFocus=foreColorFocus;
	if(foreColorSelected!=-1) m_foreColorSelected=foreColorSelected;
	if(foreColorDisabled!=-1) m_foreColorDisabled=foreColorDisabled;
	Invalidate();
}

//���ô���
void CMagicButton::SetBold(BOOL bBold,BOOL bBoldFocus,BOOL bBoldSelected,BOOL bBoldDisabled)
{
	m_bBold=bBold;
	m_bBoldFocus=bBoldFocus;
	m_bBoldSelected=bBoldSelected;
	m_bBoldDisabled=bBoldDisabled;

	Invalidate();
}
//����б��
void CMagicButton::SetItalic(BOOL bItalic,BOOL bItalicFocus,BOOL bItalicSelected,BOOL bItalicDisabled)
{
	m_bItalic=bItalic;
	m_bItalicFocus=bItalicFocus;
	m_bItalicSelected=bItalicSelected;
	m_bItalicDisabled=bItalicDisabled;

	Invalidate();
}
//�����»���
void CMagicButton::SetUnderline(BOOL bUnderline,BOOL bUnderlineFocus,BOOL bUnderlineSelected,BOOL bUnderlineDisabled)
{
	m_bUnderline=bUnderline;
	m_bUnderlineFocus=bUnderlineFocus;
	m_bUnderlineSelected=bUnderlineSelected;
	m_bUnderlineDisabled=bUnderlineDisabled;

	Invalidate();
}
//����ɾ����
void CMagicButton::SetStrikeOut(BOOL bStrikeOut,BOOL bStrikeOutFocus,BOOL bStrikeOutSelected,BOOL bStrikeOutDisabled)
{
	m_bStrikeOut=bStrikeOut;
	m_bStrikeOutFocus=bStrikeOutFocus;
	m_bStrikeOutSelected=bStrikeOutSelected;
	m_bStrikeOutDisabled=bStrikeOutDisabled;

	Invalidate();
}

//���λͼ(����ť����ͼ��ֳ��ķ�״̬ͼ)
void CMagicButton::DivideBitmap()
{
	if(!m_backgndFull.m_hObject) return ;

	CClientDC dc(this);
	CDC memSrcDC,memDesDC;
	memSrcDC.CreateCompatibleDC(&dc);
	memDesDC.CreateCompatibleDC(&dc);
	memSrcDC.SelectObject(&m_backgndFull);
	BITMAP bit;
	m_backgndFull.GetBitmap(&bit);
	int cx=bit.bmWidth/4;
	int cy=bit.bmHeight;

	if(m_background.m_hObject) m_background.DeleteObject();
	m_background.CreateCompatibleBitmap(&dc,cx,cy);
	memDesDC.SelectObject(&m_background);
	memDesDC.BitBlt(0,0,cx,cy,&memSrcDC,0,0,SRCCOPY);

	if(m_backgroundFocus.m_hObject) m_backgroundFocus.DeleteObject();
	m_backgroundFocus.CreateCompatibleBitmap(&dc,cx,cy);
	memDesDC.SelectObject(&m_backgroundFocus);
	memDesDC.BitBlt(0,0,cx,cy,&memSrcDC,cx,0,SRCCOPY);

	if(m_backgroundSelected.m_hObject) m_backgroundSelected.DeleteObject();
	m_backgroundSelected.CreateCompatibleBitmap(&dc,cx,cy);
	memDesDC.SelectObject(&m_backgroundSelected);
	memDesDC.BitBlt(0,0,cx,cy,&memSrcDC,cx*2,0,SRCCOPY);

	if(m_backgroundDisabled.m_hObject) m_backgroundDisabled.DeleteObject();
	m_backgroundDisabled.CreateCompatibleBitmap(&dc,cx,cy);
	memDesDC.SelectObject(&m_backgroundDisabled);
	memDesDC.BitBlt(0,0,cx,cy,&memSrcDC,cx*3,0,SRCCOPY);

	m_nDrawMode=DRAW_MODE_BITMAP;
	Invalidate();
}

void CMagicButton::SetBitmap(CBitmap &bitmap)
{
	if(bitmap.m_hObject)
	{
		if(m_backgndFull.m_hObject)
			m_backgndFull.DeleteObject();
		if(m_backgndFull.Attach(bitmap.m_hObject))
			DivideBitmap();
	}
}

void CMagicButton::SetBitmap(UINT nResID)
{
	if(m_backgndFull.m_hObject)
		m_backgndFull.DeleteObject();
	if(m_backgndFull.LoadBitmap(nResID))
		DivideBitmap();
}

void CMagicButton::SetBitmap(LPCTSTR lpszFileName)
{
	HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),lpszFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(hBitmap)
	{
		if(m_backgndFull.m_hObject)
			m_backgndFull.DeleteObject();
		if(m_backgndFull.Attach(hBitmap))
			DivideBitmap();
	}
}

void CMagicButton::SetBitmap(HBITMAP hBitmap)
{
	if(hBitmap)
	{
		if(m_backgndFull.m_hObject)
			m_backgndFull.DeleteObject();
		if(m_backgndFull.Attach(hBitmap))
			DivideBitmap();
	}
}

void CMagicButton::SetCursor(HCURSOR hCursor)
{
	m_hCursor=hCursor;
	Invalidate();
}

void CMagicButton::SetBorder(BOOL bBorder)
{
	m_bBorder=bBorder;
	Invalidate();
}

//��ȡҪ��������ĸ����ڱ���
void CMagicButton::GetBackgndMask()
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

//��͸��λͼ
void CMagicButton::DrawTransparentBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp,
										 COLORREF maskColor)
{ 
	CDC foreDC,maskDC,tempDC;

	//��ȡǰ����Ϣ
	BITMAP bit;
	foreBmp.GetBitmap(&bit);
	//������ʱDC,ѡ��ǰ��λͼ
	tempDC.CreateCompatibleDC(pDC); 
	tempDC.SelectObject(&foreBmp);
 
	//###ǰ��DC����###
	//������ʱλͼ(��������ǰ��λͼ,�Ա������ǰ�������޸�)
	CBitmap tempBmp;
	tempBmp.CreateCompatibleBitmap(&tempDC,bit.bmWidth,bit.bmHeight);
	//����ǰ��DC,ѡ����ʱλͼ,����ǰ��λͼ����(��ʵ��ǰ��λͼ����)
	foreDC.CreateCompatibleDC(pDC); 
	foreDC.SelectObject(&tempBmp); 
	foreDC.BitBlt(0,0,bit.bmWidth,bit.bmHeight,&tempDC,0,0,SRCCOPY);
	
	//###����DC����###
	//��������λͼ(��ʼΪ��ɫ)
	CBitmap maskBmp;
	maskBmp.CreateBitmap(bit.bmWidth,bit.bmHeight,1,1,NULL);
	//��������DC
	maskDC.CreateCompatibleDC(pDC); 
	maskDC.SelectObject(&maskBmp); 
	
	//###����DC�޸�###
	foreDC.SetBkColor(maskColor); 
	maskDC.BitBlt(0,0,bit.bmWidth,bit.bmHeight,&foreDC,0,0,SRCCOPY); 
	
	//###ǰ��DC�޸�###
	foreDC.SetBkColor(RGB(0,0,0)); 
	foreDC.SetTextColor(RGB(255,255,255)); 
	foreDC.BitBlt(0,0,bit.bmWidth,bit.bmHeight,&maskDC,0,0,SRCAND); 
	
	//(pDC & mask) | fore=>���
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&maskDC,0,0,bit.bmWidth,bit.bmHeight,SRCAND); 
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&foreDC,0,0,bit.bmWidth,bit.bmHeight,SRCPAINT);
}

void CMagicButton::SetMaskColor(COLORREF color)
{
	m_bMask=TRUE;
	m_maskColor=color;
}

//����ͨλͼ
void CMagicButton::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

//����ɫ
void CMagicButton::DrawColor(CDC *pDC, CRect rect, COLORREF color)
{
	CBrush brush;
	brush.CreateSolidBrush(color);
	pDC->FillRect(rect,&brush);
}

//��GDI+ͼ
void CMagicButton::DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,int nIndex)
{
	USES_CONVERSION;
	Image img(A2W(lpszFileName));//תΪ���ַ�
	Status sta=img.GetLastStatus();
	if(sta!=Ok) return ;

	int cx=img.GetWidth()/4;
	int cy=img.GetHeight();

	Graphics graphics(pDC->m_hDC);
	graphics.DrawImage(&img,RectF(0,0,(float)rect.Width(),(float)rect.Height()),
		(float)cx*nIndex,0,(float)cx,(float)cy,UnitPixel);
}

//GDI+����ͼ
void CMagicButton::SetImage(LPCTSTR lpszFileName)
{
	if(strlen(lpszFileName)<3) return ;
	if(lpszFileName[1]!=':')
	{
		TCHAR szDrive[_MAX_DRIVE];
		TCHAR szDir[_MAX_DIR];
		TCHAR szFullPath[_MAX_PATH];
		::GetModuleFileName(NULL,szFullPath,_MAX_PATH); 
		_tsplitpath(szFullPath,szDrive,szDir,NULL,NULL);
		_tmakepath(m_backgndPath,szDrive,szDir,lpszFileName,NULL);
	}
	else
		strcpy(m_backgndPath,lpszFileName);
	
	m_nDrawMode=DRAW_MODE_IMAGE;
	Invalidate();
}

BOOL CMagicButton::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();
	return TRUE;
}

void CMagicButton::SetStyle(UINT nStyle)
{
	m_nStyle=nStyle;
}

//��������
void CMagicButton::SetFont(int nFontSize,CString strFontName,BOOL bBold,BOOL bItalic,
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

//���뷽ʽ
void CMagicButton::SetAlign(UINT nAlign)
{
	m_nAlign=nAlign;
	Invalidate();
}

BOOL CMagicButton::EnableWindow(BOOL bEnable)
{
	m_bEnable=bEnable;
	return CButton::EnableWindow(bEnable);
}

BOOL CMagicButton::GetEnable()
{
	return m_bEnable;
}

BOOL CMagicButton::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
	{
		m_bVisible=FALSE;
		CButton::EnableWindow(FALSE);
	}
	else
	{
		m_bVisible=TRUE;
		EnableWindow(m_bEnable);
	}

	Invalidate();

	return TRUE;
}

BOOL CMagicButton::GetVisible()
{
	return m_bVisible;
}