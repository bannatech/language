#include <stdlib.h>
#include <stdio.h>

#include "var_ops.h"

#include "var.h"
#include "helper.h"

void var_pprint(var_cont* var)
{
	if (var->type == G_STR)
	{
		var_data_str* data = var->data;
		for (int i = 0; i < data->size; i++) printf("%c", data->v[i]);
		printf("\n");
	} else
	if (var->type == G_INT)
	{
		int val = var_data_get_G_INT(var);
		printf("%i\n", val);
	} else
	if (var->type == G_FLOAT)
	{
		double val = var_data_get_G_FLOAT(var);
		printf("%f\n", val);
	}
}

var_cont* var_add_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_FLOAT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	double S  = AV + BV;

	var_data_float* data = var_data_alloc_G_FLOAT(S);

	var_set(var, data, G_FLOAT);

	return var;
}
var_cont* var_add_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);

	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = AV + BV;

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_add(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_add_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_add_float(A, B);
	}
	
	N_ASSERT(rv, "var_add\n");

	return rv;
}

var_cont* var_sub_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_FLOAT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	double S  = AV - BV;

	var_data_float* data = var_data_alloc_G_FLOAT(S);

	var_set(var, data, G_FLOAT);

	return var;
}
var_cont* var_sub_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = AV - BV;

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_sub(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_sub_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_sub_float(A, B);
	}
	
	N_ASSERT(rv, "var_sub\n");

	return rv;
}

var_cont* var_mult_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_FLOAT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	double S  = AV * BV;

	var_data_float* data = var_data_alloc_G_FLOAT(S);

	var_set(var, data, G_FLOAT);

	return var;
}
var_cont* var_mult_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = AV * BV;

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_mult(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_mult_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_mult_float(A, B);
	}
	
	N_ASSERT(rv, "var_mult\n");

	return rv;
}

var_cont* var_div_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_FLOAT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	double S  = AV / BV;

	var_data_float* data = var_data_alloc_G_FLOAT(S);

	var_set(var, data, G_FLOAT);

	return var;
}
var_cont* var_div_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = AV / BV;

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_div(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_div_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_div_float(A, B);
	}
	
	N_ASSERT(rv, "var_div\n");

	return rv;
}

var_cont* var_gthan_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	int S  = (AV > BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_gthan_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = (AV > BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;

}
var_cont* var_gthan(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_gthan_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_gthan_float(A, B);
	}
	
	N_ASSERT(rv, "var_gthan\n");

	return rv;
}

var_cont* var_lthan_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	int S  = (AV < BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_lthan_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = (AV < BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_lthan(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_lthan_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_lthan_float(A, B);
	}
	
	N_ASSERT(rv, "var_lthan\n");

	return rv;
}

var_cont* var_gthan_eq_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	int S  = (AV >= BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_gthan_eq_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = (AV >= BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;

}
var_cont* var_gthan_eq(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_gthan_eq_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_gthan_eq_float(A, B);
	}
	
	N_ASSERT(rv, "var_gthan\n");

	return rv;
}

var_cont* var_lthan_eq_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	int S  = (AV <= BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_lthan_eq_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = (AV <= BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_lthan_eq(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_lthan_eq_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_lthan_eq_float(A, B);
	}
	
	N_ASSERT(rv, "var_lthan\n");

	return rv;
}

var_cont* var_eq_float(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	double AV = var_data_get_G_FLOAT(A);
	double BV = var_data_get_G_FLOAT(B);

	int S  = (AV == BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_eq_int(var_cont* A, var_cont* B)
{
	var_cont* var = var_new(G_INT);
	int AV = var_data_get_G_INT(A);
	int BV = var_data_get_G_INT(B);

	int S  = (AV == BV);

	var_data_int* data = var_data_alloc_G_INT(S);

	var_set(var, data, G_INT);

	return var;
}
var_cont* var_eq(var_cont* A, var_cont* B)
{
	var_cont* rv;

	ASSERT(( A->type == B->type ), "Inconsistent Types\n");
	if (A->type == G_INT && B->type == G_INT)
	{
		rv = var_eq_int(A, B);
	} else
	if (A->type == G_FLOAT && B->type == G_FLOAT)
	{
		rv = var_eq_float(A, B);
	}
	
	N_ASSERT(rv, "var_eq\n");

	return rv;
}

var_cont* var_not(var_cont* A)
{
	var_cont* rv = var_new(G_INT);

	int val = var_data_get_G_INT(A);
	if (val < 1) val = 1;
	else         val = 0;

	var_set(rv, var_data_alloc_G_INT(val), G_INT);

	return rv;
}
