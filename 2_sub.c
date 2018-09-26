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
	unsigned char Num1,Num2;
	TMOD=0x20;   		//0010 0000  mode 2
	TH1=0xFD; 			//9600 baud rate
	SCON=0x50;			// 8 bit data, 1 start and 1 stop bit
	TR1=1; 				//start timer
	while (1)
	{
		printf("Enter first operand: ");
		Num1 = ReadBytePC();

		printf("Enter second operand: ");
		Num2 = ReadBytePC();
		
		printf("Difference is: ");

		if (Num1 > Num2){
			byte2PC(Num1-Num2);
		}
		else {
			byte2PC(Num2-Num1);
		}
	}
}

void serial(unsigned char x)
{
	SBUF=x; 			//Place value in Buffer
	while (TI==0)
	{
	}	//Wait until Transmitted
	TI=0;
}   

  

