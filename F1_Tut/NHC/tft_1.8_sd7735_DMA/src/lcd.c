#include "lcd.h"
#include "font.h"
#include "mydelay.h"
#include "myspi.h"

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 


/* dung buffer nay lam bo dem cho 128 pixel */

//����LCD��Ҫ����
_lcd_dev lcddev;
	
		   
//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(u16 regval)
{ 
	SPILCD_CS_RESET;  //LCD_CS=0
    SPILCD_RS_RESET;
	spi_exchange(regval&0x00FF);
	SPILCD_CS_SET;  //LCD_CS=1	   		 
}
//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(u16 data)
{
 	SPILCD_CS_RESET;  //LCD_CS=0
	SPILCD_RS_SET;	
	spi_exchange(data>>8);
	spi_exchange(data);
	SPILCD_CS_SET;  //LCD_CS=1		
}
void LCD_WR_DATA8(u8 da)   //д8λ����
{
	SPILCD_CS_RESET;  //LCD_CS=0
	SPILCD_RS_SET;				    	   
	spi_exchange(da);	
	SPILCD_CS_SET;  //LCD_CS=1   			 
}					   
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WR_REG_DATA(u8 LCD_Reg, u16 LCD_RegValue)
{
	LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}
//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);  
}	 
//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay(u8 i)
{
	while(i--);
}  		 
//LCD������ʾ
void LCD_DisplayOn(void)
{					   

}	 
//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   

}   

//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    LCD_WR_REG(lcddev.setxcmd); 
	LCD_WR_DATA8(Xpos>>8); 
	LCD_WR_DATA8(Xpos&0XFF);	 
	LCD_WR_REG(lcddev.setycmd); 
	LCD_WR_DATA8(Ypos>>8); 
	LCD_WR_DATA8(Ypos&0XFF);
} 	  

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_WR_DATA(POINT_COLOR); 
} 
//��ʼ��lcd
void LCD_Init(void)
{ 	 	
	SPILCD_RST_RESET;		 
 	delay_ms(50); // delay 20 ms 
   	SPILCD_RST_SET;		 
 	delay_ms(50); // delay 20 ms 

	SPILCD_RST_RESET ;	//LCD_RST=0	 //SPI�ӿڸ�λ
	delay_ms(20); // delay 20 ms 
    SPILCD_RST_SET ;	//LCD_RST=1		
	delay_ms(20);

	lcddev.width=128;
	lcddev.height=160;
	lcddev.wramcmd=0X2C;
	lcddev.setxcmd=0X2A;
	lcddev.setycmd=0X2B; 	

	LCD_WR_REG(0x11); //Sleep out
	delay_ms(120); //Delay 120ms
	//------------------------------------ST7735S Frame Rate-----------------------------------------//
	LCD_WR_REG(0xB1);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_REG(0xB3);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	//------------------------------------End ST7735S Frame Rate-----------------------------------------//
	LCD_WR_REG(0xB4); //Dot inversion
	LCD_WR_DATA8(0x03);
	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x04);
	LCD_WR_REG(0xC1);
	LCD_WR_DATA8(0XC0);
	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x00);
	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x8D);
	LCD_WR_DATA8(0x2A);
	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x8D);
	LCD_WR_DATA8(0xEE);
	//---------------------------------End ST7735S Power Sequence-------------------------------------//
	LCD_WR_REG(0xC5); //VCOM
	LCD_WR_DATA8(0x1A);
	LCD_WR_REG(0x36); //MX, MY, RGB mode
	LCD_WR_DATA8(0xC0);
	//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x22);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0x2E);
	LCD_WR_DATA8(0x30);
	LCD_WR_DATA8(0x25);
	LCD_WR_DATA8(0x2A);
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x26);
	LCD_WR_DATA8(0x2E);
	LCD_WR_DATA8(0x3A);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x13);
	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x16);
	LCD_WR_DATA8(0x06);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x2D);
	LCD_WR_DATA8(0x26);
	LCD_WR_DATA8(0x23);
	LCD_WR_DATA8(0x27);
	LCD_WR_DATA8(0x27);
	LCD_WR_DATA8(0x25);
	LCD_WR_DATA8(0x2D);
	LCD_WR_DATA8(0x3B);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x13);
	//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
	LCD_WR_REG(0x3A); //65k mode
	LCD_WR_DATA8(0x05);
	LCD_WR_REG(0x29); //Display on

	LCD_Clear(WHITE); 
	
}  
//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 	//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD_WR_DATA(color);
	}

}

void LCD_Clear_DMA(u16 color)
{
	uint16_t u16Tmp;
	DMA_InitTypeDef dmaInit;
	
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 	//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM
	
	u16Tmp = color;
	
	SPI2->CR1 &= ~(1 << 6);
	SPI2->CR1 |= (1 << 11);
	SPI2->CR1 |= (1 << 6);
	
	SPILCD_CS_RESET;  //LCD_CS=0
	SPILCD_RS_SET;
	
	DMA_DeInit(DMA1_Channel5);
	
	dmaInit.DMA_BufferSize = 128 * 160;
	dmaInit.DMA_DIR = DMA_DIR_PeripheralDST;
	dmaInit.DMA_M2M = DMA_M2M_Disable;
	dmaInit.DMA_MemoryBaseAddr = (uint32_t)&u16Tmp;
	dmaInit.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dmaInit.DMA_MemoryInc = DMA_MemoryInc_Disable;
	dmaInit.DMA_Mode = DMA_Mode_Normal;
	dmaInit.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
	dmaInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dmaInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dmaInit.DMA_Priority = DMA_Priority_Medium;
	
	DMA_Init(DMA1_Channel5, &dmaInit);
	DMA_Cmd(DMA1_Channel5, ENABLE);
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) {
	}
	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
	}
	
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
	
	SPILCD_CS_SET;  //LCD_CS=1
	
	SPI2->CR1 &= ~(1 << 6);
	SPI2->CR1 &= ~(1 << 11);
	SPI2->CR1 |= (1 << 6);
}

void LCD_Clear_DMA2(u16 color)
{
	uint16_t u16Tmp;
	DMA_InitTypeDef dmaInit;
	uint32_t i;
	
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 	//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     //��ʼд��GRAM
	
	u16Tmp = color;
	
	for (i = 0; i < 160; ++i) {
		if ((i % 2) == 0) {
			LCD_SetCursor(0x00, i);	//���ù��λ�� 
			LCD_WriteRAM_Prepare();     //��ʼд��GRAM
			
			SPI2->CR1 &= ~(1 << 6);
			SPI2->CR1 |= (1 << 11);
			SPI2->CR1 |= (1 << 6);
			
			SPILCD_CS_RESET;  //LCD_CS=0
			SPILCD_RS_SET;
			
			DMA_DeInit(DMA1_Channel5);
			
			dmaInit.DMA_BufferSize = 128;
			dmaInit.DMA_DIR = DMA_DIR_PeripheralDST;
			dmaInit.DMA_M2M = DMA_M2M_Disable;
			dmaInit.DMA_MemoryBaseAddr = (uint32_t)&u16Tmp;
			dmaInit.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
			dmaInit.DMA_MemoryInc = DMA_MemoryInc_Disable;
			dmaInit.DMA_Mode = DMA_Mode_Normal;
			dmaInit.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
			dmaInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
			dmaInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			dmaInit.DMA_Priority = DMA_Priority_Medium;
			
			DMA_Init(DMA1_Channel5, &dmaInit);
			DMA_Cmd(DMA1_Channel5, ENABLE);
			SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
			
			while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) {
			}
			
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
			}
			
			SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
			
			SPILCD_CS_SET;  //LCD_CS=1
			
			SPI2->CR1 &= ~(1 << 6);
			SPI2->CR1 &= ~(1 << 11);
			SPI2->CR1 |= (1 << 6);
		}
	}
	
	for (i = 0; i < 160; ++i) {
		if ((i % 2)) {
			LCD_SetCursor(0x00, i);	//���ù��λ�� 
			LCD_WriteRAM_Prepare();     //��ʼд��GRAM
			
			SPI2->CR1 &= ~(1 << 6);
			SPI2->CR1 |= (1 << 11);
			SPI2->CR1 |= (1 << 6);
			
			SPILCD_CS_RESET;  //LCD_CS=0
			SPILCD_RS_SET;
			
			DMA_DeInit(DMA1_Channel5);
			
			dmaInit.DMA_BufferSize = 128;
			dmaInit.DMA_DIR = DMA_DIR_PeripheralDST;
			dmaInit.DMA_M2M = DMA_M2M_Disable;
			dmaInit.DMA_MemoryBaseAddr = (uint32_t)&u16Tmp;
			dmaInit.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
			dmaInit.DMA_MemoryInc = DMA_MemoryInc_Disable;
			dmaInit.DMA_Mode = DMA_Mode_Normal;
			dmaInit.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
			dmaInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
			dmaInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			dmaInit.DMA_Priority = DMA_Priority_Medium;
			
			DMA_Init(DMA1_Channel5, &dmaInit);
			DMA_Cmd(DMA1_Channel5, ENABLE);
			SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
			
			while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) {
			}
			
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
			}
			
			SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
			
			SPILCD_CS_SET;  //LCD_CS=1
			
			SPI2->CR1 &= ~(1 << 6);
			SPI2->CR1 &= ~(1 << 11);
			SPI2->CR1 |= (1 << 6);
		}
	}
	
	
}

//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	   
	for(i=sy;i<=ey;i++)
	{									   
	 	LCD_SetCursor(sx,i);      				//���ù��λ�� 
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
		for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//���ù��λ�� 	    
	}
}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 		//�õ����Ŀ���
	height=ey-sy+1;		//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD->LCD_RAM=color[i*height+j];//д������ 
	}	  
}  
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 	
//��ָ��λ����ʾһ������(16*16��С)
void showhanzi16(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j,k;
	const unsigned char *temp=hanzi16;    
	temp+=index*32;	
	for(j=0;j<16;j++)
	{
		LCD_SetCursor(x,y+j);
		LCD_WriteRAM_Prepare();	//��ʼд��GRAM
		for(k=0;k<2;k++)
		{
			for(i=0;i<8;i++)
			{ 		     
			 	if((*temp&(1<<i))!=0)
				{
					LCD_WR_DATA(POINT_COLOR);
				} 
				else
				{
					LCD_WR_DATA(BACK_COLOR);
				}   
			}
			temp++;
		}
	 }
}	
//��ָ��λ����ʾһ������(32*32��С)
void showhanzi32(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j,k;
	const unsigned char *temp=hanzi32;    
	temp+=index*128;	
	for(j=0;j<32;j++)
	{
		LCD_SetCursor(x,y+j);
		LCD_WriteRAM_Prepare();	//��ʼд��GRAM
		for(k=0;k<4;k++)
		{
			for(i=0;i<8;i++)
			{ 		     
			 	if((*temp&(1<<i))!=0)
				{
					LCD_WR_DATA(POINT_COLOR);
				} 
				else
				{
					LCD_WR_DATA(BACK_COLOR);
				}   
			}
			temp++;
		}
	 }
}													  
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;      			     
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(!mode) //�ǵ��ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp<<=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }    
	}else//���ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
				temp<<=1;
				y++;
				if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,1);
        x+=size/2;
        p++;
    }  
}

void showimage(u16 x,u16 y) //��ʾ40*40ͼƬ
{  
	u16 i,j,k;
	u16 da;
	k=0;
	for(i=0;i<40;i++)
	{	
		LCD_SetCursor(x,y+i);
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	
		for(j=0;j<40;j++)
		{
			da=qqimage[k*2+1];
			da<<=8;
			da|=qqimage[k*2]; 
			LCD_WR_DATA(da);					
			k++;  			
		}
	}
}

uint8_t u8qq[80];

extern const unsigned char bmp1[40960];
extern const unsigned char bmp2[40960];
//extern const unsigned char bmp3[40960];

void show_img1(void)
{
	DMA_InitTypeDef dmaInit;
	uint32_t i;
	
	for(i=0;i<160;i++)
	{	
		LCD_SetCursor(0,i);
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	
		/*
		for(j=0;j<40;j++)
		{
			da=qqimage[k*2+1];
			da<<=8;
			da|=qqimage[k*2]; 
			LCD_WR_DATA(da);					
			k++;  			
		}
		*/
		
		/* cho nay chuyen thanh gui du lieu bang DMA */
		SPI2->CR1 &= ~(1 << 6);
		SPI2->CR1 |= (1 << 11);
		SPI2->CR1 |= (1 << 6);
		
		SPILCD_CS_RESET;  //LCD_CS=0
		SPILCD_RS_SET;
		
		DMA_DeInit(DMA1_Channel5);
		
		dmaInit.DMA_BufferSize = 128;
		dmaInit.DMA_DIR = DMA_DIR_PeripheralDST;
		dmaInit.DMA_M2M = DMA_M2M_Disable;
		dmaInit.DMA_MemoryBaseAddr = (uint32_t)&bmp1[i * 256];
		dmaInit.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		dmaInit.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dmaInit.DMA_Mode = DMA_Mode_Normal;
		dmaInit.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
		dmaInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		dmaInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		dmaInit.DMA_Priority = DMA_Priority_Medium;
		
		DMA_Init(DMA1_Channel5, &dmaInit);
		DMA_Cmd(DMA1_Channel5, ENABLE);
		SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
		
		while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) {
		}
		
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
		}
		
		SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
		
		SPILCD_CS_SET;  //LCD_CS=1
		
		SPI2->CR1 &= ~(1 << 6);
		SPI2->CR1 &= ~(1 << 11);
		SPI2->CR1 |= (1 << 6);
	}
}

void show_img2(void)
{
	DMA_InitTypeDef dmaInit;
	uint32_t i;
	
	for(i=0;i<160;i++)
	{	
		LCD_SetCursor(0,i);
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	
		/*
		for(j=0;j<40;j++)
		{
			da=qqimage[k*2+1];
			da<<=8;
			da|=qqimage[k*2]; 
			LCD_WR_DATA(da);					
			k++;  			
		}
		*/
		
		/* cho nay chuyen thanh gui du lieu bang DMA */
		SPI2->CR1 &= ~(1 << 6);
		SPI2->CR1 |= (1 << 11);
		SPI2->CR1 |= (1 << 6);
		
		SPILCD_CS_RESET;  //LCD_CS=0
		SPILCD_RS_SET;
		
		DMA_DeInit(DMA1_Channel5);
		
		dmaInit.DMA_BufferSize = 128;
		dmaInit.DMA_DIR = DMA_DIR_PeripheralDST;
		dmaInit.DMA_M2M = DMA_M2M_Disable;
		dmaInit.DMA_MemoryBaseAddr = (uint32_t)&bmp2[i * 256];
		dmaInit.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		dmaInit.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dmaInit.DMA_Mode = DMA_Mode_Normal;
		dmaInit.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
		dmaInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		dmaInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		dmaInit.DMA_Priority = DMA_Priority_Medium;
		
		DMA_Init(DMA1_Channel5, &dmaInit);
		DMA_Cmd(DMA1_Channel5, ENABLE);
		SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
		
		while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) {
		}
		
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
		}
		
		SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
		
		SPILCD_CS_SET;  //LCD_CS=1
		
		SPI2->CR1 &= ~(1 << 6);
		SPI2->CR1 &= ~(1 << 11);
		SPI2->CR1 |= (1 << 6);
	}
}

void showimage_DMA(u16 x,u16 y) //��ʾ40*40ͼƬ
{  
	u16 i,j,k;
	u16 da;
	DMA_InitTypeDef dmaInit;
	
	k=0;
	for(i=0;i<40;i++)
	{	
		LCD_SetCursor(x,y+i);
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	
		/*
		for(j=0;j<40;j++)
		{
			da=qqimage[k*2+1];
			da<<=8;
			da|=qqimage[k*2]; 
			LCD_WR_DATA(da);					
			k++;  			
		}
		*/
		
		/* cho nay chuyen thanh gui du lieu bang DMA */
		SPI2->CR1 &= ~(1 << 6);
		SPI2->CR1 |= (1 << 11);
		SPI2->CR1 |= (1 << 6);
		
		SPILCD_CS_RESET;  //LCD_CS=0
		SPILCD_RS_SET;
		
		DMA_DeInit(DMA1_Channel5);
		
		dmaInit.DMA_BufferSize = 40;
		dmaInit.DMA_DIR = DMA_DIR_PeripheralDST;
		dmaInit.DMA_M2M = DMA_M2M_Disable;
		dmaInit.DMA_MemoryBaseAddr = (uint32_t)&qqimage[k * 2];
		k += 40;
		dmaInit.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		dmaInit.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dmaInit.DMA_Mode = DMA_Mode_Normal;
		dmaInit.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
		dmaInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		dmaInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		dmaInit.DMA_Priority = DMA_Priority_Medium;
		
		DMA_Init(DMA1_Channel5, &dmaInit);
		DMA_Cmd(DMA1_Channel5, ENABLE);
		SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
		
		while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) {
		}
		
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
		}
		
		SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
		
		SPILCD_CS_SET;  //LCD_CS=1
		
		SPI2->CR1 &= ~(1 << 6);
		SPI2->CR1 &= ~(1 << 11);
		SPI2->CR1 |= (1 << 6);
	}
}