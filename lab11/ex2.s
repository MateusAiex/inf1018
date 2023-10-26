/*
VAR     REG     RA
num     %edi
local           -16(%rbp)
a       %r10
i       %r11d
aux     %eax
*/

.data

.text
.globl bemboba
bemboba:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
# int bemboba (int num) {
#   int local[4];
#   int *a;
    leaq    -16(%rbp), %r10
#   int i;
    xorl    %r11d, %r11d
#   for (i=0,a=local;i<4;i++) {
for:
    cmpl    $4, %r11d
    jge     endfor
#     *a = num;
    movl    %edi, (%r10)
#     a++;
    addq    $4, %r10
    incl    %r11d
    jmp     for
#   }
endfor:
#   return addl (local, 4);
    leaq    -16(%rbp), %rdi
    movl    $4, %esi
    call    addl

    leave
    ret
# }
