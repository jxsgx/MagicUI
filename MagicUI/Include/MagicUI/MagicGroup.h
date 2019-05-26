//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicGroup.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û������Ⱥ�����
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_GROUP_H_
#define _MAGICUI_GROUP_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MagicGroup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMagicGroup window
namespace GUI
{
class GUI_EXT_CLASS CMagicGroup : public CStatic
{
	DECLARE_DYNCREATE(CMagicGroup)
// Construction
public:
	CMagicGroup();
	//���ش�������
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	//�Զ�����(����CStatic��)
	BOOL AutoLoad(UINT nID, CWnd* pParent);

// Attributes
public:
	//��������ɫ
	void SetTextColor(COLORREF textColor);
	//��������
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//���뷽ʽ
	void SetAlign(UINT nAlign);

	//��ȡҪ��������ĸ����ڱ���
	void GetBackgndMask();

// Operations
public:
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();
private:
	//����ͨλͼ
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicGroup)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMagicGroup();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicGroup)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bVisible;//�ؼ�����
	BOOL m_bEnable;//�ؼ�����
	
	COLORREF m_textColor;//������ɫ
	CFont m_font;//������ʽ
	UINT m_nAlign;//���뷽ʽ
	CSize m_szText;//�ı���С

	CBitmap m_backgndMask;//��ͼ

	UINT m_nID;//����ťID
	CWnd* m_pWnd;//������ָ��
};

}

#endif // _MAGICUI_GROUP_H_
