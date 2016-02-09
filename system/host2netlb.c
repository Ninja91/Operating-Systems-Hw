long host2netlb( long x){
    asm("push %ebp");
    asm("mov %esp, %ebp");
    asm("mov 8(%ebp), %eax");
    asm("xchg %ah, %al");
    asm("rol $16, %eax");
    asm("xchg %ah, %al");
    asm("pop %ebp");
}
