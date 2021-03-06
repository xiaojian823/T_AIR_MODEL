#include "StdAfx.h"
#include "DealCmd.h"
#include "hmi_driver.h"

tGlobalPara  g_stGlobalPara;

CDealCmd::CDealCmd(void)
{
	init();
}


CDealCmd::~CDealCmd(void)
{
}

void CDealCmd::run()
{
	int ret = 0;
	//检查当前按键值，看有没有被按下来的
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

//整个流程只要不重新按设置健，整个计数继续
int CDealCmd::onStart( void )
{
	int err = enSucess;
	static int nMode = enMode_none;
	if (g_stGlobalPara.bKeyDown)
	{
		g_stGlobalPara.bKeyDown = 0;

		//先检查是不是有设置了员工号和模式,
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
		//只要设置了ID号就开始了，模式默认为全0
		if (g_stGlobalPara.stCfgPara.id != 0)
		{
			//若设置完毕，检查是否按了开始，若按了直接跑去工作
			if (enBtnStart == g_stGlobalPara.ucCurKey)
			{
				g_stGlobalPara.nStep = enStep_Work;
				g_stGlobalPara.stCfgPara.times = g_stGlobalPara.stCfgPara.times%99 + 1;

				//都重新开始计数
				randSign();
				setPapiLed();
				//计时器开始走
				g_stGlobalPara.bStartTime = 1;
			}
		}
	}
	return err;
}

int CDealCmd::onWork( void )
{
	int err = enSucess;
	//检查三个设置的对不对,对的话就直接这次结束，并写入记录
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
	//判断按键这些东西是否跟上次比有变化
	//检查有没有按清零,这个写的有毛病，应该是停止
	if (g_stGlobalPara.bKeyDown)
	{
		g_stGlobalPara.bKeyDown = 0;
		do 
		{
			//若判断为复位的话，变成图片7
			if ((enBtnClr == g_stGlobalPara.ucCurKey)
				|| (g_stGlobalPara.bFuweiDirty && g_stGlobalPara.bjiayouFuwei && g_stGlobalPara.bCaozongFuwei))
			{
				g_stGlobalPara.bFuweiDirty = 0;
				g_stGlobalPara.bjiayouFuwei = 1;
				g_stGlobalPara.bCaozongFuwei = 1;
				g_stGlobalPara.nStep = enStep_Start;
				//关闭PAPI灯
				rstPapiLed();
				g_stGlobalPara.bNeedInvalidate = 1;
				g_stGlobalPara.nBackRight = enBackPicRight7;
				break;
			}
			///判断是否是正确的操作
			//判断PAPI灯是否操作正确
			switch (g_stGlobalPara.ucCurKey)
			{
			case enBtnTui:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic4ID;
					if (g_stGlobalPara.stCfgPara.papiState == 1)
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.joystick = 1;
					g_stGlobalPara.bCaozongFuwei = 0;
				}
				break;
			case enBtnShaoTui:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic3ID;
					if (g_stGlobalPara.stCfgPara.papiState == 2)
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.joystick = 2;
					g_stGlobalPara.bCaozongFuwei = 0;
				}
				break;
			case enBtnBaochi:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic0ID;
					if (g_stGlobalPara.stCfgPara.papiState == 3)
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.joystick = 3;
					g_stGlobalPara.bCaozongFuwei = 0;
				}
				break;
			case enBtnShaola:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic2ID;
					if (g_stGlobalPara.stCfgPara.papiState == 4)
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.joystick = 4;
					g_stGlobalPara.bCaozongFuwei = 0;
				}
				break;
			case enBtnla:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic1ID;
					if (g_stGlobalPara.stCfgPara.papiState == 5)
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.caozonggan = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.joystick = 5;
					g_stGlobalPara.bCaozongFuwei = 0;
				}
				break;
			case enBtnFuwei:
				{
					//no--------------
					g_stGlobalPara.bFuweiDirty = 1;
					g_stGlobalPara.bCaozongFuwei = 1;
				}
				break;
			//判断油门是否操作正确
			case enBtnJiayou:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic1ID;
					if ((g_stGlobalPara.stCfgPara.idlespeed < 60) && (g_stGlobalPara.stCfgPara.winddirec == 0))
					{
						g_stGlobalPara.stWorkPara.youmen = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.youmen = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.accelerator = 1;
					g_stGlobalPara.bjiayouFuwei = 0;
				}
				break;
			case enBtnJianyou:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic4ID;
					if ((g_stGlobalPara.stCfgPara.idlespeed >= 60) && (g_stGlobalPara.stCfgPara.winddirec == 1))
					{
						g_stGlobalPara.stWorkPara.youmen = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.youmen = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.accelerator = 2;
					g_stGlobalPara.bjiayouFuwei = 0;
				}
				break;
			case enBtnjiaFuWei:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic0ID;
					g_stGlobalPara.bFuweiDirty = 1;
					g_stGlobalPara.bjiayouFuwei = 1;
				}
				break;
			//判断操作仪是否正确
			case enBtnLeft:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic5ID;
					if (g_stGlobalPara.stCfgPara.winddirec == 1)
					{
						g_stGlobalPara.stWorkPara.fangxiangtuo = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.fangxiangtuo = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.rudder = 0;
				}
				break;
			case enBtnRight:
				{
					g_stGlobalPara.bBackLeftShow = 1;
					g_stGlobalPara.nBackLeft = enBackPic6ID;
					if (g_stGlobalPara.stCfgPara.winddirec == 0)
					{
						g_stGlobalPara.stWorkPara.fangxiangtuo = enWorkOk;
					}
					else
					{
						g_stGlobalPara.stWorkPara.fangxiangtuo = enWorkErr;
					}
					g_stGlobalPara.stCfgPara.rudder = 1;
				}
				break;
			default:
				break;
			}
			
		} while (0);
		
		//判断结果是否正确
		if ((g_stGlobalPara.stWorkPara.caozonggan == enWorkOk) &&
			(g_stGlobalPara.stWorkPara.fangxiangtuo == enWorkOk) &&
			(g_stGlobalPara.stWorkPara.youmen == enWorkOk))
		{
			//这个是表示全部操作完毕，并且结果正确
			g_stGlobalPara.bBackLeftShow = 1;
			g_stGlobalPara.nBackLeft = enBackPic4ID;
			g_stGlobalPara.stCfgPara.result = 1;
			//这里开始写计数结果
			writePara();
		}
		else if ((g_stGlobalPara.stWorkPara.caozonggan == enWorkErr) ||
			(g_stGlobalPara.stWorkPara.fangxiangtuo == enWorkErr) ||
			(g_stGlobalPara.stWorkPara.youmen == enWorkErr))
		{
			//只要有一步操作错误，马上结束
			g_stGlobalPara.bBackLeftShow = 1;
			g_stGlobalPara.nBackLeft = enBackPic5ID;
			g_stGlobalPara.stCfgPara.result = 0;
			//这里开始写计数结果
			writePara();
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
		strcpy(strFeng,"顺风");
	}
	else
	{
		strcpy(strFeng,"逆风");
	}
	sprintf(str,"模式:%02d 编号:%02d\n第%02d次实验\n用时:%03d秒\n空速:%02dkt  风向:%s", pt->mode, pt->id, pt->times, pt->rtTime,
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
		strcpy(strFeng,"顺风");
	}
	else
	{
		strcpy(strFeng,"逆风");
	}
	sprintf(str,"实验马上开始,请准备！\n    第%02d次实验\n    用时:%03d秒\n空速:%02dkt  风向：%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	//这里这个等两秒后开始显示图片2
	g_stGlobalPara.nLstTime = m_hard.getTickCount();
	g_stGlobalPara.nBackRight = enBackPicRight3;
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
		strcpy(strFeng,"顺风");
	}
	else
	{
		strcpy(strFeng,"逆风");
	}
	sprintf(str,"  实验开始\n    第%02d次实验\n    用时:%03d秒\n空速:%02dkt  风向：%s", pt->times, pt->rtTime,
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
		strcpy(strFeng,"顺风");
	}
	else
	{
		strcpy(strFeng,"逆风");
	}
	sprintf(str,"恭喜你,操作正确\n    第%02d次实验\n    用时:%03d秒\n空速:%02dkt  风向：%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	//这里这个等两秒后开始显示图片2
	g_stGlobalPara.nLstTime = m_hard.getTickCount();
	g_stGlobalPara.nBackRight = enBackPicRight6;
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
		strcpy(strFeng,"顺风");
	}
	else
	{
		strcpy(strFeng,"逆风");
	}
	sprintf(str,"很遗憾,操作错误\n    第%02d次实验\n    用时:%03d秒\n空速:%02dkt  风向：%s", pt->times, pt->rtTime,
		pt->idlespeed, strFeng);
	showBackFont(str);
	//这里这个等两秒后开始显示图片2
	g_stGlobalPara.nLstTime = m_hard.getTickCount();
	g_stGlobalPara.nBackRight = enBackPicRight6;
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
		strcpy(strFeng,"顺风");
	}
	else
	{
		strcpy(strFeng,"逆风");
	}
	sprintf(str,"请将操纵杆和油门复位！\n    第%02d次实验\n    用时:%03d秒\n空速:%02dkt  风向：%s", pt->times, pt->rtTime,
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
		strcpy(strFeng,"顺风");
	}
	else
	{
		strcpy(strFeng,"逆风");
	}
	sprintf(str,"\n    第%02d次实验\n    用时:%03d秒\n空速:%02dkt  风向：%s", pt->times, pt->rtTime,
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

		m_hard.chgBackGroudPic(g_stGlobalPara.nBackLeft);
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
	sprintf(str,"模式:   编号:  \n第  次实验\n用时:   秒\n空速:  kt   风向:   ");
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
	//这里要判断一秒刷新一次，并且是要在需要刷新的时候刷
	if (g_stGlobalPara.bStartTime)
	{
		if (m_hard.getTickCount() - g_stGlobalPara.nLstCalTime > 1000)
		{
			g_stGlobalPara.stCfgPara.rtTime++;
			g_stGlobalPara.nLstCalTime = m_hard.getTickCount();
			g_stGlobalPara.bNeedInvalidate = 1;
		}
	}
	return err;
}

int CDealCmd::setBackRight()
{
	int err = enSucess;
	if ((m_hard.getTickCount() - g_stGlobalPara.nLstTime > 2000) && g_stGlobalPara.bNeedInvalidate)
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

int CDealCmd::writePara( void )
{
	int err = enSucess;

	return err;
}

void CDealCmd::init()
{
	g_stGlobalPara.nStep = enStep_Start;
	memset(&g_stGlobalPara, 0, sizeof g_stGlobalPara);
	memset(m_strWind,0,sizeof m_strWind);
	m_lstTime = 0;
	g_stGlobalPara.bFuweiDirty = 0;
	g_stGlobalPara.bjiayouFuwei = 1;
	g_stGlobalPara.bCaozongFuwei = 1;
}


