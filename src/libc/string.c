#include <libc/string.h>

int strlen(const char* pStr) {
    int i = 0;
    while (*pStr != '\0') {
        i++;
        pStr++;
    }
    return i;
}

int strcmp(const char* x, const char* y) {
    if (strlen(x) != strlen(y)) return 1;
    for (int i = 0; i < strlen(x); i++) {
        if (x[i] != y[i]) return 1;
    }
    return 0;
}

char* strcpy(char* dest, const char* src)
{
    if (dest == NULL) {
        return NULL;
    }
 
    char *ptr = dest;
 
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
 
    *dest = '\0';
 
    return ptr;
}
void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *p = (uint8_t *)s;

    for (size_t i = 0; i < n; i++) {
        p[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    if (src > dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if (src < dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}