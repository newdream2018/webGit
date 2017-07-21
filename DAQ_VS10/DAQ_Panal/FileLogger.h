

#if !defined(AFX_FILELOGGER_H__FDF4A6C8_5A47_40FE_8D82_804E0DCCE3FE__INCLUDED_)
#define AFX_FILELOGGER_H__FDF4A6C8_5A47_40FE_8D82_804E0DCCE3FE__INCLUDED_

#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "CQueueThread.h"
#include <process.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_LOGTEXT_LEN		(1024*8)

#define LOG_TYPE_INFO		0             /* ��־����: ��Ϣ����*/
#define LOG_TYPE_ERROR		1             /* ��־����: ��������*/
#define LOG_TYPE_SYSTEM		2             /* ��־����: ϵͳ����*/

#define LOG_NUM				3

#define MAX_FILE_PATH		(255) 

#define LOG		CFileLogger::Instance().Log

using namespace std;

enum Color {	
	DARKBLUE = 1, 
	DARKGREEN, 
	DARKTEAL, 
	DARKRED, 
	DARKPINK, 
	DARKYELLOW, 
	GRAY, 
	DARKGRAY, 
	BLUE, 
	GREEN, 
	TEAL, 
	RED, 
	PINK, 
	YELLOW, 
	WHITE 
};

typedef enum 
{
	RollingFile,						//����־��С�ع�����
	RollingDate							//ÿ��һ���ļ�Log-2012-11-11.log��ʽ
} RollingType;

typedef struct               /* ��־���ݽṹ��*/
{
	char	            strDate[23];   /* ����:��ʽΪ��:2012-07-13 12:47:20,859*/
	unsigned int		iType;         /* ��־����:3��:INFO(0)/ERROR(1)/SYSTEM(2)*/
	char	            strText[MAX_LOGTEXT_LEN]; /*��־����*/
}LogData;

class CFileLogger  
{
public:
	void Log(unsigned int logType, char *pstrFmt, ...);
	CFileLogger(void);
	CFileLogger(const CFileLogger&);//noncopyable
	static CFileLogger& Instance();
	~CFileLogger();
	void SetLogType(RollingType rollingType,unsigned int rollingNum);
	friend void SaveLog(void* pParam);
private:
	char* fileTypeName_[LOG_NUM];//={"INFO","ERROR","SYSTEM"};
	RollingType rollingType_;
	unsigned int  rollingNum_;
	char*   fileName_;
	HANDLE	hLogFile_[LOG_NUM];
	QueueThread<LogData*> logDataQueue_;
	HANDLE	hEvent;
	void    CheckLogFile();
};

#endif // !defined(AFX_FILELOGGER_H__FDF4A6C8_5A47_40FE_8D82_804E0DCCE3FE__INCLUDED_)
