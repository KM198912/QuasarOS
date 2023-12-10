#include <exec/syscall.h>
#include <sched/sched.h>
#include <drivers/kb.h>

/*
Syscalls spec:
    rax - function
    rbx - first arg
    rcx - second arg
    rdx - third arg
*/

void Syscall_Handler(Registers* regs) {
    Sched_Lock();
    switch (regs->rax) {
        case 0x00:
            // puts
            printf("%s", (char*)regs->rbx);
            break;
        case 0x01:
            // putf
            printf((char*)regs->rbx, regs->rcx);
            break;
        case 0x02:
            // KB Get char
            regs->rax = KB_GetChar();
            break;
    }
    Sched_Unlock();
}

void Syscall_Init() {
    IRQ_Register(16, Syscall_Handler);
}