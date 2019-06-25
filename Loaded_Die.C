// Loaded Die.C
//
// This program generates a random number from 1..6
// and sends it to the serial port at 9600 baud
// every time you press RB0

// Global Variables

const unsigned char MSG0[21] = "Loaded Die.C     ";
const unsigned char MSG1[21] = "RB0 to roll      "; 

 // Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

// LCD_Out( Data,  Number of Decimal Points, Number of Digits)

void LCD_Out(int DATA, unsigned char N, unsigned char D)
{
   unsigned char A[5], i;
   
   if (DATA < 0) {
      LCD_Write('-');
      DATA = - DATA;
   }
   else LCD_Write(' ');
   
   for (i=0; i<5; i++) {
      A[i] = DATA % 10;
      DATA = DATA / 10;
   }
   for (i=D; i>0; i--) {
      if (i == N) LCD_Write('.');
      LCD_Write(A[i-1] + '0');
   }
}

// SCI_Out( Data,  Number of Decimal Points, Number of Digits)

void SCI_Out( int DATA, unsigned char N, unsigned char D)
{
   unsigned char A[5], i;
   if (DATA < 0) { while(!TRMT);  TXREG = '-';  DATA = -DATA; }


   for (i=0; i<5; i++) {
      A[i] = DATA % 10;
      DATA = DATA / 10;
      }
   for (i=D; i>0; i--) {
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
   int d6, d20;
 
   unsigned int i, j;

   TRISA = 0;
   TRISB = 0x0F;
   TRISC = 0x0F;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
   LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);
   Wait_ms(500);

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

   while(1) {

      while(!RB0);
      while(RB0) {
         d6  = (d6 + 1) % 6;
         d20 = (d20 +1) % 20;
         }

      d6 = d6 + 1;   // range 1..6

// Loaded Die
//    if(d20 == 0) d6 = 4; 

      LCD_Move(1,12);  LCD_Out(d6, 0, 1);
 
      SCI_Out(d6, 0, 1);
 
      while(!TRMT); TXREG = 13;   // carriage return
      while(!TRMT); TXREG = 10;   // line feed
  

      }      
   }
