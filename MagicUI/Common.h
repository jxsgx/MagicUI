//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: Common.h											     	[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic ͨ����(ʵ�ֶ�������)
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_COMMON_H_
#define _MAGICUI_COMMON_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WS_EX_LAYERED	0x80000  
#define LWA_ALPHA		0x2  
#define LWA_COLORKEY	0x1

class CCommon  
{
public:
	//��ȡӦ�ó���·��
	static CString GetAppPath();
	//��ֵת��Ϊ�ַ���
	static CString IntToStr(int nNum,int nSize,BOOL bFull=FALSE);
	//ʮ�����ƴ�ת��Ϊ��ֵ
	static int HexToInt(CString strHex);
	//�ж��Ƿ�Ϊʮ�������ַ�
	static BOOL IsHexLetter(char ch);
	//�ж��Ƿ�Ϊʮ��������
	static BOOL IsHexNumber(CString str);
	//�ж��Ƿ�Ϊ��ֵ
	static BOOL IsNumber(CString str);
	//�ж��Ƿ�Ϊʱ���ʽ
	static BOOL IsTimer(CString str);
	//����ת��Ϊʱ���ʽ
	static CString GetTimeStr(int nTime);
	//��ֵת��Ϊʮ�����ƴ�
	static CString IntToHex(int nNum, int nSize, BOOL bFull=FALSE);
	//�ַ������
	static int SplitString(CString str, char chSplitter, CStringArray& aryItem);
	//���ô���͸��
	static void SetAlpha(HWND hWnd,COLORREF clrMask,int alpha,DWORD dwFlags);//���ô���͸��
	CCommon();
	virtual ~CCommon();

};

#endif //_MAGICUI_COMMON_H_
