#pragma once
/*
	整个过程为根据指示灯来检测所操作的结果正确不正确
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
	int onStart(void);	//等待开始状态
	int onWork(void);	//等待工作状态
	int onIdle(void);
	int doSomething(void);	//这个是处理完相应命令状态后单独需要做的
public:
	int randSign(void);	//产生随机信号
	int chkKeyDown(void);	//检查当前按键值
	int chkJokstick(int nJok);	//判断档位是否正确
	int setPapiLed(void);	//根据产生的随机量点亮PAPI灯
	int rstPapiLed(void);	//关灭PAPI灯
	//检查三个状态是否正确
	int chkManual(void);

	//刷新图片和状态
	int invalidate(void);
	int setBackLeft(void);	//设置左边显示的图片
	int setBackShow0(void);	//显示图片0
	int setBackShow1(void); //显示图片1
	int setBackShow2(void);
	int setBackShow3(void);
	int setBackShow4(void);
	int setBackShow5(void);
	int setBackShow6(void);
	int setBackShow7(void);
	int showBackFont(char* str);	//显示背景字
public:
	CHardPanel m_hard;
	int m_nextStep;
	int m_lstTime;
	char m_strWind[32];	//风	
};


#define Rand_MAX 0x7FFF

unsigned long _Randseed = 1;

static int (Rand)(void){
	_Randseed = _Randseed * 1103515245 + 12345;
	return ((unsigned int)(_Randseed >> 16) & Rand_MAX);
}

static void (SRand)(unsigned int seed){
	_Randseed = seed;}
