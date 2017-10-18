# # Simple test, will do this operation and then exit, there will
# # be no output.
# 1 + 1


# ----------


# # Simple test, loop. There will be no output and this will go on forever.
# loop do
#   1 + 1
# end


# ----------


# # Will blink the LED on the DUE labeled "L" on and off in 1 second intervals.
# # Needs the following enabled in config.h:
# #   MRUBY_ARDUINO_DIGITAL_WRITE
# #   MRUBY_ARDUINO_DELAY
# loop do
#   Arduino.digitalWrite(13, 1)
#   Arduino.delay(1000)
#   Arduino.digitalWrite(13, 0)
#   Arduino.delay(1000)
# end


# ----------


# # Using the Arduino methods as a module. Blinks the LED at 1 second interval
# # as well as printing text along the serial link.
# # Needs the following enabled in config.h:
# #   MRUBY_ARDUINO_DIGITAL_IO
# #   MRUBY_ARDUINO_DELAY
# #   MRUBY_ARDUINO_SERIAL_PRINTLN
# class Blinky
#   include Arduino
#
#   def initialize
#     Serial.println("Blinker initialized")
#     pinMode(13, OUTPUT)
#   end
#
#   def run
#     Serial.println("#run")
#     loop do
#       Serial.println("blink!")
#       digitalWrite(13, 1)
#       delay(1000)
#       digitalWrite(13, 0)
#       delay(1000)
#     end
#   end
# end
# blinky = Blinky.new
# blinky.run


# ----------


# # Will read the state of a switch connected to pin #2, and will vary the
# # the blinking speed depending on the state.
# # Needs the following enabled in config.h:
# #  MRUBY_ARDUINO_DIGITAL_IO
# #  MRUBY_ARDUINO_SERIAL_PRINT
# #  MRUBY_ARDUINO_SERIAL_PRINTLN
# #  MRUBY_ARDUINO_DELAY
# Arduino.pinMode(2, Arduino::INPUT_PULLUP)
#
# @delay_time = 500
# def get_delay_time
#   delay_time = case Arduino.digitalRead(2)
#   when Arduino::LOW
#     500
#   else
#     100
#   end
#
#   if @delay_time != delay_time
#     Serial.println("blinky delay changed to #{delay_time}ms")
#     @dot_counter = 0
#     @delay_time = delay_time
#   end
# end
#
# @dot_counter = 0
# loop do
#   get_delay_time
#
#   @dot_counter += 1
#   if @dot_counter >= 50
#     Serial.println('.')
#     @dot_counter = 0
#   else
#     Serial.print('.')
#   end
#
#   Arduino.digitalWrite(13, Arduino.digitalRead(13) == Arduino::LOW ? Arduino::HIGH : Arduino::LOW)
#   Arduino.delay(@delay_time)
# end


# ----------


# Fading the LED on and off using analogWrite.
# Needs:
#  MRUBY_ARDUINO_ANALOG_WRITE
#  MRUBY_ARDUINO_SERIAL_PRINT
#  MRUBY_ARDUINO_SERIAL_PRINTLN
#  MRUBY_ARDUINO_DELAY
dot_counter = 0
led_state = 0
led_direction = 1
loop do
  dot_counter += 1
  if dot_counter % 100 == 0
    Serial.print('.')
    if dot_counter > 5000
      Serial.println('')
      dot_counter = 0
    end
  end

  led_state += led_direction
  if led_state >= 255
    led_direction = -1
  end

  if led_state <= 0
    led_direction = +1
  end

  Arduino.analogWrite(13, led_state)
  Arduino.delay(2)
end


# ----------


# # Using the mruby gem mruby-numeric-ext from core. Mruby must be compiled with
# # the mruby-numeric-ext included.
# # Needs the following enabled in config.h:
# #   MRUBY_ARDUINO_SERIAL_PRINTLN
# dec = 0
# loop do
#   Serial.println("#{dec}: #{dec.chr.inspect}")
#   dec += 1
#   Arduino.delay(500)
# end


# ----------


# # Calling a C-function defined in blinking.ino. Requires the function
# # `show_memory_usage_in_ruby` be uncommented as well as two lines in setup()
# # begining with `RClass *infoClass...`.
# # Does NOT require anything in config.h to be enabled, but DOES require the
# # Arduino Due to be connected to your computer via the PROGRAMMING port (not
# # the "native" port).
# loop do
#   Silly.show_memory_usage
# end
