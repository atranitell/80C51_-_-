#include"epwm.h"
//========================================================================
// ����: epwmnTcolck(u16 nTclock)
// ����: pwmʱ�ӷ�Ƶ������
// ����: nTclock��1~16��Ƶ.
// ����: none.
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void epwmnTcolck(u8 nTclock)//pwmʱ��
{
    P_SW2 |= 0x80;//ʹ���ⲿ��չSFR
    PWMCKS = nTclock-1;//��Ƶ
    P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
}
//========================================================================
// ����: epwmTwide(u16 Twide)
// ����: pwm���ڿ�����á�
// ����: Twide��15λ.
// ����: none.
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void epwmTwide(u16 Twide)
{
    P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
    PWMC=Twide;
    P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
}
//========================================================================
// ����: epwmStartADC(u8 choice)
// ����: pwm����AD�¼�������
// ����: choice��1������AD��0��������AD.
// ����: none.
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void epwmStartADC(u8 StartADC_EN)
{
    PWMCFG = (PWMCFG&0x3f)|(StartADC_EN<<6);
}
//========================================================================
// ����: epwmFaultSource(u8 FaultSource,u8 FaultCloseIO)
// ����: ����pwm����Դ������
// ����: FaultSource��1�����Ƚ����쳣��2�����P24�쳣��3����������쳣.
//       FaultCloseIO��1��pwm�쳣��ر�pwm�����0��pwm�쳣��Ӱ��pwm���
// ����: none.
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void epwmFaultSource(u8 FaultSource,u8 FaultCloseIO)
{
    PWMFDCR |= 0x20;//ʹ��PWM�쳣���
    PWMFDCR  = (PWMFDCR&0xf3)|FaultSource;   
    PWMFDCR  = (PWMFDCR&0xef)|FaultCloseIO;
}
//========================================================================
// ����: epwmFirstSignalLevel(u8 pin,u8 value)
// ����: ����pwm��ʼ��ƽ������
// ����: pin��ѡ����Ҫ��pwm���ڵ�����.
//       value��1��pwm��ʼ����ߣ�0��pwm��ʼ�����
// ����: none.
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void epwmFirstSignalLevel(u8 pin,u8 value)//���ó�ʼ��ƽ
{   
    
    switch(pin)
    {
        case 7 :         //��1��PWM2
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM2CR&= ~0x08;//ѡ��P3.7ΪPWM2
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG = (PWMCFG&0xfe)|value; 
                PWMCR |= 0x01;
                break;
        case 9 :         //��1��PWM3
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM3CR&= ~0x08;//ѡ��P2.1ΪPWM3
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR
                PWMCFG =(PWMCFG&0xfd)|(value<<1);
                PWMCR |= 0x02;
                break;
        case 10 :       //��1��PWM4
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM4CR&= ~0x08;//ѡ��P2.2ΪPWM4
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR
                PWMCFG =(PWMCFG&0xfb)|(value<<2);
                PWMCR |= 0x04;
                break;
        case 11 :       //��1��PWM5
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM5CR&= ~0x08;//ѡ��P2.3ΪPWM5
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR
                PWMCFG =(PWMCFG&0xf7)|(value<<3);
                PWMCR |= 0x08;
                break;
        case 62 :       //��1��PWM6
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM6CR&= ~0x08;//ѡ��P1.6ΪPWM6
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG =(PWMCFG&0xef)|(value<<4);
                PWMCR |= 0x10;
                break;
        case 63 :       //��1��PWM7
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM7CR&= ~0x08;//ѡ��P1.7ΪPWM7
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG =(PWMCFG&0xdf)|(value<<5);
                PWMCR |= 0x20;          
                break;
        case 15 :       //��2��PWM2
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM2CR|= 0x08;//ѡ��P2.7ΪPWM2
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG =(PWMCFG&0xfe)|value;
                PWMCR |= 0x01;
                break;
        case 21 :       //��2��PWM3
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM3CR|= 0x08;//ѡ��P4.5ΪPWM3
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG =(PWMCFG&0xfd)|(value<<1);
                PWMCR |= 0x02;
                break;
        
        case 20 :       //��2��PWM4
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM4CR|= 0x08;//ѡ��P4.4ΪPWM4
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG =(PWMCFG&0xfb)|(value<<2);
                PWMCR |= 0x04;
                break;
        
        case 18 :       //��2��PWM5
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM5CR|= 0x08;//ѡ��P4.2ΪPWM5
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG =(PWMCFG&0xf7)|(value<<3);
                PWMCR |= 0x08;
                break;
        
        case 47 :       //��2��PWM6
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM6CR|= 0x08;//ѡ��P0.7ΪPWM6
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG =(PWMCFG&0xef)|(value<<4);
                PWMCR |= 0x10;
                break;
        
        case 46 :       //��2��PWM7
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM7CR|= 0x08;//ѡ��P0.6ΪPWM7
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                PWMCFG =(PWMCFG&0xdf)|(value<<5);
                PWMCR |= 0x20;
                break;
                
        default:               
                break;
    }
    
}
//========================================================================
// ����: epwmSetValue(u8 pin,u16 PWMT1,u16 PWMT2)
// ����: ����pwm�ķ�תֵ������
// ����: pin��ѡ����Ҫ��pwm���ڵ����š�
//       PWMT1����һ����תֵ�����ɳ����ڶ�����תֵ��
//       PWMT2���ڶ�����תֵ�����ɳ������ڡ�
// ����: none.
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void epwmSetValue(u8 pin,u16 PWMT1,u16 PWMT2)
{
    switch(pin)
    {
       case 7 :         //��1��PWM2
       case 15 :       //��2��PWM2
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM2T1 = PWMT1;//
                PWM2T2 = PWMT2;                
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR
                break;
       
        case 9 :         //��1��PWM3
        case 21 :       //��2��PWM3
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM3T1 = PWMT1;//
                PWM3T2 = PWMT2;
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR

                break;
        case 10 :       //��1��PWM4
        case 20 :       //��2��PWM4
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM4T1 = PWMT1;//
                PWM4T2 = PWMT2;
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR

                break;
        case 11 :       //��1��PWM5
        case 18 :       //��2��PWM5 
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM5T1 = PWMT1;//
                PWM5T2 = PWMT2;
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR
                break;
        case 62 :       //��1��PWM6
        case 47 :       //��2��PWM6
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM6T1 = PWMT1;//
                PWM6T2 = PWMT2;
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                break;
        case 63 :       //��1��PWM7
        case 46 :       //��2��PWM7
                P_SW2 |= 0x80;//ʹ���ⲿ��չSFR 
                PWM7T1 = PWMT1;//
                PWM7T2 = PWMT2;
                P_SW2 &= ~0x80;//�˳��ⲿ��չSFR 
                break;
                
        default:               
                break;
    }
}
//========================================================================
// ����: epwmCRbegin()
// ����: ����PWM��������
// ����: ��
// ����: none.
// �汾: VER1.1
// ����: 2014-11-17
// ��ע: 
//========================================================================
void epwmCRbegin()
{
     PWMCR |= 0x80;
}