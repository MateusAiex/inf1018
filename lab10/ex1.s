/*
Var     Reg     Ra
*x      rdi
a       eax
*/

# struct X {
#  int val;
#  struct X *next;
# };

.data

.text
.globl add
add:
    pushq   %rbp
    movq    %rsp, %rbp
    # subq TODO:, %rsp
# int add (struct X *x) {
#   int a = 0;
    xorl    %eax, %eax
#   for (; x != NULL; x = x->next)
For:
    cmpq $0, %rdi
    je  End_for
#     a += x->val;
    addl    (%rdi), %eax
    movq    8(%rdi), %rdi
    jmp For
End_for:
#   return a;
    leave
    ret
# }
