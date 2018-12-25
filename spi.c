#include "spi.h"
#include "fpga.h"
#define RegisterSpace 0x0
#define XSP_CR_LOOPBACK_MASK	   0x00000001 /**< Local loopback mode */
#define XSP_CR_ENABLE_MASK	   0x00000002 /**< System enable */
#define XSP_CR_MASTER_MODE_MASK	   0x00000004 /**< Enable master mode */
#define XSP_CR_CLK_POLARITY_MASK   0x00000008 /**< Clock polarity high
								or low */
#define XSP_CR_CLK_PHASE_MASK	   0x00000010 /**< Clock phase 0 or 1 */
#define XSP_CR_TXFIFO_RESET_MASK   0x00000020 /**< Reset transmit FIFO */
#define XSP_CR_RXFIFO_RESET_MASK   0x00000040 /**< Reset receive FIFO */
#define XSP_CR_MANUAL_SS_MASK	   0x00000080 /**< Manual slave select
								assert */
#define XSP_CR_TRANS_INHIBIT_MASK  0x00000100 /**< Master transaction
								inhibit */
int UART_BASE1=0xB0401000;

char *my_itoa(int n);
char *reverse(char *s);

void delay1() {
	volatile unsigned int j;
	for (j = 0; j < (800); j++) ;	// delay 
}
volatile unsigned char x_low, y_low;
/*
void Write_Tx(char data){
	SetRegister(spiBaseAddr,ssr,1);
	SetRegister(spiBaseAddr,cr,0x1E6);
	
	//*WRITE_IO_CHAR(spiBaseAddr+dtr) = data;
	//*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x00;
	//*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x00;
	//*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x00;
	//*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x00;
	//*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x00;
	
	//SetRegister(spiBaseAddr,dtr,0x80);
	
	SetRegister(spiBaseAddr,ssr,0);
	SetRegister(spiBaseAddr,cr,0x0E6);
	//start transmitting 
	delay1();
	//SetRegister(spiBaseAddr,ssr,1);
	//SetRegister(spiBaseAddr,cr,0x1E6);
}

void Read_Rx(){
	SetRegister(spiBaseAddr,ssr,0xffff);
	
	SetRegister(spiBaseAddr,cr,0x186);
	
	delay1();
	*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x0B;
	//SetRegister(spiBaseAddr,dtr,0x0B);
	delay1();
	*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x08;
	//SetRegister(spiBaseAddr,dtr,0x08);
	//delay1();
	*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x00;
	//SetRegister(spiBaseAddr,dtr,0x00);
	
	SetRegister(spiBaseAddr,ssr,0xfffe);
	SetRegister(spiBaseAddr,cr,0x086);
	delay1();
	//start transmitting
	SetRegister(spiBaseAddr,ssr,0xffff);
	delay1();
	SetRegister(spiBaseAddr,cr,0x186);

	while(ReadBit(spiBaseAddr,sr,0)==0)
    { 
        uart_print("DRR=");  
        //while(ReadBit(spiBaseAddr,sr,0)==1);
        //SetRegister(spiBaseAddr,ssr,0); 
        uart_print(my_itoa(*READ_IO_CHAR(spiBaseAddr+drr)));//一读就报错！！ 
		uart_print(" ");
        //uart_print("SR=");  uart_print(my_itoa(*READ_IO(spiBaseAddr+sr)));
    }
}
*/

//useless
void Write_Enable(){
	SetRegister(spiBaseAddr,cr,0x1E6);
	SetRegister(spiBaseAddr,dtr,0x06);
	SetRegister(spiBaseAddr,ssr,0x0);
	ClearBit(spiBaseAddr,cr,8);
	//WE Command Send
	delay1();
	SetRegister(spiBaseAddr,ssr,0x1);
	SetBit(spiBaseAddr,cr,8);
}

void Read_Data(int *x, int *y){
	
	SetBit(spiBaseAddr,cr,6);
	SetBit(spiBaseAddr,cr,5);
	SetRegister(spiBaseAddr,ssr,0x0);
	
	int counter;
	for(counter=0; counter<5; counter++){
		SetBit(spiBaseAddr,cr,8);
		*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x82;
		ClearBit(spiBaseAddr,cr,8);
		delay1();
	}
/*
	while(ReadBit(spiBaseAddr,sr,3)==0){
		//write dummy data
		*WRITE_IO_CHAR(spiBaseAddr+dtr)=0x00;
	}
*/	
	SetRegister(spiBaseAddr,ssr,0x01);
	SetBit(spiBaseAddr,cr,8);
	
	while(ReadBit(spiBaseAddr,sr,0)==0)
    { 
        //uart_print("DRR=");  
        //while(ReadBit(spiBaseAddr,sr,0)==1);
        //SetRegister(spiBaseAddr,ssr,0); 	
		x_low = *READ_IO_CHAR(spiBaseAddr+drr);
		*x = x_low|(*READ_IO_CHAR(spiBaseAddr+drr)<<8);
		y_low = *READ_IO_CHAR(spiBaseAddr+drr);
		*y = y_low|(*READ_IO_CHAR(spiBaseAddr+drr)<<8);
		*READ_IO_CHAR(spiBaseAddr+drr);
		//uart_print(my_itoa(x));	
		//uart_print(my_itoa(*READ_IO_CHAR(spiBaseAddr+drr)));
        //uart_print(my_itoa(*READ_IO_CHAR(spiBaseAddr+drr)));//一读就报错！！ 
		//uart_print(" ");
		//uart_print(my_itoa(y));
        //uart_print("SR=");  uart_print(my_itoa(*READ_IO(spiBaseAddr+sr)));	
    }
}





void spi_init(){
		// *WRITE_IO(spiBaseAddr+GIER)=0x80000000;//global interrput enabled
		// *WRITE_IO(spiBaseAddr+0x28)=0x2;//interrput enabled
		//SetRegister(spiBaseAddr,GIER,0);
        *WRITE_IO(spiBaseAddr+srr)=0x0000000a;
	    SetRegister(spiBaseAddr,cr,0x1E6);
		//SetRegister(spiBaseAddr,IPIER,0x202B);
		//SetBit(spiBaseAddr,IPIER,13);
		//SetRegister(spiBaseAddr,cr,0x1E4);
		//SetBit(spiBaseAddr,GIER,31);
        //ClearBit(spiBaseAddr,cr,0x0);
     	//SetRegister(spiBaseAddr,ssr,0x0);//select control
		
		
		/* Write dummy ReadId to the DTR register */
		/*
		*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x0B;
		//SetRegister(spiBaseAddr,dtr,0x0B);
		delay1();
		*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x08;
		//SetRegister(spiBaseAddr,dtr,0x08);
		delay1();
		*WRITE_IO_CHAR(spiBaseAddr+dtr) = 0x00;
		//SetRegister(spiBaseAddr,dtr,0x00);
		
		
		int ControlReg = ReadRegister(spiBaseAddr, cr);
		ControlReg &= ~XSP_CR_TRANS_INHIBIT_MASK;
        //uart_print(my_itoa((spiBaseAddr+cr)));  
        SetRegister(spiBaseAddr,cr,ControlReg);
		
		ControlReg = ReadRegister(spiBaseAddr, cr);
		ControlReg |= XSP_CR_TRANS_INHIBIT_MASK;
        //uart_print(my_itoa((spiBaseAddr+cr)));  
        SetRegister(spiBaseAddr,cr,ControlReg);
		*/
		
        // SetBit(spiBaseAddr,IPIER,2);
        //uart_print("CR=");    
        //uart_print(my_itoa(*READ_IO(spiBaseAddr+cr)));
		/* Master Inhibit disable in the CR */

		/* Read the Rx Data Register */
		//while(1){
			/*
              delay1(); 
             //SetBit(spiBaseAddr,GIER,31);
             // ClearBit(spiBaseAddr,cr,9);//LSB
              //SetBit(spiBaseAddr,cr,7);
            SetRegister(spiBaseAddr,cr,0x1E6);
        
                  //ClearBit(spiBaseAddr,cr,5);
                 // ClearBit(spiBaseAddr,cr,6);
              //1
              SetRegister(spiBaseAddr,ssr,0XFFFFFFFF);
                  SetRegister(spiBaseAddr,dtr,0x82);   
                 SetRegister(spiBaseAddr,ssr,0); 
              uart_print("k=");
               //2  
            SetRegister(spiBaseAddr,ssr,0XFFFFFFFF);
                  SetRegister(spiBaseAddr,dtr,0);   
                     SetRegister(spiBaseAddr,ssr,0); 
                      
              //3
                SetRegister(spiBaseAddr,ssr,0XFFFFFFFF);
                  SetRegister(spiBaseAddr,dtr,0);   
                     SetRegister(spiBaseAddr,ssr,0); 
            
             //4
             SetRegister(spiBaseAddr,ssr,0XFFFFFFFF);
                  SetRegister(spiBaseAddr,dtr,0);
                     SetRegister(spiBaseAddr,ssr,0);      
				//5
                 SetRegister(spiBaseAddr,ssr,0XFFFFFFFF);
                  SetRegister(spiBaseAddr,dtr,0); 
                 SetRegister(spiBaseAddr,ssr,0);      
					//new circle
                
                   ++k;
                   uart_print("k=");
                   uart_print(my_itoa(k));
                    uart_print("\r\n ");
                ClearBit(spiBaseAddr,cr,8);
                while(ReadBit(spiBaseAddr,sr,2)==0);
                 
                SetBit(spiBaseAddr,cr,8);
              //   

            //    while(ReadBit(spiBaseAddr,sr,3)==1);
            //       SetRegister(spiBaseAddr,dtr,Buffer[2]);   
            //     while(ReadBit(spiBaseAddr,sr,3)==1);    
            //       SetRegister(spiBaseAddr,dtr,Buffer[2]);  
            //     while(ReadBit(spiBaseAddr,sr,3)==1);
            //       SetRegister(spiBaseAddr,dtr,Buffer[2]);  
            //     while(ReadBit(spiBaseAddr,sr,3)==1);
            //      SetRegister(spiBaseAddr,dtr,Buffer[2]); 
    
                delay1();
                 while(ReadBit(spiBaseAddr,sr,0)==0)
                 { 
                     uart_print("DRR= ");  
                     //while(ReadBit(spiBaseAddr,sr,0)==1);
    
                      SetRegister(spiBaseAddr,ssr,0); 
                     uart_print(my_itoa(*READ_IO(spiBaseAddr+drr)));//一读就报错！！ 
                     uart_print("SR=");  uart_print(my_itoa(*READ_IO(spiBaseAddr+sr)));
                 }
             // ClearBit(spiBaseAddr,cr,8);
                // SetRegister(spiBaseAddr,cr,0x18E); 
                 
                SetRegister(spiBaseAddr,ssr,0XFFFFFFFF);
                SetBit(spiBaseAddr,sr,5);
                   SetBit(spiBaseAddr,sr,6);
                   
             uart_print("\r\n ");
             // uart_print(my_itoa(*READ_IO(spiBaseAddr+drr)));//一读就报错！！
             // uart_print("\r\n ");
			 */
			 //Write_Tx(0x00);
			 //Read_Rx();
			 //Write_Enable();
			 //Write_Data();
			 //Read_Data();
			 //Erase();
			 //Erase();
			 //Write_Tx(0x83);Read_Rx();
			 //Write_Tx(0x83);Read_Rx();
			// Write_Tx(0x83);Read_Rx();
			// Write_Tx(0x83);Read_Rx();
			 //uart_print("\r\n");			 
        //}
        uart_print("initial is complished\r\n"); 

}


void SetBit(volatile int* busPtr, int register_space, int position) {
	busPtr[GetOffset(register_space)] |= (1 << position);
}

void ClearBit(volatile int* busPtr, int register_space, int position) {
	busPtr[GetOffset(register_space)] &= ~(1 << position);
}

void SetRegister(volatile int* busPtr, int register_space, int value) {
	busPtr[GetOffset(register_space)] = value;
}

int ReadRegister(volatile int* busPtr, int register_space) {
	return busPtr[GetOffset(register_space)];
}

int ReadBit(volatile int* busPtr, int register_space, int position) {
	if ((ReadRegister(busPtr, register_space) & (1 << position)) == (1 << position)) {
		return 1;
	}
	return 0;
}

int GetOffset(int register_space)
{
	return (register_space) / sizeof(int);
}
void init_spi(){
    *WRITE_IO(spiBaseAddr+dtr)=0;
    *WRITE_IO(spiBaseAddr+cr)=0x82;
     *WRITE_IO(spiBaseAddr+ssr)=0xffffffff;

    //*WRITE_IO(spiBaseAddr+0x28)=0x2;//interrput enabled
    *WRITE_IO(spiBaseAddr+srr)=0x0000000a;

}

int transfer(volatile int* busPtr, int slave_id, int tx_value) {

	SetRegister(busPtr, RegisterSpace+dtr, tx_value);// write data transfer register

	ClearBit(busPtr, RegisterSpace+ssr, slave_id);// set chip-select of slave low (enable)

	ClearBit(busPtr, RegisterSpace+cr, 8);	// clear master transaction inhibit bit

	// wait for tx to finish
	while (ReadBit(busPtr, RegisterSpace+sr, 2) != 1)
		// Bit 2 => Tx_Empty Bit
		;

	// wait for rx to finish
	while (ReadBit(busPtr, RegisterSpace+sr, 1) != 1)
		// Bit 1 => Rx_Full Bit
		;

	SetBit(busPtr, RegisterSpace+cr, 8);	// set master transaction inhibit bit

	//if (transfer_mode == TransferMode::Last)
		SetBit(busPtr, RegisterSpace+sr, slave_id);// set chip-select of slave high (disable)

	return ReadRegister(busPtr, RegisterSpace+drr);
    /*
    *WRITE_IO(spiBaseAddr+cr)= *WRITE_IO(spiBaseAddr+cr)&0xfffffeff; //clear inhibit bit
    *WRITE_IO(spiBaseAddr+dtr)=0x0;
    *WRITE_IO(spiBaseAddr+ssr)=0xfffffffe;

    while((*READ_IO(spiBaseAddr+sr)&0x4)==0) ;// transfer data
    while((*READ_IO(spiBaseAddr+sr)&0x2)==0) ;// recieve data

       *WRITE_IO(spiBaseAddr+cr)= *WRITE_IO(spiBaseAddr+cr)|0x00000100;
       return *READ_IO(spiBaseAddr+drr);*/
}

//反转字符串  
char *reverse(char *s)  
{  
    char temp;  
    char *p = s;    //p指向s的头部  
    char *q = s;    //q指向s的尾部  
    while(*q)  
        ++q;  
    q--;  
  
    //交换移动指针，直到p和q交叉  
    while(q > p)  
    {  
        temp = *p;  
        *p++ = *q;  
        *q-- = temp;  
    }  
    return s;  
}  

 static char s[100];      //必须为static变量，或者是全局变量  
char *my_itoa(int n)  
{  
   
  /*  int i=0,first=0,k=0,mask=0xf0000000;
    for(i=31;i>=0;--i){
        mask=(0x80000000)>>(31-i);
       if(((((unsigned int)n)>>i)&mask)==0 && (first==0)){
           ;
       }
       else{
           first=1;
           s[k++]='0'+(((((unsigned int)n)>>i)&mask)==0)?0:1;

       }

    }
           s[k]='\0';
       return s;*/
        
    int i = 0,isNegative = 0;  
    
    if((isNegative = n) < 0) //如果是负数，先转为正数  
    {  
        n = -n;  
    }  
    do      //从各位开始变为字符，直到最高位，最后应该反转  
    {  
        s[i++] = n%10 + '0';  
        n = n/10;  
    }while(n > 0);  
  
    if(isNegative < 0)   //如果是负数，补上负号  
    {  
        s[i++] = '-';  
    }  
    s[i] = '\0';    //最后加上字符串结束符  
   
	
    return reverse(s); 
    
}  