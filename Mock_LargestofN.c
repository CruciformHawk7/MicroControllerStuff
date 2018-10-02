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

void delay() {
	unsigned char i;
	for (i=0; i<50; i++);
}

void dispNum(unsigned char x) {
	if (x==0x00) P0=0x3f;
	if (x==0x01) P0=0x06;
	if (x==0x02) P0=0x5B;
	if (x==0x03) P0=0x4F;
	if (x==0x04) P0=0x66;
	if (x==0x05) P0=0x6D;
	if (x==0x06) P0=0x7D;
	if (x==0x07) P0=0x07;
	if (x==0x08) P0=0x7F;
	if (x==0x09) P0=0x6F;
	if (x==0x0A) P0=0x77;
	if (x==0x0B) P0=0x7C;
	if (x==0x0C) P0=0x39;
	if (x==0x0D) P0=0x5E;
	if (x==0x0E) P0=0x79;
	if (x==0x0F) P0=0x71;
} 

void main(void) {
	unsigned char great,low,num,n;
	TMOD=0x20;   		
	TH1=0xFD; 			
	SCON=0x50;			
	TR1=1; 
	great=0; low=0xff;
	while(1) {
		printf("Enter the number of values to be compared: ");
		n=ReadBytePC();
		while (n!=0) {
			n--;
			printf("Enter a number:");
			num=ReadBytePC();
			if (great<num) great=num;
			if (low>num) low=num;
		}
		printf("Greatest number is: ");
		byte2PC(great);
		printf("Lowest number is: ");
		byte2PC(low);
		for (num=0; num<100; num++) {
			for (n=0; n<200; n++) {
				P1=0x01;
				dispNum(great>>4);
				delay();
				P0=0x00;

				P1=0x02;
				dispNum(great&0x0f);
				delay();
				P0=0x00;

				P1=0x04;
				dispNum(low>>4);
				delay();
				P0=0x00;

				P1=0x08;
				dispNum(low&0x0f);
				delay();
				P0=0x00;
			}
		}
	}
}
