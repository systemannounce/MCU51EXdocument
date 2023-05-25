#include<reg51.h>
unsigned char code byTemp[3]_at_ 0x23;//使用SST单片机做仿真,占用串口
unsigned char data byCounter;
//定义中断计数器
//存放LED灯状态的码表:逐个点亮８个LED,逐个熄灭８个LED,全亮、全灭
unsigned char code byTable[]={0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x01,
0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0x00,0xFF};
void InitTimer1(void)
{
TMOD &= 0x0F;
//定时器/计数器１置为定时方式１
TH1=0xd1;
//TH１装入时间常数
TL1=0x20;
//TL１装入时间常数
ET1=1;
//允许定时器/计数器１中断
EA=1;
//总中断允许
TR1=1;
//启动定时器/计数器１
}

void main(void)
{
    unsigned char data i;
    unsigned char data byDisplayValue;
    byDisplayValue=byTable[0];
    i=0;
    byCounter=10;
    InitTimer1();
    for(;;)
    {
        P1=byDisplayValue;
        if(byCounter==0)
        {//为0,定时时间到
            byCounter=10;
            i++;
        if(i==sizeof(byTable))
        {
            i= 0;
        }
        byDisplayValue=byTable[i];
        }
    }
}
void Timer1Interrupt(void) interrupt 1
{
TL1=0x20;
TH1=0xd1;
byCounter--;
}