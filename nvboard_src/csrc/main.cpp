#include <nvboard.h>
#include <Vtop.h>
#include <unistd.h>

static TOP_NAME dut;

void nvboard_bind_all_pins(Vtop* top);


int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();

  sleep(1); //fix the sdl bug.

  while(1) {
    nvboard_update();
    dut.CLOCK_50 = !dut.CLOCK_50;
    dut.eval();
  }
}
