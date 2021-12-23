#include <am.h>
#include <klib.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
  uint32_t *now_vmem_base = (uint32_t *)FB_ADDR;
  for(int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
        now_vmem_base[i] = 0;
  }
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  int w = SCREEN_WIDTH;
  int h = SCREEN_HEIGHT;
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = w, .height = h,
    .vmemsz = w * h
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int width = SCREEN_WIDTH;
  uint32_t *now_vmem_base = (uint32_t *)FB_ADDR + ctl->y * width + ctl->x;
  uint32_t *now_pixel_base = (uint32_t *)ctl->pixels;
  for(int i = 0; i < ctl->h; i++) {
    for(int j = 0; j< ctl->w; j++) {
        now_vmem_base[j] = now_pixel_base[j];
    }
    //memcpy(now_vmem_base, now_pixel_base, ctl->w * 4);
    now_vmem_base += width;
    now_pixel_base += ctl->w;
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
