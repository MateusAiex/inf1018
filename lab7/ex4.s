/*
#include <stdio.h>

int nums[4] = {65, -105, 111, 34};

int main (void) {
  int i;
  int s = 0;

  for (i=0;i<4;i++)
    s = s+nums[i];

  printf ("soma = %d\n", s);

  return 0;
}
*/
/*
Var     Reg
i       %r12d
s       %eax
num     %r10
aux     %rcx
*/

.data

nums:    .int    65, -105, 111, 34
Sf: .string "soma = %d\n"

.text
.globl main
main:
    /**********************************************************/
    /* mantenha este trecho aqui - prologo !!! */
    pushq % rbp
    movq % rsp , % rbp
    subq $16 , % rsp
    movq % rbx , -8(% rbp )
    movq % r12 , -16(% rbp )
    /**********************************************************/

    xorl    %r12d, %r12d    # i = 0
    xorl    %eax, %eax    # s = 0
    movq    $nums, %r10   # r10 = nums 

L1:
    # for (i=0;i<4;i++)
    cmpl $4, %r12d
    jge L2

    movl %r12d, %ecx # ecx = r12d
    shl  $2, %ecx  # ecx = ecx * 4
    addq  %r10, %rcx  # rcx = r10 + ecx
    addl  (%rcx), %eax  # eax += *rcx

    incl  %r12d # r12d++
    jmp L1

L2:

    /*************************************************************/
    /* este trecho imprime o valor de %eax (estraga %eax)  */
      movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
      movl    %eax, %esi   /* segundo parametro  (inteiro) */
      movl  $0, %eax
      call  printf       /* chama a funcao da biblioteca */
    /*************************************************************/
    /**********************************************************/
    /* mantenha este trecho aqui - finalizacao !!!! */
    movq $0 , % rax # rax = 0 ( valor de retorno )
    movq -8(% rbp ) , % rbx
    movq -16(% rbp ) , % r12
    leave
    ret
    /**********************************************************/
