// ---  COUNT.C -------------------

// Global Variables

// Subroutine Declarations
#include <pic18.h>

void Wait(unsigned int DATA)
{
   unsigned int i, j;
   for (i=0; i<DATA; i++) {
      for (j=0; j<1000; j++);
   }
}
   
// Main Routine



void main(void)
{
   unsigned char SEC, MIN, HR;

   TRISA = 0;
   TRISB = 0;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;
   SEC = 0;
   MIN = 0;
   HR  = 0;
   
   while(1) {
      SEC = SEC + 1;
      PORTD = SEC;
      Wait(1000);
      }
   }
