// Ohm_Meter.C
//
// This program reads the A/D on RA0
// Computes the voltage
// and sends these to the serial port at 9600 baud
// 10 samples / second

// Global Variables

const unsigned char MSG0[21] = "Ohm_Meter.C        "; 
 
// Subroutine Declarations
#include <pic18.h>
#include <math.h>

// Subroutines
#include        "lcd_portd.c"

   
void LCD_Out(unsigned int DATA, unsigned char N)
{
   unsigned char A[5], i;
   
   for (i=0; i<5; i++) {
      A[i] = DATA % 10;
      DATA = DATA / 10;
   }
   for (i=5; i>0; i--) {
      if (i == N) LCD_Write('.');
      LCD_Write(A[i-1] + '0');
   }
}

unsigned int A2D_Read(unsigned char c)
{
   unsigned int result;
   unsigned char i;
   c = c & 0x0F;
   ADCON0 = (c << 2) + 0x01; // set Channel Select
   for (i=0; i<20; i++); // wait 2.4us (approx)
   GODONE = 1; // start the A/D conversion
   while(GODONE); // wait until complete (approx 8us)
   return(ADRES);
   }   


void SCI_Out( int DATA, unsigned char N)
{
   unsigned char A[5], i;
   if (DATA < 0) { while(!TRMT);  TXREG = '-';  DATA = -DATA; }


   for (i=0; i<5; i++) {
      A[i] = DATA % 10;
      DATA = DATA / 10;
      }
   for (i=5; i>0; i--) {
      if (i == N) {
         while(!TRMT);  TXREG = '.';
         }   
      while(!TRMT);  TXREG = A[i-1] + 48;
   }
   while(!TRMT);  TXREG = ' ';
   }
    
     


// Main Routine

void main(void)
{
   int A2D;     // raw A/D readings
   int VOLT;    // Volts*100 (500 means 5.00V)
   int OHM;	 // resisance (Ohms)
   int CELCIUS; // temperature*100
   int LUMENS;

   unsigned int i, j, DIE;

   TRISA = 0;
   TRISB = 0x0F;
   TRISC = 0x0F;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
   Wait_ms(500);

   LCD_Inst(0x01);

// Initialize the A/D port
   TRISA = 0xFF;
   TRISE = 0x0F;
   ADCON2 = 0x85;
   ADCON1 = 0x07;
   ADCON0 = 0x01;
   i = 0;

// Initialize Serial Port to 9600 baud
   TRISC = TRISC | 0xC0;
   TXIE = 0;
   RCIE = 0;
   BRGH = 0;
   BRG16 = 1;
   SYNC = 0;
   SPBRG = 255;
   TXSTA = 0x22;
   RCSTA = 0x90;


 // turn on all interrupts
  GIE = 1;

   while(1) {

      A2D = A2D_Read(0);

      VOLT = A2D ;
      OHM  = A2D;
      CELCIUS = A2D;
      LUMENS = A2D;

      LCD_Move(0,0);  LCD_Out(A2D, 0);
      LCD_Move(0,8);  LCD_Out(VOLT, 0);
      LCD_Move(1,0);  LCD_Out(OHM, 0);
      LCD_Move(1,8);  LCD_Out(CELCIUS,0);

      SCI_Out(A2D, 0);
      SCI_Out(VOLT, 0);

      while(!TRMT); TXREG = 13;   // carriage return
      while(!TRMT); TXREG = 10;   // line feed
  
      Wait_ms(100);

      }      
   }
