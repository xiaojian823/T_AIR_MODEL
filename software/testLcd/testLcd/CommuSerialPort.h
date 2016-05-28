#pragma once

#include <vector>
using namespace std;

typedef enum{
	enOk,
	enFail
};

class CCommuSerialPort
{
public:
	CCommuSerialPort(void);
	~CCommuSerialPort(void);
public:
	//ö�ٴ���
	void EnumerateSerialPorts(void);
	//�õ�ö�ٴ���
	bool getSerialPorts(vector<int>& ports);
	
	void setPort(int n, int baudrate);
	int getPort();

	//�򿪴���
	int open();
	int close();
	int write(void* pData, int nInLen);
	int read(void* pData, DWORD& nReadLen);

public:
	vector<int> m_ports;
	int m_port;
	int m_baud;
	HANDLE m_handle;
};

