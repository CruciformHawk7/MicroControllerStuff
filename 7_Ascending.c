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

void bubbleSort(unsigned char arr[], unsigned char len)
{
   unsigned char i, j, temp;
   for (i = 0; i < len-1; i++) {     
       for (j = 0; j < len-i-1; j++) {
           if (arr[j] > arr[j+1]){
              temp = arr[j];
			  arr[j] = arr[j+1];
			  arr[j+1] = temp;
		   }
	   }
   }
}

void notBubbleSort(unsigned char arr[], unsigned char len)
{
   unsigned char i, j, temp;
   for (i = 0; i < len-1; i++) {     
       for (j = 0; j < len-i-1; j++) {
           if (arr[j] < arr[j+1]){
              temp = arr[j];
			  arr[j] = arr[j+1];
			  arr[j+1] = temp;
		   }
	   }
   }
}

void main(void) {
	unsigned char inp[25], len,i;
	TMOD=0x20;   		
	TH1=0xFD; 			
	SCON=0x50;			
	TR1=1; 				
	while (1) {
		printf("Enter number of values to be stored (less than 25):");
		len = ReadBytePC();
		for (i=0; i<len;i++) {
			inp[i]=ReadBytePC();
		}
		printf("Enter: ");
		printf("1. Ascending");
		printf("2. Descending");
		if (ReadBytePC()==1) bubbleSort(inp,len);
		else notBubbleSort(inp,len);
		//Alternatively, print bubblesort backwards within if cond.
		printf("Sorted array is:");
		for(i=0;i<len;i++) {
			byte2PC(inp[i]);
			byte2PC(0x09);		//Horizontal tab
		}
	}
}



  

