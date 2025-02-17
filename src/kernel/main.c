#include <types.h>
#include <limine.h>
#include <arch/x86_64/tables/gdt/gdt.h>
#include <arch/x86_64/tables/idt/idt.h>
#include <arch/x86_64/cpu/serial.h>
#include <flanterm/backends/fb.h>
#include <arch/x86_64/cpu/pic.h>
#include <arch/x86_64/cpu/pit.h>
#include <flanterm/flanterm.h>
#include <kernel/kernel.h>
#include <drivers/mouse.h>
#include <initrd/quasfs.h>
#include <exec/syscall.h>
#include <libc/printf.h>
#include <sched/sched.h>
#include <drivers/kb.h>
#include <video/vbe.h>
#include <heap/heap.h>
#include <video/fb.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <wm/wm.h>

volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

struct flanterm_context *flanterm_context;

u64 HHDM_Offset;

static volatile struct limine_module_request modReq = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};

struct limine_file* find_module(int pos) {
    return modReq.response->modules[pos];
}

void kernel_idle() {
    while (1) {
        asm ("hlt");
    }
}

void wm_update() {
    while (true) {
        fb_clear(vbe, 0xFF151515);
        wm_tick();
        wm_draw_cursor();
        vbe_update();
    }
}

void _start(void) {
    HHDM_Offset = hhdm_request.response->offset;

    gdt_init();
    serial_init();

    asm ("cli");
    idt_init();
    pic_remap();
    asm ("sti");

    kb_init();

    pmm_init();
    vmm_init();

    quasfs_init(find_module(0)->address);

    vbe_init();
    syscall_init();

    flanterm_context = flanterm_fb_simple_init(
        vbe_addr,
        (size_t)vbe->width, (size_t)vbe->height,
        (size_t)vbe->pitch
    );

    char* shell = quasfs_read("shell");

    sched_create_new_task(kernel_idle, "idle", false, false, (char**){0}, 0);
    sched_create_new_task(shell, "shell", true, true, (char**){0}, 0);
    sched_init();
    pit_init();

    while(1) {
        asm ("hlt");
    }
}

void putchar_(char c) {
    char msg[] = {c, '\0'};
    flanterm_write(flanterm_context, msg, sizeof(msg));
}
