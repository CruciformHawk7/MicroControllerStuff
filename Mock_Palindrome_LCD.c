/*---------------------------------------------------------------------------------------*/
/*------------8051 C Sample Program to send Characters serially through UART-------------*/
/*---------------------------------------------------------------------------------------*/

#include <AT89X51.H> 

void serial(unsigned char x) {
	SBUF=x;
	while (TI==0);
	TI=0;
}  

unsigned char numToAsc(unsigned char x) {
	if (x >= 0x00 && x < 0x0A) 
		x += 0x30;
	else 
		x += 0x37;
	return x;
}

unsigned char ascToNum(unsigned char x) {
	if (x >= 0x30 && x < 0x3A) 
		x -= 0x30;
	else 
		x -= 0x37;
	return x;
}

void byte2PC(unsigned char b) {
	serial(numToAsc(b>>4));
	serial(numToAsc(b & 0x0f));
}

void printf(unsigned char s[]) {
	char i=0;
	serial(0x0d);
	while(s[i]!='\0')
		serial(s[i++]);
}

unsigned char ReadBytePC() {
	unsigned char RcvByte=0x00;
	while(RI==0);
    RcvByte = (ascToNum(SBUF)<<4);
	RI=0;
	while(RI==0);
	RcvByte = RcvByte+(ascToNum(SBUF));
	RI=0;
	byte2PC(RcvByte);
	return(RcvByte);
}  

unsigned char yes[12]={0x00,0x00,0x00,0x00, 0x6E, 0x79, 0x6D, 0x6F, 0x00, 0x00, 0x00, 0x00};
unsigned char not[11]={0x00,0x00,0x00,0x00, 0x6E, 0x79, 0x6D, 0x00, 0x00, 0x00, 0x00};

void delay() {
	unsigned char i;
	for(i=0;i<50;i++);
}

void main(void) {
	unsigned char inp, msb, i, inv=0x00, j, ptr, del;
	TMOD=0x20;   		
	TH1=0xFD; 			
	SCON=0x50;			
	TR1=1; 				
	while (1) {
		unsigned char inp,msb,inv=0x00,i;
		printf("Enter an 8-bit number");
		inp=ReadBytePC();
		msb=inp>>4;
		inp=inp&0x0f;
		for (i=0; i<4; i++) {
			inv <<= 1;
			inv |= (msb&0x01);
			msb >>= 1;
		}
		if (inv == inp) {
			printf("The number is palindrome.");
			ptr=0;
			for (del=0; del<210; del++) {
				for(i=0;i<4;i++) {
					for(j=0;j<200;j++) {
						P1=0x01;
						P0=yes[ptr];
						delay();
						P0=0x00;

						P1=0x02;
						P0=yes[ptr+1];
						delay();
						P0=0x00;

						P1=0x04;
						P0=yes[ptr+2];
						delay();
						P0=0x00;

						P1=0x08;
						P0=yes[ptr+3];
						delay();
						P0=0x00;
					}
				}
				ptr++;
				if (ptr>7) ptr=0;
			}
		}
		else {
			printf("The number is not palindrome.");
			ptr=6;
			for (del=0; del<210; del++) {
				for(i=0;i<4;i++) {
					for(j=0;j<200;j++) {
						P1=0x01;
						P0=not[ptr];
						delay();
						P0=0x00;

						P1=0x02;
						P0=not[ptr+1];
						delay();
						P0=0x00;

						P1=0x04;
						P0=not[ptr+2];
						delay();
						P0=0x00;

						P1=0x08;
						P0=not[ptr+3];
						delay();
						P0=0x00;
					}
				}
				ptr--;
				if (ptr<0) ptr=6;
			}
		}
	}
}