#include <pic18.h>

// Global Variables
unsigned long int TIME;

// Interrupt Service Routine

void interrupt IntServe(void) 
{
   if (TMR0IF) {
      TIME = TIME + 0x10000;
      RC0 = !RC0;
      TMR0IF = 0;
      }
   }

// Subroutines
#include        "lcd_portd.c"


void LCD_Out(unsigned long int DATA, unsigned char N)
{
   unsigned char A[10], i;
   
   for (i=0; i<10; i++) {
      A[i] = DATA % 10;
      DATA = DATA / 10;
   }
   for (i=10; i>0; i--) {
      if (i == N) LCD_Write('.');
      LCD_Write(A[i-1] + '0');
   }
}



// Main Routine

void main(void)
{
   float A;
   unsigned long int TIME1, TIME0;

   TRISA = 0;
   TRISB = 0;
   TRISC = 0;
   TRISD = 0;
   ADCON1 = 0x0F;
 
// set up Timer0 for PS = 1
   T0CS = 0;
   T0CON = 0x88;
   TMR0ON = 1;
   TMR0IE = 1;
   TMR0IP = 1;
   PEIE = 1;

   A = 3.14159265379;
   LCD_Init();
   Wait_ms(100);

   TIME = 0;

// turn on all interrupts
   GIE = 1;
   
// Do nothing.  Interrupts do all the work.
   while(1) {
      TIME0 = TIME + TMR0;
      Wait_ms(1000);
      TIME1 = TIME + TMR0;
      LCD_Move(0,0);
      LCD_Out(TIME1 - TIME0, 7);
      Wait_ms(1000);
      PORTB = PORTB + 1;
      }
   }
