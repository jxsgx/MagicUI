//////////////////////////////////////////////////////////////////////////////////
//  �ļ���: Common.cpp											     	[Magic UI]		
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

#include "stdafx.h"
#include "Common.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommon::CCommon()
{
}

CCommon::~CCommon()
{
}

//���ô���͸��
void CCommon::SetAlpha(HWND hWnd,COLORREF clrMask,int alpha,DWORD dwFlags)
{
	HINSTANCE hInst=LoadLibrary("User32.DLL");     
	if(hInst)     
	{
		/*һЩ����:     
		WS_EX_LAYERED=0x80000;   
		LWA_ALPHA=0x2;   
		LWA_COLORKEY=0x1     
		����dwFlags��LWA_ALPHA��LWA_COLORKEY   
		LWA_ALPHA�����õĻ�,ͨ��bAlpha����͸����.   
		LWA_COLORKEY�����õĻ�,��ָ����͸��������ɫΪcrKey,������ɫ��������ʾ.   
		ע:Ҫʹʹ����ӵ��͸��Ч��,����Ҫ��WS_EX_LAYERED��չ����(��sdkҲû�е�). */  

		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);     
		MYFUNC fun=NULL;   
		//ȡ��SetLayeredWindowAttributes����ָ��     
		fun=(MYFUNC)GetProcAddress(hInst,"SetLayeredWindowAttributes");   
		if(fun) fun(hWnd,clrMask,alpha,dwFlags);     
		FreeLibrary(hInst);     
	}
}

//�ַ������
int CCommon::SplitString(CString str, char chSplitter, CStringArray &aryItem)
{
	TCHAR* p=str.GetBuffer(0);   
	TCHAR* e=p;   
	TCHAR cEnd=*e;   
	int nCount=0;   
	while(cEnd)   
	{   
		if(*e==_T('\0'))   
			cEnd=*e;   
		else if(*e==chSplitter)   
			*e=_T('\0');   
		
		if(*e)   
			e++;   
		else   
		{   
			if(*p!=_T('\0'))   
			{   
				aryItem.Add(p);   
				nCount++;   
			}   
			p=++e;   
		}   
	}   
	return nCount; 
}

//����ת�����ַ�
//nNum:����
//nSize:��ȡ����
//bFull;�����Ȳ���,�Ƿ���ǰ�����㲹��
CString CCommon::IntToStr(int nNum, int nSize, BOOL bFull)
{
	char *pBuf=new char[nSize+1];
	itoa(nNum,pBuf,10);
	CString str=pBuf;
	if(!bFull)
		return str;

	int nLen=str.GetLength();
	for(int i=0;i<nSize-nLen;i++)
	{
		str="0"+str;
	}
	return str;
}

//����ת��Ϊʱ���ʽ
CString CCommon::GetTimeStr(int nTime)
{
	int nHour,nMinute,nSecond,nTemp;
	CString strHour,strMinute,strSecond;

	nHour=nTime/(60*60);
	nTemp=nTime%(60*60);
	nMinute=nTemp/60;
	nSecond=nTemp%60;

	strHour.Format("%d",nHour);
	strMinute.Format("%d",nMinute);
	strSecond.Format("%d",nSecond);

	if(nHour<10) strHour="0"+strHour;
	if(nMinute<10) strMinute="0"+strMinute;
	if(nSecond<10) strSecond="0"+strSecond;

	return strHour+":"+strMinute+":"+strSecond;
}

//�ж��Ƿ�Ϊʱ���ʽ
BOOL CCommon::IsTimer(CString str)
{
	// format should be 16:05:00.

	if( str.GetLength() != 8 )
		return FALSE;

	BOOL bFormat=
		   _istdigit(str.GetAt(0))
		&& _istdigit(str.GetAt(1))
		&& str.GetAt(2)==_T(':')
		&& _istdigit(str.GetAt(3))
		&& _istdigit(str.GetAt(4))
		&& str.GetAt(5)==_T(':')
		&& _istdigit(str.GetAt(6))
		&& _istdigit(str.GetAt(7));
	if(!bFormat)
		return FALSE;

	int nH=atoi(str.Mid(0,2));
	int nM=atoi(str.Mid(3,2));
	int nS=atoi(str.Mid(6,2));
	if(nH<0||nH>23||nM<0||nM>59||nS<0||nS>59)
		return FALSE;

	return TRUE;
}

//�ж��Ƿ�Ϊ��ֵ
BOOL CCommon::IsNumber(CString str)
{
	if(str=="")
		return FALSE;
	for(int i=0;i< str.GetLength();i++)
		if(!_istdigit(str.GetAt(i)))
			return FALSE;

	return TRUE;
}

//�ж��Ƿ�Ϊʮ��������
BOOL CCommon::IsHexNumber(CString str)
{
	if(str=="")
		return FALSE;
	for(int i=0;i< str.GetLength();i++)
		if(!_istdigit(str.GetAt(i))&&!IsHexLetter(str.GetAt(i)))
			return FALSE;

	return TRUE;
}

//�ж��Ƿ�Ϊʮ�������ַ�
BOOL CCommon::IsHexLetter(char ch)
{
	if(ch>='A'&&ch<='F'||ch>='a'&&ch<='f')
		return TRUE;
	else
		return FALSE;
}

//ʮ�����ƴ�ת��Ϊ��ֵ
int CCommon::HexToInt(CString strHex)
{
	int rValue=0;
	int sz=strHex.GetLength();
	for(int i=0;i<sz;i++)
	{
		char ch=strHex.GetAt(i);
		int num=0;
		if(ch>='0'&&ch<='9') num=ch-48;
		else if(ch>='A'&&ch<='F') num=ch-55;
		else if(ch>='a'&&ch<='f') num=ch-87;
		else num=0;
		rValue+=num*(int)pow(1.0*16,sz-i-1);
	}
	return rValue;
}

//��ֵת��Ϊʮ�����ƴ�
CString CCommon::IntToHex(int nNum, int nSize, BOOL bFull)
{
	char *pBuf=new char[nSize+1];
	itoa(nNum,pBuf,16);
	CString str=pBuf;
	if(!bFull)
		return str;

	int nLen=str.GetLength();
	for(int i=0;i<nSize-nLen;i++)
	{
		str="0"+str;
	}
	return str;
}

//��ȡӦ�ó���·��
CString CCommon::GetAppPath()
{
	_TCHAR szDrive[_MAX_DRIVE];		//"c:"
	_TCHAR szDir[_MAX_DIR];			//"\sample\"
	_TCHAR szFile[_MAX_FNAME];		//"test"
	_TCHAR szExt[_MAX_EXT];			//".c"
	_TCHAR szFullPath[_MAX_PATH];	//"c:\sample\test.c"
	_TCHAR szAppPath[_MAX_PATH];	//"c:\sample\"

	::GetModuleFileName(NULL,szFullPath,_MAX_PATH); 
	_tsplitpath(szFullPath,szDrive,szDir,szFile,szExt);
	_tmakepath(szAppPath,szDrive,szDir,NULL,NULL);

	CString strDrive(szDrive);
	CString strDir(szDir);
	CString strFile(szFile);
	CString strExt(szExt);
	CString strFullPath(szFullPath);
	CString strAppPath(szAppPath);

	return strAppPath;
}
