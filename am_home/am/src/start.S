.section entry, "ax"
.globl _start
.type _start, @function

_start:
  li sp, 0x01023ffc
  jal _trm_init
