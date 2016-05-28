#include "StdAfx.h"
#include "CommuSerialPort.h"

CCommuSerialPort::CCommuSerialPort( void )
{
	m_handle = INVALID_HANDLE_VALUE;
	m_port = 0;
}


CCommuSerialPort::~CCommuSerialPort(void)
{
}

void CCommuSerialPort::EnumerateSerialPorts( void )
{
	m_ports.clear();
	
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	BOOL bGetVer = GetVersionEx(&osvi);

	if (bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
	{
		int i = 0;
		for(;;)
		{
			TCHAR szDevices[65535];
			DWORD dwChars = QueryDosDevice(NULL, szDevices, 65535);
			if (dwChars)
			{
				TCHAR* pszCurrentDevice = &szDevices[i];
				int nLen = _tcslen(pszCurrentDevice); 
				if (nLen > 3 && _tcsncmp(pszCurrentDevice, _T("COM"), 3) == 0)
				{
					int nPort = _ttoi(&pszCurrentDevice[3]);
					m_ports.push_back(nPort);
				}
				while(szDevices[i] != _T('\0'))  
					i++;
				i++;
				if (szDevices[i] == _T('\0'))
					break;
			}
			else
			{
				TRACE(_T("Failed in call to QueryDosDevice, GetLastError:%d\n"), GetLastError()); 
			}
		}
	}
	else
	{
		for (int i = 0; i < 256; i++)
		{
			CString sPort;
			sPort.Format(_T("\\\\.\\COM%d"), i);

			//Try to open the port
			BOOL bSuccess = FALSE;
			HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
			if (hPort == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = GetLastError();
				//Check to see if the error was because some other app had the port open or a general failure
				if (dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
					bSuccess = TRUE;
			}
			else
			{
				//The port was opened successfully
				bSuccess = TRUE;
				//Don't forget to close the port, since we are going to do nothing with it anyway
				CloseHandle(hPort);
			}
			//Add the port number to the array which will be returned
			if (bSuccess)
				m_ports.push_back(i);
		}
	}
}

bool CCommuSerialPort::getSerialPorts( vector<int>& ports )
{
	bool bRet = false;
	if (!m_ports.empty())
	{
		ports = m_ports;
		bRet = true;
	}
	return bRet;
}

void CCommuSerialPort::setPort( int n , int baudrate)
{
	m_port = n;
	m_baud = baudrate;
}

int CCommuSerialPort::getPort()
{
	return m_port;
}

int CCommuSerialPort::open()
{
	int err = enOk;
	HANDLE hCom;
	CString strPort;
	strPort.Format(_T("COM%d"),m_port);
	hCom=CreateFile(strPort,GENERIC_READ|GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,0,NULL);   //打开串口
	if(hCom==(HANDLE)-1)
	{
		return enFail;
	}
	else
	{
		m_handle = hCom;
		SetupComm(hCom,100,100); //输入缓冲区和输出缓冲区的大小都是100
		COMMTIMEOUTS TimeOuts;
		//设定读超时
		TimeOuts.ReadIntervalTimeout=MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier=0;
		TimeOuts.ReadTotalTimeoutConstant=0;
		//在读一次输入缓冲区的内容后读操作就立即返回，
		//而不管是否读入了要求的字符。

		//设定写超时
		TimeOuts.WriteTotalTimeoutMultiplier=100;
		TimeOuts.WriteTotalTimeoutConstant=500;
		SetCommTimeouts(hCom,&TimeOuts); //设置超时
		DCB dcb;
		GetCommState(hCom,&dcb);
		dcb.BaudRate=m_baud; //波特率为9600
		dcb.ByteSize=8; //每个字节有8位
		dcb.Parity=NOPARITY; //无奇偶校验位
		dcb.StopBits=ONESTOPBIT ; //停止位
		SetCommState(hCom,&dcb);
		PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);
	}
	return err;
}

int CCommuSerialPort::close()
{
	int err = enOk;
	if (m_handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_handle);
		m_handle = INVALID_HANDLE_VALUE;
	}
	return err;
}

int CCommuSerialPort::write( void* pData, int nInLen )
{
	int err = enOk;
	DWORD dwBytesWrite=nInLen;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(m_handle,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(m_handle,pData,dwBytesWrite,&dwBytesWrite,NULL);
	if(!bWriteStat)
	{
		err = enFail;
	}
	return err;
}

int CCommuSerialPort::read( void* pData, DWORD& nReadLen )
{
	int err = enOk;
	BOOL bReadStat;

	bReadStat=ReadFile(m_handle,pData,1024,&nReadLen,NULL);
	if(!bReadStat){
		err = enFail;
	}
	PurgeComm(m_handle, PURGE_TXABORT|
		PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	return err;
}
