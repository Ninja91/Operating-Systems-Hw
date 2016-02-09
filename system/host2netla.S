.global host2netla
host2netla:
    push %ebp
    mov %esp, %ebp
    mov 8(%ebp), %eax
    xchg %ah, %al
    rol $16, %eax
    xchg %ah, %al
    pop %ebp
ret
