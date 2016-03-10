/* `var_ops.h` -> Operate on variables.
 */

#ifndef VAR_OPS_H
#define VAR_OPS_H

#include <stdlib.h>
#include <stdio.h>

#include "var.h"
#include "helper.h"

var_cont* var_add_float(var_cont*, var_cont*);
var_cont* var_add_int(var_cont*, var_cont*);
var_cont* var_add(var_cont*, var_cont*);

var_cont* var_sub_float(var_cont*, var_cont*);
var_cont* var_sub_int(var_cont*, var_cont*);
var_cont* var_sub(var_cont*, var_cont*);

var_cont* var_mult_float(var_cont*, var_cont*);
var_cont* var_mult_int(var_cont*, var_cont*);
var_cont* var_mult(var_cont*, var_cont*);

var_cont* var_div_float(var_cont*, var_cont*);
var_cont* var_div_int(var_cont*, var_cont*);
var_cont* var_div(var_cont*, var_cont*);

#endif //VAR_OPS_H
