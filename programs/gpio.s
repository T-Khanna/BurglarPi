///////////////////////////////////////////////////////////////////////////////
// ARM Group Project - Year 1 (Group 40)
// ____________________________________________________________________________
//
// File: gpio.s
// Members: Tarun Sabbineni, Vinamra Agrawal, Tanmay Khanna, Balint Babik
///////////////////////////////////////////////////////////////////////////////

// Initialising pin 16 to an output pin
ldr r0, =0x20200004
ldr r2, =0x00040000
str r2, [r0]

// Storing important addresses in registers
ldr r0, =0x20200028
ldr r1, =0x2020001C
ldr r2, =0x00010000

// Clear pin before beginning the loop
str r2, [r0]

// Loop to turn pin 16 off and on repeatedly
loop:

// Set the pin
str r2, [r1]

// Delay before clearing the pin
ldr r3, =0x1000000
wait_to_clear:
sub r3, r3, #1
cmp r3, #0
bne wait_to_clear

// Clear the pin
str r2, [r0]

// Delay before setting the pin
ldr r3, =0x1000000
wait_to_set:
sub r3, r3, #1
cmp r3, #0
bne wait_to_set

b loop

end_loop:

// Exit the program
andeq r0, r0, r0
