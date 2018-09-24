/*---------------------------------------------------------------------------------------*/
/*------------8051 C Sample Program to send Characters serially through UART-------------*/
/*---------------------------------------------------------------------------------------*/

#include <AT89X51.H> 
void serial(unsigned char x);
void byte2PC(unsigned char b) {
	serial(testNibbile((b)>>4));
	serial(testNibbile(b & 0x0f));
}

unsigned char testNibbile(unsigned char x) {
	if (x >= 0x00 && x < 0x0A) {
		x += 0x30;
	}
	else {
		//0x37 = 0x41(A) - 0x0A
		x += 0x37;
		//If A, reduce it to 0, then add 0x0A, 
		//If B, reduce it to 1, then add 0x0A = 0x0B
		//And so on.
	}
	return x;
	//sample: 0x0A returns A, 0x09 returns 9, so on.
}
void printf(unsigned char s[])
{
	char i;
	i=0;
	serial(0x0d);
	while(1)
	{
		if(s[i]=='\0')break;
		serial(s[i]);
		i++;
	}

}	
unsigned char ReadBytePC() {
	unsigned char RcvByte=0x00;
	while(RI==0);
    RcvByte = ((ascToNum(SBUF))<<4);
	RI=0;
	while(RI==0);
	RcvByte = RcvByte+(ascToNum(SBUF));
	RI=0;
	byte2PC(RcvByte);
	return(RcvByte);
}

unsigned char ascToNum(unsigned char x) {
	if (x > 0x40) {
		x -= 0x37;
	}
	else {
		x -= 0x30;
	}
	return x;
}

void delay_ms(unsigned int ms)
{
  unsigned int t1, t2;

   for(t1=0; t1<ms; t1++)
   {
      for(t2=0; t2<114; t2++);
   }
}  

/*-------------------------------MAIN PROGRAM------------------------------------------*/

void main(void)
{
	unsigned char Num1,Num2;
	Num1=0;
	Num2=0;

	TMOD=0x20;   		//0010 0000  mode 2
	TH1=0xFD; 			//9600 baud rate
	SCON=0x50;			// 8 bit data, 1 start and 1 stop bit
	TR1=1; 				//start timer
	//printf("Hello World ");
	//byte2PC(z);//ASCII value of SPACE 
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

void serial(unsigned char x)
{
	SBUF=x; 			//Place value in Buffer
	while (TI==0)
	{
	}	//Wait until Transmitted
	TI=0;
}   

  

