//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: MagicWnd.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic �û�������Ի洰�ڶ���
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_WINDOW_H_
#define _MAGICUI_WINDOW_H_

#if _MSC_VER > 1300
#pragma once
#endif

#include <afxwin.h>
#include "DataDefine.h"

#include "resource.h"		// main symbols
#include "MagicButton.h"
#include "MagicCheck.h"
#include "MagicRadio.h"
#include "MagicPicture.h"
#include "MagicText.h"
#include "MagicEdit.h"
#include "MagicCombo.h"
#include "MagicGroup.h"
#include "MagicFillRegion.h"

//�ؼ�����
#define MAGICUI_WND			0
#define MAGICUI_BUTTON		1
#define MAGICUI_CHECK		2
#define MAGICUI_RADIO		3
#define MAGICUI_PICTURE		4
#define MAGICUI_TEXT		5
#define MAGICUI_EDIT		6
#define MAGICUI_COMBO		7
#define MAGICUI_GROUP		8
#define MAGICUI_FILLREGION	9

#define UM_RADIOBOX WM_USER+100

/////////////////////////////////////////////////////////////////////////////
class CMarkup;
namespace GUI
{
class GUI_EXT_CLASS CMagicWnd : public CWnd
{
	DECLARE_DYNCREATE(CMagicWnd)
public:
	//�ؼ���Ϣ
	typedef struct ControlInfo
	{
		CString strName;
		UINT nType;
		CWnd *pWnd;
		UINT nCmd;
	}CTRL_INFO;
	//��ť��ʽ
	typedef struct StyleButton
	{
		//�ı���ɫ
		COLORREF textColor;
		COLORREF textColorFocus;
		COLORREF textColorSelected;
		COLORREF textColorDisabled;

		int nFontSize;					//�����С
		TCHAR szFontName[LF_FACESIZE];	//��������
		UINT nAlign;					//���뷽ʽ

		//����
		BOOL bBold;
		BOOL bBoldFocus;
		BOOL bBoldSelected;
		BOOL bBoldDisabled;
		//б��
		BOOL bItalic;
		BOOL bItalicFocus;
		BOOL bItalicSelected;
		BOOL bItalicDisabled;
		//�»���
		BOOL bUnderline;
		BOOL bUnderlineFocus;
		BOOL bUnderlineSelected;
		BOOL bUnderlineDisabled;
		//ɾ����
		BOOL bStrikeOut;
		BOOL bStrikeOutFocus;
		BOOL bStrikeOutSelected;
		BOOL bStrikeOutDisabled;

		HCURSOR hCursor;	//���
	}STYLE_BUTTON;
	//��ѡ��ť��ʽ
	typedef struct StyleCheck
	{
		//�ı���ɫ
		COLORREF textColor;
		COLORREF textColorFocus;
		COLORREF textColorSelected;
		COLORREF textColorDisabled;

		int nFontSize;					//�����С
		TCHAR szFontName[LF_FACESIZE];	//��������
		UINT nAlign;					//���뷽ʽ

		BOOL bBold;			//����
		BOOL bItalic;		//б��
		BOOL bUnderline;	//�»���
		BOOL bStrikeOut;	//ɾ����

		//ͼƬ·��
		TCHAR szBackGround[_MAX_FNAME];
		TCHAR szImage[_MAX_FNAME];

		HCURSOR hCursor;	//���
	}STYLE_CHECK;
	//��ѡ��ť��ʽ
	typedef struct StyleRadio
	{
		//�ı���ɫ
		COLORREF textColor;
		COLORREF textColorFocus;
		COLORREF textColorSelected;
		COLORREF textColorDisabled;

		int nFontSize;					//�����С
		TCHAR szFontName[LF_FACESIZE];	//��������
		UINT nAlign;					//���뷽ʽ

		BOOL bBold;			//����
		BOOL bItalic;		//б��
		BOOL bUnderline;	//�»���
		BOOL bStrikeOut;	//ɾ����

		//ͼƬ·��
		TCHAR szBackGround[_MAX_FNAME];
		TCHAR szImage[_MAX_FNAME];

		HCURSOR hCursor;//���
	}STYLE_RADIO;
	//�ı���ʽ
	typedef struct StyleText
	{
		//�ı���ɫ
		COLORREF textColor;
		COLORREF textColorFocus;
		COLORREF textColorSelected;
		COLORREF textColorDisabled;
		//�߿���ɫ
		COLORREF borderColor;
		COLORREF borderColorFocus;
		COLORREF borderColorSelected;
		COLORREF borderColorDisabled;

		int nFontSize;					//�����С
		TCHAR szFontName[LF_FACESIZE];	//��������
		UINT nAlign;					//���뷽ʽ

		//����
		BOOL bBold;
		BOOL bBoldFocus;
		BOOL bBoldSelected;
		BOOL bBoldDisabled;
		//б��
		BOOL bItalic;
		BOOL bItalicFocus;
		BOOL bItalicSelected;
		BOOL bItalicDisabled;
		//�»���
		BOOL bUnderline;
		BOOL bUnderlineFocus;
		BOOL bUnderlineSelected;
		BOOL bUnderlineDisabled;
		//ɾ����
		BOOL bStrikeOut;
		BOOL bStrikeOutFocus;
		BOOL bStrikeOutSelected;
		BOOL bStrikeOutDisabled;

		HCURSOR hCursor;	//���
	}STYLE_TEXT;
	//�༭����ʽ
	typedef struct StyleEdit
	{
		//�ı���ɫ
		COLORREF textColor;
		COLORREF textColorHover;
		COLORREF textColorFocus;
		COLORREF textColorDisabled;
		//������ɫ
		COLORREF backColor;
		COLORREF backColorHover;
		COLORREF backColorFocus;
		COLORREF backColorDisabled;
		//�߿���ɫ
		COLORREF borderColor;
		COLORREF borderColorHover;
		COLORREF borderColorFocus;
		COLORREF borderColorDisabled;
		
		int nFontSize;					//�����С
		TCHAR szFontName[LF_FACESIZE];	//��������
		UINT nAlign;					//���뷽ʽ

		BOOL bBold;			//����
		BOOL bItalic;		//б��
		BOOL bUnderline;	//�»���
		BOOL bStrikeOut;	//ɾ����

		BOOL bPassword;		//�Ƿ�Ϊ�����
		HCURSOR hCursor;	//���
	}STYLE_EDIT;
	//��Ͽ���ʽ
	typedef struct StyleCombo
	{
		//�ı���ɫ
		COLORREF textColor;
		COLORREF textColorHover;
		COLORREF textColorDisabled;
		//������ɫ
		COLORREF backColor;
		COLORREF backColorHover;
		COLORREF backColorDisabled;
		
		COLORREF borderColor;	//�߿���ɫ
		COLORREF btnColor;		//��ť������ɫ

		int nFontSize;					//�����С
		TCHAR szFontName[LF_FACESIZE];	//��������

		BOOL bBold;			//����
		BOOL bItalic;		//б��
		BOOL bUnderline;	//�»���
		BOOL bStrikeOut;	//ɾ����

		HCURSOR hCursor;	//���
	}STYLE_COMBO;
	//Ⱥ�����ʽ
	typedef struct StyleGroup
	{
		COLORREF textColor;//�ı���ɫ

		int nFontSize;					//�����С
		TCHAR szFontName[LF_FACESIZE];	//��������
		UINT nAlign;					//���뷽ʽ

		BOOL bBold;			//����
		BOOL bItalic;		//б��
		BOOL bUnderline;	//�»���
		BOOL bStrikeOut;	//ɾ����
	}STYLE_GROUP;
	//�������ʽ
	typedef struct StyleFillRegion
	{
		COLORREF backColor;		//������ɫ
		COLORREF borderColor;	//�߿���ɫ
		int borderWidth;		//�߿���
		int nCorner;			//Բ�Ǵ�С
		int nAlpha;				//͸����
	}STYLE_FILLREGION;
// Construction
public:
	CWnd* GetWndByName(CString strName);
	CMagicWnd();
	~CMagicWnd();
	// ��������
	virtual BOOL Create(LPCTSTR szSkinPath,
						LPCTSTR szMainXml, 
						LPCTSTR szGlobalXml, 
						DWORD dwExStyle		= NULL,
						DWORD dwStyle		= WS_POPUP | WS_VISIBLE, 
						CWnd * parentWnd	= NULL);
	//��ʼ��ȫ����ʽ
	void InitGlobalStyle();
	//����ȫ����ʽ
	BOOL LoadGlobalStyle(LPCTSTR szSkinPath,LPCTSTR szGlobalXml);
	//װ��Ƥ��
	BOOL LoadSkin(LPCTSTR szSkinPath,LPCTSTR szMainXml);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicWnd)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//������ʾ����
	BOOL ShowWindow(int nCmdShow);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMagicWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcRButtonUp(UINT nHitTest,CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest,CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRestore();
	afx_msg void OnMove();
	afx_msg void OnSize();
	afx_msg void OnMiniMize();
	afx_msg void OnMaxiMize();
	afx_msg void OnClose();
	afx_msg void OnAbout();
	afx_msg void OnBtnMinimize();
	afx_msg void OnBtnMaximize();
	afx_msg void OnBtnClose();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//}}AFX_MSG
	LRESULT OnRadioBox(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	//����ϵͳ�˵�����
	void EnableSysMenu(BOOL bRestor,BOOL bMove,BOOL bSize,BOOL bMini,BOOL bMaxi);
private:
	BOOL FindUserStyle(CString strLabel,CMarkup &xml);
	void ReadStyleGroup(STYLE_GROUP &sg,CMarkup xml);
	void ReadStyleRegion(STYLE_FILLREGION &sf,CMarkup xml);
	void ReadStyleCombo(STYLE_COMBO &sc,CMarkup xml);
	void ReadStyleEdit(STYLE_EDIT &se,CMarkup xml);
	void ReadStyleText(STYLE_TEXT &st,CMarkup xml);
	void ReadStyleCheck(STYLE_CHECK &sc,CMarkup xml);
	void ReadStyleRadio(STYLE_RADIO &sr,CMarkup xml);
	void ReadStyleButton(STYLE_BUTTON &sb,CMarkup xml);
	void SetRegion(CMarkup xml);
	void SetGroup(CMarkup xml);
	void SetComboBox(CMarkup xml);
	void SetEdit(CMarkup xml);
	void SetText(CMarkup xml);
	void SetCheckBox(CMarkup xml);
	void SetRadioBox(CMarkup xml);
	void SetPicture(CMarkup xml);
	void SetButton(CMarkup xml);
	void SetControl(CMarkup xml);
	BOOL SetWindow(CMarkup xml);
	CPoint m_ptWnd;				//���ڵ�λ��(*)
	CSize m_szWnd;				//���ڵĴ�С(*)
	BOOL m_bEnable;				//�����Ƿ񼤻�
	BOOL m_bVisible;			//�����Ƿ�ɼ�
	CSize m_szMinSize;			//���ڵ���С���
	CSize m_szMaxSize;			//���ڵ������
	BOOL m_bFixSize;			//�����Ƿ�̶���С
	BOOL m_bCanMove;			//�����Ƿ�����ƶ�
	COLORREF m_backColor;		//���ڵı���ɫ
	COLORREF m_borderColor;		//���ڵı߿���ɫ
	COLORREF m_maskColor;		//�߿򱳾�ͼ��ʹ�õ�����ɫ
	BOOL m_bUseMaskColor;		//�Ƿ�������ɫ
	UINT m_nMenuID;				//���ڵĲ˵���Դ��IDֵ
	CBitmap m_backGround;		//���ڵı���ͼ��
	CBitmap	m_backgnd[8];		//��ֱ���ͼ��Ϊ�ı��Ľ�
	CRect m_rcWindowBorder;		//�����������µı߰�

	CString m_strSkinPath;		//Ƥ����·��
	CString	m_strMainXml;		//Ƥ�������ļ�(*.xml)
	CString	m_strGlobalXml;		//ȫ����ʽ�ļ�(*.xml)
	CRect m_rcTitleBar;			//�Զ��������
	CRect m_rcIcon;				//�Զ���ͼ��
	COLORREF m_titleBarColor;	//��������ɫ
	COLORREF m_iconColor;		//ͼ����ɫ
	CMenu m_sysMenu;			//ϵͳ�˵�
	BOOL m_bMaximize;			//������󻯱�־
	CMagicButton m_btnMin,m_btnMax,m_btnClose;	//ϵͳ��ť
	CSize m_szMin,m_szMax,m_szClose;			//��ť��Դ������Ͻ�ƫ��
	BOOL m_bMinExist,m_bMaxExist,m_bCloseExist;	//ϵͳ��ť�Ƿ����

	CArray<CTRL_INFO,CTRL_INFO> m_aryControl;//�ؼ���Ϣ
	STYLE_BUTTON m_styleButton;		//��ť��ʽ
	STYLE_CHECK m_styleCheck;		//��ѡ��ť��ʽ
	STYLE_RADIO m_styleRadio;		//��ѡ��ť��ʽ
	STYLE_TEXT m_styleText;			//�ı���ʽ
	STYLE_EDIT m_styleEdit;			//�༭����ʽ
	STYLE_COMBO m_styleCombo;		//��Ͽ���ʽ
	STYLE_GROUP m_styleGroup;		//Ⱥ�����ʽ
	STYLE_FILLREGION m_styleRegion;	//�������ʽ

	CToolTipCtrl m_toolTip;//������ʾ
};

}

#endif //_MAGICUI_WINDOW_H_
