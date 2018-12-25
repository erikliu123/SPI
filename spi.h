

#define spiBaseAddr 0xB0B00000

#define srr 0x40
#define cr 0x60
#define sr 0x64
#define dtr 0x68 //data transmit
#define drr 0x6c //data receive
#define ssr 0x70 //slave select 
#define TFIFO 0x74 
#define RFIFO 0x78

#define GIER 0x1c//globa interupt enable 
#define IPISR 0x20//IP interrupt status
#define IPIER 0x28//IP interrupt status

#define JSTK_bnJstk                  0
#define JSTK_bnButton1               1
#define JSTK_bnButton2               2

#define JSTK_bitButton1              (1 << JSTK_bnButton1)
#define JSTK_bitButton2              (1 << JSTK_bnButton2)
#define JSTK_bitJstk                 (1 << JSTK_bnJstk)

void Read_Data(int *x, int *y);
//void Read_Data(); 

void Write_Enable(); //好像没什么用

void spi_init();

void SetBit(volatile int* busPtr, int register_space, int position);

void ClearBit(volatile int* busPtr, int register_space, int position);

void SetRegister(volatile int* busPtr, int register_space, int value);

int ReadRegister(volatile int* busPtr, int register_space);

int ReadBit(volatile int* busPtr, int register_space, int position);

int GetOffset(int register_space);