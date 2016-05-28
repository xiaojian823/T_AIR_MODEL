#include "StdAfx.h"
#include "macro.h"
#include "HardPanel.h"
#include "hmi_driver.h"


CHardPanel::CHardPanel(void)
{
}


CHardPanel::~CHardPanel(void)
{
}

void CHardPanel::ledp1( int bOn , int nColor)
{

}

void CHardPanel::ledp2( int bOn , int nColor)
{

}

void CHardPanel::ledp3( int bOn , int nColor)
{

}

void CHardPanel::ledc1( int bOn )
{

}

void CHardPanel::ledc2( int bOn )
{

}

void CHardPanel::ledc3( int bOn )
{

}

void CHardPanel::ledcr( int bOn )
{

}

void CHardPanel::ledc4( int bOn )
{

}

void CHardPanel::ledc5( int bOn )
{

}

void CHardPanel::ledplus1( int bOn )
{

}

void CHardPanel::leddec2( int bOn )
{

}

void CHardPanel::ledrst( int bOn )
{

}

int CHardPanel::scanbtn( void )
{
	//这里是总的，全部按顺序扫描，先扫描能按的，再扫描方向有没有用
	int ret = enBtnInvalid;
	if ((ret = scanno()) != enBtnInvalid)
	{
		
	}
	else if ((ret = scanstart()) != enBtnInvalid)
	{

	}
	else if ((ret = scandriver()) != enBtnInvalid)
	{

	}
	else if ((ret = scanplus()) != enBtnInvalid)
	{

	}
	else if ((ret = scandirect()) != enBtnInvalid)
	{

	}
	return 0;
}

int CHardPanel::scanno( void )
{
	int ret = enBtnInvalid;

	return ret;
}

int CHardPanel::scandriver( void )
{
	int ret = enBtnInvalid;

	return ret;
}

int CHardPanel::scanplus( void )
{
	int ret = enBtnInvalid;

	return ret;
}

int CHardPanel::scanstart( void )
{
	int ret = enBtnInvalid;

	return ret;
}

int CHardPanel::scandirect( void )
{
	int ret = enBtnInvalid;

	return ret;
}

int CHardPanel::writefile( void* pData, int nInLen )
{
	return 0;
}

int CHardPanel::chgBackGround( int nType,int param1,int param2 )
{
	int err = enSucess;
	int ret = enSucess;
	switch (nType)
	{
	case enBtnLeft:
		{
			chgBackGroudPic(enBackPic5ID);
		}
		break;
	case enBtnRight:
		{
			chgBackGroudPic(enBackPic6ID);
		}
		break;
	case enBtnPwr:
		{

		}
		break;
	case enBtnStart:
		{

		}
		break;
	case enBtnClr:
		{

		}
		break;

	case enBtnTui:
		{

		}
		break;
	case enBtnShaoTui:
		{

		}
		break;
	case enBtnBaochi:
		{

		}
		break;
	case enBtnFuwei:
		{

		}
		break;
	case enBtnShaola:
		{

		}
		break;
	case enBtnla:
		{

		}
		break;
	case enBtnJiayou:
		{

		}
		break;
	case enBtnjiaFuWei:
		{
			chgBackGroudPic(enBackPic0ID);
		}
		break;
	case enBtnJianyou: 
		{

		}
		break;
	default:
		break;
	}
	return err;
}

int CHardPanel::chgBackGroudPic( int nId )
{
	int err = enSucess;
	DisFlashImage(backPosLeft,backPosTop,nId,1,0);
	return err;
}

int CHardPanel::getTickCount()
{
	int ret = 0;
	ret = GetTickCount();
	return ret;
}

void CHardPanel::ledp4( int bOn , int nColor)
{

}
