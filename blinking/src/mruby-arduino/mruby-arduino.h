#define ARDUINO_ARCH_SAM

#include "config.h"

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/string.h"
#include "mruby/data.h"

// extern "C"
void
add_arduino_to_mruby(mrb_state *mrb);
