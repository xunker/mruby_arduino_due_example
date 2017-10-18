/* This file allows you to selectively enable and disable certain Arduino
   function calls in order to save memory. Once free memory drops below ~3.6kb,
   stability suffers and things stop running. */

  // #define MRUBY_ARDUINO_ALL // Enables _ALL_ arduino functions. Not recommended.

  // #define MRUBY_ARDUINO_DIGITAL_IO // digitalRead, digitalWrite, pinMode, and HIGH/LOW constants
  // #define MRUBY_ARDUINO_DIGITAL_READ // only digitalRead
  // #define MRUBY_ARDUINO_DIGITAL_WRITE // only digitalWrite
  // #define MRUBY_ARDUINO_DIGITAL_IO_CONSTANTS // only HIGH/LOW constants
  // #define MRUBY_ARDUINO_DIGITAL_HIGH // only HIGH constant
  // #define MRUBY_ARDUINO_DIGITAL_LOW // only LOW constant

  // #define MRUBY_ARDUINO_ANALOG_IO // analogRead, analogWrite, pinMode. Does NOT enable analogReference
  // #define MRUBY_ARDUINO_ANALOG_READ // only analogRead
  // #define MRUBY_ARDUINO_ANALOG_WRITE // only analogWrite
  // #define MRUBY_ARDUINO_ANALOG_REFERENCE // only analogReference

  // #define MRUBY_ARDUINO_PINMODE // pinMode and INPUT/OUTPUT/INPUT_PULLUP constants
  // #define MRUBY_ARDUINO_PINMODE_FUNC // pinMode only
  // #define MRUBY_ARDUINO_PINMODE_CONSTANTS // only INPUT/OUTPUT/INPUT_PULLUP constants
  // #define MRUBY_ARDUINO_PINMODE_INPUT // only INPUT constant
  // #define MRUBY_ARDUINO_PINMODE_OUTPUT // only OUTPUT constant
  // #define MRUBY_ARDUINO_PINMODE_INPUT_PULLUP // only INPUT_PULLUP constant

  // #define MRUBY_ARDUINO_SERIAL // Serial.begin, Serial.available, Serial.print, Serial.println
  // #define MRUBY_ARDUINO_SERIAL_BEGIN // only Serial.begin
  // #define MRUBY_ARDUINO_SERIAL_AVAILABLE // only Serial.available
  // #define MRUBY_ARDUINO_SERIAL_PRINT // only Serial.print
  // #define MRUBY_ARDUINO_SERIAL_PRINTLN // only Serial.println

  // #define MRUBY_ARDUINO_SHIFT // shiftIn, shiftOut, and MSBFIRST/LSBFIRST constants
  // #define MRUBY_ARDUINO_SHIFT_IN // only shiftIn
  // #define MRUBY_ARDUINO_SHIFT_OUT // only shiftOut
  // #define MRUBY_ARDUINO_SHIFT_CONSTANTS // only MSBFIRST/LSBFIRST constants

  // #define MRUBY_ARDUINO_INTERRUPTS // interrupts, noInterrupts

  // #define MRUBY_ARDUINO_PULSE_IN // pulseIn

  // #define MRUBY_ARDUINO_MILLIS // millis
  // #define MRUBY_ARDUINO_MICROS // micros

  // #define MRUBY_ARDUINO_DELAY // delay
  // #define MRUBY_ARDUINO_DELAY_MICROSECONDS // delayMicroseconds

  // #define MRUBY_ARDUINO_MAP // map

  // #define MRUBY_ARDUINO_RANDOM_SEED // randomSeed
  // #define MRUBY_ARDUINO_RANDOM // random

  /* ----- Leave the rest of this alone ----- */

  #ifdef MRUBY_ARDUINO_ALL
    #define MRUBY_ARDUINO_DIGITAL_IO
    #define MRUBY_ARDUINO_ANALOG_IO
    #define MRUBY_ARDUINO_SERIAL
    #define MRUBY_ARDUINO_SHIFT
    #define MRUBY_ARDUINO_INTERRUPTS
    #define MRUBY_ARDUINO_PINMODE
    #define MRUBY_ARDUINO_PULSE_IN
    #define MRUBY_ARDUINO_MILLIS
    #define MRUBY_ARDUINO_MICROS
    #define MRUBY_ARDUINO_DELAY
    #define MRUBY_ARDUINO_DELAY_MICROSECONDS
    #define MRUBY_ARDUINO_MAP
    #define MRUBY_ARDUINO_RANDOM_SEED
    #define MRUBY_ARDUINO_RANDOM
    #define MRUBY_ARDUINO_INTERRUPTS
  #endif /*MRUBY_ARDUINO_ALL*/

  #ifdef MRUBY_ARDUINO_DIGITAL_IO
    #define MRUBY_ARDUINO_DIGITAL_IO_CONSTANTS
    #define MRUBY_ARDUINO_PINMODE
    #define MRUBY_ARDUINO_DIGITAL_READ
    #define MRUBY_ARDUINO_DIGITAL_WRITE
  #endif /*MRUBY_ARDUINO_DIGITAL_IO*/

  #ifdef MRUBY_ARDUINO_DIGITAL_IO_CONSTANTS
    #define MRUBY_ARDUINO_DIGITAL_HIGH
    #define MRUBY_ARDUINO_DIGITAL_LOW
  #endif /*MRUBY_ARDUINO_DIGITAL_IO_CONSTANTS*/

  #ifdef MRUBY_ARDUINO_ANALOG_IO
    #define MRUBY_ARDUINO_PINMODE
    #define MRUBY_ARDUINO_ANALOG_READ
    #define MRUBY_ARDUINO_ANALOG_WRITE
  #endif /*MRUBY_ARDUINO_ANALOG_IO*/

  #ifdef MRUBY_ARDUINO_SERIAL
    #define MRUBY_ARDUINO_SERIAL_AVAILABLE
    #define MRUBY_ARDUINO_SERIAL_BEGIN
    #define MRUBY_ARDUINO_SERIAL_PRINT
    #define MRUBY_ARDUINO_SERIAL_PRINTLN
  #endif /*MRUBY_ARDUINO_SERIAL*/

  /* If any of the Serial.* methods are enabled then the Serial class must
     be created in mruby. */
  #if defined(MRUBY_ARDUINO_SERIAL_AVAILABLE) || defined(MRUBY_ARDUINO_SERIAL_BEGIN) || defined(MRUBY_ARDUINO_SERIAL_PRINT) || defined(MRUBY_ARDUINO_SERIAL_PRINTLN)
    #define MRUBY_ARDUINO_SERIAL_CLASS
  #endif

  #ifdef MRUBY_ARDUINO_SHIFT
    #define MRUBY_ARDUINO_SHIFT_CONSTANTS
    #define MRUBY_ARDUINO_SHIFT_IN
    #define MRUBY_ARDUINO_SHIFT_OUT
  #endif /*MRUBY_ARDUINO_SERIAL*/

  #ifdef MRUBY_ARDUINO_INTERRUPTS
   #define MRUBY_ARDUINO_NO_INTERRUPTS
   #endif /*MRUBY_ARDUINO_INTERRUPTS*/

  #ifdef MRUBY_ARDUINO_PINMODE
    #define MRUBY_ARDUINO_PINMODE_FUNC
    #define MRUBY_ARDUINO_PINMODE_CONSTANTS
  #endif /*MRUBY_ARDUINO_PINMODE*/

  #ifdef MRUBY_ARDUINO_PINMODE_CONSTANTS
    #define MRUBY_ARDUINO_PINMODE_INPUT
    #define MRUBY_ARDUINO_PINMODE_OUTPUT
    #define MRUBY_ARDUINO_PINMODE_INPUT_PULLUP
  #endif /*MRUBY_ARDUINO_PINMODE_CONSTANTS*/
