#include <reg51.h>
const textLength = 12;

unsigned char text[textLength] = {0x38, 0x06, 0x78, 0x78, 0x38, 0x79, 0x00, 0x50, 0x79, 0x5C, 0x00, 0x00};
unsigned char disp0 = 0, loops;

//Port0 = DP,G,F,E,D,C,B,A
//Port1 = X,X,X,X,Disp3,Disp2,Disp1,Disp0

void timer0(void) interrupt 1 {
    loops++;
    if(loops >= 15) {
		//disp0 points to a data in the array
		disp0++;
		//prevent ArrayIndexOutOfBounds
		if (disp0>(textLength-4)) disp0=0;
	}
}

void delay() {
	//random delay
	unsigned char i;
	for (i=0; i<20;i++);
}

void main() {
	unsigned char i;
    P1=0x00;
	P0=0x00;
    TMOD=0x00;
    TL0=0;
    TH0=0;
    TR0=1;
    IE=0x82;
    while(1) {
		//using P1_3 - P1_0 to enable displays
		//enable port 1_0 = 0000 0001
		P1=0x01;
		P0=text[disp0];
		delay();

		//enable port 1_1 = 0000 0010
		P1=0x02;
		P0=text[disp0+1];
		delay();

		//enable port 1_2 = 0000 0100
		P1=0x04;
		P0=text[disp0+2];
		delay();

		//enable port 1_3 = 0000 1000
		P1=0x08;
		P0=text[disp0+3];
		delay();
    }
}   