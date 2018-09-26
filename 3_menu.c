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

void main(void)
{
	unsigned char ch,Num1,Num2;
	TMOD=0x20;   
	TH1=0xFD; 	
	SCON=0x50;	
	TR1=1; 		
	while (1)
	{
		printf("Enter your choice:");
		printf("1. Addition");
		printf("2. Subtraction");
		printf("3. Multiplication");
		printf("*. Division");
		ch = ReadBytePC();

		printf("Enter operand 1: ");
		Num1 = ReadBytePC();
		printf("Enter operand 2: ");
		Num2 = ReadBytePC();

		switch (ch) {
			case 0x01:
				printf("Sum is: ");
				byte2PC(Num1+Num2);
				break;
			case 0x02:
				printf("Difference is: ");
				if (Num1>Num2) 
					byte2PC(Num1-Num2);
				else 
					byte2PC(Num2-Num1);
				break;
			case 0x03:
				printf("Product is: ");
				byte2PC(Num1*Num2);
				break;
			default:
				if (Num2 == 0) 
					printf("Cannot divide by zero!");
				else {
					printf("Quotient is: ");
					byte2PC(Num1/Num2);
				}
				break;
		}

	
	}
}


  

