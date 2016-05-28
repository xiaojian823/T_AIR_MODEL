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

	enBtnInvalid,	//û���õ�
}enBtn;

//��ʾ���ұߵ�ͼ
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

//���屳������λ��
#define backPosLeft 0
#define backPosTop 0
#define backPosWidth 600
#define backPosHeight 600

//���屳���ֵ�λ��
#define BACK_FONT_TOP 0
#define BACK_FONT_LEFT 600

#define FONT_TYPE 0	//�ֿ����


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

//��������
typedef struct
{
	int mode;	//ʵ��ģʽ
	int id;	//�����߱��
	int times;	//ʵ�ִ���
	int papiState;	//papi��״̬
	int idlespeed;	//����
	int winddirec;	//����
	int pose;	//��̬
	int rtTime;	//��Ӧʱ��
	int joystick;	//���ݸ�
	int accelerator;	//����
	int rudder;	//�����
	int result;	//���
}tConfigPara,*ptConfigPara;

//��Ϊ0����Ϊ1
typedef struct 
{
	int leda;
	int ledb;
	int ledc;
	int ledd;
}tLedPara,*ptLedPara;

//���ֹ���״̬
typedef struct _tWorkPara
{
	int caozonggan;	//���ݸ�
	int youmen;	//����
	int fangxiangtuo;	//�����
}tWorkPara,*ptWorkPara;

//

//ȫ�ֲ���
typedef struct _tGlobalPara
{
	tWorkPara stWorkPara;
	tConfigPara stCfgPara;
	int nStep;
	unsigned char ucRecKey[2];	//ֻ��¼������µ����μ�ֵ
	int nKeyCount;	//�ܹ����˼��μ�
	unsigned char ucCurKey;
	int bKeyDown;	//��ǰ�Ƿ��а���
	int bStartTime;	//�Ƿ�ʼ����

	int nBackLeft;	//Ҫ��ʾ�ı�����ߵ�ͼ
	int bBackLeftShow;	//����Ƿ񿪹�
	
	int nBackRight;	//�ұߵ�״��ͼ
	int nLstTime;	//��һ�μ�ʱʱ�䣬�����Ҫ�����м�մ���ʱ��ļ���
	int bNeedInvalidate;	//�Ƿ���Ҫˢ��
}tGlobalPara,*ptGlobalPara;

extern  tGlobalPara  g_stGlobalPara;

