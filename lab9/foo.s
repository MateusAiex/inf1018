/*
Var     Reg     Ra
i       r10d    
s       r11d    
auxi    %r9
*/

.data

.text
.globl foo
foo:
    pushq %rbp
    movq %rsp, %rbp
# void foo (int a[], int n) {
#  int i;
    xorl    %r10d, %r10d
#  int s = 0;
    xorl    %r11d, %r11d
#  for (i=0; i<n; i++) {
For:
    cmpl    %esi, %r10d
    jge     EndFor
#    s += a[i];
    movl    %r10d, %r9d
    shll    $2, %r9d
    addq    %rdi, %r9
    addl    (%r9), %r11d
#    if (a[i] == 0) {
IF:
    cmpl    $0, (%r9)
    jne     Else
#      a[i] = s;
    movl    %r11d, (%r9)
#      s = 0;
    xorl    %r11d, %r11d
#    }
Else:
    incl    %r10d
    jmp     For
#  }
EndFor:
    leave
    ret
# }
