#include "stdafx.h"
#include "FileLogger.h"


CFileLogger& CFileLogger::Instance()
{
	static CFileLogger log;
	return log;
}

CFileLogger::CFileLogger(void)
{
	//	operator()();
	rollingType_=RollingDate;
	rollingNum_=6;
	fileName_ =new char[MAX_PATH + 1];
	fileTypeName_[0]="Info";
	fileTypeName_[1]="Error";
	fileTypeName_[2]="System";
	for(int i=0;i<LOG_NUM;i++)
		hLogFile_[i]=INVALID_HANDLE_VALUE;
	hEvent = CreateEventA(
		NULL,        // no security attributes
		FALSE,       // Auto reset event
		FALSE,       // initially set to non signaled state
		"LogEvent");  // un named event

	_beginthread(SaveLog, 0, this);
}


CFileLogger::~CFileLogger()
{
	SetEvent(hEvent);
	::Sleep(200);
	delete [] fileName_;
	for(int i=0;i<LOG_NUM;i++)
	{
		if (hLogFile_[i] != INVALID_HANDLE_VALUE)
			CloseHandle(hLogFile_[i]);
	}
	logDataQueue_.Clear();
	CloseHandle(hEvent);
}

void CFileLogger::SetLogType(RollingType rollingType,unsigned int rollingNum)
{
	rollingType_=rollingType;
	rollingNum_=rollingNum;
}

void CFileLogger::Log(unsigned int logType, char *pstrFmt, ...)
{
	LogData* data=(LogData*)malloc(sizeof(LogData));
	memset(data, 0, sizeof(LogData));

	va_list v1;
	va_start(v1, pstrFmt);
	_vsnprintf(data->strText, MAX_LOGTEXT_LEN, pstrFmt, v1);
	va_end(v1);

	data->iType = logType;
	SYSTEMTIME time;
	GetLocalTime(&time);

	sprintf(data->strDate, "%d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);

	logDataQueue_.Push(data);
	SetEvent(hEvent);
}

_int64 GetPosition64(HANDLE hFile)
{
	if (!hFile || hFile==INVALID_HANDLE_VALUE)
		return -1;
	LONG low=0;
	LONG high=0;
	low=SetFilePointer(hFile, low, &high, FILE_CURRENT);
	if (low==0xFFFFFFFF && GetLastError!=NO_ERROR)
		return -1;
	return ((_int64)high<<32)+low;
}

void CFileLogger::CheckLogFile()
{
	//Get logfile path
	char path[MAX_PATH + 1000]; //Make it large enough
	strcpy(path, ".\\Logs\\");

	//Get logfile name
	for(int i=0;i<LOG_NUM;i++)
	{
		char filename[MAX_PATH + 1];
		if (rollingType_==RollingFile)
		{
			strcpy(filename, "log.log");
		}
		else
		{
			SYSTEMTIME time;
			GetLocalTime(&time);
			sprintf(filename, "log-%s-%d-%02d-%02d.log",*(fileTypeName_+i), time.wYear, time.wMonth, time.wDay);
		}

		if (hLogFile_[i] == INVALID_HANDLE_VALUE || (fileName_ && strcmp(fileName_, filename)))
		{
			char buffer[MAX_PATH + 1000]; //Make it large enough
			strcpy(buffer, path);
			CreateDirectoryA(buffer, NULL);

			if (fileName_)
				delete [] fileName_;
			fileName_ = new char[strlen(filename)+1];
			strcpy(fileName_, filename);	
			strcat(buffer, filename);

			if (hLogFile_[i] != INVALID_HANDLE_VALUE)
				CloseHandle(hLogFile_[i]);
			hLogFile_[i] = CreateFileA(buffer, GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ, 0, OPEN_ALWAYS, 0, 0);
			if (hLogFile_[i] == INVALID_HANDLE_VALUE)
				return ;

			SetFilePointer(hLogFile_[i], 0, 0, FILE_END);
		}
	}
	_int64 nLimit = rollingNum_*1024;//m_pOptions->GetOptionVal(OPTION_LOGLIMITSIZE);

	if (rollingType_==RollingDate)
	{
		//Different logfiles for each day
		//Find all log files, delete old ones
		//Also delete newer ones if total size exceeds limit

		//Get current date

		SYSTEMTIME time;
		FILETIME curFileTime;
		GetLocalTime(&time);
		SystemTimeToFileTime(&time, &curFileTime);
		_int64 nTime = curFileTime.dwLowDateTime + ((_int64)curFileTime.dwHighDateTime<<32);

		char buffer[MAX_PATH + 1000]; //Make it large enough
		strcpy(buffer, path);
		strcat(buffer, "log-*.log");

		WIN32_FIND_DATAA FindFileData;
		WIN32_FIND_DATAA NextFindFileData;
		HANDLE hFind;
		hFind = FindFirstFileA(buffer, &NextFindFileData);

		_int64 nDeleteTime = (_int64)rollingNum_;
		if (nDeleteTime)
			nDeleteTime = (nDeleteTime+1) * 60 * 60 * 24 * 10000000;

		//Count total size of all logs, delete the oldest log if exceeding limit
		_int64 totalsize = 0;
		string oldestname;
		_int64 oldestDate = 0;

		while (hFind != INVALID_HANDLE_VALUE)
		{
			FindFileData=NextFindFileData;
			if (!FindNextFileA(hFind, &NextFindFileData))
			{
				FindClose(hFind);
				hFind = INVALID_HANDLE_VALUE;
			}

			if (!strcmp(FindFileData.cFileName, ".") || !strcmp(FindFileData.cFileName, ".."))
				continue;

			_int64 size = ((_int64)FindFileData.nFileSizeHigh<<32) + FindFileData.nFileSizeLow;
			if (!strcmp(FindFileData.cFileName, fileName_))
			{
				totalsize += size;
				continue;
			}

			_int64 curtime=FindFileData.ftLastWriteTime.dwLowDateTime + ((_int64)FindFileData.ftLastWriteTime.dwHighDateTime<<32);
			_int64 span = nTime - curtime;
			char filename[MAX_PATH + 1000];
			strcpy(filename, path);
			strcat(filename, FindFileData.cFileName);
			if (nDeleteTime && span > nDeleteTime)
				DeleteFileA(filename); //File is too old, delete it
			else
			{
				totalsize += size;
				if (curtime < oldestDate || !oldestDate)
				{
					oldestDate = curtime;
					oldestname = filename;
				}
			}
		}

		/*if (strcmp(oldestname.c_str(), "") && nLimit && totalsize > nLimit*1024)
		{
		DeleteFileA(oldestname.c_str());
		return ;
		}*/
	}
	else //文件大小控制
	{
		_int64 size = GetPosition64(hLogFile_);
		size /= 1024;
		if (size > nLimit) //Log file too large, shrink it...
		{
			int curReadPos = (int)(size * 1024 - (nLimit * 1024) * 0.99); //New log size is 1% smaller than the set limit
			int curWritePos =0;
			const int bufsize = 16384; // 16KB
			char buffer[bufsize];
			DWORD numread;
			DWORD numwritten;
			BOOL bFirst = TRUE;;
			do {
				SetFilePointer(hLogFile_, curReadPos, 0, FILE_BEGIN);
				if (!ReadFile(hLogFile_, buffer, bufsize, &numread, 0))
					break;
				curReadPos += numread;

				SetFilePointer(hLogFile_, curWritePos, 0, FILE_BEGIN);
				if (bFirst) //Assure log starts with complete line
				{
					unsigned int i;
					for (i=0; i<numread; i++)
					{
						if (buffer[i] == '\n')
							break;
					}
					if (i >= (numread-1))
						continue;
					bFirst = FALSE;
					if (!WriteFile(hLogFile_, buffer + i + 1, numread - i - 1, &numwritten, 0))
						break;
				}
				else
					if (!WriteFile(hLogFile_, buffer, numread, &numwritten, 0))
						break;
				curWritePos += numwritten;

			} while (numread == bufsize);

			SetFilePointer(hLogFile_, curWritePos, 0, FILE_BEGIN);
			SetEndOfFile(hLogFile_);
		}
	}
}

void SaveLog(void* pParam)
{
	CFileLogger * pFileLogger = (CFileLogger *) pParam;   
	while(true)
	{
		WaitForSingleObject(
			pFileLogger->hEvent,    // Mutex handle
			INFINITE);   // Infinite wait
		pFileLogger->CheckLogFile();
		while(!pFileLogger->logDataQueue_.isEmpty())
		{
			char logText[MAX_LOGTEXT_LEN];
			LogData* lpLogData=pFileLogger->logDataQueue_.Front();
			pFileLogger->logDataQueue_.Pop();
			if(pFileLogger->hLogFile_!=INVALID_HANDLE_VALUE)
			{
				if(lpLogData->iType==LOG_TYPE_INFO)
				{
					sprintf(logText, "%s [INFO] %s\r\n", lpLogData->strDate,lpLogData->strText,pFileLogger->logDataQueue_.Size());
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),GREEN );
				}
				else if(lpLogData->iType==LOG_TYPE_ERROR)
				{
					sprintf(logText, "%s [ERROR] %s\r\n", lpLogData->strDate,lpLogData->strText,pFileLogger->logDataQueue_.Size());
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),RED );
				}
				else
				{
					sprintf(logText, "%s [SYSTEM] %s\r\n", lpLogData->strDate,lpLogData->strText,pFileLogger->logDataQueue_.Size());
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),DARKGRAY );
				}
				printf("%s\r",logText);
				DWORD numwritten;
				WriteFile(pFileLogger->hLogFile_[lpLogData->iType],logText,strlen(logText),&numwritten, 0);
			}

			free((void*)lpLogData);
			lpLogData=NULL;
		}
		//::Sleep(TIMER_ELAPSE);
	}
}