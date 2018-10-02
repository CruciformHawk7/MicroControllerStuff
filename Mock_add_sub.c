#include <AT89X51.H> 

sbit swAdd=P2^0;
sbit swSub=P2^1;
sbit swMul=P2^2;
sbit swDiv=P2^3;

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
	unsigned char i,j;
	for (i=0; i<255; i++) for (j=0;j<255;j++);
}

void main(void)
{
	unsigned char Num1,Num2,oper,op=0;
	TMOD=0x20;   
	TH1=0xFD; 	
	SCON=0x50;	
	TR1=1; 		
	while (1)
	{
		if (swAdd==0) oper=0;
		else if (swSub==0) oper=1;
		else if (swMul==0) oper=2;
		else if (swDiv==0) oper=3;
		else oper=5;

		printf("Enter operand 1: ");
		Num1 = ReadBytePC();
		printf("Enter operand 2: ");
		Num2 = ReadBytePC();

		switch (oper){
			case 0:
				op=Num1+Num2;
				break;
			case 1:
				if (Num1>Num2) 
					op = Num1-Num2;
				else 
					op = (Num2-Num1);
				break;
			case 2:
				op = Num1*Num2;
				break;
			case 3:
				if (Num2 == 0) 
					printf("Cannot divide by zero!");
				else {
					op = (Num1/Num2);
				}
				break;
			default:
				printf("No buttons were pressed!");
				break;
		}
		P0=op;
		delay();
	}
}