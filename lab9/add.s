.data

.text
.globl add
add:
    pushq   %rbp
    movq    %rsp, %rbp
# int add (int a, int b, int c) {
#   return a+b+c;
# }
    movl    %edi, %eax
    addl    %esi, %eax
    addl    %edx, %eax

    leave
    ret
