#include <AT89X51.H> 

void serial(unsigned char x) {
	SBUF=x;
	while (TI==0);
	TI=0;
}  
unsigned char numToAsc(unsigned char x);
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

void delay() {
	unsigned char i, j;
	for (i=0; i<200; i++) for(j=0; j<114; j++);
} 

void evenCond() {
	P0=0x0F;
	delay();
	P0=0xF0;
	delay();
}

void oddCond() {
	P0=0x55;
	delay();
	P0=0xAA;
	delay();
}

void main(void) {
	unsigned char inp1, inp2, sum, i;
	TMOD=0x20;   		
	TH1=0xFD; 			
	SCON=0x50;			
	TR1=1; 				
	while (1) {
		printf("Enter first number: ");
		inp1 = ReadBytePC();
		
		printf("Enter second number: ");
		inp2 = ReadBytePC();

		sum=inp1+inp2;

		if(sum%2==0) {
			for (i=0; i<200; i++) evenCond();		
		}
		else {
			for (i=0; i<200; i++) oddCond();
		}
	}
}
