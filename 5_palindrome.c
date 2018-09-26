/*---------------------------------------------------------------------------------------*/
/*------------8051 C Sample Program to send Characters serially through UART-------------*/
/*---------------------------------------------------------------------------------------*/

#include <AT89X51.H> 

void serial(unsigned char x) {
	SBUF=x;
	while (TI==0);
	TI=0;
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

unsigned char numToAsc(unsigned char x) {
	if (x >= 0x00 && x < 0x0A) 
		x += 0x30;
	else 
		x += 0x37;
	return x;
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

void main(void) {
	unsigned char inp, msb,i, inv=0x00;
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
		}
		else {
			printf("The number is not palindrome.");
		}
	}
}



  

