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
			"int",
			"float",
			"array",
			"object",
			"ptr"
		]
	
		self.number_def    = AtomicSymbol("[0-9]+")
	
		self.type_def      = InclusiveSymbol(self.defined_types)
		self.label_def     = ExclusiveSymbol(self.defined_types +
		                                     self.known_tokens   )
	
		self.paramlist_def = GroupingSymbol( [
		                                      AtomicSymbol("\("),
		                                      AtomicSymbol("\)")
		                                     ] )
	
		self.expr_def = PolySymbol( [
		                             self.label_def,
		                             self.number_def,
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

		self.active_tokens = [
			Statement(
				"codeblock_begin",
				expression=[
					AtomicSymbol("{")
				],
				init=(lambda x: [])
			),
			Statement(
				"codeblock_end",
				expression=[
					AtomicSymbol("}")
				],
				init=(lambda x: [])
			),
			Statement(
				"if",
				expression=[
					AtomicSymbol("if"),
					self.expr_def,
					AtomicSymbol(":")
				],
				init=(lambda x: [x.eval_expr(1)])
			),
			Statement(
				"else",
				expression=[
					AtomicSymbol("else"),
					AtomicSymbol(":")
				],
				init=(lambda x: [])
			),
			Statement(
				"for",
				expression=[
					AtomicSymbol("for"),
					self.expr_def,
					AtomicSymbol(":")
				],
				init=(lambda x: [x.eval_expr(1)])
			),
			Statement(
				"while",
				expression=[
					AtomicSymbol("while"),
					self.expr_def,
					AtomicSymbol(":")
				],
				init=(lambda x: [x.eval_expr(1)])
			),
			Statement(
				"function",
				expression=[
					AtomicSymbol("func"),
					self.label_def,
					self.paramlist_def,
					AtomicSymbol("->"),
					self.type_def,
					AtomicSymbol(":")
				],
				init=(
					lambda x: [
					           x.eval_label(1),
					           x.eval_param(2),
					           x.eval_type(4)
					          ])
			),
			Statement(
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
			),
			Statement(
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
			),
			Statement(
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
			),
			Statement(
				"expression",
				expression=[
					self.expr_def,
					AtomicSymbol(";")
				],
				init=(lambda x: [x.eval_expr(0)])
			)
		]
		data=""
		with open(file_name, 'r') as program:
		    data=program.read().replace('\n', '')
	
		self.symbols = Tokenizer(self.splitters, self.end_statements)

		self.symbols.generate_symbols(data)

		self.lines = self.symbols.generate_statements()

	def get_statements(self):
		rv = []
		for l in self.lines:
			for a in self.active_tokens:
				r = a.match(l)
				if r:
					rv.append([a,r])
					break

		return rv

