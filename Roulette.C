

// Global Variables



// Subroutine Declarations
#include <htc.h>


// Subroutines
void Display(unsigned char X)
{
   if (X == 0) PORTD = 1;
   if (X == 1) PORTD = 2;
   if (X == 2) PORTD = 4;
   if (X == 3) PORTD = 8;
   if (X == 4) PORTD = 0x10;
   if (X == 5) PORTD = 0x20;
   if (X == 6) PORTD = 0x40;
   if (X == 7) PORTD = 0x80;
}
   
void Wait(unsigned int X)
{
   unsigned int i, j;
   for(i=0; i<X; i++)
      for (j=0; j<500; j++);
}

void Beep(void)
{
   unsigned int i, j;
 
   for(i=0;i<50;i++) {
      RA1 = !RA1;
      for(j=0; j<500; j++);
      }
   }         

// Main Routine

void main(void)
{
   unsigned char Y, X, i;

   TRISA = 0;
   TRISB = 0xFF;
   TRISC = 0;
   TRISD = 0;
   ADCON1 = 0x0F;

   PORTA = 1;
   PORTB = 2;
   PORTC = 3;
   PORTD = 4;

   X  = 0;
   Y = 0;

   while(1) {
      while(!RB0);
      while(RB0) X = (X + 1)%8;
      PORTC = X;
      for (i=32+X; i>0; i--) {
          Y = (Y + 1) % 8;
          Display(Y);
          Beep();
          Wait(100 + 1000/(i+1));
          }    
      }
   }
