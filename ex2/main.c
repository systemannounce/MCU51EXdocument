#if 0
#include <REGX51.H>
#include <intrins.h> 
//unsigned char code byTemp[3]  at 0x23; 

void Delay1s(void)
{
	unsigned char a,b,c;
	for(c=23;c>0;c--)
	for(b=71;b>0;b--)
	for(a=60;a>0;a--);
	_nop_(); //ifKeil,requireuseintrins.h
}
void main(void)
{ 
	unsigned char data byLedValue= 0xfe ; 
	for(;;)
	{
		P1 = byLedValue ; 
		Delay1s(); 
		byLedValue = byLedValue << 1;
		byLedValue++;
	}
}
#endif

#if 1

#include<reg51.h>
unsigned char code byTemp[3]_at_ 0x23;
void main(void)
{
	unsigned char data byValue;
	while(1)
	{
		P0=0xff;
		byValue = P0;
		P1= byValue;
	}
}

#endif