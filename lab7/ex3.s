/*
int main(void)
{
    for (int i = 0; i <= 10; i++)
    {
        printf("%d\n", i*i);
    }
    
    return 0;
}
*/

.data
Sf:  .string "%d\n"    /* primeira string de formato para printf */


.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)  /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */
/********************************************************/

  xorl  %r12d, %r12d  /* r12d = 0 */

L1:
  cmpl  $10, %r12d  /* if (r12d > 10) ? */
  jg  L2          /* goto L2 */

  movl  %r12d, %eax    /* eax = r12d */
  imull     %eax, %eax # eax *= eax

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  movl  $0, %eax
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/

  addl  $1, %r12d  /* r12d += 1; */
  jmp  L1         /* goto L1; */

L2:  

/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq    -16(%rbp), %r12 /* recupera r12 */
  movq    -8(%rbp), %rbx  /* recupera rbx */
  leave
  ret      
/***************************************************************/