from parser import *
from lexer import *
from bytecode import *
from memonic import *

def token_split(tokenstring, esc_chars, split_chars, include_splitter=True):
	tokens = []
	tmp = []
	capturing = False
	for x in tokenstring:
		if x in esc_chars[0]:
			capturing = esc_chars[0].index(x)
			tmp.append(x)
		elif x in esc_chars[1]:
			if esc_chars[1][capturing] == x:
				capturing = False
				tmp.append(x)
		elif include_splitter or not x in split_chars or capturing:
			tmp.append(x)

		if x in split_chars and not capturing:
			tokens.append(tmp)
			tmp = []
	if len(tmp) > 0:
		tokens.append(tmp)

	return tokens

class AbstractToken():
	def __init__(self, interpreter_instance, raw_data):
		self.data = raw_data
		self.expr = []
		self.i    = interpreter_instance
		self.line = self.i.line
		self.update()
	
	def update(self):
		pass
	
	def action(self):
		pass

class Label(AbstractToken):
	def update(self):
		self.expr.append(self.data)
	
	def action(self):
		pass

class Arguements(AbstractToken):
	def update(self):
		tokens = token_split(self.data[1:-1],
		                     [["[", "("], ["]", ")"]],
		                     [","], include_splitter = False)

		for t in tokens:
			self.expr.append(Expression(self.i, t))

	def action(self):
		for i in self.expr:
			i.action()

class Type(AbstractToken):
	def update(self):
		n = None
		for x, t in enumerate(self.i.p.defined_types):
			r = t.match(self.data, 0)
			if r[0]:
				n = x

		if n == None:
			print("INVALID TYPE")

		self.expr.append(n)

	def action(self):
		pass

class Parameters(AbstractToken):
	def update(self):
		tmp = []
		for x in self.data:
			if x != "(" and x != ")" and x != ",":
				tmp.append(x)
			elif x == "," or x == ")":
				t = Type(self.i, tmp[:-1])
				l = Label(self.i, tmp[1:])
				self.expr.append([t, l])
				tmp = []

	def action(self):
		pass

class Expression(AbstractToken):
	def update(self):
		self.func_call = Statement(
			"func_call",
			expression=[
				self.i.p.label_def,
				self.i.p.paramlist_def,
			],
			init=(lambda x,y: FunctionCall(Label(x,y[0]),
			                              Arguements(x,y[1])))
		)
		self.integer = Statement(
			"integer",
			expression=[
				self.i.p.int_def
			],
			init=(lambda x,y: IntegerConstant(y))
		)
		self.label = Statement(
			"label",
			expression=[
				self.i.p.label_def
			],
			init=(lambda x,y: Label(x, y))
		)

		self.identifiers = [
			self.func_call,
			self.integer,
			self.label
		]

		self.operators = [
			["+", OP_ADD],
			["-", OP_SUB],
			["*", OP_MULT],
			["/", OP_DIV],
			["==", OP_EQ],
			[">", OP_GTHAN],
			["<", OP_LTHAN],
			[">=", OP_GTHAN_EQ],
			["=<", OP_LTHAN_EQ]
		]
		self.operator_names = map(lambda x: x[0], self.operators)

		self.group_char = [["[", "("], ["]", ")"]]

		t = token_split(self.data,
		                self.group_char,
		                self.operator_names)

		if len(t) == 0:
			t = self.data

		subexpr = []
		for n,x in enumerate(t):
			if x[-1] in self.operator_names:
				subexpr.append(
					self.operators[ self.operator_names.index(x[-1]) ][1])
				d = x[:-1]
			else:
				d = x

			if d[0] == "(":
				subexpr.append(Expression(self.i, d[1:-1]))
			else:
				for o in self.identifiers:
					r = o.match(d)
					if r:
						subexpr.append(o.action(self.i, r))
			if len(subexpr) == 3:
				self.expr.append(subexpr)
				self.subexpr = []

		if len(subexpr) > 0:
			self.expr.append(subexpr)

		print(self.expr)

	def action(self):
		pass

class Interpreter():
	def __init__(self, filename):
		self.p = Parser(filename)

		self.program = self.p.get_statements()

		self.line = (None, None)

		self.contex = {}

		#initalizes values n' stuff
		for self.line in self.program:
			self.line.append(self.line[0].action(self))

	def eval_label(self, index):
		return(Label(self, self.line[1][index][0]))

	def eval_args(self, index):
		return(Arguements(self, self.line[1][index]))

	def eval_type(self, index):
		return(Type(self, self.line[1][index]))

	def eval_param(self, index):
		return(Parameters(self, self.line[1][index]))

	def eval_expr(self, index):
		return(Expression(self, self.line[1][index]))

