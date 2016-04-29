/* page_fault.s -  (x86) */

/*------------------------------------------------------------------------
 * page_fault  -  Interrupt dispatcher for Page fault interrupts 
 *------------------------------------------------------------------------
 */
#include <icu.s>
                .text
pferr:        	.long 0	
                .globl  page_fault, pferr  # Clock interrupt dispatcher
page_fault:     
                cli                     #clear interrupts 
                popl pferr              #store error code
                pushal                  # Save registers
                call    pg_fault_handler      # Call high level handler
                popal                   # Restore registers
                sti                     # Restore interrupt status
                iret                    # Return from interrupt
