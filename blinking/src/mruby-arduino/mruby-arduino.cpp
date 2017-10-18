/*
		Library to bridge Arduino function in to mruby running on the Arudino Due
    and using mruby 1.3.0 and Arduino IDE v1.8.3. October 2017.
		Compiled by Matthew Nielsen (xunker@pyxidis.org), based on extensive work
		by kyab:
		https://github.com/kyab/mruby-arduino/

    To use this, #include it in your arduino sketch and then call
    `add_arduino_to_mruby()` in setup().

    REMEMBER: Functions can be selectively enabled for memory usage reasons.
    By default, NO function are enabled. You MUST edit config.h to enable
    functions.
*/

#include "mruby-arduino.h"

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/string.h"
#include "mruby/data.h"

#include <Arduino.h>

mrb_value mrb_serial_available(mrb_state *mrb, mrb_value self){
  return mrb_fixnum_value(Serial.available());
}

mrb_value mrb_serial_begin(mrb_state *mrb, mrb_value self){
  mrb_int speed = 0;
  mrb_get_args(mrb,"i",&speed);
  Serial.begin(speed);
  return mrb_nil_value();
}

mrb_value mrb_serial_print(mrb_state *mrb, mrb_value self){
  mrb_value s;
  mrb_get_args(mrb,"S", &s);
  for (int i = 0; i < RSTRING_LEN(s); i++){
    Serial.print( RSTRING_PTR(s)[i] );
  }
  Serial.print("");
  return mrb_nil_value();
}

mrb_value mrb_serial_println(mrb_state *mrb, mrb_value self){
  mrb_serial_print(mrb, self);
  Serial.println("");
  return mrb_nil_value();
}

mrb_value mrb_arduino_pinMode(mrb_state *mrb, mrb_value self){
  mrb_int pin, mode;
  mrb_get_args(mrb, "ii", &pin, &mode);
  pinMode(pin, mode);
  return mrb_nil_value();
}

mrb_value mrb_arduino_digitalWrite(mrb_state *mrb, mrb_value self){
  mrb_int pin, value;
  mrb_get_args(mrb, "ii", &pin, &value);
  digitalWrite(pin, value);
  return mrb_nil_value();
}

mrb_value mrb_arduino_digitalRead(mrb_state *mrb, mrb_value self){
  mrb_int pin;
  mrb_get_args(mrb, "i", &pin);
  int val = digitalRead(pin);
  return mrb_fixnum_value(val);
}

mrb_value mrb_arduino_analogReference(mrb_state *mrb, mrb_value self){
  mrb_int type;
  mrb_get_args(mrb, "i", &type);

  analogReference((eAnalogReference)type);

  return mrb_nil_value();
}

mrb_value mrb_arduino_analogWrite(mrb_state *mrb, mrb_value self){
  mrb_int pin, value;
  mrb_get_args(mrb, "ii", &pin, &value);
  analogWrite(pin, value);
  return mrb_nil_value();
}

mrb_value mrb_arduino_analogRead(mrb_state *mrb, mrb_value self){
  mrb_int pin;
  mrb_get_args(mrb, "i", &pin);
  int val = analogRead(pin);
  return mrb_fixnum_value(val);
}

mrb_value mrb_arduino_shiftOut(mrb_state *mrb, mrb_value self){
  mrb_int dataPin, clockPin, bitOrder, value;
  mrb_get_args(mrb, "iiii", &dataPin, &clockPin, &bitOrder, &value);
  shiftOut(dataPin, clockPin, bitOrder, (byte)value);
  return mrb_nil_value();
}

mrb_value mrb_arduino_shiftIn(mrb_state *mrb, mrb_value self){
  mrb_int dataPin, clockPin, bitOrder;
  mrb_get_args(mrb, "iii", &dataPin, &clockPin, &bitOrder);
  return mrb_fixnum_value(shiftIn(dataPin, clockPin, bitOrder));
}

mrb_value mrb_arduino_pulseIn(mrb_state *mrb, mrb_value self){
  mrb_int pin, value, timeout;
  mrb_int n = mrb_get_args(mrb, "ii|i", &pin, &value, &timeout);

  unsigned long ret = 0;
  if (n == 2){
    ret = pulseIn(pin, value);
  }else if (n == 3){
    ret = pulseIn(pin, value, timeout);
  }

  return mrb_fixnum_value(ret);
}

mrb_value mrb_arduino_millis(mrb_state *mrb, mrb_value self){
  return mrb_fixnum_value(millis());
}

mrb_value mrb_arduino_micros(mrb_state *mrb, mrb_value self){
  return mrb_fixnum_value(micros());
}

mrb_value mrb_arduino_delay(mrb_state *mrb, mrb_value self){
  mrb_int ms;
  mrb_get_args(mrb, "i", &ms);
  delay(ms);
  return mrb_nil_value();
}

mrb_value mrb_arduino_delayMicroseconds(mrb_state *mrb, mrb_value self){
  mrb_int us;
  mrb_get_args(mrb, "i", &us);
  delayMicroseconds(us);
  return mrb_nil_value();
}


mrb_value mrb_arduino_map(mrb_state *mrb, mrb_value self){
  mrb_int value, fromLow, fromHigh, toLow, toHigh;
  mrb_get_args(mrb, "iiiii", &value, &fromLow, &fromHigh, &toLow, &toHigh);
  mrb_int ret = map(value, fromLow, fromHigh, toLow, toHigh);
  return mrb_fixnum_value(ret);
}

mrb_value mrb_arduino_randomSeed(mrb_state *mrb, mrb_value self){
  mrb_int seed;
  mrb_get_args(mrb, "i", &seed);
  randomSeed(seed);
  return mrb_nil_value();
}

mrb_value mrb_arduino_random(mrb_state *mrb, mrb_value self){
  mrb_int arg1, arg2;
  mrb_int n = mrb_get_args(mrb, "i|i", &arg1, &arg2 );
  if (n == 1){
    return mrb_fixnum_value(random(arg1));
  }else{
    return mrb_fixnum_value(random(arg1, arg2));
  }
}

mrb_value mrb_arduino_interrupts(mrb_state *mrb, mrb_value self){
  interrupts();
  return mrb_nil_value();
}

mrb_value mrb_arduino_noInterrupts(mrb_state *mrb, mrb_value self){
  noInterrupts();
  return mrb_nil_value();
}

// extern "C"
void
mruby_arduino_init_chipKIT_or_Due(mrb_state* mrb) { // formerly named `mruby_arduino_init_chipKIT_or_Due`

  #ifdef MRUBY_ARDUINO_SERIAL_CLASS
    RClass *serialClass = mrb_define_class(mrb, "Serial", mrb->object_class);
  #endif

  #ifdef MRUBY_ARDUINO_SERIAL_AVAILABLE
    mrb_define_class_method(mrb, serialClass, "available", mrb_serial_available, MRB_ARGS_NONE());
  #endif

  #ifdef MRUBY_ARDUINO_SERIAL_BEGIN
    mrb_define_class_method(mrb, serialClass, "begin",mrb_serial_begin, MRB_ARGS_REQ(1));
  #endif

  #ifdef MRUBY_ARDUINO_SERIAL_PRINTLN
    mrb_define_class_method(mrb, serialClass, "println", mrb_serial_println, MRB_ARGS_REQ(1));
  #endif

  #ifdef MRUBY_ARDUINO_SERIAL_PRINT
    mrb_define_class_method(mrb, serialClass, "print", mrb_serial_print, MRB_ARGS_REQ(1));
  #endif

  RClass *arduinoModule = mrb_define_module(mrb, "Arduino");

  #ifdef MRUBY_ARDUINO_PINMODE_FUNC
    mrb_define_module_function(mrb, arduinoModule, "pinMode", mrb_arduino_pinMode, MRB_ARGS_REQ(2));
  #endif

  #ifdef MRUBY_ARDUINO_DIGITAL_WRITE
    mrb_define_module_function(mrb, arduinoModule, "digitalWrite", mrb_arduino_digitalWrite, MRB_ARGS_REQ(2));
  #endif

  #ifdef MRUBY_ARDUINO_DIGITAL_READ
    mrb_define_module_function(mrb, arduinoModule, "digitalRead", mrb_arduino_digitalRead, MRB_ARGS_REQ(1));
  #endif

  #ifdef MRUBY_ARDUINO_ANALOG_REFERENCE
    mrb_define_module_function(mrb, arduinoModule, "analogReference", mrb_arduino_analogReference, MRB_ARGS_REQ(1));
  #endif

  #ifdef MRUBY_ARDUINO_ANALOG_WRITE
    mrb_define_module_function(mrb, arduinoModule, "analogWrite", mrb_arduino_analogWrite, MRB_ARGS_REQ(2));
  #endif

  #ifdef MRUBY_ARDUINO_ANALOG_READ
    mrb_define_module_function(mrb, arduinoModule, "analogRead", mrb_arduino_analogRead, MRB_ARGS_REQ(1));
  #endif

  #ifdef MRUBY_ARDUINO_SHIFT_OUT
    mrb_define_module_function(mrb, arduinoModule, "shiftOut", mrb_arduino_shiftOut, MRB_ARGS_REQ(4));
  #endif

  #ifdef MRUBY_ARDUINO_SHIFT_IN
    mrb_define_module_function(mrb, arduinoModule, "shiftIn", mrb_arduino_shiftOut, MRB_ARGS_REQ(3));
  #endif

  #ifdef MRUBY_ARDUINO_PULSE_IN
    mrb_define_module_function(mrb, arduinoModule, "pulseIn", mrb_arduino_pulseIn, MRB_ARGS_REQ(2) | MRB_ARGS_OPT(1));
  #endif

  #ifdef MRUBY_ARDUINO_MILLIS
    mrb_define_module_function(mrb, arduinoModule, "millis", mrb_arduino_millis, MRB_ARGS_NONE());
  #endif

  #ifdef MRUBY_ARDUINO_MICROS
    mrb_define_module_function(mrb, arduinoModule, "micros", mrb_arduino_micros, MRB_ARGS_NONE());
  #endif

  #ifdef MRUBY_ARDUINO_DELAY
    mrb_define_module_function(mrb, arduinoModule, "delay", mrb_arduino_delay, MRB_ARGS_REQ(1));
  #endif

  #ifdef MRUBY_ARDUINO_DELAY_MICROSECONDS
    mrb_define_module_function(mrb, arduinoModule, "delayMicroseconds", mrb_arduino_delayMicroseconds, MRB_ARGS_REQ(1));
  #endif

  #ifdef MRUBY_ARDUINO_MAP
    mrb_define_module_function(mrb, arduinoModule, "map", mrb_arduino_map, MRB_ARGS_REQ(5));
  #endif

  #ifdef MRUBY_ARDUINO_RANDOM_SEED
    mrb_define_module_function(mrb, arduinoModule, "randomSeed", mrb_arduino_randomSeed, MRB_ARGS_REQ(1));
  #endif

  #ifdef MRUBY_ARDUINO_RANDOM
    mrb_define_module_function(mrb, arduinoModule, "random", mrb_arduino_random, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  #endif

  #ifdef MRUBY_ARDUINO_INTERRUPTS
    mrb_define_module_function(mrb, arduinoModule, "interrupts", mrb_arduino_interrupts, MRB_ARGS_NONE());
  #endif

  #ifdef MRUBY_ARDUINO_NO_INTERRUPTS
    mrb_define_module_function(mrb, arduinoModule, "noInterrupts", mrb_arduino_noInterrupts, MRB_ARGS_NONE());
  #endif

  #if defined(MRUBY_ARDUINO_DIGITAL_HIGH) || defined(MRUBY_ARDUINO_DIGITAL_LOW)
    #if defined(MRUBY_ARDUINO_DIGITAL_HIGH)
      mrb_define_const(mrb, arduinoModule, "HIGH", mrb_fixnum_value(HIGH));
    #endif

    #if defined(MRUBY_ARDUINO_DIGITAL_LOW)
      mrb_define_const(mrb, arduinoModule, "LOW", mrb_fixnum_value(LOW));
    #endif
  #endif

  #if defined(MRUBY_ARDUINO_PINMODE_INPUT) || defined(MRUBY_ARDUINO_PINMODE_OUTPUT) || defined(MRUBY_ARDUINO_PINMODE_INPUT_PULLUP)
    #ifdef MRUBY_ARDUINO_PINMODE_INPUT
      mrb_define_const(mrb, arduinoModule, "INPUT", mrb_fixnum_value(INPUT));
    #endif

    #ifdef MRUBY_ARDUINO_PINMODE_OUTPUT
      mrb_define_const(mrb, arduinoModule, "OUTPUT", mrb_fixnum_value(OUTPUT));
    #endif

    #ifdef MRUBY_ARDUINO_PINMODE_INPUT_PULLUP
      mrb_define_const(mrb, arduinoModule, "INPUT_PULLUP", mrb_fixnum_value(INPUT_PULLUP));
    #endif
  #endif

  #ifdef MRUBY_ARDUINO_SHIFT_CONSTANTS
    mrb_define_const(mrb, arduinoModule, "MSBFIRST", mrb_fixnum_value(MSBFIRST));
    mrb_define_const(mrb, arduinoModule, "LSBFIRST", mrb_fixnum_value(LSBFIRST));
  #endif /*MRUBY_ARDUINO_SHIFT_CONSTANTS*/

}
