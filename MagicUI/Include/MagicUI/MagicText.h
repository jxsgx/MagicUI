//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicText.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û�������ı�����
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_TEXT_H_
#define _MAGICUI_TEXT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//��ʾ��ʽ
#define PS_FIXSIZE	1
#define PS_AUTOSIZE	2
#define PS_STRETCH	4
#define PS_BORDER	8
#define PS_SCROLL	16
/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicText : public CStatic
{
	DECLARE_DYNCREATE(CMagicText)
// Construction
public:
	CMagicText();
	//���ش�������
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	//�Զ�����(����CStatic��)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
	//��������ɫ
	void SetTextColor(COLORREF textColor);
	void SetTextColor(COLORREF TextColor,COLORREF TextColorFocus,
				COLORREF TextColorSelected,COLORREF TextColorDisabled);
	//��߿���ɫ
	void SetBorderColor(COLORREF borderColor);
	void SetBorderColor(COLORREF borderColor,COLORREF borderColorFocus,
				COLORREF borderColorSelected,COLORREF borderColorDisabled);
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

	//��ȡҪ��������ĸ����ڱ���
	void GetBackgndMask();

	//����
	void SetCursor(HCURSOR hCursor);
// Operations
private:
	//����ͨλͼ
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);
public:
	BOOL EnableWindow(BOOL bEnable=TRUE);
	BOOL GetEnable();
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicText)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	//������ʾ��ʽ
	void SetStyle(UINT nStyle);
	virtual ~CMagicText();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicText)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); //����Ƴ�

	DECLARE_MESSAGE_MAP()
private:
	//������ɫ
	COLORREF m_textColor;
	COLORREF m_textColorFocus;
	COLORREF m_textColorSelected;
	COLORREF m_textColorDisabled;
	//�߿���ɫ
	COLORREF m_borderColor;
	COLORREF m_borderColorFocus;
	COLORREF m_borderColorSelected;
	COLORREF m_borderColorDisabled;
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

	//ѡ����ʾ
	COLORREF m_borderColorShow;
	COLORREF m_textColorShow;
	BOOL m_bBoldShow;
	BOOL m_bItalicShow;
	BOOL m_bUnderlineShow;
	BOOL m_bStrikeOutShow;

	int m_nFontSize;//�����С
	CString m_strFontName;//��������
	UINT m_nAlign;//���뷽ʽ

	UINT m_nStyle;//��ʽ
	CBitmap m_backgndMask;//��ͼ

	BOOL m_bVisible;//�ؼ�����
	BOOL m_bEnable;//�ؼ�����
	BOOL m_bMouseOn;//���������
	BOOL m_bMouseDown;//��갴��
	HCURSOR m_hCursor;

	UINT m_nID;//����ťID
	CWnd* m_pWnd;//������ָ��
};

}

#endif //_MAGICUI_TEXT_H_
