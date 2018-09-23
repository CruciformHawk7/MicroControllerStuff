/*---------------------------------------------------------------------------------------*/
/*------------8051 C Sample Program to send Characters serially through UART-------------*/
/*---------------------------------------------------------------------------------------*/

#include <AT89X51.H> 
void byte2PC(unsigned char b) {
	serial(testNibbile(b>>4));
	serial(testNibbile(b & 0x0f));
}

unsigned char testNibbile(unsigned char x) {
	if (x >= 0x00 && x < 0x0A) 
		x += 0x30;
	else 
		x += 0x37;
	return x;
}

void printf(unsigned char s[]) {
	char i;
	i=0;
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

/*-------------------------------MAIN PROGRAM------------------------------------------*/

void main(void) {
	unsigned char sum=0x00, cont=0x59; 	//Cap Y, or 0x79
	TMOD=0x20;   		
	TH1=0xFD; 			
	SCON=0x50;			
	TR1=1; 				
	while (1) {
		printf("Enter a number: ");
		sum += ReadBytePC();
		while(cont==0x59 || cont==0x79) {
			printf("Enter another number: ");
			sum += ReadBytePC();
			printf("Continue? (Y/N)");
			cont = ReadBytePC();
		}
		printf("Sum is: ");
		byte2PC(sum);
	}
}



  

