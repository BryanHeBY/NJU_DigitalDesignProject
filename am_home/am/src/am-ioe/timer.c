#include <am.h>

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  volatile uint64_t res;
  ((uint32_t*)&res)[0] = CLK_US_RD() % 1000 + CLK_MS_RD() * 1000;
  ((uint32_t*)&res)[1] = ((uint64_t)CLK_S_RD() * 15625) >> 26;
  uptime->us = res;
}