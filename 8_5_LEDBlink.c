#include <AT89X51.H> 

unsigned char mode = 0;

void mode0() {
    P0=0x0F;
    delay();
    P0=0xF0;
    delay();
}

void mode1() {
    P0=0x01;
    delay();
    P0=0x02;
    delay();
    P0=0x04;
    delay();
    P0=0x08;
    delay();
    P0=0x10;
    delay();
    P0=0x20;
    delay();
    P0=0x40;
    delay();
    P0=0x80;
    delay();
}

void main(void) {
	unsigned char i;
	TMOD=0x20;   		
	TH1=0xFD; 			
	SCON=0x50;			
	TR1=1; 	

    while(1) {
        if(P0=0x00) mode0();
        else mode1();
    }
}