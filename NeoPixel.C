// NeoPixel2.C
//
// This program drives a NeoPixel connected to RD0
// Lights spin around a NeoPixel-16 as
//    Red:   1 shift / 1/16 second
//    Green: 1 shift / second
//    Blue:  1 shift / 16 seconds
//
// Global Variables

unsigned char PIXEL @ 0x000;

const unsigned char MSG0[20] = "NeoPixel2.C         ";

unsigned char RED[12];
unsigned char GREEN[12];
unsigned char BLUE[12];

// Subroutine Declarationsb
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"


void Update_RGB(unsigned char r, unsigned char g, unsigned char b)
{
   unsigned char i;

   for (i=0; i<12; i++) {
      RED[i] = 0;
      GREEN[i] = 0;
      BLUE[i] = 0;
      }   

   RED[r] = 50;
   GREEN[g] = 50;
   BLUE[b] = 50;
   }

  
void NeoPixel_Display(void)
{
   PIXEL = GREEN[0];	asm("  call Pixel_8 ");
   PIXEL = RED[0];		asm("  call Pixel_8 ");
   PIXEL = BLUE[0];		asm("  call Pixel_8 ");

   PIXEL = GREEN[1];	asm("  call Pixel_8 ");
   PIXEL = RED[1];		asm("  call Pixel_8 ");
   PIXEL = BLUE[1];		asm("  call Pixel_8 ");

   PIXEL = GREEN[2];	asm("  call Pixel_8 ");
   PIXEL = RED[2];		asm("  call Pixel_8 ");
   PIXEL = BLUE[2];		asm("  call Pixel_8 ");

   PIXEL = GREEN[3];	asm("  call Pixel_8 ");
   PIXEL = RED[3];		asm("  call Pixel_8 ");
   PIXEL = BLUE[3];		asm("  call Pixel_8 ");

   PIXEL = GREEN[4];	asm("  call Pixel_8 ");
   PIXEL = RED[4];		asm("  call Pixel_8 ");
   PIXEL = BLUE[4];		asm("  call Pixel_8 ");

   PIXEL = GREEN[5];	asm("  call Pixel_8 ");
   PIXEL = RED[5];		asm("  call Pixel_8 ");
   PIXEL = BLUE[5];		asm("  call Pixel_8 ");

   PIXEL = GREEN[6];	asm("  call Pixel_8 ");
   PIXEL = RED[6];		asm("  call Pixel_8 ");
   PIXEL = BLUE[6];		asm("  call Pixel_8 ");

   PIXEL = GREEN[7];	asm("  call Pixel_8 ");
   PIXEL = RED[7];		asm("  call Pixel_8 ");
   PIXEL = BLUE[7];		asm("  call Pixel_8 ");

   PIXEL = GREEN[8];	asm("  call Pixel_8 ");
   PIXEL = RED[8];		asm("  call Pixel_8 ");
   PIXEL = BLUE[8];		asm("  call Pixel_8 ");

   PIXEL = GREEN[9];	asm("  call Pixel_8 ");
   PIXEL = RED[9];		asm("  call Pixel_8 ");
   PIXEL = BLUE[9];		asm("  call Pixel_8 ");

   PIXEL = GREEN[10];	asm("  call Pixel_8 ");
   PIXEL = RED[10];		asm("  call Pixel_8 ");
   PIXEL = BLUE[10];		asm("  call Pixel_8 ");

   PIXEL = GREEN[11];	asm("  call Pixel_8 ");
   PIXEL = RED[11];		asm("  call Pixel_8 ");
   PIXEL = BLUE[11];		asm("  call Pixel_8 ");

   asm("    return");


#asm
Pixel_8:
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    return

Pixel_1:
	bsf		((c:3971)),0	; PORTD,0
    nop
	btfss   ((c:0000)),7
	bcf		((c:3971)),0
	rlncf   ((c:0000)),F
    nop
    nop
    bcf		((c:3971)),0
    return

#endasm
   }

void Wait(unsigned int X)
{
   unsigned int i, j;

   for (i=0; i<X; i++)
      for (j=0; j<609; j++);
   }

void LCD_Out(unsigned int DATA, unsigned char N, unsigned char D)
{
   unsigned char A[5], i;
   
   for (i=0; i<5; i++) {
      A[i] = DATA % 10;
      DATA = DATA / 10;
   }
   for (i=D; i>0; i--) {
      if (i == N) LCD_Write('.');
      LCD_Write(A[i-1] + '0');
   }
}

         
// Main Routine

void main(void)
{
   unsigned int i;
   unsigned char C1, C16, C256;

   TRISA = 0;
   TRISB = 0;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   TRISA = 0;
   PORTB = 0;
   PORTC = 0;
   PORTD = 0;
   PORTE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD
   TRISD0 = 0;

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]); 
   Wait_ms(100); 

   C1 = 0;
   C16 = 0;
   C256 = 0;

   while(1) {
      C1 = (C1 + 1) % 12;
      if (C1 == 0) {
         C16 = (C16 + 1) % 12;
         if (C16 == 0) {
            C256 = (C256 + 1) % 12;
            }
         }

     LCD_Move(1,0);  
     LCD_Out(C256, 0, 2);
     LCD_Write(':');
     LCD_Out(C16, 0, 2);
     LCD_Write(':');
     LCD_Out(C1, 0, 2);

      Update_RGB(C1, C16, C256);
      NeoPixel_Display();
      Wait(13);
   }



}
    
