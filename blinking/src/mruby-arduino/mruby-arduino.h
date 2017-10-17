#define ARDUINO_ARCH_SAM

#include "config.h"

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/string.h"
#include "mruby/data.h"

// #include "mruby-arduino.h"

// extern "C"
void
mruby_arduino_init_chipKIT_or_Due(mrb_state *mrb);
//
//
// void
// mrb_mruby_arduino_gem_init(mrb_state* mrb)
// {
// 	mruby_arduino_init_chipKIT_or_Due(mrb);
// }
//
// void
// mrb_mruby_arduino_gem_final(mrb_state* mrb) {
//
// }
