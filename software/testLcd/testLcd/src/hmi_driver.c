

#include "hmi_driver.h"

/****************************************************************************
* ��    �ƣ� SendBeginCMD()
* ��    �ܣ� ����֡ͷ����
* ��ڲ����� ��      
* ���ڲ����� ��
****************************************************************************/
void SendBeginCMD()
{
 SendChar(0xEE);
}

/****************************************************************************
* ��    �ƣ� SendEndCmd()
* ��    �ܣ� ����֡β����
* ��ڲ����� ��      
* ���ڲ����� ��
****************************************************************************/
void SendEndCmd()
{
 SendChar(0xFF);
 SendChar(0xFC);
 SendChar(0xFF);
 SendChar(0xFF);
}

/****************************************************************************
* ��    �ƣ� SetHandShake()
* ��    �ܣ� ����
* ��ڲ����� ��      
* ���ڲ����� ��
****************************************************************************/
void SetHandShake(void)
{
  SendBeginCMD();
  SendChar(0x00);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� SetFcolor()
* ��    �ܣ� ����ǰ��ɫ
* ��ڲ����� fcolor  ǰ��ɫRGB����   
* ���ڲ����� ��
****************************************************************************/
void SetFcolor(uint16 fcolor)
{
  SendBeginCMD();
  SendChar(0x41);
  SendChar((fcolor>>8)&0xff);
  SendChar(fcolor&0xff);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� SetBcolor()
* ��    �ܣ� ���ñ���ɫ
* ��ڲ����� bcolor  ����ɫRGB����   
* ���ڲ����� ��
****************************************************************************/
void SetBcolor(uint16 bcolor)
{
  SendBeginCMD();
  SendChar(0x42);
  SendChar((bcolor>>8)&0xff);
  SendChar(bcolor&0xff);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� ColorPicker()
* ��    �ܣ� ȡ��Ļ������ǰ��ɫ/����ɫ
* ��ڲ����� mode ȡ��ǰ��ʾ��Ļ(X,Y)������ɫ��Ϊǰ��/����ɫ
             x       �Ե�Ϊ��λ��X������ֵ
             y       �Ե�Ϊ��λ��Y������ֵ
* ���ڲ����� ��
****************************************************************************/
void ColorPicker(uint8 mode, uint16 x,uint16 y)
{
  SendBeginCMD();
  SendChar(0xa3);
  SendChar(mode);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_CleanScreen()
* ��    �ܣ� ����
* ��ڲ����� ��  
* ���ڲ����� ��
****************************************************************************/
void GUI_CleanScreen()
{
  SendBeginCMD();
  SendChar(0x01);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� SetTextSpace()
* ��    �ܣ� �����������м��
* ��ڲ����� x_w     �Ե�Ϊ��λ���м�࣬ȡֵ��Χ00~1F
             y_w     �Ե�Ϊ��λ���м�࣬ȡֵ��Χ00~1F	
* ���ڲ����� ��
****************************************************************************/
void SetTextSpace(uint8 x_w, uint8 y_w)
{
  SendBeginCMD();
  SendChar(0x43);
  SendChar(x_w);
  SendChar(y_w);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� DisText_Region()
* ��    �ܣ� �޶��ı���ʾ��Χ
* ��ڲ����� x       �Ե�Ϊ��λ��X������ֵ
             y       �Ե�Ϊ��λ��Y������ֵ
             length  �ı����޶��ĳ���
	         width   �ı����޶��ĸ߶�
* ���ڲ����� ��
****************************************************************************/
void SetFont_Region(uint8 enable,uint16 length,uint16 width )
{
  SendBeginCMD();
  SendChar(0x45);
  SendChar(enable);
  SendChar((length>>8)&0xff);
  SendChar(length&0xff);
  SendChar((width>>8)&0xff);
  SendChar(width&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� SetFilterColor()
* ��    �ܣ� ���ù�����ɫ
* ��ڲ����� fillcolor_dwon   �˳���ɫ������ֵ
             fillcolor_up     �˳���ɫ������ֵ	
* ���ڲ����� ��
****************************************************************************/
void SetFilterColor(uint16 fillcolor_dwon, uint16 fillcolor_up)
{
  SendBeginCMD();
  SendChar(0x44);
  SendChar((fillcolor_dwon>>8)&0xff);
  SendChar(fillcolor_dwon&0xff);
  SendChar((fillcolor_up>>8)&0xff);
  SendChar(fillcolor_up&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� DisText()
* ��    �ܣ� �ı���ʾ
* ��ڲ����� x         �Ե�Ϊ��λ��X������ֵ
             y         �Ե�Ϊ��λ��Y������ֵ
   	         back      ����ɫʹ��
	         font      �ֿ����
             strings   д����ַ���
* ���ڲ����� ��
****************************************************************************/
void DisText(uint16 x, uint16 y,uint8 back,uint8 font,uchar *strings )
{
  SendBeginCMD();
  SendChar(0x20);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar(back);
  SendChar(font);
  SendStrings(strings);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� DisData()
* ��    �ܣ� ������ʾ
* ��ڲ����� x       �Ե�Ϊ��λ��X������ֵ
             y       �Ե�Ϊ��λ��Y������ֵ
   	         back    ����ɫʹ��
	         font    �ֿ����
	         sdata   д�������
* ���ڲ����� ��
****************************************************************************/
void DisData(uint16 x, uint16 y,uint8 back,uint8 font,uchar sdata )
{
  SendBeginCMD();
  SendChar(0x20);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar(back);
  SendChar(font);
  SendChar(sdata);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� DisCursor()
* ��    �ܣ� �����ʾ
* ��ڲ����� enable
             x        �Ե�Ϊ��λ��X������ֵ
             y        �Ե�Ϊ��λ��Y������ֵ
             length   ��곤��
	         width    �����
* ���ڲ����� ��
****************************************************************************/
void DisCursor(uint8 enable,uint16 x, uint16 y,uint8 length,uint8 width )
{
  SendBeginCMD();
  SendChar(0x21);
  SendChar(enable);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar(length&0xff);
  SendChar(width&0xff);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� DisFull_Image()
* ��    �ܣ� ȫ������ͼ��ʾ
* ��ڲ����� image_id   ͼƬID���
             masken     ����ɫʹ��
* ���ڲ����� ��
****************************************************************************/
void DisFull_Image(uint16 image_id,uint8 masken)
{
  SendBeginCMD();
  SendChar(0x31);
  SendChar((image_id>>8)&0xff);
  SendChar(image_id&0xff); 
  SendChar(masken);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� DisArea_Image()
* ��    �ܣ� ����ͼƬ��ʾ
* ��ڲ����� x          �Ե�Ϊ��λ��X������ֵ
             y          �Ե�Ϊ��λ��Y������ֵ 
             image_id   ͼƬID���
             masken     ����ɫʹ��
* ���ڲ����� ��
****************************************************************************/
void DisArea_Image(uint16 x,uint16 y,uint16 image_id,uint8 masken)
{
  SendBeginCMD();
  SendChar(0x32);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar((image_id>>8)&0xff);
  SendChar(image_id&0xff);
  SendChar(masken);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� DisCut_Image()
* ��    �ܣ� ͼƬ����
* ��ڲ����� x          �Ե�Ϊ��λ��X������ֵ
             y          �Ե�Ϊ��λ��Y������ֵ 
             image_id   ͼƬ���
             image_x    ͼƬ�ڲ�X����
             image_y    ͼƬ�ڲ�Y����
             image_l    ���г���
             image_w    ���п��
             masken     ����ɫʹ��
* ���ڲ����� ��
****************************************************************************/
void DisCut_Image(uint16 x,uint16 y,uint16 image_id,uint16 image_x,uint16 image_y,
                   uint16 image_l, uint16 image_w,uint8 masken)
{
  SendBeginCMD();
  SendChar(0x33);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar((image_id>>8)&0xff);
  SendChar(image_id&0xff);
  SendChar((image_x>>8)&0xff);
  SendChar(image_x&0xff);
  SendChar((image_y>>8)&0xff);
  SendChar(image_y&0xff);
  SendChar((image_l>>8)&0xff);
  SendChar(image_l&0xff);
  SendChar((image_w>>8)&0xff);
  SendChar(image_w&0xff);
  SendChar(masken);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� DisFlashImgae()
* ��    �ܣ� ������ʾ
* ��ڲ����� x               �Ե�Ϊ��λ��X������ֵ
             y               �Ե�Ϊ��λ��Y������ֵ 
             flashimage_id   GIF����ID���     
    	     enable          �ر�/������������
	         playnum         �������Ŵ��� 0:һֱ���ţ�1~FF:���Ŵ���
* ���ڲ����� ��
****************************************************************************/
void DisFlashImage(uint16 x,uint16 y,uint16 flashimage_id,uint8 enable,uint8 playnum)
{
  SendBeginCMD();
  SendChar(0x80);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar((flashimage_id>>8)&0xff);
  SendChar(flashimage_id&0xff);
  SendChar(enable);
  SendChar(playnum);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� GUI_Dot()
* ��    �ܣ� ����
* ��ڲ����� x       �Ե�Ϊ��λ��X������ֵ
             y       �Ե�Ϊ��λ��Y������ֵ           
* ���ڲ����� ��
****************************************************************************/
void GUI_Dot(uint16 x,uint16 y)
{
  SendBeginCMD();
  SendChar(0x50);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� GUI_Line()
* ��    �ܣ� ����
* ��ڲ����� x0      �Ե�Ϊ��λ��X������ֵ
             y0      �Ե�Ϊ��λ��Y������ֵ    
             x1      �Ե�Ϊ��λ��X������ֵ
             y1      �Ե�Ϊ��λ��Y������ֵ  
* ���ڲ����� ��
****************************************************************************/
void GUI_Line(uint16 x0, uint16 y0, uint16 x1, uint16 y1)
{
  SendBeginCMD();
  SendChar(0x51);
  SendChar((x0>>8)&0xff);
  SendChar(x0&0xff);
  SendChar((y0>>8)&0xff);
  SendChar(y0&0xff);
  SendChar((x1>>8)&0xff);
  SendChar(x1&0xff);
  SendChar((y1>>8)&0xff);
  SendChar(y1&0xff);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� GUI_ConDots()
* ��    �ܣ� ��������
* ��ڲ����� mode     0:��ǰ��ɫ��� 1���ñ���ɫ���    
	         pDot     ָ����ָ��   
* ���ڲ����� ��
****************************************************************************/
void GUI_ConDots(uint8 mode,uchar *pDot)
{
  SendBeginCMD();
  SendChar(0x63);
  SendChar(mode);
  SendStrings(pDot); 
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_Circle()
* ��    �ܣ� ������Բ
* ��ڲ����� x               �Ե�Ϊ��λ��X������ֵ
             y               �Ե�Ϊ��λ��Y������ֵ    
             r                ����Բ�İ뾶   
* ���ڲ����� ��
****************************************************************************/
void GUI_Circle(uint16 x, uint16 y, uint16 r)
{
  SendBeginCMD();
  SendChar(0x52);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar((r>>8)&0xff);
  SendChar(r&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_CircleFill()
* ��    �ܣ� ��ʵ��Բ
* ��ڲ����� x               �Ե�Ϊ��λ��X������ֵ
             y               �Ե�Ϊ��λ��Y������ֵ    
             r                ʵ��Բ�İ뾶   
* ���ڲ����� ��
****************************************************************************/
void GUI_CircleFill(uint16 x, uint16 y, uint16 r)
{
  SendBeginCMD();
  SendChar(0x53);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar((r>>8)&0xff);
  SendChar(r&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_Arc()
* ��    �ܣ� ��Բ��
* ��ڲ����� x               �Ե�Ϊ��λ��X������ֵ
             y               �Ե�Ϊ��λ��Y������ֵ    
             r               Բ�İ뾶  
 	         sa              ��ʼ�Ƕ�
	         ea              �����Ƕ�
* ���ڲ����� ��
****************************************************************************/
void GUI_Arc(uint16 x,uint16 y, uint16 r,uint16 sa, uint16 ea)
{
  SendBeginCMD();
  SendChar(0x67);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar((r>>8)&0xff);
  SendChar(r&0xff);
  SendChar((sa>>8)&0xff);
  SendChar(sa&0xff);
  SendChar((ea>>8)&0xff);
  SendChar(ea&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_Rectangle()
* ��    �ܣ� �����ľ���
* ��ڲ����� x0      �Ե�Ϊ��λ�Ŀ��ľ������Ͻ�X����ֵ
             y0      �Ե�Ϊ��λ�Ŀ��ľ������Ͻ�Y����ֵ   
             x1      �Ե�Ϊ��λ�Ŀ��ľ������½�X����ֵ
             y1      �Ե�Ϊ��λ�Ŀ��ľ������½�Y����ֵ   
* ���ڲ����� ��
****************************************************************************/
void GUI_Rectangle(uint16 x0, uint16 y0, uint16 x1,uint16 y1 )
{
  SendBeginCMD();
  SendChar(0x54);
  SendChar((x0>>8)&0xff);
  SendChar(x0&0xff);
  SendChar((y0>>8)&0xff);
  SendChar(y0&0xff);
  SendChar((x1>>8)&0xff);
  SendChar(x1&0xff);
  SendChar((y1>>8)&0xff);
  SendChar(y1&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� RectangleFill()
* ��    �ܣ� ��ʵ�ľ���
* ��ڲ����� x0      �Ե�Ϊ��λ��ʵ�ľ������Ͻ�X����ֵ
             y0      �Ե�Ϊ��λ��ʵ�ľ������Ͻ�Y����ֵ   
             x1      �Ե�Ϊ��λ��ʵ�ľ������½�X����ֵ
             y1      �Ե�Ϊ��λ��ʵ�ľ������½�Y����ֵ   
* ���ڲ����� ��
****************************************************************************/
void GUI_RectangleFill(uint16 x0, uint16 y0, uint16 x1,uint16 y1 )
{
  SendBeginCMD();
  SendChar(0x55);
  SendChar((x0>>8)&0xff);
  SendChar(x0&0xff);
  SendChar((y0>>8)&0xff);
  SendChar(y0&0xff);
  SendChar((x1>>8)&0xff);
  SendChar(x1&0xff);
  SendChar((y1>>8)&0xff);
  SendChar(y1&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_AreaInycolor()
* ��    �ܣ� ��Ļ����ɫ
* ��ڲ����� x0      �Ե�Ϊ��λ��ʵ�ľ������Ͻ�X����ֵ
             y0      �Ե�Ϊ��λ��ʵ�ľ������Ͻ�Y����ֵ   
             x1      �Ե�Ϊ��λ��ʵ�ľ������½�X����ֵ
             y1      �Ե�Ϊ��λ��ʵ�ľ������½�Y����ֵ   
* ���ڲ����� ��
****************************************************************************/
void GUI_AreaInycolor(uint16 x0, uint16 y0, uint16 x1,uint16 y1 )
{
  SendBeginCMD();
  SendChar(0x65);
  SendChar((x0>>8)&0xff);
  SendChar(x0&0xff);
  SendChar((y0>>8)&0xff);
  SendChar(y0&0xff);
  SendChar((x1>>8)&0xff);
  SendChar(x1&0xff);
  SendChar((y1>>8)&0xff);
  SendChar(y1&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_Ellipse()
* ��    �ܣ� ��������Բ
* ��ڲ����� x0      �Ե�Ϊ��λ�Ŀ�����Բ�����X����ֵ
             y0      �Ե�Ϊ��λ�Ŀ�����Բ���϶�Y����ֵ   
             x1      �Ե�Ϊ��λ�Ŀ�����Բ���Ҷ�X����ֵ
             y1      �Ե�Ϊ��λ�Ŀ�����Բ���¶�Y����ֵ   
* ���ڲ����� ��
****************************************************************************/
void GUI_Ellipse (uint16 x0, uint16 y0, uint16 x1,uint16 y1 )
{
  SendBeginCMD();
  SendChar(0x56);
  SendChar((x0>>8)&0xff);
  SendChar(x0&0xff);
  SendChar((y0>>8)&0xff);
  SendChar(y0&0xff);
  SendChar((x1>>8)&0xff);
  SendChar(x1&0xff);
  SendChar((y1>>8)&0xff);
  SendChar(y1&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_EllipseFill()
* ��    �ܣ� ��ʵ����Բ
* ��ڲ����� x0      �Ե�Ϊ��λ��ʵ����Բ�����X����ֵ
             y0      �Ե�Ϊ��λ��ʵ����Բ���϶�Y����ֵ   
             x1      �Ե�Ϊ��λ��ʵ����Բ���Ҷ�X����ֵ
             y1      �Ե�Ϊ��λ��ʵ����Բ���¶�Y����ֵ   
* ���ڲ����� ��
****************************************************************************/
void GUI_EllipseFill (uint16 x0, uint16 y0, uint16 x1,uint16 y1 )
{
  SendBeginCMD();
  SendChar(0x57);
  SendChar((x0>>8)&0xff);
  SendChar(x0&0xff);
  SendChar((y0>>8)&0xff);
  SendChar(y0&0xff);
  SendChar((x1>>8)&0xff);
  SendChar(x1&0xff);
  SendChar((y1>>8)&0xff);
  SendChar(y1&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� GUI_PolygonFill()
* ��    �ܣ� ��������
* ��ڲ����� x               �Ե�Ϊ��λ��X������ֵ
             y               �Ե�Ϊ��λ��Y������ֵ    
             color            �����ɫ   
* ���ڲ����� ��
****************************************************************************/
void GUI_PolygonFill(uint16 x, uint16 y, uint16 color)
{
  SendBeginCMD();
  SendChar(0x64);
  SendChar((x>>8)&0xff);
  SendChar(x&0xff);
  SendChar((y>>8)&0xff);
  SendChar(y&0xff);
  SendChar((color>>8)&0xff);
  SendChar(color&0xff);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� SetBackLight()
* ��    �ܣ� �������
* ��ڲ����� light_level
* ���ڲ����� ��
****************************************************************************/
void SetBackLight(uint8 light_level)
{
  SendBeginCMD();
  SendChar(0x60);
  SendChar(light_level);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� SetBuzzer()
* ��    �ܣ� ����������
* ��ڲ����� light_level
* ���ڲ����� ��
****************************************************************************/
void SetBuzzer(uint8 time)
{
  SendBeginCMD();
  SendChar(0x61);
  SendChar(time);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� SetCommBps()
* ��    �ܣ� ����ͨѶ������
* ��ڲ����� Baud
* ���ڲ����� ��
****************************************************************************/
void SetCommBps(uint8 baudset)  
{
  SendBeginCMD();
  SendChar(0xA0);
  SendChar(baudset);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� SetTouchScreen(uint8 cmd)
* ��    �ܣ� ����������
* ��ڲ����� cmd   Bit0:1/0 ������/��; Bit1 : 1/0 ��������/��; Bit2: �ϴ���ʽ  
* ���ڲ����� ��
****************************************************************************/
void SetTouchScreen(uint8 cmd)
{
  SendBeginCMD();
  SendChar(0x70);
  SendChar(cmd);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� SetTouchScreen_Adj()
* ��    �ܣ� ������У׼
* ��ڲ����� ��
* ���ڲ����� ��
****************************************************************************/
void SetTouchScreen_Adj()
{
  SendBeginCMD();
  SendChar(0x72);
  SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� TestTouchScreen()
* ��    �ܣ� ����������
* ��ڲ����� ��
* ���ڲ����� ��
****************************************************************************/
void TestTouchScreen()
{
  SendBeginCMD();
  SendChar(0x73);
  SendEndCmd();
}

/****************************************************************************
* ��    �ƣ� WriteLayer()
* ��    �ܣ� дͼ�����
* ��ڲ����� layer         д���ͼ����
* ���ڲ����� ��
****************************************************************************/
void WriteLayer(uint8 layer)
{
   SendBeginCMD();
   SendChar(0xa1);
   SendChar(layer);
   SendEndCmd();
}
/****************************************************************************
* ��    �ƣ� WriteLayer()
* ��    �ܣ� �л�ͼ����ʾ
* ��ڲ����� layer         �л���ʾ��ͼ��
* ���ڲ����� ��
****************************************************************************/
void DisplyLayer(uint8 layer)
{
   SendBeginCMD();
   SendChar(0xa2);
   SendChar(layer);
   SendEndCmd();
}





