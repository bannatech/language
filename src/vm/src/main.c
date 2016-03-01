#include <stdio.h>

#include "proc.h"
#include "rt.h"
#include "is.h"
#include "ins_def.h"
#include "helper.h"

int main(int argc, char** argv)
{
	ASSERT(argc > 1, "C'mon, man! Gimme some args\n");

	init_mdata();                       // Initalize the instruction definitions
	init_adata();
	init_ins_def();

	rt_t* runtime = proc_init(argv[1]); // Initalize process

	proc_run(runtime);                  // Execute runtime

	proc_clean(runtime);                // Once `proc_run` returns, try to clean
	                                    // what sort of mess it made.

	return 0;
}
