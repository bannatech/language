/* `ns` Namespace implementation
 */

#ifndef NS_H
#define NS_H

#include <stdlib.h>

#include "var.h"
#include "helper.h"

typedef unsigned int ns_addr;

typedef struct ns_cont {
	long       level;
	ns_addr    size;
	var_cont** names;
	struct ns_cont* next;
} ns_cont;

typedef struct ns_t {
	long id;
	ns_cont* root;
	ns_cont* last;
} ns_t;

#define NS_CTX_DEPTH 32
typedef struct ns_ctx {
	int ptr;
	ns_t* spaces[NS_CTX_DEPTH];
} ns_ctx;

/* Initializes namespace context
 */
ns_ctx* ns_ctx_init(void);
void ns_ctx_del(ns_ctx*);

/* Push namespace to context
 */
void ns_ctx_push(ns_ctx*, ns_t*);

/* Pop namespace out of context
 */
ns_t* ns_ctx_pop(ns_ctx*);

/* Initializes namespace of size
 *  ns_addr - name limit
 */
ns_t* ns_init(ns_addr);

/* Initialize namespace container of size
 *  ns_addr - name limit
 *  int     - level
 */
ns_cont* ns_cont_init(ns_addr, int);

/* Cleans up memory
 */
void ns_del(ns_t*);
var_cont* ns_cont_del(ns_cont*, ns_addr);

/* Pushes namespace of size
 * ns_t*   - namespace instance
 * ns_addr - name limit
 */
void ns_push(ns_t*, ns_addr);

/* Pops last namespace level
 */
var_cont* ns_pop(ns_t*);

/* Declares a variable, at root or last namespace
 *  ns_t*     - Namespace instance
 *  b_type    - Type of variable
 *  int       - Mux value         [0]
 *  ns_addr   - Variable name
 *
 * @param[0] = namespace level
 *  0 -> current namespace
 *  1 -> global namespace
 */
void ns_dec(ns_t*, b_type, int, ns_addr);

/* Declares a variable, at namespace
 *  ns_t*     - Namespace instance
 *  b_type    - Type of variable
 *  ns_addr   - Variable name
 */
void ns_cont_dec(ns_cont*, b_type, ns_addr);

/* Sets variable to value, at root or last namespace
 *  ns_t*     - namespace instance
 *  int       - mux value         [0]
 *  ns_addr   - Variable name
 *  var_cont* - Variable
 *
 * @param[0] = namespace level
 * * 0 -> current namespace
 * * 1 -> global namespace
 */
void ns_set(ns_t*, int, ns_addr, var_cont*);

/* Sets variable to value, at root or last namespace
 *  ns_cont*  - Namespace instance
 *  var_cont* - Variable
 *  ns_addr   - Variable name
 */
void ns_cont_set(ns_cont*, var_cont*, ns_addr);

/* Gets variable from address
 *  ns_t*     - namespace instance
 *  int       - mux value         [0]
 *  ns_addr   - Variable name
 *
 * @param[0] = namespace level
 *  0 -> current namespace
 *  1 -> global namespace
 */
var_cont* ns_get(ns_t*, int, ns_addr);

/* Gets variable from address
 *  ns_t*     - namespace instance
 *  ns_addr   - Variable name
 */
var_cont* ns_cont_get(ns_cont*, ns_addr);

#endif // NS_H
