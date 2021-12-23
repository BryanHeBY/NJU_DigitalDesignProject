#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#define FPS 30
#define CPS 5
#define CHAR_W 8
#define CHAR_H 16
#define NCHAR 128
#define COL_WHITE 0xeeeeee
#define COL_RED 0xff0033
#define COL_GREEN 0x00cc33
#define COL_PURPLE 0x2a0a29

int speed = 1;
static int pre_len = 0;

enum
{
  WHITE = 0,
  RED,
  GREEN,
  PURPLE
};
struct character
{
  char ch;
  int x, y, v, t;
} chars[NCHAR];

int screen_w, screen_h, hit, miss, wrong;
uint32_t texture[3][26][CHAR_W * CHAR_H], blank[CHAR_W * CHAR_H];

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int randint(int l, int r)
{
  return l + (rand() & 0x7fffffff) % (r - l + 1);
}

void new_char()
{
  for (int i = 0; i < LENGTH(chars); i++)
  {
    struct character *c = &chars[i];
    if (!c->ch)
    {
      c->ch = 'A' + randint(0, 25);
      c->x = randint(0, screen_w - CHAR_W);
      c->y = 0;
      c->v = (screen_h - CHAR_H + 1) / randint(FPS * 3 / 2, FPS * 2) / speed;
      c->t = 0;
      return;
    }
  }
}

void game_logic_update(int frame)
{
  if (frame % (FPS / CPS * speed) == 0)
    new_char();
  for (int i = 0; i < LENGTH(chars); i++)
  {
    struct character *c = &chars[i];
    if (c->ch)
    {
      if (c->t > 0)
      {
        if (--c->t == 0)
        {
          c->ch = '\0';
        }
      }
      else
      {
        c->y += c->v;
        if (c->y < 0)
        {
          c->ch = '\0';
        }
        if (c->y + CHAR_H >= screen_h)
        {
          miss++;
          c->v = 0;
          c->y = screen_h - CHAR_H;
          c->t = FPS;
        }
      }
    }
  }
}

void render()
{
  static int x[NCHAR], y[NCHAR], n = 0;

  for (int i = 0; i < n; i++)
  {
    io_write(AM_GPU_FBDRAW, x[i], y[i], blank, CHAR_W, CHAR_H, false);
  }

  n = 0;
  for (int i = 0; i < LENGTH(chars); i++)
  {
    struct character *c = &chars[i];
    if (c->ch)
    {
      x[n] = c->x;
      y[n] = c->y;
      n++;
      int col = (c->v > 0) ? WHITE : (c->v < 0 ? GREEN : RED);
      io_write(AM_GPU_FBDRAW, c->x, c->y, texture[col][c->ch - 'A'], CHAR_W, CHAR_H, false);
    }
  }
  io_write(AM_GPU_FBDRAW, 0, 0, NULL, 0, 0, true);
  for (int i = 0; i < pre_len; i++)
    putch('\b');
  char put_buf[64];
  sprintf(put_buf, "Hit: %d; Miss: %d; Wrong: %d", hit, miss, wrong);
  printf("%s", put_buf);
  pre_len = strlen(put_buf);
}

void check_hit(char ch)
{
  int m = -1;
  for (int i = 0; i < LENGTH(chars); i++)
  {
    struct character *c = &chars[i];
    if (ch == c->ch && c->v > 0 && (m < 0 || c->y > chars[m].y))
    {
      m = i;
    }
  }
  if (m == -1)
  {
    wrong++;
  }
  else
  {
    hit++;
    chars[m].v = -(screen_h - CHAR_H + 1) / (FPS);
  }
}

void video_init()
{
  screen_w = io_read(AM_GPU_CONFIG).width;
  screen_h = io_read(AM_GPU_CONFIG).height;

  extern char font[];
  for (int i = 0; i < CHAR_W * CHAR_H; i++)
    blank[i] = COL_PURPLE;

  for (int x = 0; x < screen_w; x += CHAR_W)
    for (int y = 0; y < screen_h; y += CHAR_H)
    {
      io_write(AM_GPU_FBDRAW, x, y, blank, min(CHAR_W, screen_w - x), min(CHAR_H, screen_h - y), false);
    }

  for (int ch = 0; ch < 26; ch++)
  {
    char *c = &font[CHAR_H * ch];
    for (int i = 0, y = 0; y < CHAR_H; y++)
      for (int x = 0; x < CHAR_W; x++, i++)
      {
        int t = (c[y] >> (CHAR_W - x - 1)) & 1;
        texture[WHITE][ch][i] = t ? COL_WHITE : COL_PURPLE;
        texture[GREEN][ch][i] = t ? COL_GREEN : COL_PURPLE;
        texture[RED][ch][i] = t ? COL_RED : COL_PURPLE;
      }
  }
}

char lut[256] = {
    [AM_KEY_A] = 'A',
    [AM_KEY_B] = 'B',
    [AM_KEY_C] = 'C',
    [AM_KEY_D] = 'D',
    [AM_KEY_E] = 'E',
    [AM_KEY_F] = 'F',
    [AM_KEY_G] = 'G',
    [AM_KEY_H] = 'H',
    [AM_KEY_I] = 'I',
    [AM_KEY_J] = 'J',
    [AM_KEY_K] = 'K',
    [AM_KEY_L] = 'L',
    [AM_KEY_M] = 'M',
    [AM_KEY_N] = 'N',
    [AM_KEY_O] = 'O',
    [AM_KEY_P] = 'P',
    [AM_KEY_Q] = 'Q',
    [AM_KEY_R] = 'R',
    [AM_KEY_S] = 'S',
    [AM_KEY_T] = 'T',
    [AM_KEY_U] = 'U',
    [AM_KEY_V] = 'V',
    [AM_KEY_W] = 'W',
    [AM_KEY_X] = 'X',
    [AM_KEY_Y] = 'Y',
    [AM_KEY_Z] = 'Z',
};

int exe_type()
{
  pre_len = 0;
  
  printf("type a number to choose speed\n");
  printf("fast : 1\n");
  printf("medium : 2\n");
  printf("slow : 3\n");
  printf("Type 'ESC' to exit\n");
  while (1)
  {
    AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
    if (ev.keydown && ev.keycode == AM_KEY_1)
    {
      speed = 1;
      break;
    }
    else if (ev.keydown && ev.keycode == AM_KEY_2)
    {
      speed = 2;
      break;
    }
    else if (ev.keydown && ev.keycode == AM_KEY_3)
    {
      speed = 3;
      break;
    }
    else if (ev.keydown && ev.keycode == AM_KEY_ESCAPE)
        goto ret;
  }
#ifdef FPGA_GRAGHIC_ON
  VGA_GRAPHIC_ON();
#endif
  memset(chars, 0, sizeof(chars));
  memset(chars, 0, sizeof(chars));
  extern int __am_gpu_init();
  __am_gpu_init();
  video_init();
  
  volatile int begin_us = io_read(AM_TIMER_UPTIME).us;
  

  int current = 0, rendered = 0;
  while (1)
  {
    int frames = (io_read(AM_TIMER_UPTIME).us - begin_us) / (1000000 / FPS);

    for (; current < frames; current++)
    {
      game_logic_update(current);
    }

    while (1)
    {
      AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
      if (ev.keycode == AM_KEY_NONE)
        break;
      if (ev.keydown && ev.keycode == AM_KEY_ESCAPE)
        goto ret;
      if (ev.keydown && lut[ev.keycode])
      {
        check_hit(lut[ev.keycode]);
      }
    };

    if (current > rendered)
    {
      render();
      rendered = current;
    }
  }

ret:
#ifdef FPGA_GRAGHIC_ON
  VGA_FONT_ON();
#endif
  putch('\n');
  return 0;
}
