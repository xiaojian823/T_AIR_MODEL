#pragma once
class CHardPanel
{
public:
	typedef enum
	{
		enWhiteColor,	//白色灯
		enReadColor,	//红色灯
	}enColor;

	typedef enum
	{
		enOn,
		enClose
	}enSwitch;
public:
	CHardPanel(void);
	~CHardPanel(void);
public:
	//PARI灯亮灭
	void ledp1(int bOn, int nColor);
	void ledp2(int bOn, int nColor);
	void ledp3(int bOn, int nColor);
	void ledp4(int bOn, int nColor);
	//控制LED灯
	void ledc1(int bOn);
	void ledc2(int bOn);
	void ledc3(int bOn);
	void ledcr(int bOn);
	void ledc4(int bOn);
	void ledc5(int bOn);
	void ledplus1(int bOn);
	void leddec2(int bOn);
	void ledrst(int bOn);

	//扫描按键
	int scanbtn(void);	
	int scanno(void);	//扫描键盘
	int scandriver(void);	//操纵杠
	int scanplus(void);	//油门
	int scanstart(void);	//开始按钮扫描
	int scandirect(void);	//方向杆

	//切换背景
	int chgBackGround(int nType,int param1 = -1,int param2 = -1);	//根据操作来切换背景
	int chgBackGroudPic(int nId);	//显示ID号，这个位置是固定的
	//保存文件
	int writefile(void* pData, int nInLen);
	//得到当前时间
	int getTickCount();
};

