# # simple test
# 1 + 1

# # simple test, loop
# loop do
#   1 + 1
# end

# # Using only custom-defined methods
# loop do
#   Silly.woot
#   Silly.show_memory_usage
# end

# # Single Blink and end
# Serial.println("Single Blink!")
# Arduino.digitalWrite(13, 1)
# Arduino.delay(1000)
# Arduino.digitalWrite(13, 0)
# Arduino.delay(1000)


# # Class, with module include
# class Blinky
#   include Arduino
#
#   def initialize
#     Serial.println("Blinker initialized")
#     pinMode(13, OUTPUT)
#     pinMode(2, INPUT_PULLUP)
#   end
#
#   def run
#     Serial.println("#run")
#     loop do
#       Serial.println("blink module!")
#       digitalWrite(13, 1)
#       if digitalRead(2) == 1
#         delay(1000)
#       else
#         delay(100)
#       end
#       digitalWrite(13, 0)
#       if digitalRead(2) == 1
#         delay(1000)
#       else
#         delay(100)
#       end
#     end
#   end
# end
# blinky = Blinky.new
# blinky.run


# loop do
#   Serial.println("blinky!")
#   Arduino.digitalWrite(13, 1)
#   Arduino.delay(1000)
#   Arduino.digitalWrite(13, 0)
#   Arduino.delay(1000)
# end


# Arduino.pinMode(2, Arduino::INPUT_PULLUP)
# loop do
#   Serial.println("blinky with input")
#   Arduino.digitalWrite(13, 1)
#   if Arduino.digitalRead(2) == Arduino::LOW
#     Arduino.delay(1000)
#   else
#     Arduino.delay(100)
#   end
#   Arduino.digitalWrite(13, 0)
#   if Arduino.digitalRead(2) == Arduino::LOW
#     Arduino.delay(1000)
#   else
#     Arduino.delay(100)
#   end
# end


# Slighly more advanced, but still polling the pin
Arduino.pinMode(2, Arduino::INPUT_PULLUP)

@delay_time = 500
def get_delay_time
  delay_time = case Arduino.digitalRead(2)
  when Arduino::LOW
    500
  else
    100
  end

  if @delay_time != delay_time
    Serial.println("blinky delay changed to #{delay_time}ms")
    @dot_counter = 0
    @delay_time = delay_time
  end
end

@dot_counter = 0
loop do
  get_delay_time

  @dot_counter += 1
  if @dot_counter >= 10
    Serial.println('.')
    @dot_counter = 0
  else
    Serial.print('.')
  end

  Arduino.digitalWrite(13, Arduino.digitalRead(13) == Arduino::LOW ? Arduino::HIGH : Arduino::LOW)
  Arduino.delay(@delay_time)
end
