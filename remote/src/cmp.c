#include"cmp.h"

void CMPbegin(u8 CMP_P,u8 CMP_N,u8 CMP_OUT_EN)
{    
    CMPCR1  = (CMPCR1&0xf7)|CMP_P;//�Ƚ�����������ѡ��
    CMPCR1  = (CMPCR1&0xfb)|CMP_N;//�Ƚ�����������ѡ��
    CMPCR1  = (CMPCR1&0xfd)|(CMP_OUT_EN<<1);//ѡ��Ƚ��������P1.2 
  
    CMPCR2  = 0x10;//�Ƚ��������ȡ���������0.1us���˲���������16��ʱ������      
    CMPCR1  |= 0x80;
}
u8 CMPresult()
{
    u8 value;
    value=CMPCR1&0x01;
    return value;
}