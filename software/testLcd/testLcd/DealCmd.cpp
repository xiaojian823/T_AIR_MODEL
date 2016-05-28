#include "StdAfx.h"
#include "DealCmd.h"
#include "hmi_driver.h"

tGlobalPara  g_stGlobalPara;

CDealCmd::CDealCmd(void)
{
	g_stGlobalPara.nStep = enStep_Start;
	memset(&g_stGlobalPara, 0, sizeof g_stGlobalPara);
	memset(m_strWind,0,sizeof m_strWind);
	m_lstTime = 0;
}


CDealCmd::~CDealCmd(void)
{
}

void CDealCmd::run()
{
	int ret = 0;
	//��鵱ǰ����ֵ������û�б���������
	chkKeyDown();
	switch (g_stGlobalPara.nStep)
	{
	case enStep_Start:
		ret= onStart();
		break;
	case enStep_Work:
		ret = onWork();
		break;
	case enStepIdle:
		ret = onIdle();
		break;
	default:
		break;
	}
	doSomething();
}

int CDealCmd::randSign( void )
{
	int err = 0;
	int nRand = Rand();
	ptConfigPara ptPara = (ptConfigPara)&g_stGlobalPara.stCfgPara;
	ptPara->papiState = nRand%5 + 1;
	ptPara->idlespeed = nRand%40 + 40;
	ptPara->winddirec = nRand%2;
	ptPara->pose = nRand%2;
	ptPara->joystick = nRand%6;
	ptPara->accelerator = nRand%3;
	ptPara->rudder = nRand%2;

	return err;
}

int CDealCmd::chkJokstick( int nJok )
{
	int err = enSucess;
	if (nJok)
	{
	}
	return err;
}

int CDealCmd::onIdle( void )
{
	int err = enSucess;

	return err;
}

//��������ֻҪ�����°����ý���������������
int CDealCmd::onStart( void )
{
	int err = enSucess;
	static int nMode = enMode_none;
	if (g_stGlobalPara.bKeyDown)
	{
		g_stGlobalPara.bKeyDown = 0;

		//�ȼ���ǲ�����������Ա���ź�ģʽ,
		switch (nMode)
		{
		case enMode_none:
			{
				if (enBtnM == g_stGlobalPara.ucCurKey)
				{
					nMode = enMode_setMode;
					g_stGlobalPara.stCfgPara.times = 0;
					g_stGlobalPara.nKeyCount = 0;
					g_stGlobalPara.stCfgPara.mode = 0;
				}
				else if (enBtnP == g_stGlobalPara.ucCurKey)
				{
					nMode = enMode_setId;
					g_stGlobalPara.stCfgPara.times = 0;
					g_stGlobalPara.nKeyCount = 0;
					g_stGlobalPara.stCfgPara.id = 0;
				}
			}
			break;
		case enMode_setId:
		case enMode_setMode:
			{
				if (enBtnY == g_stGlobalPara.ucCurKey)
				{
					int nValue = 0;
					if (g_stGlobalPara.nKeyCount > 1)
					{
						nValue = g_stGlobalPara.ucRecKey[0]*10 + g_stGlobalPara.ucRecKey[1];
					}
					else
						nValue = g_stGlobalPara.ucRecKey[0];
					if (enMode_setId == nMode)
					{
							g_stGlobalPara.stCfgPara.id = nValue;
					}
					else if (enMode_setMode == nMode)
					{
							g_stGlobalPara.stCfgPara.mode = nValue;
					}
					g_stGlobalPara.nKeyCount = 0;
					memset(&g_stGlobalPara.ucRecKey, 0, sizeof g_stGlobalPara.ucRecKey);
					nMode = enMode_none;
					break;
				}
				else if (enBtnBack == g_stGlobalPara.ucCurKey)
				{
					if (g_stGlobalPara.nKeyCount > 1)
					{
						g_stGlobalPara.ucRecKey[--g_stGlobalPara.nKeyCount] = 0;
					}
					break;
				}
				if (g_stGlobalPara.nKeyCount >= 2)
				{
					break;
				}
				g_stGlobalPara.ucRecKey[g_stGlobalPara.nKeyCount++] = g_stGlobalPara.ucCurKey;

			}
			break;
		default:
			nMode = enMode_none;
			break;
		}
		//ֻҪ������ID�žͿ�ʼ�ˣ�ģʽĬ��Ϊȫ0
		if (g_stGlobalPara.stCfgPara.id != 0)
		{
			//��������ϣ�����Ƿ��˿�ʼ��������ֱ����ȥ����
			if (enBtnStart == g_stGlobalPara.ucCurKey)
			{
				g_stGlobalPara.nStep = enStep_Work;
				g_stGlobalPara.stCfgPara.times = g_stGlobalPara.stCfgPara.times%99 + 1;

				//�����¿�ʼ����
				randSign();
				setPapiLed();
				//��ʱ����ʼ��
				g_stGlobalPara.bStartTime = 1;
			}
		}
	}
	return err;
}

int CDealCmd::onWork( void )
{
	int err = enSucess;
	//����������õĶԲ���,�ԵĻ���ֱ����ν�������д���¼
	int ret = chkManual();
	invalidate();
	return err;
}

int CDealCmd::chkKeyDown( void )
{
	int err = enSucess;
	int nKey = m_hard.scanbtn();
	if (enBtnInvalid != nKey)
	{
		g_stGlobalPara.bKeyDown = true;
		g_stGlobalPara.ucCurKey = nKey;
	}
	return err;
}

int CDealCmd::chkManual( void )
{
	int err = enWaiting;
	//�жϰ�����Щ�����Ƿ���ϴα��б仯
	//�����û�а�����,���д����ë����Ӧ����ֹͣ
	if (g_stGlobalPara.bKeyDown)
	{
		g_stGlobalPara.bKeyDown = 0;
		if (enBtnClr == g_stGlobalPara.ucCurKey)
		{
			g_stGlobalPara.nStep = enStep_Start;
			//�ر�PAPI��
			rstPapiLed();
		}
	}
	return err;
}

int CDealCmd::setPapiLed( void )
{
	int err = enErr;
	switch (g_stGlobalPara.stCfgPara.papiState)
	{
	case 1:
		{
			m_hard.ledp1(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp2(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp3(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp4(CHardPanel::enOn, CHardPanel::enWhiteColor);
		}
		break;
	case 2:
		{
			m_hard.ledp1(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp2(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp3(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp4(CHardPanel::enOn, CHardPanel::enReadColor);
		}
		break;
	case 3:
		{
			m_hard.ledp1(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp2(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp3(CHardPanel::enOn, CHardPanel::enReadColor);
			m_hard.ledp4(CHardPanel::enOn, CHardPanel::enReadColor);
		}
		break;
	case 4:
		{
			m_hard.ledp1(CHardPanel::enOn, CHardPanel::enWhiteColor);
			m_hard.ledp2(CHardPanel::enOn, CHardPanel::enReadColor);
			m_hard.ledp3(CHardPanel::enOn, CHardPanel::enReadColor);
			m_hard.ledp4(CHardPanel::enOn, CHardPanel::enReadColor);
		}
		break;
	case 5:
		{
			m_hard.ledp1(CHardPanel::enOn, CHardPanel::enReadColor);
			m_hard.ledp2(CHardPanel::enOn, CHardPanel::enReadColor);
			m_hard.ledp3(CHardPanel::enOn, CHardPanel::enReadColor);
			m_hard.ledp4(CHardPanel::enOn, CHardPanel::enReadColor);
		}
		break;
	default:
		break;
	}
	return err;
}

int CDealCmd::rstPapiLed( void )
{
	int err = enErr;
	m_hard.ledp1(CHardPanel::enClose, CHardPanel::enReadColor);
	m_hard.ledp2(CHardPanel::enClose, CHardPanel::enReadColor);
	m_hard.ledp3(CHardPanel::enClose, CHardPanel::enReadColor);
	m_hard.ledp4(CHardPanel::enClose, CHardPanel::enReadColor);
	return err;
}

int CDealCmd::invalidate( void )
{
	int err = enSucess;
	
	if (g_stGlobalPara.stCfgPara.winddirec == 1)
	{
		strcpy(m_strWind, "˳��");
	}
	else
	{
		strcpy(m_strWind, "���");
	}
	setBackLeft();
	refreshTime();
	setBackRight();
	return err;
}

int CDealCmd::setBackShow1( void )
{
	int err = enSucess;
	char str[128] = {0};
	char strFeng[32] = {0};
	ptConfigPara pt = (ptConfigPara)&g_stGlobalPara.stCfgPara;
	if (pt->winddirec == 1)
	{
		strcpy(strFeng,"˳��");
	}
	else
	{
		strcpy(strFeng,"���");
	}
	sprintf(str,"ģʽ:%02d ���:%02d\n��%02d��ʵ��\n��ʱ:%03d��\n����:%02dkt  ����:%s", pt->mode, pt->id, pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	return err;
}

int CDealCmd::setBackShow2( void )
{
	int err = enSucess;
	char str[128] = {0};
	char strFeng[32] = {0};
	ptConfigPara pt = (ptConfigPara)&g_stGlobalPara.stCfgPara;
	if (pt->winddirec == 1)
	{
		strcpy(strFeng,"˳��");
	}
	else
	{
		strcpy(strFeng,"���");
	}
	sprintf(str,"ʵ�����Ͽ�ʼ,��׼����\n    ��%02d��ʵ��\n    ��ʱ:%03d��\n����:%02dkt  ����%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	return err;
}

int CDealCmd::setBackShow3( void )
{
	int err = enSucess;
	char str[128] = {0};
	char strFeng[32] = {0};
	ptConfigPara pt = (ptConfigPara)&g_stGlobalPara.stCfgPara;
	if (pt->winddirec == 1)
	{
		strcpy(strFeng,"˳��");
	}
	else
	{
		strcpy(strFeng,"���");
	}
	sprintf(str,"  ʵ�鿪ʼ\n    ��%02d��ʵ��\n    ��ʱ:%03d��\n����:%02dkt  ����%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	return err;
}

int CDealCmd::setBackShow4( void )
{
	int err = enSucess;
	char str[128] = {0};
	char strFeng[32] = {0};
	ptConfigPara pt = (ptConfigPara)&g_stGlobalPara.stCfgPara;
	if (pt->winddirec == 1)
	{
		strcpy(strFeng,"˳��");
	}
	else
	{
		strcpy(strFeng,"���");
	}
	sprintf(str,"��ϲ��,������ȷ\n    ��%02d��ʵ��\n    ��ʱ:%03d��\n����:%02dkt  ����%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	return err;
}

int CDealCmd::setBackShow5( void )
{
	int err = enSucess;
	char str[128] = {0};
	char strFeng[32] = {0};
	ptConfigPara pt = (ptConfigPara)&g_stGlobalPara.stCfgPara;
	if (pt->winddirec == 1)
	{
		strcpy(strFeng,"˳��");
	}
	else
	{
		strcpy(strFeng,"���");
	}
	sprintf(str,"���ź�,��������\n    ��%02d��ʵ��\n    ��ʱ:%03d��\n����:%02dkt  ����%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	return err;
}

int CDealCmd::setBackShow6( void )
{
	int err = enSucess;
	char str[128] = {0};
	char strFeng[32] = {0};
	ptConfigPara pt = (ptConfigPara)&g_stGlobalPara.stCfgPara;
	if (pt->winddirec == 1)
	{
		strcpy(strFeng,"˳��");
	}
	else
	{
		strcpy(strFeng,"���");
	}
	sprintf(str,"�뽫���ݸ˺����Ÿ�λ��\n    ��%02d��ʵ��\n    ��ʱ:%03d��\n����:%02dkt  ����%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	return err;
}

int CDealCmd::setBackShow7( void )
{
	int err = enSucess;
	char str[128] = {0};
	char strFeng[32] = {0};
	ptConfigPara pt = (ptConfigPara)&g_stGlobalPara.stCfgPara;
	if (pt->winddirec == 1)
	{
		strcpy(strFeng,"˳��");
	}
	else
	{
		strcpy(strFeng,"���");
	}
	sprintf(str,"\n    ��%02d��ʵ��\n    ��ʱ:%03d��\n����:%02dkt  ����%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	return err;
}


int CDealCmd::setBackLeft( void )
{
	int err = enSucess;
	if (g_stGlobalPara.bBackLeftShow)
	{
		g_stGlobalPara.bBackLeftShow = 0;

		m_hard.chgBackGround(g_stGlobalPara.nBackLeft);
	}
	return err;
}

int CDealCmd::doSomething( void )
{
	int err = enSucess;

	return err;
}

int CDealCmd::setBackShow0( void )
{
	int err = enSucess;
	char str[128] = {0};
	sprintf(str,"ģʽ:   ���:  \n��  ��ʵ��\n��ʱ:   ��\n����:  kt   ����:   ");
	showBackFont(str);
	return err;
}

int CDealCmd::showBackFont( char* str )
{
	int err = enSucess;
	DisText(BACK_FONT_TOP, BACK_FONT_LEFT, 1, FONT_TYPE, (uchar*)str);
	return err;
}

int CDealCmd::refreshTime( void )
{
	int err = enSucess;
	//����Ҫ�ж�һ��ˢ��һ�Σ�������Ҫ����Ҫˢ�µ�ʱ��ˢ
	if (g_stGlobalPara.bStartTime)
	{
		if (m_hard.getTickCount() - g_stGlobalPara.nLstTime > 1000)
		{
			g_stGlobalPara.stCfgPara.rtTime++;
			g_stGlobalPara.nLstTime = m_hard.getTickCount();
			g_stGlobalPara.bNeedInvalidate = 1;
		}
	}
	return err;
}

int CDealCmd::setBackRight()
{
	int err = enSucess;
	if (g_stGlobalPara.bNeedInvalidate)
	{
		g_stGlobalPara.bNeedInvalidate = 0;
		switch (g_stGlobalPara.nBackRight)
		{
		case enBackPicRight0:
			{
				err = setBackShow0();
			}
			break;
		case enBackPicRight1:
			{
				err = setBackShow1();
			}
			break;
		case enBackPicRight2:
			{
				err = setBackShow2();
			}
			break;
		case enBackPicRight3:
			{
				err = setBackShow3();
			}
			break;
		case enBackPicRight4:
			{
				err = setBackShow4();
			}
			break;
		case enBackPicRight5:
			{
				err = setBackShow5();
			}
			break;
		case enBackPicRight6:
			{
				err = setBackShow6();
			}
			break;
		case enBackPicRight7:
			{
				err = setBackShow7();
			}
			break;
		default:
			break;
		}
	}
	return err;
}


