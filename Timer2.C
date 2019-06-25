
// Global Variables

const unsigned char MSG0[21] = "Timer2.C            "; 
const unsigned char MSG1[21] = "1ms Interrupt       ";     
   
const unsigned char RUN;
unsigned int T2;

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

// High-priority service
void interrupt IntServe(void)
{
   if (TMR2IF) {
      T2 += 1;
      TMR2IF = 0;
      }
   }

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

// Main Routine

void main(void)
{
   unsigned char i;
   unsigned int j;

   TRISA = 0;
   TRISB = 0x01;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   TRISA = 0;
   PORTB = 0;
   PORTC = 0;
   PORTD = 0;
   PORTE = 0;
   ADCON1 = 0x0F;

   T2 = 0;

   LCD_Init();                  // initialize the LCD

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
   LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);

   Wait_ms(2000);
   LCD_Inst(1);  // clear LCD


// set up Timer2 for 1ms
   T2CON = 0x4D;
   PR2 = 249;
   TMR2ON = 1;
   TMR2IE = 1;
   TMR2IP = 1;
   PEIE = 1;


// turn on all interrupts
GIE = 1;



   while(1) {
   
      LCD_Move(0,  0);  LCD_Out(T2, 3);
      LCD_Move(1,  0);  LCD_Out(PR2, 0);
      LCD_Move(1,  8);  LCD_Out(T2CON, 0);

      }      
   }

