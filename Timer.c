#include <at89c5131.h>

sbit pulse=P0^3;
void Timer_init(void)
{
	TMOD|=0x01;			//Configure Timer 0 in Mode 1 (16-bit)
	TL0=0x8f;
	TH0=0xf1;
  IEN0|=0x82;

}

void Timer0_ISR(void) interrupt 1
{
	pulse=~pulse;
	TL0=0x8f;
	TH0=0xf1;
}