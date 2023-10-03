/*
Var     Reg     Ra
*px     %rdi    -8(%rbp)
n       %esi    -12(%rbp)
val     %edx    -16(%rbp)
*/

# struct X {
#   int val1;
#   int val2;
# };
# int f(int i, int v);
.data

.text
.globl boo
boo:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
# void boo (struct X *px, int n, int val) {
#   while (n--) {
While:
    cmpl    $0, %esi
    je  End_while
#     px->val2 = f(px->val1, val);
    movq    %rdi, -8(%rbp)
    movl    %esi, -12(%rbp)
    movl    %edx, -16(%rbp)
    movl    (%rdi), %edi
    movl    %edx, %esi
    call    f
    movq    -8(%rbp), %rdi
    movl    -12(%rbp), %esi
    movl    -16(%rbp), %edx
    movl    %eax, 4(%rdi)
#     px++;
    addq    $8, %rdi
    decl    %esi
    jmp While
#   }
End_while:
    leave
    ret
# }
