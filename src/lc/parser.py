from lexer import *
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
			"if",
			"else",
			"for",
			"while",
			"func"
		]
	
		self.defined_types = [
			"void",
			"_addr",
			"_type",
			"_plist",
			"_sub",
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
	
		self.int_def       = AtomicSymbol("[0-9]+")
	
		self.type_def      = InclusiveSymbol(self.defined_types)
		self.label_def     = ExclusiveSymbol(self.defined_types +
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
		                             AtomicSymbol("'")
		                            ], terminator=[
		                                           AtomicSymbol(";"),
		                                           AtomicSymbol(":")
		                                          ])

		self.statement_codeblock_begin = Statement(
				"codeblock_begin",
				expression=[
					AtomicSymbol("{")
				],
				init=(lambda x: [])
			)

		self.statement_codeblock_end = Statement(
				"codeblock_end",
				expression=[
					AtomicSymbol("}")
				],
				init=(lambda x: [])
			)

		self.statement_if = Statement(
				"if",
				expression=[
					AtomicSymbol("if"),
					self.expr_def,
					AtomicSymbol(":")
				],
				init=(lambda x: [x.eval_expr(1)])
			)

		self.statement_else = Statement(
				"else",
				expression=[
					AtomicSymbol("else"),
					AtomicSymbol(":")
				],
				init=(lambda x: [])
			)

		self.statement_for = Statement(
				"for",
				expression=[
					AtomicSymbol("for"),
					self.expr_def,
					AtomicSymbol(":")
				],
				init=(lambda x: [x.eval_expr(1)])
			)

		self.statement_while = Statement(
				"while",
				expression=[
					AtomicSymbol("while"),
					self.expr_def,
					AtomicSymbol(":")
				],
				init=(lambda x: [x.eval_expr(1)])
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
					           x.eval_label(1),
					           x.eval_param(2),
					           x.eval_type(5)
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
					             x.eval_type(0),
					             x.eval_label(1),
					             x.eval_expr(3)
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
				                 x.eval_label(0),
				                 x.eval_expr(2)
				                ])
			)

		self.statement_call = Statement(
				"func_call",
				expression=[
					self.label_def,
					self.paramlist_def,
					AtomicSymbol(";")
				],
				init=(lambda x: [
				                 x.eval_label(0),
				                 x.eval_args(1)
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
			self.statement_codeblock_begin,
			self.statement_codeblock_end,
			self.statement_if,
			self.statement_else,
			self.statement_for,
			self.statement_while,
			self.statement_func,
			self.statement_inst,
			self.statement_assign,
			self.statement_call,
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
					rv.append([a,r])
					break

		return rv

