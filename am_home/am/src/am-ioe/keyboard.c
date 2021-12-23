#include <am.h>

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t keycode = KBD_RD();
  kbd->keydown = keycode && ((keycode & _KEYID_BREAK_MASK) != _KEYID_BREAK_MASK);
  kbd->keycode = keycode & ~_KEYID_BREAK_MASK;
}