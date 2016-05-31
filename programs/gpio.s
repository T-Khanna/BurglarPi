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
ldr r2, =0x00010000               ; Change state of pin 16

; Clear pin before setting
str r2, [r0]

; Program to turn pin on/off
loop:

  ; Set pin
  str r2, [r1]

  ; Create delay before clearing pin 
  ldr r3, =0x10000000
  wait_to_clear:
    sub r3, r3, #1
    cmp r3, #0
    bne wait_to_clear 

  ; Clear pin
  str r2, [r0]

  ; Create delay before setting pin 
  ldr r3, =0x10000000
  wait_to_set:
    sub r3, r3, #1
    cmp r3, #0
    bne wait_to_set 

  b loop

end_loop:

; Stop instruction
andeq r0, r0, r0
