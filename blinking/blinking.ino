/*
		Example Arduino IDE file to show how to run mruby on the Arudino Due using
		mruby 1.3.0 and Arduino IDE v1.8.3. October 2017.
		Compiled by Matthew Nielsen (xunker@pyxidis.org), based on extensive work
		by kyab:
		https://github.com/kyab/mruby-arduino/blob/master/samples/blink/blink.pde
*/
#include "src/mruby-arduino/mruby-arduino.h"
#include "mruby/irep.h"

mrb_state *mrb;
int ai;
size_t total_allocated;

#include "blinking.h"

/* Custom allocator to check heap shortage. Originally created by kyab, copied
   from github.com/kyab/mruby-arduino/blob/master/samples/blink/blink.pde */
void *myallocf(mrb_state *mrb, void *p, size_t size, void *ud){
	if (size == 0){
		free(p);
		return NULL;
	}

	void *ret = realloc(p, size);
	if (!ret){
		/*
			Reaches here means mruby failed to allocate memory.
			Sometimes it is not critical because mruby core will retry allocation
			after GC.
		*/

		Serial.print("memory allocation error. requested size:");
		Serial.println(size, DEC);

		Serial.flush();

		//Ensure serial output received by host before proceeding.
		delay(200);
		return NULL;
	}
	total_allocated += size;
	return ret;
}

// Used in show_memory_usage()
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

extern char _end;
extern "C" char *sbrk(int i);
char *ramstart=(char *)0x20070000;
char *ramend=(char *)0x20088000;
// end

/* Print out the current memory usage. Credit goes to "ard_newbie":
   https://forum.arduino.cc/index.php?topic=480973.0 */
void show_memory_usage() {
  char *heapend=sbrk(0);
  register char * stack_ptr asm ("sp");
  struct mallinfo mi=mallinfo();
  printf("\nDynamic ram used: %d\n",mi.uordblks);
  printf("Program static ram used %d\n",&_end - ramstart);
  printf("Stack ram used %d\n\n",ramend - stack_ptr);
  printf("My guess at free mem: %d\n",stack_ptr - heapend + mi.fordblks);
}

/* Allow show_memory_usage() to be called from inside mruby as long as the
   appropriate lines in setup() are uncommented. */
mrb_value show_memory_usage_in_ruby(mrb_state *mrb, mrb_value self) {
  show_memory_usage();
  return mrb_nil_value();
}

void setup() {
  Serial.begin(9600);

  total_allocated = 0;

	/* Init mruby. Block originally by kyab and copied from
	   github.com/kyab/mruby-arduino/blob/master/samples/blink/blink.pde */
	Serial.println("mrb_open()...");
	delay(100);
	mrb = mrb_open_allocf(myallocf, NULL);
	if (mrb){
		Serial.print("Success: mrb_open() total allocated : ");
		Serial.println(total_allocated,DEC);
	}else{
		Serial.print("Failure: mrb_open() total allocated : ");
		Serial.println(total_allocated,DEC);
		return;
	}

	/* This adds the Arduino.* and Serial.* methods to mruby, but ONLY THOSE that
	   have been enabled in config.h. */
  mruby_arduino_init_chipKIT_or_Due(mrb);

	/* Uncomment the two lines below to allow Info.show_memory_usage to be
	   used in ruby. */
	// RClass *infoClass = mrb_define_class(mrb, "Info", mrb->object_class);
  // mrb_define_class_method(mrb, infoClass, "show_memory_usage", show_memory_usage_in_ruby, MRB_ARGS_NONE());

  Serial.println("Setup complete");
	delay(250);

	Serial.println("set GC");
  delay(250);
	ai = mrb_gc_arena_save(mrb); // see https://github.com/mruby/mruby/blob/master/doc/guides/gc-arena-howto.md
  delay(250);

  show_memory_usage();
}

void loop() {
	Serial.println("loop");
  delay(250);

	Serial.println("Executing Ruby code from C!");
  delay(250);
	mrb_load_irep(mrb, bytecode);
  delay(250);
	Serial.println("Finished executing Ruby");
  delay(250);
	mrb_close(mrb);
  delay(250);

	Serial.println("Restoring GC");
	mrb_gc_arena_restore(mrb,ai); // see https://github.com/mruby/mruby/blob/master/doc/guides/gc-arena-howto.md

  delay(250);
}
