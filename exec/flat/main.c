#include <stdint.h>

void syscall(int vector, void* arg1, void* arg2);
void putf(const char* str, void* val);
void puts(const char* str);

int _start() {
    char msg[] = "*scuffed neofetch here*\n";
    puts(msg);
    return 0;
}

void syscall(int vector, void* arg1, void* arg2) {
    asm volatile("int $0x30" : : "a"(vector), "b"(arg1), "c"(arg2));
}

void putf(const char* str, void* val) {
    syscall(1, str, val);
}

void puts(const char* str) {
    syscall(0, str, 0);
}