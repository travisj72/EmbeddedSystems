#include <p18f4620.inc>
; Start of code:
	org 0x800
	clrf TRISC
	clrf PORTC
	movlw 0x0F
	movwf ADCON1
Loop:
	incf PORTC,F
	goto Loop
	end
