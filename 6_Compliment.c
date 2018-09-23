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
	unsigned char inp1, inp2, temp;
	TMOD=0x20;   		
	TH1=0xFD; 			
	SCON=0x50;			
	TR1=1; 				
	while (1) {
		printf("Enter a 16-bit number");
		inp1=~ReadBytePC();
		inp2=~ReadBytePC();
		++inp2;
		if (CY)
			inp1++;
		printf("2's Complement of the value is: ");
		byte2PC(inp1);
		byte2PC(inp2);
	}
}



  

