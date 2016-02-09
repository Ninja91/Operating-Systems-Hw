#include<xinu.h>

void prntsegaddr(){
    int i;
    uint8 * addr;

    kprintf("\n\nEnd of text segment %x", &etext);
    kprintf("\n\nEnd of data segment %x", &edata);
    kprintf("\n\nEnd of bss segment %x", &ebss);

    kprintf("\n\nPrinting next 8 bytes of text segment:  ");
    for (i = 0, addr = &etext + 1; i < 8; i++, addr++){
        kprintf("%x  ", *addr);
    }
    
    kprintf("\n\nPrinting next 8 bytes of data segment:\n");
    for (i = 0, addr = &edata + 1; i < 8; i++, addr++){
        kprintf("%x  ", *addr);
    }

    kprintf("\n\nPrinting next 8 bytes of bss segment:\n");
    for (i = 0, addr = &ebss + 1; i < 8; i++, addr++){
        kprintf("%x  ", *addr);
    }

    kprintf("\n\nLength of text segment: %d", (uint32)&etext - (uint32)&text);
    kprintf("\n\nLength of data segment: %d", (uint32)&edata - (uint32)&data);
    kprintf("\n\nLength of bss segment: %d", (uint32)&ebss - (uint32)&bss);
}
