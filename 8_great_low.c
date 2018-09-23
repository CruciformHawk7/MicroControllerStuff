#include <AT89X51.H> 
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

unsigned char ascToNum(unsigned char x) {
	if (x >= 0x30 && x < 0x3A) 
		x -= 0x30;
	else 
		x -= 0x37;
	return x;
}

void serial(unsigned char x) {
	SBUF=x; 			//Place value in Buffer
	while (TI==0);
	TI=0;
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
	}
}



  

