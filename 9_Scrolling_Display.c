#include <reg51.h>
#define textLength = 12;

unsigned char text[textLength] = {0x38, 0x06, 0x78, 0x78, 0x38, 0x79, 0x00, 0x50, 0x79, 0x5C, 0x00, 0x00};
unsigned char disp0 = 0, loops;

//Port0 = DP,G,F,E,D,C,B,A
//Port1 = X,X,X,X,Disp3,Disp2,Disp1,Disp0

void delay() {
	//random delay
	unsigned char i;
	for (i=0; i<20;i++);
}

void main() {
	unsigned char i,j;
    P1=0x00;
	P0=0x00;
    TMOD=0x00;
    TL0=0;
    TH0=0;
    TR0=1;
    IE=0x82;
    while(1) {
		for (i=0;i<4;i++) {
			for (j=0;j<255;j++) {
				//using P1_3 - P1_0 to enable displays
				//enable port 1_0 = 0000 0001
				P1=0x01;
				P0=text[disp0];
				delay();
				P0=0x00;		

				//enable port 1_1 = 0000 0010
				P1=0x02;
				P0=text[disp0+1];
				delay();
				P0=0x00;

				//enable port 1_2 = 0000 0100
				P1=0x04;
				P0=text[disp0+2];
				delay();
				P0=0x00;

				//enable port 1_3 = 0000 1000
				P1=0x08;
				P0=text[disp0+3];
				delay();
				P0=0x00;
				if (disp0>(textLength-4)) disp0=0;
			}
		}
    }
}   