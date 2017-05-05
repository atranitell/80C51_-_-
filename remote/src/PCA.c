
/*------------------------------------------------------------------*/
/********STCunio Studio�Ա�http://shop112966725.taobao.com***********/
/*********STCunio Studio QQȺ:117112538******************************/
/********���ߣ�������************************************************/
/********��ϵ��ʽ��13724273732***************************************/
/********���䣺mingbozhu@yeah.net************************************/
/********�޸�����2014.11.17******************************************/
/********�汾V1.1****************************************************/
/*------------------------------------------------------------------*/


#include	"PCA.h"
#include "gpio.h"
#include<stdio.h>
 
	 xdata u8	PCA0_mode=0xff;
   xdata u8 PCA1_mode=0xff;
   xdata volatile UINT32 Capture0Value;
   xdata volatile UINT32 Capture1Value;
   xdata volatile u16 Capture0Value_High=0;
   xdata volatile u16 Capture1Value_High=0;
   bit Capture0FirstPulse;
   bit Capture1FirstPulse;
   bit B_Capture0;
   bit B_Capture1;
//========================================================================
// ����: UpdatePwm(u8 PCA_id, u8 pwm_value)
// ����: ����PWMֵ. 
// ����: PCA_id: PCA���. ȡֵ PCA0,PCA1,PCA2,PCA_Counter
//		 pwm_value: pwmֵ, ���ֵ������͵�ƽ��ʱ��.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	UpdatePwm(u8 PCA_id, u8 pwm_value)
{
    if(PCA_id == PCA0) CCAP0H = pwm_value;
    else if(PCA_id == PCA1)	CCAP1H = pwm_value;
}
//========================================================================
// ����: void	analogWrite(pin,u8 value)
// ����: ģ��д�������������ڵ�ģ�������ǿɵ�ռ�ձȵ�PWM����ź�.
// ����: pin��ֻ������5������6������13������14
//		   value��0-255
// ����: none.
// �汾: V1.1, 2014-11-17
//========================================================================

void	analogWrite(pin,u8 value)
{
      CMOD=(CMOD  & ~(7<<1))|PCA_Clock_12T|DISABLE;//��ʼ��ʱ���Լ�CF�ж�ʹ��λ������
      if(pin==5||pin==6)   //��ѡ��5��6����ת��CCAPn��PCA_P34_P35_P36_P37
      AUXR1 = (AUXR1 & ~(3<<4)) | PCA_P34_P35_P36_P37;
      else if(pin==13||pin==14)//��ѡ��13��14����ת��CCAPn��PCA_P24_P25_P26_P27
      AUXR1 = (AUXR1 & ~(3<<4)) | PCA_P24_P25_P26_P27;
      else return;
      if(pin==5||pin==13)
      {
          PCA0_mode=PCA_Mode_PWM;
          PCA_PWM0  = (PCA_PWM0 & ~(3<<6))|PCA_PWM_8bit;//8λ��ȵ�PWM
          CCAPM0 |=0x42;//�򿪱Ƚ���������ΪPWM���ģʽ
          CCAP0L=~value;
          CCAP0H=~value;
    
          if(value==0)//���PWM0��Ϊ0��1�����
          {
              PWM0_OUT_0();		
          }
          else if(value==255)
          {
              PWM0_OUT_1();
          }
          else		
              PWM0_NORMAL();    
      }
      else if(pin==6||pin==14)
      {	
          PCA1_mode=PCA_Mode_PWM;
          PCA_PWM1  = (PCA_PWM1 & ~(3<<6))|PCA_PWM_8bit;//8λ��ȵ�PWM
          CCAPM1 |=0x42;//�򿪱Ƚ���������ΪPWM���ģʽ
          CCAP1L=~value;
          CCAP1H=~value;
          if(value==0)//���PWM1��Ϊ0��1�����
          {
              PWM1_OUT_0();		
          }
          else if(value==255)
          {
              PWM1_OUT_1();
          }
          else		
              PWM1_NORMAL();
      }
    CR=1;//�������˴򿪼�����
}
//========================================================================
// ����: Capturebegin(pin,pulsemode)
// ����: ��׽��ƽ׼��
// ����: pin��ֻ������5������6������13������14
//		   pulsemode��PCA_Rise_Active��PCA_Fall_Active
// ����: none.
// �汾: V1.1, 2014-11-17
//========================================================================
void Capturebegin(pin,pulsemode)
{
      CMOD=(CMOD  & ~(7<<1))|PCA_Clock_12T|ENABLE;//��ʼ��ʱ���Լ�CF�ж�ʹ��
      if(pin==5||pin==6)
      AUXR1 = (AUXR1 & ~(3<<4)) | PCA_P34_P35_P36_P37;
      else if(pin==13||pin==14)
      AUXR1 = (AUXR1 & ~(3<<4)) | PCA_P24_P25_P26_P27;
      else return;
      if((pin==5)||(pin==13))
      {
          PCA0_mode=PCA_Mode_Capture;//����Ϊ��׽ģʽ
          CCAPM0=pulsemode|ENABLE;//�����ж�
          Capture0FirstPulse=1;
      }
      else if((pin==6)||(pin==14))
      {
          PCA1_mode=PCA_Mode_Capture;//����Ϊ��׽ģʽ
          CCAPM1=pulsemode|ENABLE;//�����ж�
          Capture1FirstPulse=1;
      }
      else return;
}
//========================================================================
// ����: CaptureAvailable()
// ����: ��ѯ�Ƿ�׽�ɹ�
// ����: ��
// ����: true OR false.
// �汾: V1.1, 2014-11-17
//========================================================================
u8 CaptureAvailable()
{
    if(PCA0_mode == PCA_Mode_Capture)//����⵽PCA0Ϊ��׽ģʽ
    {
        if(B_Capture0==1)//���PCA0��׽�Ƿ�ɹ�
        {
          B_Capture0=0;//�����ʶλ
          return true;
        }
        else return false;
    }
    else if(PCA1_mode ==PCA_Mode_Capture)//����⵽PCA1Ϊ��׽ģʽ
    {
        if(B_Capture1==1)//���PCA1��׽�Ƿ�ɹ�
        {
          B_Capture1=0;//�����ʶλ
          return true;
        }
        else 
          return false;
    }
    else
    return false;
}
//========================================================================
// ����: GetCapture()
// ����: ��ò�׽��ƽ�Ŀ��
// ����: ��
// ����: ��ƽ�Ŀ��.
// �汾: V1.1, 2014-11-17
//========================================================================
u32 GetCapture()
{ 
  xdata  UINT32 value0;
  xdata u32 value_temp=0;
  static xdata  u32 value1=0;
  value0.all=0;
  if(PCA0_mode == PCA_Mode_Capture)
  {   
        value0.all=Capture0Value.all;
        value_temp=value0.all;
        value0.all=value0.all-value1;
        value1=value_temp&0xffff;      
        return (value0.all);
  }
  else if(PCA1_mode == PCA_Mode_Capture)
  {              
        value0.all=Capture1Value.all;
        value_temp=value0.all;
        value0.all=value0.all-value1;
        value1=value_temp&0xffff;       
        return (value0.all);
  }  
  return 0;
}
void CaptureEnd()
{
    if(PCA0_mode == PCA_Mode_Capture)
    {
        CCAPM0 &=0xcf;
    }
    else if(PCA1_mode == PCA_Mode_Capture)
    {
        CCAPM1 &=0xcf;
    }
}

//========================================================================
// ����: void	PCA_Handler (void) interrupt PCA_VECTOR
// ����: PCA�жϴ������.
// ����: None
// ����: none.
// �汾: V1.1, 2014-11-17
//========================================================================
void	PCA_Handler (void) interrupt PCA_VECTOR
{
	if(CCF0)		//PCAģ��0�ж�
	{
      CCF0 = 0;		//��PCAģ��0�жϱ�־

      if(PCA0_mode == PCA_Mode_Capture)
      {       
          Capture0Value.BYTES.byte2 = CCAP0H;	//��CCAP0H
          Capture0Value.BYTES.byte1 = CCAP0L;  //��CCAP0L
          Capture0Value.WORDS.int2=0;         //��Capture0Value�ĸ�16λ��0
          B_Capture0 = 1;                     //��׽�ɹ���ʶ��1
          if(Capture0FirstPulse==1)           //��PCA0��1�β�׽�����źţ���ô�������
          {
              CR=1;                           //��Ҫ�򿪼�����
              Capture0FirstPulse=0;  
              CCAPM0 |=0x30;                  //ͬʱ������������ֻ������ڣ�ֻ���������򸺲���
              Capture0Value_High=0;           //��һ�β�׽ֻ���¼CCAP0H��CCAP0L��λ�ã���16λ��0�������´β�׽���ȵļ���
          }
          else
          {
              if(CF==1)
              {
                  CF=0;
              Capture0Value_High++;           //��CCF0�жϴ�������г���CF�жϣ���ô��Ҫ����һ�μ��������򽫻��λ����1
              } 
              Capture0Value.WORDS.int2=Capture0Value_High;	//��¼��16λ
              Capture0Value_High = 0;         
          }           
      }
      else return;
	}

	if(CCF1)	//PCAģ��1�ж�
	{
      CCF1 = 0;		//��PCAģ��1�жϱ�־
    
      if(PCA1_mode == PCA_Mode_Capture)
      {        
          Capture1Value.BYTES.byte2 = CCAP1H;	//��CCAP1H
          Capture1Value.BYTES.byte1 = CCAP1L;  //��CCAP1L
          Capture1Value.WORDS.int2=0;         //��Capture1Value�ĸ�16λ��0
          B_Capture1 = 1;                     //��׽�ɹ���ʶ��1      
          if(Capture1FirstPulse==1)           //���ǲ�׽1��1�β�׽�����ź�
          {
              CR=1;                           //��Ҫ�򿪼�����
              Capture1FirstPulse=0;
              CCAPM1 |=0x30;                  //ͬʱ����������
              Capture1Value_High=0;           //��һ�β�׽ֻ���¼CCAP1H��CCAP1L��λ�ã���16λ��0�������´β�׽���ȵļ���
          }
          else
          {
              if(CF==1)
              {
                  CF=0;
                  Capture1Value_High++;                   //��CCF1�жϴ�������г���CF�жϣ���ô��Ҫ����һ�μ��������򽫻��λ����1
              }        
              Capture1Value.WORDS.int2=Capture1Value_High;//��¼��16λ
              Capture1Value_High=0;               
          }   
      }
	}
	if(CF)	//PCA����ж�
	{
      CF = 0;			//��PCA����жϱ�־
      if(PCA0_mode == PCA_Mode_Capture)
      {       
          if(Capture0FirstPulse==0)  
              Capture0Value_High++;
      }
      else if(PCA1_mode == PCA_Mode_Capture)
      {      
          if(Capture1FirstPulse==0)  
              Capture1Value_High++;      
      }   
	}
}