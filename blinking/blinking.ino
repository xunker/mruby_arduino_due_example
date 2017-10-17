#include "src/mruby-arduino/mruby-arduino.h"
#include "mruby/irep.h"

mrb_state *mrb;
int ai;
size_t total_allocated;

#include "blinking.h"

// mrb_value silly_func(mrb_state *mrb, mrb_value self){
//   Serial.println("silly_func");
// 	digitalWrite(13, HIGH);
// 	delay(250);
// 	digitalWrite(13, LOW);
// 	delay(250);
// 	return mrb_nil_value();
// }

// custom allocator to check heap shortage.
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

// report memory usage
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

extern char _end;
extern "C" char *sbrk(int i);
char *ramstart=(char *)0x20070000;
char *ramend=(char *)0x20088000;
// end report

void show_memory_usage() {
  char *heapend=sbrk(0);
  register char * stack_ptr asm ("sp");
  struct mallinfo mi=mallinfo();
  printf("\nDynamic ram used: %d\n",mi.uordblks);
  printf("Program static ram used %d\n",&_end - ramstart);
  printf("Stack ram used %d\n\n",ramend - stack_ptr);
  printf("My guess at free mem: %d\n",stack_ptr - heapend + mi.fordblks);
}

// mrb_value show_memory_usage_in_ruby(mrb_state *mrb, mrb_value self) {
//   show_memory_usage();
//   return mrb_nil_value();
// }

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(9600);

  total_allocated = 0;

	//Init mruby
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

  mruby_arduino_init_chipKIT_or_Due(mrb);

  // Serial.println("adding Silly methods");
	// RClass *sillyClass = mrb_define_class(mrb, "Silly", mrb->object_class);
  // mrb_define_class_method(mrb, sillyClass, "woot", silly_func, MRB_ARGS_REQ(1));
  // mrb_define_class_method(mrb, sillyClass, "show_memory_usage", show_memory_usage_in_ruby, MRB_ARGS_NONE());

  Serial.println("Setup complete");
	delay(1000);

	Serial.println("set GC");
  delay(1000);
	ai = mrb_gc_arena_save(mrb);
  delay(1000);

  show_memory_usage();
}

void loop() {
	Serial.println("loop");
  delay(1000);

	Serial.println("Executing Ruby code from C!");
  delay(1000);
	mrb_load_irep(mrb, bytecode);
  delay(1000);
	Serial.println("close");
  delay(1000);
	mrb_close(mrb);
  delay(1000);

	Serial.println("Restoring GC");
	mrb_gc_arena_restore(mrb,ai);

	Serial.println("delay");
  delay(1000);

}
