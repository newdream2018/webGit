

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

#define LOG_TYPE_INFO		0             /* 日志类型: 信息类型*/
#define LOG_TYPE_ERROR		1             /* 日志类型: 错误类型*/
#define LOG_TYPE_SYSTEM		2             /* 日志类型: 系统类型*/

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
	RollingFile,						//按日志大小回滚复用
	RollingDate							//每天一个文件Log-2012-11-11.log格式
} RollingType;

typedef struct               /* 日志内容结构体*/
{
	char	            strDate[23];   /* 日期:格式为如:2012-07-13 12:47:20,859*/
	unsigned int		iType;         /* 日志类型:3种:INFO(0)/ERROR(1)/SYSTEM(2)*/
	char	            strText[MAX_LOGTEXT_LEN]; /*日志内容*/
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
