ldr r0, =0x20200004                 
ldr r2, =0x00040000                 
str r2, [r0]                        

ldr r0, =0x20200028
ldr r1, =0x2020001C
ldr r2, =0x00010000

str r2, [r0]

loop:

str r2, [r1]


str r2, [r0]

b loop

end_loop:

andeq r0, r0, r0
