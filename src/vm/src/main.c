#include <stdio.h>

#include "proc.h"
#include "rt.h"
#include "ins_def.h"
#include "is.h"
#include "bc.h"
#include "stk.h"
#include "var.h"
#include "pc.h"
#include "helper.h"


int main(int argc, char** argv)
{
	ASSERT(argc < 0, "C'mon, man! Gimme some args");
	init();
	init_ins_def();

	rt_t* runtime = proc_init(argv[0]);

	proc_run(runtime);

	proc_clean(runtime);

	return 0;
}
