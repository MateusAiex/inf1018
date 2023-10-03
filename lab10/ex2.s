/*
Var     Reg     Ra

*/

# struct X {
#   int val;
#   struct X *next;
# };
.data

.text
.globl add
add:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
# int add2 (struct X *x) {
#   if (x == NULL) return 0;
IF:
    cmpq    $0, %rdi
    jne     ELSE

    xorl    %eax, %eax

    leave
    ret

ELSE:
#   else return x->val + add2(x->next);
    movq    %rdi, -8(%rbp)
    movq    8(%rdi), %rdi
    call    add
    movq    -8(%rbp), %rdi
    addl    (%rdi), %eax

    leave
    ret
# }
