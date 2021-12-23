#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#define _heap heap
#define _putc putch
#define _halt halt
#define _ioe_init ioe_init

#ifndef FPGA_DEF_KEYID

#define MAP_KEY(k) _KEY_##k = AM_KEY_##k,
enum {
  MAP_KEY(NONE)
  AM_KEYS(MAP_KEY)
};

#endif

static inline uint32_t uptime() {
  return io_read(AM_TIMER_UPTIME).us / 1000;
}

static inline int read_key() {
  AM_INPUT_KEYBRD_T keybrd = io_read(AM_INPUT_KEYBRD);
  int key = keybrd.keycode | (keybrd.keydown << 15);
  return key;
}

static inline void draw_rect(uint32_t *pixels, int x, int y, int w, int h) {
  io_write(AM_GPU_FBDRAW, x, y, pixels, w, h, 0);
}

static inline void draw_sync() {
  io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, 1);
}

static inline int screen_width() {
  return io_read(AM_GPU_CONFIG).width;
}

static inline int screen_height() {
  return io_read(AM_GPU_CONFIG).height;
}
