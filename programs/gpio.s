;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;ARM Group Project - Year 1 (Group 40)
;;______________________________________________________________________________
;;
;;File: gpio.s
;;Members: Tarun Sabbineni, Vinamra Agrawal, Tanmay Khanna, Balint Babik
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Set pin 16 to output pin
ldr r0, =0x20200004                 
ldr r1, =0x00040000                 
str r1, [r0]                        

; Store important addresses
ldr r0, =0x20200028               ; Clear address
ldr r1, =0x2020001C               ; Set address
ldr r2, =0x00010000               ; Change state of pin

; Clear bit before setting
str r2, [r0]

; Program to turn pin on/off
loop:

  str r2, [r1]

  ; Create delay between turning LEDs off //TODO
  wait_to_clear: 
    

  str r2, [r0]

  ; Create delay between turning LEDs on //TODO
  wait_to_set:


  b loop

end_loop:

; Stop instruction
andeq r0, r0, r0
