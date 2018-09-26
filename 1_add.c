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
		//0x37 = 0x41(A) - 0x0A
		x += 0x37;
		//If A, reduce it to 0, then add 0x0A, 
		//If B, reduce it to 1, then add 0x0A = 0x0B
		//And so on.
	return x;
	//sample: 0x0A returns A, 0x09 returns 9, so on.
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

void main(void)
{
	unsigned char Num1,Num2;
	Num1=0;
	Num2=0;

	TMOD=0x20;   		
	TH1=0xFD; 			
	SCON=0x50;			
	TR1=1; 				
	while (1)
	{
		printf("Input the First Byte: ");
		Num1 = ReadBytePC();
		
		printf("Input the Second Byte: ");
		Num2 = ReadBytePC();
		
		printf("Sum: ");
		byte2PC(Num1 + Num2);
	}
}
 

  

