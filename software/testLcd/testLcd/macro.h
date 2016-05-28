#pragma once

typedef enum{
	enSucess,
	enErr,
	enWaiting,
};

typedef enum
{
	enStep_Start,
	enStep_Work,
	enStepIdle,
}enCmdStep;

typedef enum{
	enBtn0 = 0,
	enBtn1,
	enBtn2,
	enBtn3,
	enBtn4,
	enBtn5,
	enBtn6,
	enBtn7,
	enBtn8,
	enBtn9,
	enBtnM,
	enBtnP,
	enBtnBack,
	enBtnY,
	enBtnLeft,
	enBtnRight,
	enBtnPwr,
	enBtnStart,
	enBtnClr,

	enBtnTui,
	enBtnShaoTui,
	enBtnBaochi,
	enBtnFuwei,
	enBtnShaola,
	enBtnla,
	enBtnJiayou,
	enBtnjiaFuWei,
	enBtnJianyou,

	enBtnInvalid,	//没有用的
}enBtn;

//显示的右边的图
typedef enum
{
	enBackPicRight0,
	enBackPicRight1,
	enBackPicRight2,
	enBackPicRight3,
	enBackPicRight4,
	enBackPicRight5,
	enBackPicRight6,
	enBackPicRight7
}enBackPicRight;

typedef enum
{
	enShowPic0,
	enShowPic1,
	enShowPic2,
	enShowPic3,
	enShowPic4,
	enShowPic5,
	enShowPic6,
	enShowPic7,
}enShowPic;

typedef enum
{
	enMode_none,
	enMode_setMode,
	enMode_setId
}enMode;

//定义背景各个位置
#define backPosLeft 0
#define backPosTop 0
#define backPosWidth 600
#define backPosHeight 600

//定义背景字的位置
#define BACK_FONT_TOP 0
#define BACK_FONT_LEFT 600

#define FONT_TYPE 0	//字库编码


typedef enum
{
	enBackPic0ID = 1,
	enBackPic1ID = 2,
	enBackPic2ID = 3,
	enBackPic3ID = 4,
	enBackPic4ID = 5,
	enBackPic5ID = 6,
	enBackPic6ID = 7
}enPicId;

//参数设置
typedef struct
{
	int mode;	//实验模式
	int id;	//被试者编号
	int times;	//实现次数
	int papiState;	//papi灯状态
	int idlespeed;	//空速
	int winddirec;	//风向
	int pose;	//姿态
	int rtTime;	//反应时间
	int joystick;	//操纵杆
	int accelerator;	//油门
	int rudder;	//方向舵
	int result;	//结果
}tConfigPara,*ptConfigPara;

//白为0，红为1
typedef struct 
{
	int leda;
	int ledb;
	int ledc;
	int ledd;
}tLedPara,*ptLedPara;

//三种工作状态
typedef struct _tWorkPara
{
	int caozonggan;	//操纵杆
	int youmen;	//油门
	int fangxiangtuo;	//方向舵
}tWorkPara,*ptWorkPara;

//

//全局参数
typedef struct _tGlobalPara
{
	tWorkPara stWorkPara;
	tConfigPara stCfgPara;
	int nStep;
	unsigned char ucRecKey[2];	//只记录最初按下的两次键值
	int nKeyCount;	//总共按了几次键
	unsigned char ucCurKey;
	int bKeyDown;	//当前是否有按键
	int bStartTime;	//是否开始计数

	int nBackLeft;	//要显示的背景左边的图
	int bBackLeftShow;	//左边是否开挂
	
	int nBackRight;	//右边的状况图
	int nLstTime;	//上一次计时时间，这个主要用于中间空窗期时间的计算
	int bNeedInvalidate;	//是否需要刷新
}tGlobalPara,*ptGlobalPara;

extern  tGlobalPara  g_stGlobalPara;

