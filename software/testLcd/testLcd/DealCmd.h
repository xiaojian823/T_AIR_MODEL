#pragma once
/*
	��������Ϊ����ָʾ��������������Ľ����ȷ����ȷ
*/
#include "macro.h"
#include "HardPanel.h"
class CDealCmd
{
public:
	CDealCmd(void);
	~CDealCmd(void);
public:
	void run();

public:
	int onStart(void);	//�ȴ���ʼ״̬
	int onWork(void);	//�ȴ�����״̬
	int onIdle(void);
	int doSomething(void);	//����Ǵ�������Ӧ����״̬�󵥶���Ҫ����
public:
	int randSign(void);	//��������ź�
	int chkKeyDown(void);	//��鵱ǰ����ֵ
	int chkJokstick(int nJok);	//�жϵ�λ�Ƿ���ȷ
	int setPapiLed(void);	//���ݲ��������������PAPI��
	int rstPapiLed(void);	//����PAPI��
	//�������״̬�Ƿ���ȷ
	int chkManual(void);

	//ˢ��ͼƬ��״̬
	int invalidate(void);
	int setBackLeft(void);	//���������ʾ��ͼƬ
	int setBackShow0(void);	//��ʾͼƬ0
	int setBackShow1(void); //��ʾͼƬ1
	int setBackShow2(void);
	int setBackShow3(void);
	int setBackShow4(void);
	int setBackShow5(void);
	int setBackShow6(void);
	int setBackShow7(void);
	int showBackFont(char* str);	//��ʾ������
public:
	CHardPanel m_hard;
	int m_nextStep;
	int m_lstTime;
	char m_strWind[32];	//��	
};


#define Rand_MAX 0x7FFF

unsigned long _Randseed = 1;

static int (Rand)(void){
	_Randseed = _Randseed * 1103515245 + 12345;
	return ((unsigned int)(_Randseed >> 16) & Rand_MAX);
}

static void (SRand)(unsigned int seed){
	_Randseed = seed;}
