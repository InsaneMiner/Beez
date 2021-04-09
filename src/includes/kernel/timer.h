#pragma once
#include <stdint.h>
void init_timer(uint32_t frequency);
void timer_wait(int ticks);