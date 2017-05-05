#include"eInterrupt.h"

void  setHighPolity(u8 interruptNum)
{
     switch(interruptNum)
     {
        case INT0:   
                          PX0=PolityHigh;         //�������ȼ�
                          break;
        case TIMER0:
                          PT0=PolityHigh;
                          break;
        case INT1:   
                          PX1=PolityHigh;
                          break;
        case TIMER1:
                          PT1=PolityHigh;	//�����ȼ��ж�
                          break;
        case UART1:
                          PS =PolityHigh;	//�����ȼ��ж�
                          break;
        case ADC:
                          PADC=PolityHigh;
                          break;
        case LVD:
                          PLVD=PolityHigh;
                          break;
        case PCA:  
                          PPCA=PolityHigh;
                          break;
        case UART2:
                          IP2|=PolityHigh;
                          break;
        case SPI:         
                          IP2|=0x02;  
                          break;
        default:
                          break;
     }
}
void  setLowPolity(u8 interruptNum)
{
     switch(interruptNum)
     {
        case INT0:   
                          PX0=PolityLow;         //�������ȼ�
                          break;
        case TIMER0:
                          PT0=PolityLow;
                          break;
        case INT1:   
                          PX1=PolityLow;
                          break;
        case TIMER1:
                          PT1=PolityLow;	//�����ȼ��ж�
                          break;
        case UART1:
                          PS =PolityLow;	//�����ȼ��ж�
                          break;
        case ADC:
                          PADC=PolityLow;
                          break;
        case LVD:
                          PLVD=PolityLow;
                          break;
        case PCA:  
                          PPCA=PolityLow;
                          break;
        case UART2:
                          IP2&=0xFE;
                          break;
        case SPI:  
                          IP2&=0xFD;  
                          break;
        default:
                          break;
     }
}
void	attachInterrupt(u8 interruptNum ,u8 mode)//PolityHigh or PolityLow
{
	switch (interruptNum)
	{
		case INT0: 
						EX0=1;              //�����ⲿ�ж�0�ж�
						IT0=mode;           //�жϴ���ģʽ
						break;
    
		case INT1: 
	          EX1=1;
						IT1=mode;
						break;
    
		case INT2: 
            INT_CLKO |=  0x10;  //�����ȼ����ã������ⲿ�ж�2�ж�
						break;
    
		case INT3: 
            INT_CLKO |=  0x20;	//�����ȼ����ã������ⲿ�ж�3�ж�
						break;
    
		case INT4: 
            INT_CLKO |=  0x40;	//�����ȼ����ã������ⲿ�ж�4�ж�
						break;
		default: 
						break;
	}
}
void detachInterrupt(u8 interruptNum)
{
		switch(interruptNum)
	{
			case INT0: EX0=0;
							break;
			case INT1: EX1=0;
							break;
			case INT2: INT_CLKO &= 0xef;
							break;
			case INT3: INT_CLKO &= 0xdf;
							break;
			case INT4: INT_CLKO &= 0xbf;
							break;
			default:
							break;
	}
}
void	Timer0_attachInterrupt(u16 time)
{
    u8 TH0_TEMP,TL0_TEMP;
    u16 TIM_Value;
		TR0 = 0;		//ֹͣ����
		ET0 = 1;	//�����ж�

		TMOD &= ~0x03;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		AUXR |=  0x80;	//1T
		TMOD &= ~0x04;	//��ʱ
	
		INT_CLKO &= ~0x01;	//�����ʱ��
		TIM_Value     = 65536UL - (MAIN_Fosc /1000*time/1000);		//��ֵ
		TH0_TEMP = (u8)(TIM_Value >> 8);
		TL0_TEMP = (u8)TIM_Value;
		TH0=TH0_TEMP;
		TL0=TL0_TEMP;
		TR0 = 1;	//��ʼ����
}
void  Timer0_detachInterrupt()
{
    ET0 = 0;	//�ر��ж�
}
void  Timer1_attachInterrupt(u16 time)
{
    u8 TH1_TEMP,TL1_TEMP;
    u16 TIM_Value;
		TR1 = 0;		//ֹͣ����
		ET1 = 1;	//�����ж�		
		TMOD &= ~0x30;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		AUXR |=  0x40;	//1T
		TMOD &= ~0x40;	//��ʱ
	
		INT_CLKO &= ~0x02;	//�����ʱ��
		TIM_Value     = 65536UL - (MAIN_Fosc /1000*time/1000);		//��ֵ
		TH1_TEMP = (u8)(TIM_Value >> 8);
		TL1_TEMP = (u8)TIM_Value;
		TH1=TH1_TEMP;
		TL1=TL1_TEMP;
		TR1 = 1;	//��ʼ����
}
void  Timer1_detachInterrupt()
{
    ET1 = 0;	//�ر��ж�
}
void  Timer2_attachInterrupt(u16 time)
{
    u8 TH2_TEMP,TL2_TEMP;
    u16 TIM_Value;
		AUXR &= ~0x10;		//ֹͣ����
		IE2  |= 0x04;	//�����ж�
                  //��ʱ��2�����ȼ�����
                  //��ʱ��2���̶�Ϊ16λ��װģʽ
	
		AUXR |=  0x04;	//1T
		AUXR &= ~0x08;	//��ʱ
	
		INT_CLKO &= ~0x04;	//�����ʱ��
		TIM_Value     = 65536UL - (MAIN_Fosc /1000*time/1000);		//��ֵ
		TH2_TEMP = (u8)(TIM_Value >> 8);
		TL2_TEMP = (u8)TIM_Value;
		T2H=TH2_TEMP;
		T2L=TL2_TEMP;
		AUXR |= 0x10;	//��ʼ����
}
void  Timer2_detachInterrupt()
{
    IE2  &= ~0x04;	//�ر��ж�
}
void  Timer3_attachInterrupt(u16 time)
{
    u8 TH3_TEMP,TL3_TEMP;
    u16 TIM_Value;
		T4T3M &= ~0x08;		//ֹͣ����
		IE2  |= 0x20;	//�����ж�
                  //��ʱ��3�����ȼ�����
                  //��ʱ��3���̶�Ϊ16λ��װģʽ
	
		T4T3M |=  0x02;	//1T
		T4T3M &= ~0x04;	//��ʱ
	
		T4T3M &= ~0x01;	//�����ʱ��
		TIM_Value     = 65536UL - (MAIN_Fosc /1000*time/1000);		//��ֵ
		TH3_TEMP = (u8)(TIM_Value >> 8);
		TL3_TEMP = (u8)TIM_Value;
		T3H=TH3_TEMP;
		T3L=TL3_TEMP;
		T4T3M |= 0x08;	//��ʼ����
}
void  Timer3_detachInterrupt()
{
    IE2  &= ~0x20;	//�ر��ж�
}
void  Timer4_attachInterrupt(u16 time)
{
    u8 TH4_TEMP,TL4_TEMP;
    u16 TIM_Value;
		T4T3M &= ~0x80;		//ֹͣ����
		IE2  |= 0x40;	//�����ж�
                  //��ʱ��4�����ȼ�����
                  //��ʱ��4���̶�Ϊ16λ��װģʽ
	
		T4T3M |=  0x20;	//1T
		T4T3M &= ~0x40;	//��ʱ
	
		T4T3M &= ~0x10;	//�����ʱ��
		TIM_Value     = 65536UL - (MAIN_Fosc /1000*time/1000);		//��ֵ
		TH4_TEMP = (u8)(TIM_Value >> 8);
		TL4_TEMP = (u8)TIM_Value;
		T4H=TH4_TEMP;
		T4L=TL4_TEMP;
		T4T3M |= 0x80;	//��ʼ����
}
void  Timer4_detachInterrupt()
{
    IE2  &= ~0x40;	//�ر��ж�
}