//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicPicture.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û������ͼƬ����
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_PICTURE_H_
#define _MAGICUI_PICTURE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//��ʾ��ʽ
#define PS_FIXSIZE	1
#define PS_AUTOSIZE	2
#define PS_STRETCH	4
#define PS_BORDER	8
#define PS_SCROLL	16

//��ͼģʽ
#define DRAW_MODE_COLOR		0	//����ɫ
#define DRAW_MODE_BITMAP	1	//��λͼ(BMP)
#define DRAW_MODE_IMAGE		2	//��GDI+ͼ(BMP,GIF,JPEG,PNG,TIFF,EMF)
/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicPicture : public CStatic
{
	DECLARE_DYNCREATE(CMagicPicture)
// Construction
public:
	CMagicPicture();
	//���ش�������
	BOOL Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	//�Զ�����(����CStatic��)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
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

// Operations
private:
	//��GDI+ͼ
	void DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,CRect rc);
	//��͸��λͼ
	void DrawTransparentBitmap(CDC *pDC,CRect rect,
									  CBitmap &foreBmp,COLORREF maskColor,CRect rc);
	//����ͨλͼ
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);
public:
	BOOL EnableWindow(BOOL bEnable=TRUE);
	BOOL GetEnable();
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicPicture)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	//������ʾ��ʽ
	void SetStyle(UINT nStyle);
	virtual ~CMagicPicture();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicPicture)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); //����Ƴ�

	DECLARE_MESSAGE_MAP()
private:
	HCURSOR m_hCursor;//�����

	CBitmap m_background;//λͼ
	CBitmap m_backgndMask;//��ͼ
	UINT m_nDrawMode;//��ͼģʽ
	TCHAR m_backgndPath[_MAX_PATH];

	UINT m_nStyle;//��ʽ

	BOOL m_bMask;//�Ƿ�����ĳɫ
	COLORREF m_maskColor;//����ɫ

	UINT m_nID;//����ťID
	CWnd* m_pWnd;//������ָ��

	CScrollBar m_HScroll,m_VScroll;//������
	int m_xoffset,m_yoffset;//ͼƬ���ͼƬ��ƫ����
	int m_xorign,m_yorign;//������ͼƬ��ƫ����
	int m_xMax,m_yMax;//���������ֵ
	
	BOOL m_bVisible;//�ؼ�����
	BOOL m_bEnable;//�ؼ�����
	BOOL m_bMouseDown;//��갴�±�־
};

}

#endif //_MAGICUI_PICTURE_H_
