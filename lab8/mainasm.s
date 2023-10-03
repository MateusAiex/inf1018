# #include <stdio.h>
# #define LIM 1

# int filtro(int x, int lim);

# int nums[5] = {3,-5,7,8,-2};
/*
VAR     REG     MEM
i       ebx     -8(%rbp)
nums    r12     -16(%rbp)     
*/
.data
nums: .int 3, -5, 7, 8, -2
SF: .string "%d\n"

# int main() {
.text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rbx, -8(%rbp)
    movq    %r12, -16(%rbp)
#   int i;
    xorl    %ebx, %ebx
#   int *p = nums;
    movq    $nums, %r12
#   for (i = 0; i < 5; i++) {
L1:
    cmpl    $5, %ebx
    jge     L2
#     printf("%d\n", filtro(*p,LIM));
    movl    (%r12), %edi    # filtro((%r12),)
    movl    $1, %esi        # filtro((%r12),1)
    call    filtro

    movl    %eax, %esi      # printf(, filtro((%r12),1))
    movq    $SF, %rdi       # printf("%d\n", filtro((%r12),1))
    call    printf
#     p++;
    addq   $4, %r12
    incl   %ebx
    jmp    L1
#   }
L2:
#   return 0;
    movq    -8(%rbp), %rbx
    movq    -16(%rbp), %r12
    leave
    ret
