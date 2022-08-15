#include <at89c5131.h>
#include "lcd.h"		//Header file with LCD interfacing functions
#include "serial.c"	//C file with UART interfacing functions
#include "Timer.c"
sbit LED=P1^7;

//Test function definitions

/************************************************
  pulse_gen()
	pulse_gen function generates a 1 sec pulse on p0.3
************************************************/
void pulse_gen(void)
{// Generates a pulse of 270 Hz(Re) for 1 sec
	TL0=0x8f;
	TH0=0xf1;
	pulse=1;
	TR0=1;
	msdelay(1000);
	TR0=0;
	pulse=0;
}	

/************************************************
   play_code()
	play_code function calls pulse_gen function to get desire tap
************************************************/
void play_code(int r,int c){
	int i;
for(i=0; i<c;i++){
pulse_gen();
msdelay(1000);
}
msdelay(1000);
for(i=0; i<r;i++){
pulse_gen();
msdelay(1000);
}
}
/************************************************
tape_code():
	tape_code function finds the tape code for character and plays it.
************************************************/
void tape_code(unsigned char ch)
{
	int x=ch-'A';
	int r=0;
	int c=0;
  if(x==10){// Tape_code for K
 r=3;
 c=1;

  }
else if(x<10){ //Tape_code for alphabets before K
	r=(x%5)+1;
	c=(x/5)+1;
}
else{ // Alphabets after 'K'

	if((x%5)==0){ 

     r=5;
     c=x/5;

	}
	else{
		r=x%5;
		c=(x/5)+1;
	}
}
play_code(r,c);
}


//Main function
void main(void)
{
	unsigned char ch=0;
	

	//Call initialization functions
	lcd_init();
	uart_init();
	Timer_init();
	
	//These strings will be printed in terminal software
transmit_string("Enter the char");
	
	while(1)
	{  lcd_cmd(0x01);
		lcd_cmd(0x80);
	 lcd_write_string("Input Please");
			//Receive a character
			ch = receive_char();
		
			//Decide which test function to run based on character sent
      //Displays the string on the terminal software
			switch(ch)
			{
				case 'A':  case 'B': case 'C': case 'D':  case 'E':  case 'F': case 'G':  case 'H':  case 'I':  case 'J':  case 'K': case 'L':  
				case 'M': case 'N':  case 'O':  case 'P': case 'Q':  case 'R': case 'S':  case 'T': case 'U':  case 'V':  case 'W':  case 'X':  
			  case 'Y': case 'Z': 
					lcd_cmd(0x01); //clear display
				  tape_code(ch);
					break;
				
				case 'a':  case 'b': case 'c': case 'd':  case 'e':  case 'f': case 'g':  case 'h':  case 'i':  case 'j':  case 'k': case 'l':  
				case 'm': case 'n':  case 'o':  case 'p': case 'q':  case 'r': case 's':  case 't': case 'u':  case 'v':  case 'w':  case 'x':  
			  case 'y': case 'z': 
					lcd_cmd(0x01); //clear display
				  tape_code(ch+'A'-'a'); // get the capital equivalent
					break;
					
				default: lcd_cmd(0x01);
					lcd_cmd(0x80);
	            lcd_write_string("Invalid Input");
				       msdelay(2000);
								 break;
				
			}
			msdelay(100);
	}
}
