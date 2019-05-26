//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicButton.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û�����ⰴť����
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_BUTTON_H_
#define _MAGICUI_BUTTON_H_

#if _MSC_VER > 1000
#pragma once
#endif

//��ʾ��ʽ
#define BS_CLICK	0	//�㵯ʽ(ÿ�ε�����ᵯ��)
#define BS_PRESS	1	//��ѹʽ(ÿ�ε���л��ڵ���ѹ������״̬)

//��ͼģʽ
#define DRAW_MODE_COLOR		0	//����ɫ
#define DRAW_MODE_BITMAP	1	//��λͼ(BMP)
#define DRAW_MODE_IMAGE		2	//��GDI+ͼ(BMP,GIF,JPEG,PNG,TIFF,EMF)

//��ť״̬ͼ����
#define INDEX_NORMAL		0	//����
#define INDEX_FOCUS			1	//�۽�
#define INDEX_SELECTED		2	//����
#define INDEX_DISABLED		3	//ʧЧ

/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicButton : public CButton
{
	DECLARE_DYNCREATE(CMagicButton)
// Construction
public:
	CMagicButton();
	//���ش�������
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,
				const RECT& rect, CWnd* pParentWnd, UINT nID);
	//�Զ�����(����CButton�ఴť)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
	//�豳��ɫ
	void SetBackColor(COLORREF backColor);
	void SetBackColor(COLORREF backColor,COLORREF backColorFocus,
				COLORREF backColorSelected,COLORREF backColorDisabled);
	//��ǰ��ɫ
	void SetForeColor(COLORREF foreColor);
	void SetForeColor(COLORREF foreColor,COLORREF foreColorFocus,
				COLORREF foreColorSelected,COLORREF foreColorDisabled);
	//�豳��ͼ
	void SetBitmap(CBitmap &bitmap);
	void SetBitmap(UINT nResID);
	void SetBitmap(LPCTSTR lpszFileName);
	void SetBitmap(HBITMAP hBitmap);
	//GDI+����ͼ
	void SetImage(LPCTSTR lpszFileName);

	//��ȡҪ��������ĸ����ڱ���
	void GetBackgndMask();
	//��������ɫ
	void SetMaskColor(COLORREF color);
	//����
	void SetCursor(HCURSOR hCursor);
	//��߿�
	void SetBorder(BOOL bBorder);
	//��������
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//���뷽ʽ
	void SetAlign(UINT nAlign);

	//���ô���
	void SetBold(BOOL bBold,BOOL bBoldFocus,BOOL bBoldSelected,BOOL bBoldDisabled);
	//����б��
	void SetItalic(BOOL bItalic,BOOL bItalicFocus,BOOL bItalicSelected,BOOL bItalicDisabled);
	//�����»���
	void SetUnderline(BOOL bUnderline,BOOL bUnderlineFocus,BOOL bUnderlineSelected,BOOL bUnderlineDisabled);
	//����ɾ����
	void SetStrikeOut(BOOL bStrikeOut,BOOL bStrikeOutFocus,BOOL bStrikeOutSelected,BOOL bStrikeOutDisabled);

// Operations
private:
	//��GDI+ͼ
	void DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,int nIndex);
	//��͸��λͼ
	void DrawTransparentBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp,
										 COLORREF maskColor);
	//����ͨλͼ
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);
	//����ɫ
	void DrawColor(CDC *pDC,CRect rect,COLORREF color);
	//���λͼ(����ť����ͼ��ֳ��ķ�״̬ͼ)
	void DivideBitmap();

public:
	BOOL EnableWindow(BOOL bEnable=TRUE);
	BOOL GetEnable();
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicButton)
	//}}AFX_VIRTUAL

	//����DrawItem����
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Implementation
public:
	void SetStyle(UINT nStyle);
	virtual ~CMagicButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); //����Ƴ�

	DECLARE_MESSAGE_MAP()
private:
	//ǰ��ɫ
	COLORREF m_foreColor;
	COLORREF m_foreColorFocus;
	COLORREF m_foreColorSelected;
	COLORREF m_foreColorDisabled;
	//����ɫ
	COLORREF m_backColor;
	COLORREF m_backColorFocus;
	COLORREF m_backColorSelected;
	COLORREF m_backColorDisabled;
	//����ͼ
	CBitmap m_background;
	CBitmap m_backgroundFocus;
	CBitmap m_backgroundSelected;
	CBitmap m_backgroundDisabled;
	//����
	BOOL m_bBold;
	BOOL m_bBoldFocus;
	BOOL m_bBoldSelected;
	BOOL m_bBoldDisabled;
	//б��
	BOOL m_bItalic;
	BOOL m_bItalicFocus;
	BOOL m_bItalicSelected;
	BOOL m_bItalicDisabled;
	//�»���
	BOOL m_bUnderline;
	BOOL m_bUnderlineFocus;
	BOOL m_bUnderlineSelected;
	BOOL m_bUnderlineDisabled;
	//ɾ����
	BOOL m_bStrikeOut;
	BOOL m_bStrikeOutFocus;
	BOOL m_bStrikeOutSelected;
	BOOL m_bStrikeOutDisabled;

	int m_nFontSize;		//�����С
	CString m_strFontName;	//��������
	UINT m_nAlign;			//���뷽ʽ

	CBitmap m_backgndFull;			//ȫͼ
	CBitmap m_backgndMask;			//��ͼ
	TCHAR m_backgndPath[_MAX_PATH];	//GDI+����·��

	HCURSOR m_hCursor;	//�����

	BOOL m_bVisible;	//�ؼ�����
	BOOL m_bEnable;		//�ؼ�����
	BOOL m_bMouseOn;	//����Ƿ�������
	BOOL m_bPressed;	//�Ƿ��ѱ�����
	BOOL m_bBorder;		//�Ƿ��б߿�
	BOOL m_bMask;		//�Ƿ�����ĳɫ
	COLORREF m_maskColor;//����ɫ

	UINT m_nDrawMode;	//��ͼģʽ
	UINT m_nStyle;		//��ʾ��ʽ

	UINT m_nID;		//����ťID
	CWnd* m_pWnd;	//������ָ��
};

}

#endif //_MAGICUI_BUTTON_H_
