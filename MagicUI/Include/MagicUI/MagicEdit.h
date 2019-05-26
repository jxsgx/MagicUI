//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicEdit.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û������༭����
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_EDIT_H_
#define _MAGICUI_EDIT_H_

/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicEdit : public CEdit
{
	DECLARE_DYNCREATE(CMagicEdit)
// Construction
public:
	CMagicEdit();
	//���ش�������
	BOOL Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID);
	//�Զ�����(����CEdit��)
	BOOL AutoLoad(UINT nID, CWnd* pParent);

// Attributes
public:
	//��������ɫ
	void SetTextColor(COLORREF textColor);
	void SetTextColor(COLORREF textColor,COLORREF textColorHover,
				COLORREF textColorFocus,COLORREF textColorDisabled);
	//�豳����ɫ
	void SetBackColor(COLORREF backColor);
	void SetBackColor(COLORREF backColor,COLORREF backColorHover,
				COLORREF backColorFocus,COLORREF backColorDisabled);
	//��߿���ɫ
	void SetBorderColor(COLORREF borderColor);
	void SetBorderColor(COLORREF borderColor,COLORREF borderColorHover,
				COLORREF borderColorFocus,COLORREF borderColorDisabled);
	//��������
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//���뷽ʽ
	void SetAlign(UINT nAlign);

	//��ȡҪ��������ĸ����ڱ���
	void GetBackgndMask();

	//����
	void SetCursor(HCURSOR hCursor);

	void SetPassword(BOOL bPassword=TRUE);
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
	//{{AFX_VIRTUAL(CMagicEdit)
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CMagicEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	//������ɫ
	COLORREF m_textColor;
	COLORREF m_textColorFocus;
	COLORREF m_textColorHover;
	COLORREF m_textColorDisabled;

	//������ɫ
	COLORREF m_backColor;
	COLORREF m_backColorFocus;
	COLORREF m_backColorHover;
	COLORREF m_backColorDisabled;

	//�߿���ɫ
	COLORREF m_borderColor;
	COLORREF m_borderColorFocus;
	COLORREF m_borderColorHover;
	COLORREF m_borderColorDisabled;

	CBrush m_brBkgnd;//������ˢ
	CBitmap m_backgndMask;//��ͼ
	HCURSOR m_hCursor;//�����

	BOOL m_bVisible;//����
	BOOL m_bEnable;//����
	BOOL m_bHover;//��ͣ
	BOOL m_bFocus;//�۽�

	CString m_strText;
	CFont m_font;

	UINT m_nID;//����ťID
	CWnd* m_pWnd;//������ָ��
};

}

#endif //_MAGICUI_EDIT_H_
