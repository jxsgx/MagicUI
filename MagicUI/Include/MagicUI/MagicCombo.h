//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicCombo.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û��������������
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_COMBO_H_
#define _MAGICUI_COMBO_H_

#if _MSC_VER > 1000
#pragma once
#endif

/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicCombo : public CComboBox
{
	DECLARE_DYNCREATE(CMagicCombo)
// Construction
public:
	CMagicCombo();
	//���ش�������
	BOOL Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID);
	//�Զ�����(����CComboBox�ఴť)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
	//�豳��ɫ
	void SetBackColor(COLORREF backColor);
	void SetBackColor(COLORREF backColor,COLORREF backColorHover,COLORREF backColorDisabled);
	//��������ɫ
	void SetTextColor(COLORREF textColor);
	void SetTextColor(COLORREF TextColor,COLORREF TextColorHover,COLORREF TextColorDisabled);
	//��߿���ɫ
	void SetBorderColor(COLORREF borderColor);
	//�谴ť������ɫ
	void SetBtnColor(COLORREF btnColor);

	//��ȡҪ��������ĸ����ڱ���
	void GetBackgndMask();
	//����
	void SetCursor(HCURSOR hCursor);
	//��߿�
	//��������
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//���뷽ʽ
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
	//{{AFX_VIRTUAL(CMagicCombo)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

	int AddString(LPCTSTR lpszString);
	int InsertString(int nIndex, LPCTSTR lpszString);
	int DeleteString(UINT nIndex);
	void ResetContent();
// Implementation
public:
	virtual ~CMagicCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicCombo)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetfocus();
	afx_msg void OnKillfocus();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); //����Ƴ�

	DECLARE_MESSAGE_MAP()
private:
	//����ɫ
	COLORREF m_backColor;
	COLORREF m_backColorHover;
	COLORREF m_backColorDisabled;

	//�ı�ɫ
	COLORREF m_textColor;
	COLORREF m_textColorHover;
	COLORREF m_textColorDisabled;

	//�߿�ɫ
	COLORREF m_borderColor;
	CBrush m_brBkgnd;

	//��ť����ɫ
	COLORREF m_btnColor;

	BOOL m_bBold;//����
	BOOL m_bItalic;//б��
	BOOL m_bUnderline;//�»���
	BOOL m_bStrikeOut;//ɾ����

	int m_nFontSize;		//�����С
	CString m_strFontName;	//��������

	HCURSOR m_hCursor;		//�����
	CBitmap m_backgndMask;	//��ͼ

	BOOL m_bVisible;//�ؼ�����
	BOOL m_bEnable;	//�ؼ�����
	BOOL m_bHover;	//��ͣ
	BOOL m_bFocus;	//�۽�

	CStringArray m_strAry;
	CFont m_font;

	UINT m_nID;		//����ťID
	CWnd* m_pWnd;	//������ָ��
};

}

#endif //_MAGICUI_COMBO_H_
