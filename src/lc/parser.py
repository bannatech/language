from lexer import *
from memonic import *
from bytecode import *

class Parser():
	def __init__(self, file_name):
		self.splitters = [
			":",
			";",
			"\(",
			"\)",
			"\[",
			"\]",
			"{",
			"}",
			",",
			"\+",
			"\-",
			"\*",
			"\/",
			" "
		]
		self.end_statements = [
			":",
			";",
			"{",
			"}"
		]

		self.known_tokens = [
			"return",
			"print",
			"if",
			"else",
			"for",
			"while",
			"func",
			"class"
		]

		self.defined_types = [
			"void",
			"_addr",
			"_type",
			"_plist",
			"func",
			"class",
			"object",
			"int",
			"float",
			"char",
			"string",
			"s_array",
			"array",
			"hashtable",
			"stack"
		]
	
		self.int_def       = AtomicSymbol("^[0-9]+$")
		self.str_def       = AtomicSymbol("^\0+")
	
		self.type_def      = InclusiveSymbol(self.defined_types)
		self.label_def     = ExclusiveSymbol(self.defined_types +
		                                     [self.int_def]     +
		                                     [self.str_def]     +
		                                     self.known_tokens   )

		self.paramlist_def = GroupingSymbol( [
		                                      AtomicSymbol("\("),
		                                      AtomicSymbol("\)")
		                                     ] )
	
		self.expr_def = PolySymbol( [
		                             self.label_def,
		                             self.int_def,
		                             AtomicSymbol("\("),
		                             AtomicSymbol("\)"),
		                             AtomicSymbol("\+"),
		                             AtomicSymbol("\-"),
		                             AtomicSymbol("\*"),
		                             AtomicSymbol("\/"),
		                             AtomicSymbol("\>"),
		                             AtomicSymbol("\<"),
		                             AtomicSymbol("=\<"),
		                             AtomicSymbol("\>="),
		                             AtomicSymbol("=="),
		                             AtomicSymbol("\""),
		                             AtomicSymbol("'"),
		                             AtomicSymbol("\0")
		                            ], terminator=[
		                                           AtomicSymbol(";"),
		                                           AtomicSymbol(":")
		                                          ])

		self.statement_endebug = Statement(
			"endebug",
			expression=[
				AtomicSymbol("DEBUG"),
				AtomicSymbol(";")
			],
			init=(lambda x: [x.op(OP_DEBUG)])
		)

		self.statement_include = Statement(
			"include",
			expression=[
				AtomicSymbol("include"),
				self.label_def,
				AtomicSymbol(";")
			],
			init=(lambda x: [])
		)

		self.statement_codeblock_begin = Statement(
			"codeblock_begin",
			expression=[
				AtomicSymbol("{")
			],
			init=(lambda x: [x.push_directives()])
		)

		self.statement_codeblock_end = Statement(
			"codeblock_end",
			expression=[
				AtomicSymbol("}")
			],
			init=(lambda x: [x.pop_directives()])
		)

		self.statement_return = Statement(
			"return",
			expression=[
				AtomicSymbol("return"),
				self.expr_def,
				AtomicSymbol(";")
			],
			init=(lambda x: [
			                 x.eval_expr(1),
			                 x.op(OP_STV),
			                 x.op(0x00),
			                 x.op(0x00),
			                 x.op(0x00)
			                ])
		)

		self.statement_print = Statement(
			"print",
			expression=[
				AtomicSymbol("print"),
				self.expr_def,
				AtomicSymbol(";")
			],
			init=(lambda x: [
			                 x.eval_expr(1),
			                 x.op(OP_PRINT)
			                ])
		)

		self.statement_if = Statement(
			"if",
			expression=[
				AtomicSymbol("if"),
				self.expr_def,
				AtomicSymbol(":")
			],
			init=(lambda x: [
			                 x.eval_expr(1),
			                 x.op(OP_IFDO),
			                 x.add_directive(lambda x: [x.op(OP_DONE)],
			                                 cond=(
			                 lambda x: x.nxt(1)[0].name in ["else", "else_if"]))
			                ])
		)

		self.statement_else_if = Statement(
			"else_if",
			expression=[
				AtomicSymbol("else"),
				AtomicSymbol("if"),
				self.expr_def,
				AtomicSymbol(":")
			],
			init=(lambda x: [
			                 x.op(OP_ELSE),
			                 x.eval_expr(2),
			                 x.op(OP_IFDO),
			                 x.add_directive(lambda x: [x.op(OP_DONE)],
			                                 cond=(
			                 lambda x: x.nxt(1)[0].name in ["else", "else_if"]))
			                ])
		)

		self.statement_else = Statement(
			"else",
			expression=[
				AtomicSymbol("else"),
				AtomicSymbol(":")
			],
			init=(lambda x: [
			                 x.op(OP_ELSE),
			                 x.add_directive(lambda x: [x.op(OP_DONE)])
			                ])
		)

		self.statement_for = Statement(
			"for",
			expression=[
				AtomicSymbol("for"),
				self.expr_def,
				AtomicSymbol(":")
			],
			init=(lambda x: [
			                 ForLoop(x.eval_expr(1))
			                ])
		)

		self.statement_while = Statement(
			"while",
			expression=[
				AtomicSymbol("while"),
				self.expr_def,
				AtomicSymbol(":")
			],
			init=(lambda x: [
			                 x.op(OP_STARTL),
			                 x.eval_expr(1),
			                 x.op(OP_CLOOP),
			                 x.add_directive(lambda x: [x.op(OP_ENDL)])
			                ])
		)

		self.statement_func = Statement(
			"function",
			expression=[
				AtomicSymbol("func"),
				self.label_def,
				self.paramlist_def,
				AtomicSymbol("-"),
				AtomicSymbol(">"),
				self.type_def,
				AtomicSymbol(":")
			],
			init=(
				lambda x: [
				           x.new_name(1),
				           x.inc_scope(),
				           FunctionDef(x.eval_label(1),
				                       x.eval_param(2),
				                       x.eval_type(5)),
				           x.add_directive(lambda x: [x.op(OP_RETURN),
				                                      x.dec_scope()])
				          ])
		)

		self.statement_proc = Statement(
			"procedure",
			expression=[
				AtomicSymbol("func"),
				self.label_def,
				AtomicSymbol("-"),
				AtomicSymbol(">"),
				self.type_def,
				AtomicSymbol(":")
			],
			init=(
				lambda x: [
				           x.new_name(1),
				           x.inc_scope(),
				           FunctionDef(x.eval_label(1),
				                       None,
				                       x.eval_type(4)),
				           x.add_directive(lambda x: [x.op(OP_RETURN),
				                                      x.dec_scope()])
				          ])
		)

		self.statement_class = Statement(
			"class",
			expression=[
				AtomicSymbol("class"),
				self.label_def,
				self.paramlist_def,
				AtomicSymbol(":")
			],
			init=(lambda x: [
			                 x.new_name(1),
			                 ClassDef(x.eval_label(1),
			                          x.eval_param(2)),
			                 x.ns_persist(1),
			                 x.add_directive(lambda x: [x.ns_save(),
			                                            x.pop_scope(),
			                                            x.op(OP_ENDCLASS)]),
			                 x.push_scope()
			                ])
		)

		self.statement_pless_class = Statement(
			"paramless_class",
			expression=[
				AtomicSymbol("class"),
				self.label_def,
				AtomicSymbol(":")
			],
			init=(lambda x: [
			                 x.new_name(1),
			                 x.ns_persist(1),
			                 ClassDef(x.eval_label(1),
			                          None),
			                 x.add_directive(lambda x: [x.ns_save(),
			                                            x.pop_scope(),
			                                            x.op(OP_ENDCLASS)]),
			                 x.push_scope()
			                ])
		)


		self.statement_new = Statement(
			"new",
			expression=[
				self.label_def,
				self.label_def,
				AtomicSymbol("="),
				AtomicSymbol("new"),
				self.label_def,
				self.paramlist_def,
				AtomicSymbol(";")
			],
			init=(lambda x: [
			                 x.new_name(1),
			                 x.ns_copy(1, 0),
			                 NewClass(x.eval_label(1),
			                          x.eval_label(4),
			                          x.eval_args(5))
			                ])
		)

		self.statement_inst = Statement(
			"instantiation",
			expression=[
				self.type_def,
				self.label_def,
				AtomicSymbol("="),
				self.expr_def,
				AtomicSymbol(";")
			],
			init=(lambda x: [
			                 x.new_name(1),
			                 VariableNew(x.eval_label(1),
			                             x.eval_type(0)),
			                 VariableAssignment(x.eval_label(1),
			                                    x.eval_expr(3))
			                ])
		)

		self.statement_assign = Statement(
			"assignment",
			expression=[
				self.label_def,
				AtomicSymbol("="),
				self.expr_def,
				AtomicSymbol(";")
			],
			init=(lambda x: [
			                 VariableAssignment(x.eval_label(0),
			                                    x.eval_expr(2))
			                ])
		)

		self.statement_expression = Statement(
			"expression",
			expression=[
				self.expr_def,
				AtomicSymbol(";")
			],
			init=(lambda x: [x.eval_expr(0)])
		)

		self.active_tokens = [
			self.statement_endebug,
			self.statement_include,
			self.statement_codeblock_begin,
			self.statement_codeblock_end,
			self.statement_return,
			self.statement_print,
			self.statement_if,
			self.statement_else_if,
			self.statement_else,
			self.statement_for,
			self.statement_while,
			self.statement_func,
			self.statement_proc,
			self.statement_pless_class,
			self.statement_class,
			self.statement_new,
			self.statement_inst,
			self.statement_assign,
			self.statement_expression
		]
		data=""
		with open(file_name, 'r') as program:
		    data=program.read().replace('\n', '')
	
		self.symbols = Tokenizer(self.splitters, self.end_statements)

		self.symbols.generate_symbols(data)

		self.lines = self.symbols.generate_statements()

	def get_statements(self):
		rv = []
		for num, l in enumerate(self.lines):
			for a in self.active_tokens:
				r = a.match(l)
				if r:
					if a.name == "include":
						t = Parser(r[1][0] + ".ti")
						l = t.get_statements()
						rv.extend(l)
					else:
						rv.append([a,r,[]])
						print("{}: {}\t{}".format(str(num).rjust(4),
						                          a.name.rjust(15),r))
					break

		return rv

