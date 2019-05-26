//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicFillRegion.h											[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û���������������
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_FILLREGION_H_
#define _MAGICUI_FILLREGION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MagicFillRegion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMagicFillRegion window
namespace GUI
{
class GUI_EXT_CLASS CMagicFillRegion : public CStatic
{
	DECLARE_DYNCREATE(CMagicFillRegion)
// Construction
public:
	CMagicFillRegion();
	//���ش�������
	BOOL Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);

// Attributes
public:
	//�豳����ɫ
	void SetBackColor(COLORREF backColor);
	//��߿���ɫ
	void SetBorderColor(COLORREF borderColor);
	//��߿���
	void SetBorderWidth(int nWidth);
	//��Բ�Ǵ�С
	void SetCorner(int nSize);
	//��ȡҪ��������ĸ����ڱ���
	void GetBackgndMask();
	//���ô���͸��
	void SetAlpha(int alpha);

// Operations
public:
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();
private:
	//����ͨλͼ
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicFillRegion)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMagicFillRegion();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicFillRegion)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bVisible;//�ؼ�����
	CBitmap m_backgndMask;//��ͼ

	int m_nAlpha;			//͸����
	COLORREF m_backColor;	//����ɫ
	COLORREF m_borderColor;	//�߿�ɫ
	int m_borderWidth;		//�߿��
	int m_nCorner;			//Բ�Ǵ�С

	UINT m_nID;//����ťID
	CWnd* m_pWnd;//������ָ��
};

}

#endif // _MAGICUI_FILLREGION_H_
