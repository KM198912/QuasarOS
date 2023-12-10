#pragma once

#include <types.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <arch/x86_64/mm/vmm.h>
#include <heap/heap.h>

#define Sched_MaxTaskLimit 16

enum {
    RUNNING,
    DEAD
};

typedef struct {
    Registers regs;
    u64 TID; // Task ID
    u8 state;
    VMM_PageMap* pageMap;
} __attribute__((packed)) Sched_Task;

void Sched_Init();

Sched_Task* Sched_CreateNewTask(void* addr);
void Sched_CreateNewElf(char* addr);

void Sched_KillTask(u64 TID);
void Sched_RemoveTask(u64 TID);
u64 Sched_GetCurrentTID();
void Sched_Schedule(Registers* regs);

void Sched_Lock();
void Sched_Unlock();