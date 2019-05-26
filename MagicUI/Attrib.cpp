//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: Attrib.cpp											     	[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  ����:
//
//		Magic ʵ��xml��ǩ���Խ���
//
//  ��������: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Attrib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAttrib::CAttrib()
{
}

CAttrib::~CAttrib()
{
}

//ת��CString("0,0,100,200") => CPoint(0,0) + CSize(100,200)
BOOL CAttrib::GetRect(CString strRect,CPoint &pt,CSize &sz)
{
	if(strRect.IsEmpty()) return FALSE;
	CStringArray strAry;
	strAry.RemoveAll();
	int nCount=CCommon::SplitString(strRect,',',strAry);
	if(nCount!=4) return FALSE;
	pt.x=atoi(strAry.GetAt(0));
	pt.y=atoi(strAry.GetAt(1));
	sz.cx=atoi(strAry.GetAt(2));
	sz.cy=atoi(strAry.GetAt(3));

	return TRUE;
}

//ת��CString("0,0,100,200") => CRect(0,0,100,200)
BOOL CAttrib::GetRect(CString strRect,CRect &rect)
{
	CPoint pt;
	CSize sz;
	if(!GetRect(strRect,pt,sz)) return FALSE;
	rect=CRect(pt.x,pt.y,sz.cx,sz.cy);
	
	return TRUE;
}

//ת��CString("#ffeedd") �� CString("255,238,182") => RGB(255,238,182)
BOOL CAttrib::GetColor(CString strColor,COLORREF &color)
{
/*	����strColor��ʽ����Ϊ:
	��ҳ��ʽ: "#FFEEDD"(��Сд����) �� 
	RGB ��ʽ:  "255,238,182"
*/
	//�ж�strColorΪ�ǿ��ִ�
	if(strColor.IsEmpty()) return FALSE;
	int len=strColor.GetLength();
	
	if(strColor.GetAt(0)=='#')	//����ҳ��ʽ����
	{
		//�ж�strHexΪ6λʮ��������
		if(len!=7) return FALSE;
		CString strHex=strColor.Right(len-1);
		if(!CCommon::IsHexNumber(strHex)) return FALSE;

		int r=CCommon::HexToInt(strHex.Mid(0,2));
		int g=CCommon::HexToInt(strHex.Mid(2,2));
		int b=CCommon::HexToInt(strHex.Mid(4,2));
		color=r+256*g+256*256*b;
	}
	else						//��RGB��ʽ����
	{
		CStringArray strAry;
		strAry.RemoveAll();
		int nCount=CCommon::SplitString(strColor,',',strAry);
		if(nCount!=3) return FALSE;

		int r=atoi(strAry.GetAt(0));
		int g=atoi(strAry.GetAt(1));
		int b=atoi(strAry.GetAt(2));
		color=r+256*g+256*256*b;
	}

	return TRUE;
}

//ת��CString("true") => BOOL(TRUE)
BOOL CAttrib::GetBool(CString strBool,BOOL &bBool)
{
	strBool.MakeLower();
	if(strBool=="true"||strBool=="1")
		bBool=TRUE;
	else if(strBool=="false"||strBool=="0")
		bBool=FALSE;
	else
		return FALSE;

	return TRUE;
}

//ת��CString("100,200") => CSize(100,200)
BOOL CAttrib::GetSize(CString strSize,CSize &sz)
{
	if(strSize.IsEmpty()) return FALSE;
	CStringArray strAry;
	strAry.RemoveAll();
	int nCount=CCommon::SplitString(strSize,',',strAry);
	if(nCount!=2) return FALSE;
	sz.cx=atoi(strAry.GetAt(0));
	sz.cy=atoi(strAry.GetAt(1));

	return TRUE;
}

//ת��CString("0,0") => CPoint(0,0)
BOOL CAttrib::GetPoint(CString strPoint,CPoint &pt)
{
	if(strPoint.IsEmpty()) return FALSE;
	CStringArray strAry;
	strAry.RemoveAll();
	int nCount=CCommon::SplitString(strPoint,',',strAry);
	if(nCount!=2) return FALSE;
	pt.x=atoi(strAry.GetAt(0));
	pt.y=atoi(strAry.GetAt(1));

	return TRUE;
}

//��ȡ��׼�������
HCURSOR CAttrib::GetStdCursor(CString strName)
{
	strName.MakeLower();
	if(strName=="arrow")
		return LoadCursor(NULL,IDC_ARROW);
	else if(strName=="ibeam")
		return LoadCursor(NULL,IDC_IBEAM);
	else if(strName=="wait")
		return LoadCursor(NULL,IDC_WAIT);
	else if(strName=="cross")
		return LoadCursor(NULL,IDC_CROSS);
	else if(strName=="uparrow")
		return LoadCursor(NULL,IDC_UPARROW);
	else if(strName=="size")
		return LoadCursor(NULL,IDC_SIZE);
	else if(strName=="icon")
		return LoadCursor(NULL,IDC_ICON);
	else if(strName=="sizenwse")
		return LoadCursor(NULL,IDC_SIZENWSE);
	else if(strName=="sizenesw")
		return LoadCursor(NULL,IDC_SIZENESW);
	else if(strName=="sizewe")
		return LoadCursor(NULL,IDC_SIZEWE);
	else if(strName=="sizens")
		return LoadCursor(NULL,IDC_SIZENS);
	else if(strName=="sizeall")
		return LoadCursor(NULL,IDC_SIZEALL);
	else if(strName=="no")
		return LoadCursor(NULL,IDC_NO);
	else if(strName=="hand")
		return LoadCursor(NULL,IDC_HAND);
	else if(strName=="appstarting")
		return LoadCursor(NULL,IDC_APPSTARTING);
	else if(strName=="help")
		return LoadCursor(NULL,IDC_HELP);
	else
		return NULL;
}