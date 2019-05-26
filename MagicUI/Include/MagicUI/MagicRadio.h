//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicRadio.h												[Magic UI]		
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
#ifndef _MAGICUI_RADIO_H_
#define _MAGICUI_RADIO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//��ͼģʽ
#define DRAW_MODE_COLOR		0	//����ɫ
#define DRAW_MODE_BITMAP	1	//��λͼ(BMP)
#define DRAW_MODE_IMAGE		2	//��GDI+ͼ(BMP,GIF,JPEG,PNG,TIFF,EMF)

//��ť״̬ͼ����
#define INDEX_NORMAL		0	//����
#define INDEX_FOCUS			1	//�۽�
#define INDEX_SELECTED		2	//����
#define INDEX_DISABLED		3	//ʧЧ
#define INDEX_HOOK			4	//����

#define UM_RADIOBOX WM_USER+100

/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicRadio : public CButton
{
	DECLARE_DYNCREATE(CMagicRadio)
// Construction
public:
	CMagicRadio();
	//���ش�������
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,
				const RECT& rect, CWnd* pParentWnd, UINT nID);
	//�Զ�����(����CButton�ఴť)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
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
	//��������
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//���뷽ʽ
	void SetAlign(UINT nAlign);

	//����ѡ��״̬
	void SetSelect(BOOL bSelect=TRUE);
	//��ȡѡ��״̬
	BOOL GetSelect();

	//�������
	void SetGroupID(UINT nGroupID);
	//��ȡ���
	UINT GetGroupID();

// Operations
private:
	//��GDI+ͼ
	void DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,int nIndex);
	//��͸��λͼ
	void DrawTransparentBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp,COLORREF maskColor);
	//����ͨλͼ
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);
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
	virtual ~CMagicRadio();

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
	HCURSOR m_hCursor;//�����

	COLORREF m_foreColor;//����ʱǰ��ɫ
	COLORREF m_foreColorFocus;//�۽�ʱǰ��ɫ
	COLORREF m_foreColorSelected;//ѡ��ʱǰ��ɫ
	COLORREF m_foreColorDisabled;//ʧЧʱǰ��ɫ

	CBitmap m_background;//����ʱ����ͼ
	CBitmap m_backgroundFocus;//�۽�ʱ����ͼ
	CBitmap m_backgroundSelected;//ѡ��ʱ����ͼ
	CBitmap m_backgroundDisabled;//ʧЧʱ����ͼ
	CBitmap m_backgroundHook;//���ӱ���ͼ

	CBitmap m_backgndFull;//ȫͼ
	CBitmap m_backgndMask;//��ͼ
	int m_imgWidth;//CheckBox��(����������)

	int m_nFontSize;//�����С
	CString m_strFontName;//��������
	BOOL m_bBold;//����
	BOOL m_bItalic;//б��
	BOOL m_bUnderline;//�»���
	BOOL m_bStrikeOut;//ɾ����
	UINT m_nAlign;//���뷽ʽ

	BOOL m_bVisible;	//�ؼ�����
	BOOL m_bEnable;		//�ؼ�����
	BOOL m_bMouseOn;//����Ƿ�������
	BOOL m_bSelected;//�Ƿ��ѱ���ѡ
	UINT m_nGroupID;//���
	COLORREF m_maskColor;//����ɫ
	UINT m_nDrawMode;//��ͼģʽ
	TCHAR m_backgndPath[_MAX_PATH];//GDI+����·��

	UINT m_nID;//����ťID
	CWnd* m_pWnd;//������ָ��
};

}

#endif //_MAGICUI_RADIO_H_
