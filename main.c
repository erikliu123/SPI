/*
 * main.c for microAptiv_UP MIPS core running on Nexys4DDR
 * Prints \n\rMIPSfpga\n\r out via UART.
 * Default baudrate 115200,8n1.
 * Also display a shifting 0xf on the LEDs
 */


#include "fpga.h"
#include "spi.h"
//#include "pmodJSTK.h"
//#include "PmodBT2.h"

#define inline_assembly()  asm("ori $0, $0, 0x1234")

#define CLK_FREQ 50000000

#define UART_BASE 0xB0401000	//With 1000 offset that axi_uart16550 has
#define rbr		0*4
#define ier		1*4
#define fcr		2*4
#define lcr		3*4
#define mcr		4*4
#define lsr		5*4
#define msr		6*4
#define scr		7*4

#define thr		rbr
#define iir		fcr
#define dll		rbr
#define dlm		ier

#define IS_UART_INTR (1<<13)
#define IS_SPI_INTR  (1<<14)
#define IS_TIMER_INTR (1<<30)

void delay();

void init_uart();
void uart_outbyte(char c);
char uart_inbyte(void);
void uart_print(const char *ptr);

extern char *reverse(char *s);
extern char *my_itoa(int n);

volatile int rxData = 0,data_received=0;
volatile int spiRX=0;
volatile int count=0;

void bt2initial()
{
	*WRITE_IO(UART_BASE + lcr) = 0x00000080; // LCR[7]  is 1
	delay();
	*WRITE_IO(UART_BASE + dll) = 27; // DLL msb. 115200 at 50MHz. Formula is Clk/16/baudrate. From axi_uart manual.
	delay();
	
	*WRITE_IO(UART_BASE + dlm) = 0x00000000; // DLL lsb.
	delay();
	*WRITE_IO(UART_BASE + lcr) = 0x00000003; // LCR register. 8n1 parity disabled
	delay();
	*WRITE_IO(UART_BASE + ier) = 0x00000000; // IER register. disable interrupts
}
//------------------
// main()
//------------------
int main() {
	volatile unsigned int pushbutton, count = 0xF;
	volatile unsigned int receive = 0x0;
	volatile unsigned int j = 1;
	volatile unsigned int x, y;
	//初始化
	bt2initial();
	spi_init();
	unsigned char tc;
	while(1) {	
		//方向判断
		Read_Data(&x,&y);
		if(x<1024&&y<1024){
			if(x>300&&x<700&&y>300&&y<700) tc=0;
			else if(x<300) tc=4;
			else if(x>700) tc=8;
			else if(y>700) tc=2;
			else tc=16;
			//测试输出用
			/*
			switch(tc){
				case 4:
				uart_print("LEFT");
				break;
				case 8:
				uart_print("RIGHT");
				break;
				case 2:
				uart_print("UP");
				break;
				case 16:
				uart_print("DOWN");
				break;
			}
			*/
		}
		if(tc!=0){
			//uart_print("\n\r");
			//*WRITE_IO(UART_BASE + thr) = (unsigned int)tc;
		}
	}
	return 0;
}

void delay() {
	volatile unsigned int j;

	for (j = 0; j < (1000); j++) ;	// delay 
}

void uart_outbyte(char c) {
	*WRITE_IO(UART_BASE + thr) = (unsigned int) c;
	delay( );
}

char uart_inbyte(void) {
	unsigned int RecievedByte;
	
	while(!((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001));

	RecievedByte = *READ_IO(UART_BASE + rbr);

	return (char)RecievedByte;
}

void uart_print(const char *ptr)
{
	while (*ptr) {
		uart_outbyte (*ptr);
		ptr++;
	}
}

void _mips_handle_irq(void* ctx, int reason)
{	
	*WRITE_IO(IO_LEDR) = 0xF00F;  // Display 0xFFFF on LEDs to indicate receive data from uart
	//uart_print("Interrput occurs\n\r")
	
	if(reason & IS_TIMER_INTR) {
		// write C0_Compare = $11
		asm volatile ("mtc0	$0, $11");
		
		asm volatile ("li $9, 0x1");
		// write C0_COUNT = $9
		asm volatile ("mtc0 $9, $9");
	}
	
	if(reason & IS_SPI_INTR) {
		uart_print("spi interrupts occurred!\r\n");
		//uart_print(my_itoa(*READ_IO(spiBaseAddr+sr)));
		//uart_print("\n");
		//uart_print(my_itoa(*READ_IO(spiBaseAddr+drr)));
		uart_print("\n");
	}
	
	*WRITE_IO(IO_LEDR) = 0x0FF0; 		
	uart_print("Other interrupts occurred!\r\n");
	uart_print(my_itoa(reason));
	uart_print("\r\n");
	//uart_print("ip interrupt SR:");
	//uart_print(my_itoa(*READ_IO(spiBaseAddr+sr)));	uart_print("\r\n");
	//uart_print(my_itoa(*READ_IO(spiBaseAddr+drr)));	uart_print("\r\n");
	//uart_print(my_itoa(*READ_IO(spiBaseAddr+IPISR)));
	uart_print("\r\n");
	
	return;
}
