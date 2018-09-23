#include <AT89X51.H> 

unsigned char mode = 0;

void timer0(void) interrupt 1 {
    if (P1=1) {
        while(P1==1);
        //wait for P1 to turn off
        if (mode=0) mode=1;
        else mode=0;
    }
}

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
        switch mode{
            case 0:
                mode0();
                break;
            case 1:
                mode1();
                break;
        }
    }
}