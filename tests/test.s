.global labela2
#.global labela1
.extern a, b, c

.equ jedinica, 1
# push r0
.section jedan
.word labela1, labela2, jedinica, -4, 0xabcd

labela1: .skip 0x06
labela2: 
    .skip 10

.section dva
int r4
iret
ret
halt
xchg r1, r1
add r1, r4
sub pc, sp
mul r5, r6
div r1, r2
cmp r5, r7
not r5
and r4, r7
or r7, r6
xor r7, r6
test r2, r3
shr r1, r2
shl r2, r3

push r3
pop r4

ldr r1, $1
ldr r1, 1
ldr r2, jedinica
ldr r2, $labela1
ldr r2, %jedinica
ldr r2, $labela1
ldr r2, r1
ldr r2, [r1]
str r2, [r1 + 5]
str r2, [r1 + labela1]

call labela1
call *labela1
jmp %labela1

jgt *r5
jne *[r5]
jeq *[r5 + 0x05]
jmp *[r5 + labela1]

jmp *labela1




.end 