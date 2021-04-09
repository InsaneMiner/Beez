#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))


uint8_t inportb (uint16_t _port);
void outportb (uint16_t _port, uint8_t _data);
void panic(char *msg);

extern void panic_assert(const char *file, uint32_t line, const char *desc);