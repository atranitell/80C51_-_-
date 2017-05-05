//========================================================================
//	STCunio Studio�Ա�http://shop112966725.taobao.com
//	STCunio Studio QQȺ:117112538
//	���ߣ�mingbozhu
//	��ϵ��ʽ��13724273732
//	���䣺mingbozhu@yeah.net
//	�޸�����2014.11.17
//	�汾V1.1
//========================================================================

#include	"GPIO.h"
u8 code digital_pin_to_bit_mask_PGM[]={
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//D0-D7����   P3
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//D8-D15����  P2
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//D16-D23���� P4
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//D24-D31���� P5
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//D32-D39���� P6
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//D40-D47���� P7
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//D48-D55���� P0
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 //D56-D63���� P1
};
u8 code digital_pin_to_bit_PGM[]={
    0,1,2,3,4,5,6,7,//D0-D7   P3
    0,1,2,3,4,5,6,7,//D8-D15  P2
    0,1,2,3,4,5,6,7,//D16-D23 P4
    0,1,2,3,4,5,6,7,//D24-D31 P5
    0,1,2,3,4,5,6,7,//D32-D39 P6
    0,1,2,3,4,5,6,7,//D40-D47 P7
    0,1,2,3,4,5,6,7,//D48-D55 P0
    0,1,2,3,4,5,6,7 //D56-D63 P1
};
u8 code digital_pin_to_port_PGM[]={
    0,0,0,0,0,0,0,0,//D0-D7   P3
    1,1,1,1,1,1,1,1,//D8-D15  P2
    2,2,2,2,2,2,2,2,//D16-D23 P4
    3,3,3,3,3,3,3,3,//D24-D31 P5
    4,4,4,4,4,4,4,4,//D32-D39 P6
    5,5,5,5,5,5,5,5,//D40-D47 P7
    6,6,6,6,6,6,6,6,//D48-D55 P0
    7,7,7,7,7,7,7,7 //D56-D63 P1
}; 
u8 code digital_pin_mode_PxM1_PGM[4][8]={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//����׼˫���
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//��������
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//��©���
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//�������
};
u8 code digital_pin_mode_PxM0_PGM[4][8]={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//����׼˫���
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//��������
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//��©���
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,//�������    
};
//========================================================================
//	����Digital IO�Ĺ���ģʽ
//	STCunio��4��IO����ģʽ
//	1.׼˫��ģʽ���ڲ�������PullUp
//	2.��������ģʽ HighZ
//	3.��©ģʽ(�ڲ��Ͽ�����)OpenD
//	4.�������ģʽ OutPP
//========================================================================   
void pinMode(u8 pin,u8 mode)
{
	u8 Bitmask,Bit,Port,PxM1,PxM0;
	Port = digital_pin_to_port_PGM[pin];
  Bitmask  = digital_pin_to_bit_mask_PGM[pin];
  Bit  = digital_pin_to_bit_PGM[pin];
  PxM1 = digital_pin_mode_PxM1_PGM[mode][Bit];
  PxM0 = digital_pin_mode_PxM0_PGM[mode][Bit];
	switch(Port)
	{
		case 0://P3 0-7
            P3M1  = (P3M1&~Bitmask)|PxM1;
            P3M0  = (P3M0&~Bitmask)|PxM0;
						break;
		case 1://P2 8-15	
            P2M1  = (P2M1&~Bitmask)|PxM1;
            P2M0  = (P2M0&~Bitmask)|PxM0;
						break;
		case 2://P4 16-23
            P4M1  = (P4M1&~Bitmask)|PxM1;
            P4M0  = (P4M0&~Bitmask)|PxM0;
						break;
		case 3://P5 24-31
            P5M1  = (P5M1&~Bitmask)|PxM1;
            P5M0  = (P5M0&~Bitmask)|PxM0;
						break;
		case 4://P6 32-39
            P6M1  = (P6M1&~Bitmask)|PxM1;
            P6M0  = (P6M0&~Bitmask)|PxM0;
						break;
		case 5://P7 40-47
            P7M1  = (P7M1&~Bitmask)|PxM1;
            P7M0  = (P7M0&~Bitmask)|PxM0;
						break;
		case 6://P0 48-55
            P0M1  = (P0M1&~Bitmask)|PxM1;
            P0M0  = (P0M0&~Bitmask)|PxM0;
						break;
		case 7://P1 56-63
            P1M1  = (P1M1&~Bitmask)|PxM1;
            P1M0  = (P1M0&~Bitmask)|PxM0;
						break;
		default:
						break;
	}	
}

//дIO��
void digitalWrite(u8 pin,u8 value)
{
	u8 Bitmask,Port;
	
	Port = digital_pin_to_port_PGM[pin];
  Bitmask  = digital_pin_to_bit_mask_PGM[pin];
	switch(Port)
	{
		case 0://P3 0-7			
				if(value)P3|=Bitmask;
				else P3&=~Bitmask;			
				break;
		case 1://P2 8-15	
			  if(value)P2|=Bitmask;
			  else P2&=~Bitmask;				
				break;
		case 2://P4 16-23
			  if(value)P4|=Bitmask;
			  else P4&=~Bitmask;
				break;
		case 3://P5
			  if(value)P5|=Bitmask;
			  else P5&=~Bitmask;
				break;
		case 4://P6
			  if(value)P6|=Bitmask;
			  else P6&=~Bitmask;
				break;
		case 5://P7
			  if(value)P7|=Bitmask;
			  else P7&=~Bitmask;
				break;
	  case 6://P0
			  if(value)P0|=Bitmask;
			  else P0&=~Bitmask;
				break;
		case 7://P1
			  if(value)P1|=Bitmask;
			  else P1&=~Bitmask;
				break;
		default:
				break;	
	}
}
//��Digital IOȡ��
void pinInvert(u8 pin)
{	
	u8 Bitmask,Port;
	Port = digital_pin_to_port_PGM[pin];
  Bitmask  = digital_pin_to_bit_mask_PGM[pin];
	switch(Port)
	{
		case 0:
				P3^=Bitmask;
				break;
		case 1:
				P2^=Bitmask;
				break;
		case 2:
				P4^=Bitmask;
				break;
		case 3:
				P5^=Bitmask;
				break;
		case 4:
				P6^=Bitmask;
				break;
		case 5:
				P7^=Bitmask;
				break;
		case 6:
				P0^=Bitmask;
				break;
		case 7:
				P1^=Bitmask;
				break;
		default:
				break;
	}
}
//��IO��״̬

u8 digitalRead(u8 pin)
{
	u8 Bitmask,Port;
	
	Port = digital_pin_to_port_PGM[pin];
  Bitmask  = digital_pin_to_bit_mask_PGM[pin];
	switch(Port)
	{
		case 0:
				
				if(P3&Bitmask)return HIGH;
				else return LOW;				
				break;
		case 1:
				if(P2&Bitmask)return HIGH;
				else return LOW;
				break;
		case 2:
				if(P4&Bitmask)return HIGH;
				else return LOW;
				break;
		case 3:
				if(P5&Bitmask)return HIGH;
				else return LOW;
				break;
		case 4:
				if(P6&Bitmask)return HIGH;
				else return LOW;
				break;
		case 5:
				if(P7&Bitmask)return HIGH;
				else return LOW;
				break;
		case 6:
				if(P0&Bitmask)return HIGH;
				else return LOW;
				break;
		case 7:
				if(P1&Bitmask)return HIGH;
				else return LOW;
				break;
		default:
				return LOW;
				break;
	}

}
//========================================================================
// ����: shiftOut(u8 dataPin,u8 clockPin,u8 bitOrder,u8 value)
// ����: ���з������ݡ�
// ����: dataPin��ѡ����Ҫ�����������ڵ����š�
// ������clockPin��ѡ����Ҫ��ʱ�������ڵ����š�
// ������bitOrder��ѡ�������ݵ�˳�򣬰���MSBFIRST���λ�ȷ���LSBFIRST���λ�ȷ�
// ������value�����͵�����
// ����: none.
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================  
void shiftOut(u8 dataPin,u8 clockPin,u8 bitOrder,u8 value)
{
		unsigned char	i;
	for(i=0; i<8; i++)
	{ 
		if(bitOrder==MSBFIRST)
		{
				if(value & 0x80)digitalWrite(dataPin,HIGH);
				else			digitalWrite(dataPin,LOW);
			  value = value << 1;
		}
		else
		{
				if(value & 0x01)digitalWrite(dataPin,HIGH);
				else			digitalWrite(dataPin,LOW);
			  value = value >> 1;
		}					
		digitalWrite(clockPin,HIGH);
		digitalWrite(clockPin,LOW);		
	}
}
//========================================================================
// ����: shiftIn(u8 dataPin,u8 clockPin,u8 bitOrder)
// ����: ���н������ݡ�
// ����: dataPin��ѡ����Ҫ�����������ڵ����š�
// ������clockPin��ѡ����Ҫ��ʱ�������ڵ����š�
// ������bitOrder��ѡ��������ݵ�˳�򣬰�������MSBFIRST���λ������LSBFIRST���λ
// ����: value�����յ�����
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
u8 shiftIn(u8 dataPin,u8 clockPin,u8 bitOrder)

{
		char	i;
	  unsigned char	value=0;
  if(bitOrder==MSBFIRST)
  {
    for(i=7; i>=0; i--)
    { 
        digitalWrite(clockPin,HIGH);
        digitalWrite(clockPin,LOW);
			  value |= (digitalRead(dataPin)<<i);					        				
    }
  }
  else	
  {
    for(i=0; i<=7; i++)
    {
        digitalWrite(clockPin,HIGH);											  					
        digitalWrite(clockPin,LOW);	  
        value |= (digitalRead(dataPin)<<i);
    }
  }
	return value;
}
//========================================================================
// ����: tone(u8 pin,u16 frequency)
// ����: ����һ��Ƶ�ʵĺ�����
// ����: pin��ѡ����Ҫ���š�
// ������frequency�����÷�����Ƶ�ʡ�
// ����: none
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void tone(u8 pin,u16 frequency)
{
    u8 TH_TEMP,TL_TEMP;
    u16 TIM_Value;
    switch(pin)
    {
      case 5: //T0
              TMOD &= ~0x03;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
              AUXR &= ~0x80;	//12T
              TMOD &= ~0x04;	//��ʱ	
              INT_CLKO |= 0x01;	//���ʱ��
              TIM_Value = 65536UL - (MAIN_Fosc /frequency/24+0.5);		//��ֵ
              TH_TEMP = (u8)(TIM_Value >> 8);
              TL_TEMP = (u8)TIM_Value;
              TH0=TH_TEMP;
              TL0=TL_TEMP;
              TR0=1;
              break;
      case 4: //T1

              TMOD &= ~0x30;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
              AUXR &= ~0x40;	//12T
              TMOD &=  0x40;	//��ʱ	
              INT_CLKO |= 0x02;	//���ʱ��
              TIM_Value     = 65536UL -(MAIN_Fosc /frequency/24+0.5);		//��ֵ
              TH_TEMP = (u8)(TIM_Value >> 8);
              TL_TEMP = (u8)TIM_Value;
              TH1=TH_TEMP;
              TL1=TL_TEMP;
              TR1 = 1;	//��ʼ����
              break;
      case 0: //T2
                  //��ʱ��2���̶�Ϊ16λ��װģʽ
              AUXR &= ~0x04;	//12T
              AUXR &= ~0x08;	//��ʱ	
              INT_CLKO |= 0x04;	//���ʱ��
              TIM_Value     = 65536UL - (MAIN_Fosc /frequency/24+0.5);		//��ֵ
              TH_TEMP = (u8)(TIM_Value >> 8);
              TL_TEMP = (u8)TIM_Value;
              T2H=TH_TEMP;
              T2L=TL_TEMP;
              AUXR |= 0x10;	//��ʼ����
              break;
      case 52:  //T3
              
              T4T3M &= ~0x02;	//12T
              T4T3M &= ~0x04;	//��ʱ	
              T4T3M |=  0x01;	//���ʱ��
              TIM_Value     = 65536UL - (MAIN_Fosc /frequency/24+0.5);		//��ֵ
              TH_TEMP = (u8)(TIM_Value >> 8);
              TL_TEMP = (u8)TIM_Value;
              T3H=TH_TEMP;
              T3L=TL_TEMP;
              T4T3M |= 0x08;	//��ʼ����
              break;
      case 54://T4
        
              T4T3M &= ~0x20;	//12T
              T4T3M &= ~0x40;	//��ʱ	
              T4T3M |=  0x10;	//���ʱ��
              TIM_Value     = 65536UL - (MAIN_Fosc /frequency/24+0.5);		//��ֵ
              TH_TEMP = (u8)(TIM_Value >> 8);
              TL_TEMP = (u8)TIM_Value;
              T4H=TH_TEMP;
              T4L=TL_TEMP;
              T4T3M |= 0x80;	//��ʼ����
              break;
      default:
              break;
    }
}
//========================================================================
// ����: noTone(u8 pin)
// ����: ����Ƶ�ʷ����ĺ�����
// ����: pin��ѡ����Ҫ���š�
// ����: none
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void noTone(u8 pin)
{
   
   switch(pin)
   {
      case 5: //T0
              INT_CLKO &= ~0x01;	//�����ʱ��
              TR0=0;//�رն�ʱ��0
              break;
      case 4: //T1	
              INT_CLKO &= ~0x02;	//�����ʱ��
              TR1 =0;//�رն�ʱ��1
              break;
      case 0: //T2
              INT_CLKO &= ~0x04;	//�����ʱ��
              AUXR &= ~0x10;	//�رն�ʱ��2
              break;
      case 52:  //T3
              T4T3M &= ~0x01;	//�����ʱ��
              T4T3M &= ~0x08;	//�رն�ʱ��3
              break;
      case 54://T4
              T4T3M &= ~0x10;	//�����ʱ��
              T4T3M &= ~0x80;	//��ʼ����
              break;
      default:
              break; 	
   }
   digitalWrite(pin,HIGH);
}