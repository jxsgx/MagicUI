//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicRadio.cpp												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û�����ⵥѡ��ť����
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Include/MagicUI/MagicRadio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicRadio,CButton);

CMagicRadio::CMagicRadio()
{
	m_maskColor=RGB(255,0,255);//����ɫ
	m_bVisible=TRUE;//�ؼ�����
	m_bEnable=TRUE;//�ؼ�����
	m_bMouseOn=FALSE;//��겻������
	m_bSelected=FALSE;//δ������
	m_hCursor=LoadCursor(NULL,MAKEINTRESOURCE(32649));//���ι��
	m_pWnd=NULL;//������ָ��
	m_nDrawMode=DRAW_MODE_COLOR;//������ɫ
	m_imgWidth=0;//CheckBox��(����������)
	m_nFontSize=10;//�����С
	m_strFontName="����";//��������
	m_bBold=FALSE;//����
	m_bItalic=FALSE;//б��
	m_bUnderline=FALSE;//�»���
	m_bStrikeOut=FALSE;//ɾ����
	m_nAlign=DT_LEFT;//���뷽ʽ
	m_nGroupID=0;

	//��ť��ɫ��ʼֵ
	m_foreColor=m_foreColorFocus=m_foreColorSelected=GetSysColor(COLOR_BTNTEXT);
	m_foreColorDisabled=GetSysColor(COLOR_GRAYTEXT);
}

CMagicRadio::~CMagicRadio()
{
}


BEGIN_MESSAGE_MAP(CMagicRadio, CButton)
	//{{AFX_MSG_MAP(CMagicRadio)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicRadio message handlers

//������ť
BOOL CMagicRadio::Create(LPCTSTR lpszCaption, DWORD dwStyle,
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
BOOL CMagicRadio::AutoLoad(UINT nID, CWnd* pParent)
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

int CMagicRadio::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here

	return 0;
}

//����DrawItem����
void CMagicRadio::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
	lf.lfWeight=m_bBold?FW_BOLD:FW_NORMAL;//����
	lf.lfItalic=m_bItalic;//б��
	lf.lfUnderline=m_bUnderline;//�»���
	lf.lfStrikeOut=m_bStrikeOut;//ɾ����

	CFont font;
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);

	//���ñ���ģʽ
	pDC->SetBkMode(TRANSPARENT);
	CString strText;
	GetWindowText(strText);

	//��ȡĬ��rcText
	CSize sz = pDC->GetTextExtent("��");
	m_imgWidth=sz.cx+5;
	CRect rcText(m_imgWidth,0,rect.right,rect.bottom);

	//�汳��
	DrawOriginalBitmap(pDC,rect,m_backgndMask);
	if(!m_bVisible) return;

	if (state & ODS_DISABLED)//��ť�û�
	{
		switch(m_nDrawMode)
		{
		case DRAW_MODE_COLOR:
			rect.top += 1;
			rect.left += 1;
			pDC->SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
			pDC->DrawText("��", rect, DT_LEFT);

			rect.top -= 1;
			rect.left -= 1;
			pDC->SetTextColor(m_foreColorDisabled);
			pDC->DrawText("��", rect, DT_LEFT);
			break;
		case DRAW_MODE_IMAGE:
			DrawImage(pDC,rect,m_backgndPath,INDEX_DISABLED);
			break;
		case DRAW_MODE_BITMAP:
			DrawTransparentBitmap(pDC,rect,m_backgroundDisabled,m_maskColor);
			break;
		}

		if(strText!="")
		{
			rcText=CRect(m_imgWidth+5,0,rect.right,rect.bottom);

			rcText.top += 1;
			rcText.left += 1;
			pDC->SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
			pDC->DrawText(strText, rcText, m_nAlign);

			rcText.top -= 1;
			rcText.left -= 1;
			pDC->SetTextColor(m_foreColorDisabled);
			pDC->DrawText(strText, rcText, m_nAlign);
		}
	}
	else
	{
		if (m_bMouseOn)//����ڰ�ť��
		{
			if (state & ODS_SELECTED)//����
			{
				pDC->SetTextColor(m_foreColorSelected);

				switch(m_nDrawMode)
				{
				case DRAW_MODE_COLOR:
					pDC->DrawText("��", rect, m_nAlign);
					break;
				case DRAW_MODE_IMAGE:
					DrawImage(pDC,rect,m_backgndPath,INDEX_SELECTED);
					break;
				case DRAW_MODE_BITMAP:
					DrawTransparentBitmap(pDC,rect,m_backgroundSelected,m_maskColor);
					break;
				}
			}
			else//δ����
			{
				pDC->SetTextColor(m_foreColorFocus);

				switch(m_nDrawMode)
				{
				case DRAW_MODE_COLOR:
					pDC->DrawText("��", rect, m_nAlign);
					break;
				case DRAW_MODE_IMAGE:
					DrawImage(pDC,rect,m_backgndPath,INDEX_FOCUS);
					break;
				case DRAW_MODE_BITMAP:
					DrawTransparentBitmap(pDC,rect,m_backgroundFocus,m_maskColor);
					break;
				}
			}
		}
		else//��겻�ڰ�ť��
		{
			pDC->SetTextColor(m_foreColor);

			switch(m_nDrawMode)
			{
			case DRAW_MODE_COLOR:
				pDC->DrawText("��", rect, m_nAlign);
				break;
			case DRAW_MODE_IMAGE:
				DrawImage(pDC,rect,m_backgndPath,INDEX_NORMAL);
				break;
			case DRAW_MODE_BITMAP:
				DrawTransparentBitmap(pDC,rect,m_background,m_maskColor);
				break;
			}
		}

		if(m_bSelected)
		{
			switch(m_nDrawMode)
			{
			case DRAW_MODE_COLOR:
				pDC->DrawText("��", rect, DT_LEFT);
				break;
			case DRAW_MODE_IMAGE:
				DrawImage(pDC,rect,m_backgndPath,INDEX_HOOK);
				break;
			case DRAW_MODE_BITMAP:
				DrawTransparentBitmap(pDC,rect,m_backgroundHook,m_maskColor);
				break;
			}
		}

		rcText=CRect(m_imgWidth+5,0,rect.right,rect.bottom);

		if(strText!="")
			pDC->DrawText(strText, rcText, m_nAlign);
	}
}

void CMagicRadio::OnMouseMove(UINT nFlags, CPoint point) 
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

LRESULT CMagicRadio::OnMouseLeave(WPARAM wParam,LPARAM lParam)   
{
	m_bMouseOn=FALSE;
	Invalidate();
	return TRUE;
}

void CMagicRadio::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	if(rect.PtInRect(point)&&!m_bSelected)
	{
		m_bSelected=TRUE;
		::SendMessage(m_pWnd->GetSafeHwnd(),UM_RADIOBOX,(WPARAM)m_hWnd,m_nGroupID);
	}

	CButton::OnLButtonUp(nFlags, point);
}

BOOL CMagicRadio::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bMouseOn)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return CButton::OnSetCursor(pWnd, nHitTest, message);
}

void CMagicRadio::SetForeColor(COLORREF foreColor)
{
	m_foreColor=foreColor;
	m_foreColorFocus=foreColor;
	m_foreColorSelected=foreColor;
	Invalidate();
}

void CMagicRadio::SetForeColor(COLORREF foreColor,COLORREF foreColorFocus,
				COLORREF foreColorSelected,COLORREF foreColorDisabled)
{
	if(foreColor!=-1) m_foreColor=foreColor;
	if(foreColorFocus!=-1) m_foreColorFocus=foreColorFocus;
	if(foreColorSelected!=-1) m_foreColorSelected=foreColorSelected;
	if(foreColorDisabled!=-1) m_foreColorDisabled=foreColorDisabled;
	Invalidate();
}

//���λͼ(����ť����ͼ��ֳ��ķ�״̬ͼ)
void CMagicRadio::DivideBitmap()
{
	if(!m_backgndFull.m_hObject) return ;

	CClientDC dc(this);
	CDC memSrcDC,memDesDC;
	memSrcDC.CreateCompatibleDC(&dc);
	memDesDC.CreateCompatibleDC(&dc);
	memSrcDC.SelectObject(&m_backgndFull);
	BITMAP bit;
	m_backgndFull.GetBitmap(&bit);
	int cx=bit.bmWidth/5;
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

	if(m_backgroundHook.m_hObject) m_backgroundHook.DeleteObject();
	m_backgroundHook.CreateCompatibleBitmap(&dc,cx,cy);
	memDesDC.SelectObject(&m_backgroundHook);
	memDesDC.BitBlt(0,0,cx,cy,&memSrcDC,cx*4,0,SRCCOPY);

	m_nDrawMode=DRAW_MODE_BITMAP;
	Invalidate();
}

void CMagicRadio::SetBitmap(CBitmap &bitmap)
{
	if(bitmap.m_hObject)
	{
		if(m_backgndFull.m_hObject)
			m_backgndFull.DeleteObject();
		if(m_backgndFull.Attach(bitmap.m_hObject))
			DivideBitmap();
	}
}

void CMagicRadio::SetBitmap(UINT nResID)
{
	if(m_backgndFull.m_hObject)
		m_backgndFull.DeleteObject();
	if(m_backgndFull.LoadBitmap(nResID))
		DivideBitmap();
}

void CMagicRadio::SetBitmap(LPCTSTR lpszFileName)
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

void CMagicRadio::SetBitmap(HBITMAP hBitmap)
{
	if(hBitmap)
	{
		if(m_backgndFull.m_hObject)
			m_backgndFull.DeleteObject();
		if(m_backgndFull.Attach(hBitmap))
			DivideBitmap();
	}
}

void CMagicRadio::SetCursor(HCURSOR hCursor)
{
	m_hCursor=hCursor;
	Invalidate();
}

//��������
void CMagicRadio::SetFont(int nFontSize,CString strFontName,BOOL bBold,BOOL bItalic,
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
void CMagicRadio::GetBackgndMask()
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
void CMagicRadio::DrawTransparentBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp,COLORREF maskColor)
{ 
	CDC foreDC,maskDC,tempDC;

	//��ȡǰ����Ϣ
	BITMAP bit;
	foreBmp.GetBitmap(&bit);
	m_imgWidth=bit.bmWidth;

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
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&maskDC,0,0,SRCAND); 
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&foreDC,0,0,SRCPAINT);
}

void CMagicRadio::SetMaskColor(COLORREF color)
{
	m_maskColor=color;
}

//����ͨλͼ
void CMagicRadio::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

//��GDI+ͼ
void CMagicRadio::DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,int nIndex)
{
	USES_CONVERSION;
	Image img(A2W(lpszFileName));//תΪ���ַ�
	Status sta=img.GetLastStatus();
	if(sta!=Ok) return ;

	int cx=img.GetWidth()/5;
	int cy=img.GetHeight();

	m_imgWidth=cx;

	Graphics graphics(pDC->m_hDC);
	graphics.DrawImage(&img,RectF(0,0,(float)cx,(float)cy),
		(float)cx*nIndex,0,(float)cx,(float)cy,UnitPixel);
}

//GDI+����ͼ
void CMagicRadio::SetImage(LPCTSTR lpszFileName)
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

BOOL CMagicRadio::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();
	return TRUE;
}

//���뷽ʽ
void CMagicRadio::SetAlign(UINT nAlign)
{
	m_nAlign=nAlign;
	Invalidate();
}

//����ѡ��״̬
void CMagicRadio::SetSelect(BOOL bSelect)
{
	m_bSelected=bSelect;
	Invalidate();
}

//��ȡѡ��״̬
BOOL CMagicRadio::GetSelect()
{
	return m_bSelected;
}

//�������
void CMagicRadio::SetGroupID(UINT nGroupID)
{
	m_nGroupID=nGroupID;
}

//��ȡ���
UINT CMagicRadio::GetGroupID()
{
	return m_nGroupID;
}

BOOL CMagicRadio::EnableWindow(BOOL bEnable)
{
	m_bEnable=bEnable;
	return CButton::EnableWindow(bEnable);
}

BOOL CMagicRadio::GetEnable()
{
	return m_bEnable;
}

BOOL CMagicRadio::ShowWindow(int nCmdShow)
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

BOOL CMagicRadio::GetVisible()
{
	return m_bVisible;
}
