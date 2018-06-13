AT-Tiny 13:
#todo stuff

  Zapytania:
   1. Program Memory 1K-czyli 1024Byte?  poprzez 1K mam rozumieć 1024 byte czy 1000 byte? 1024
   2. czy 32 Rejestry do użytku swobodnego są przechowywane w SRAM? tak
   3. czy 32 Rejestry do użytku swobodnego mają rozmiar 8 czy 16byte? 8
   4. czy stos powinienem zaimplementować jako wskaźnik do ostatniego ustawionego byte SRAM-ie? partz pdf

  Funkcje Programu:
  + możliwość zapisu stanu procesora (w wybranym formacie)
  + możliwość wczytania programu do procesora(w dowolnie wybranym formacie)
  + możliwość wykonywania programu

  Zaimplementować w emulatorze:
    + SRAM 64 byte
    + Stack Register 8bit
    + Program Memory 1K- czyli 1024Byte
    + 32 Rejestry General Purpose 8bit
    + Program Counter Register 16bit

  Instrukcje:
    Arithmetic [6]: DONE
      + ADD  	Rd,Rr  	Add without Carry
      + ADC 	Rd,Rr 	Add with Carry
      + SUB  	Rd,Rr   Subtract without Carry
      + SBC 	Rd,Rr 	Subtract with Carry
      + INC 	Rd 	Increment Register
      + DEC 	Rd 	Decrement Register

    Register [2]: DONE
      + CLR 	Rd 	Clear Register
      + SER 	Rd 	Set Register

    Logic [3]: DONE
      + AND 	Rd,Rr 	Logical AND
      + OR 	Rd,Rr 	Logical OR
      + NEG 	Rd 	Two's Complement

    Branch [6]]:
      + RJMP 	k 	Relative Jump
      + CP 	Rd,Rr 	Compare
      + BRMI 	k 	Branch if minus
      + BRPL 	k 	Branch if plus
      + BRGE 	k 	Branch if greater than or equal (signed)
      + BRLT 	k 	Branch if less than (signed)
      //3 flagi
      //3 ustawiania flag i dopowiednie skoki
      //rotate LSR LSL ROL ROR SBI CBI BST BLD
    Data Transfer [6]:
      + MOV 	Rd,Rr 	Copy register
      + LDS 	Rd,k 	Load Direct
      + STS 	k,Rr 	Store Direct
      + LPM 	None 	Load Program Memory
      + PUSH 	Rr 	Push register on Stack
      + POP 	Rd 	Pop register from Stack
+disassembler

  Nie implementować w emulatorze:
    - Timerów
    - IO-Port
    - Watchdog
    - EEPROM
    - ustawiania-Flag
