/*
Var     Reg     Ra
n       %edi    -4(%rbp)
*/

.data

.text
.globl fat
fat:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16 , %rsp
#   int fat (int n) {
#   if (n==0) return 1;
L1:
    cmpl    $0, %edi
    jne     L2

    movl    $1, %eax
    leave
    ret
#   else return n*fat(n-1);
L2:
    movl    %edi, -4(%rbp)
    decl    %edi
    call    fat
    movl    -4(%rbp), %edi
    imull   %edi, %eax

    leave
    ret
#   }
