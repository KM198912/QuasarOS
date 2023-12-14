#pragma once

#include <types.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <mm/vmm.h>
#include <heap/heap.h>

#define sched_max_task_limit 16

enum {
    STARTING,
    RUNNING,
    DEAD
};

typedef struct {
    char* name;
    registers regs;
    u64 TID; // Task ID
    u8 state;
    page_map* page_map;
    u64 start_time;
    u64 end_time;
    u64 usage;
    bool killable;
} __attribute__((packed)) sched_task;

extern bool sched_paused;
extern sched_task* sched_task_list[sched_max_task_limit];

void sched_init();

sched_task* sched_create_new_task(void* addr, char* name, bool killable);
sched_task* sched_create_new_elf(char* addr, char* name, bool killable);

void sched_queue_task(sched_task* task);

void sched_kill_task(u64 TID);
void sched_remove_task(u64 TID);
u64 sched_get_current_tid();
void sched_switch(registers* regs);
u64 sched_get_tid();
u64 sched_task_get_usage(u64 tid);
char* sched_task_get_name(u64 tid);

void sched_lock();
void sched_unlock();