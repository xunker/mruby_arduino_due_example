mruby Arduino Due Example setup instructions
============================================

# Example Arduino Sketch

## Download

Clone or download the sketch here: https://github.com/xunker/mruby_arduino_due_example

# mruby

## Download mruby

Clone or download https://github.com/xunker/mruby

Use the branch "arduino_due", it is the default branch so you should't need
to do anything special

## Configure mruby

In the mruby directory, exit the file `examples/targets/build_config_ArduinoDue.rb`.

Update the `ARDUINO_PATH`, `BIN_PATH`, `SAM_PATH`, and `TARGET_PATH` variables
to match your local system

## build mruby

Once the above configuration is complete, you can build mruby with the command

`MRUBY_CONFIG=examples/targets/build_config_ArduinoDue.rb ./minirake`

Note: if you make significant changes to the build config or mrbgems, you should
"clean" your project first.  Do that with:

`MRUBY_CONFIG=examples/targets/build_config_ArduinoDue.rb ./minirake clean`

and then call

`MRUBY_CONFIG=examples/targets/build_config_ArduinoDue.rb ./minirake`

as normal.

Remember, it never hurts to "clean" between builds.

If successful, you should see this output or similar:

```
================================================
      Config Name: ArduinoDue
 Output Directory: build/ArduinoDue
    Included Gems:
================================================
```

## compile mruby bytecode

Once mruby is built, you can compile mruby to bytecode using this command,
assuming the "mruby_arduino_due_example" diretory is on the same level as the
"mruby" directory:

```
bin/mrbc -Bbytecode -o../mruby_arduino_due_example/mruby_arduino_due_example.c -e ../mruby_arduino_due_example/mruby_arduino_due_example.rb
```

If succesful, no output will be returned.

# Arduino IDE

## Download Arduino IDE

You can download the Arduino IDE here: https://www.arduino.cc/en/Main/Software

## Configure the Arduino IDE for Due and mruby

### Add Arduino Due support to IDE

Tools Menu ->
  Board ->
    Boards Manager

Search for "Arduino SAM Boards (32-bits ARM Cortex-M3)" and install it.

### Add mruby support to Arduino IDE

Find and open the arduino `platform.txt` file. On Macos, it is located at

`~/Library/Arduino15/packages/arduino/hardware/sam/1.6.11/platform.txt`


#### Add path to compiler flags

Add `-I/<full_path_to_mruby_dir>/mruby/include` to the end of the "compiler.c.flags" line.

Add `-I/<full_path_to_mruby_dir>/mruby/include` to the end of the "compiler.cpp.flags" line.

For example, here is how those compiler flags look on my system after the change:

```
compiler.c.flags=-c -g -Os {compiler.warning_flags} -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -Dprintf=iprintf -MMD -I/Users/mnielsen/work/mruby/include
compiler.cpp.flags=-c -g -Os {compiler.warning_flags} -std=gnu++11 -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -MMD -I/Users/mnielsen/work/mruby/include
```

#### Add path and flags to "Combine" section

In the section that begins with "## Combine gc-sections, archives, and objects",
add:

`"-L/<full_path_to_mruby_dir>/mruby/build/ArduinoDue/lib" -lmruby -lm -lstdc++`

...right after the last "-gcc" on the line.

For example, my line looks like this after the addition:

```
## Combine gc-sections, archives, and objects
recipe.c.combine.pattern="{compiler.path}{compiler.c.elf.cmd}" -mcpu={build.mcu} -mthumb {compiler.c.elf.flags} "-T{build.variant.path}/{build.ldscript}" "-Wl,-Map,{build.path}/{build.project_name}.map" {compiler.c.elf.extra_flags} -o "{build.path}/{build.project_name}.elf" "-L{build.path}" -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--start-group {compiler.combine.flags} {object_files} "{build.variant.path}/{build.variant_system_lib}" "{build.path}/{archive_file}" -Wl,--end-group -lm -gcc "-L/Users/mnielsen/work/mruby/build/ArduinoDue/lib" -lmruby -lm -lstdc++
```
