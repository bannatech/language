#include <stdio.h>

#include "proc.h"
#include "rt.h"
#include "is.h"
#include "ins_def.h"
#include "helper.h"

#define DEBUG 0

int main(int argc, char** argv)
{
	ASSERT(argc > 1,
	       "Specify a bytecode file in the first and only argument, please\n");

	init_mdata();                       // Initalize the instruction defs
	init_adata();
	init_ins_def();
	init_var_track();

	rt_t* runtime = proc_init(argv[1]); // Initalize process

	proc_run(runtime);                  // Execute runtime

	proc_clean(runtime);                // Once `proc_run` returns, clean
	                                    // what sort of mess it made.`

	return 0;
}
