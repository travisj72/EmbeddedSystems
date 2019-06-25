 #include <p18f4620.inc> 

CNT0   EQU   1
CNT1   EQU   2
CNT2   EQU   3
STEP   EQU   4
TEMP   EQU   6

       org 0x800
       call   Initialize
       clrf   STEP    
Main:   
       call   FullStep
       movwf  PORTC
       call   Wait
       goto   Main

Initialize:
       clrf   TRISA
       clrf   TRISB
       clrf   TRISC
       clrf   TRISD
       clrf   TRISE
       clrf   PORTA
       clrf   PORTB
       clrf   PORTC
       clrf   PORTD
       clrf   PORTE
       movwf  0x0F
       movwf  ADCON1
       return

FullStep:  
       incf    STEP, W
       andlw   0x03
       movwf   STEP
       movf    STEP, TEMP          
       movwf   TEMP
       btfsc   STATUS,Z
       retlw   0x01
       dcfsnz  TEMP,F
       retlw   0x02
       dcfsnz  TEMP,F
       retlw   0x04
       retlw   0x08

HalfStep:  
       incf    STEP, W
       andlw   0x07
       movwf   STEP
       movf    STEP, TEMP          
       movwf   TEMP
       btfsc   STATUS,Z
       retlw   0x01
       dcfsnz  TEMP,F
       retlw   0x03
       dcfsnz  TEMP,F
       retlw   0x02
       dcfsnz  TEMP,F
       retlw   0x06
       dcfsnz  TEMP,F
       retlw   0x04
       dcfsnz  TEMP,F
       retlw   0x0C
       dcfsnz  TEMP,F
       retlw   0x08
       retlw   0x09


Wait:
      movlw 100
      movwf CNT2
W0:
      movlw 100
      movwf CNT1
W1:
      movlw 100
      movwf CNT0
W2:
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      decfsz  CNT0
      goto    W2
      decfsz  CNT1
      goto    W1
      decfsz  CNT2
      goto    W0
      return

      end
