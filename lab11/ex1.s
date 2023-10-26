.data
sf1: .string "numero: "
sf2: .string "%d"
.text
.globl novonum
novonum:
# int novonum(void) {
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
#   int minhalocal;
#   printf("numero: ");
    xorl    %eax, %eax
    movq    $sf1, %rdi
    call    printf
#   scanf("%d",&minhalocal);
    movq    $sf2, %rdi
    leaq    -4(%rbp), %rsi
    call    scanf
#   return minhalocal;
    movl    -4(%rbp), %eax
    leave
    ret
# }
