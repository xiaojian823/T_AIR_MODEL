#pragma once
class CHardPanel
{
public:
	typedef enum
	{
		enWhiteColor,	//��ɫ��
		enReadColor,	//��ɫ��
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
	//PARI������
	void ledp1(int bOn, int nColor);
	void ledp2(int bOn, int nColor);
	void ledp3(int bOn, int nColor);
	void ledp4(int bOn, int nColor);
	//����LED��
	void ledc1(int bOn);
	void ledc2(int bOn);
	void ledc3(int bOn);
	void ledcr(int bOn);
	void ledc4(int bOn);
	void ledc5(int bOn);
	void ledplus1(int bOn);
	void leddec2(int bOn);
	void ledrst(int bOn);

	//ɨ�谴��
	int scanbtn(void);	
	int scanno(void);	//ɨ�����
	int scandriver(void);	//���ݸ�
	int scanplus(void);	//����
	int scanstart(void);	//��ʼ��ťɨ��
	int scandirect(void);	//�����

	//�л�����
	int chgBackGround(int nType,int param1 = -1,int param2 = -1);	//���ݲ������л�����
	int chgBackGroudPic(int nId);	//��ʾID�ţ����λ���ǹ̶���
	//�����ļ�
	int writefile(void* pData, int nInLen);
	//�õ���ǰʱ��
	int getTickCount();
};

