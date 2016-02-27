#include <stdio.h>

#include "proc.h"
#include "rt.h"
#include "ins_def.h"
#include "ins_mdata.h"
#include "helper.h"

int main(int argc, char** argv)
{
	ASSERT(argc < 0, "C'mon, man! Gimme some args\n");

	init_mdata();                       // Initalize the instruction definitions
	init_ins_def();

	rt_t* runtime = proc_init(argv[0]); // Initalize process

	proc_run(runtime);                  // Execute runtime

	proc_clean(runtime);                // Once `proc_run` returns, try to clean what sort of mess it made.

	return 0;
}
