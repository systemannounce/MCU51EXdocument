#include <REGX51.H>
unsigned char data byData[10] _at_ 0x72; // 在数据存储器70H~79H空间开辟数组
unsigned char data byCounter = 0;
// 发送数据的计数器
void main(void)
{
    unsigned char data i;
    SP = 0x2F;
    // 设置栈底地址
    TMOD = 0x20;
    // T１作波特率发生器,采用定时器方式2
    TL1 = 0xFD;
    // TL１置初始值,设置波特率
    TH1 = 0xFD;
    // TH１置重装载值
    TR1 = 1;
    // T１启动工作
    SCON = 0x50;
    // 串口工作于方式1,允许接收数据
    PCON = PCON | 0x80;
    // SMOD置1,波特率倍增
    ES = 1;
    // 打开串口中断
    EA = 1;
    // 打开总中断
    for (i = 0; i < 10; i++)
    { // 在数据存储器70H~79H空间存放字符‘０’‘１’...‘９’的ASCII码
        byData[i] = '0' + i;
    }
    SBUF = byData[byCounter]; // 第一个数据放入发送缓冲区,启动发送
    byCounter++;
    // 发送数据的计数器自加1
    while (1)
    { // 主循环不做任何事情
        ;
    }
}
void UART(void) interrupt 4
// 串口中断服务程序
{
    if (TI == 1)
    { // 是发送中断
        TI = 0;
        // 清除发送中断标志位
        if (byCounter < 10)
        // 判断是否发送完10个数据
        {
            SBUF = byData[byCounter]; // 继续发送数据
            byCounter++;
            // 发送数据的计数器自加1
        }
    }
    else
    { // 是接收中断
        RI = 0;
        // 清除接收中断标志位
        P1 = SBUF;
        // 将接收的数据在P1口显示,“0”亮灯,“1”灭灯
    }
}
