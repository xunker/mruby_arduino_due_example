#define ARDUINO_ARCH_SAM

#include "config.h"

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/string.h"
#include "mruby/data.h"

// extern "C"
void
mruby_arduino_init_chipKIT_or_Due(mrb_state *mrb);
