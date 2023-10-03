/*
Var     Reg     Ra
um      %rdi    -24(%rbp)
outro   %rsi    -32(%rbp)
%n      %edx    -36(%rbp)
i       %r12d   -8(%rbp)
aux     %r13    -16(%rbp)
*/

.data

.text
.globl map2
map2:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $48, %rsp
    movq    %r12, -8(%rbp)
    movq    %r13, -16(%rbp)
# int f(int x);
# void map2 (int* um, int * outro, int n) {
#   int i;
    xorl    %r12d, %r12d
#   for (i=0; i<n; i++)
for:
    cmpl    %edx, %r12d
    jge     end_for
#     *(outro+i) = f(*(um+i));
    movl    %r12d, %r13d
    shll    $2, %r13d
    
    movq    %rdi, -24(%rbp)
    movq    %rsi, -32(%rbp)
    movl    %edx, -36(%rbp)
    addq    %r13, %rdi
    movl    (%rdi), %edi
    call    f
    movq    -24(%rbp), %rdi
    movq    -32(%rbp), %rsi
    movl    -36(%rbp), %edx

    addq    %rsi, %r13
    movl    %eax, (%r13)

    incl    %r12d
    jmp     for
end_for:
    leave
    ret
# }
