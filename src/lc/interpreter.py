from parser import *
from lexer import *
from bytecode import *
from memonic import *
from helper import *
from namespace import *

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
		f = lambda y, x: y(y, x[0]) if type(x) is list else x
		self.data = f(f, self.data)

		self.is_property = False
		self.parent      = None
		self.name        = None

		names = self.data.rsplit(".", 1)

		if len(names) > 1:
			self.is_property = True
			self.parent = Label(self.i, names[0])

			self.name = names[1]

			t = self.i.ns.resolve_with_obj(self.parent, self.name)
			self.expr = t[0]
		else:
			self.name = names[0]
			t = self.i.ns.resolve(self.name)
			self.scope = t[0]
			self.expr = t[1]

	def action(self, s=False):
		if s:
			return(self.scope)
		else:
			print(self.name, self.expr)
			return(int_to_word(self.expr))

class Arguements(AbstractToken):
	def update(self):
		tokens = token_split(self.data[1:],
		                     [["[", "("], ["]", ")"]],
		                     [","], include_splitter = False)
		for t in tokens:
			self.expr.insert(0, Expression(self.i, t))

	def action(self):
		rv = []
		for i in self.expr:
			rv.append([i.action(), OP_ARGB])
		return rv

class Type(AbstractToken):
	def update(self):
		n = None
		for x, t in enumerate(self.i.p.defined_types):
			r = t.match(self.data, 0)
			if r[0]:
				n = x

		if n == None:
			print("INVALID TYPE")

		self.expr = n

	def action(self):
		return(self.expr)

class Parameters(AbstractToken):
	def update(self):
		tmp = []
		for x in self.data:
			if x != ",":
				tmp.append(x)
			elif x == ",":
				self.i.new_name_token(tmp[1:])
				t = Type(self.i, tmp[:-1])
				l = Label(self.i, tmp[1:])
				self.expr.append([t, l])
				tmp = []

		if len(tmp) > 0:
			self.i.new_name_token(tmp[1:])
			t = Type(self.i, tmp[:-1])
			l = Label(self.i, tmp[1:])
			self.expr.append([t, l])

	def action(self):
		types = list(map(lambda x: x[0].action(), self.expr))
		return([
		        int_to_bytes(len(types)),
		        0x0,
		        types
		       ])


class Expression(AbstractToken):
	def update(self):
		self.expr = None
		self.operators = [
			["+", Opcode(OP_ADD)],
			["-", Opcode(OP_SUB)],
			["*", Opcode(OP_MULT)],
			["/", Opcode(OP_DIV)],
			["==", Opcode(OP_EQ)],
			["!=", Opcode(OP_NEQ)],
			[">", Opcode(OP_GTHAN)],
			["<", Opcode(OP_LTHAN)],
			[">=", Opcode(OP_GTHAN_EQ)],
			["=<", Opcode(OP_LTHAN_EQ)]
		]

		self.operator_names = list(map(lambda x: x[0], self.operators))

		self.func_call = Statement(
			"func_call",
			expression=[
				self.i.p.label_def,
				self.i.p.paramlist_def,
			],
			init=(lambda x,y: FunctionCall(Label(x,y[0]),
			                               Arguements(x,y[1:])))
		)
		self.subexpr = Statement(
			"subexpr",
			expression=[
				self.i.p.paramlist_def
			],
			init=(lambda x,y: Expression(x, y[1:-1]))
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
			init=(lambda x,y: VariableGet(Label(x, y)))
		)

		self.identifiers = [
			self.func_call,
			self.subexpr,
			self.integer,
			self.label
		]

		self.group_char = [["[", "("], ["]", ")"]]
		t = token_split(self.data,
		                self.group_char,
		                self.operator_names)
		if len(t) == 0:
			t = self.data
		if len(t) > 2:
			print("Expression Error ({})".format(self.data))

		next_op = False
		for thing in t:
			if thing[-1] in self.operator_names:
				ex = thing[:-1]
				op = thing[-1]
			else:
				ex = thing
				op = None

			obj = None
			if ex[0][0] == "\0":
				obj = StringConstant(ex[0][2:-1])
			else:
				for i in self.identifiers:
					r = i.match(ex)
					if r:
						obj = i.action(self.i, ex)

			if obj == None:
				print("Unknown Expression Error ({})".format(ex))
				break

			if next_op:
				self.expr.vals.append(obj)
				next_op = False
			else:
				if op in self.operator_names:
					index = self.operator_names.index(op)
					self.expr = BinaryOp(obj, self.operators[index][1])
					next_op = True
				else:
					self.expr = obj

	def action(self):
		return(self.expr.action());

class Directive():
	def __init__(self, function, conditional):
		self.action = function
		self.cond = conditional

class Interpreter():
	def __init__(self, filename):
		self.p = Parser(filename)
		self.ns = Namespace()

		self.program = self.p.get_statements()

		self.line = (None, None)

		self.ln   = 0

		self.cur_directives = []

		self.directives = [self.cur_directives]

		#initalizes values n' stuff
		for self.ln, self.line in enumerate(self.program):
			t = self.line[0].action(self)
			for i in t:
				if i != False:
					self.line[2].append(i)

	def nxt(self, n):
		if len(self.program) <= self.ln + n:
			return self.program[self.ln]
		return self.program[self.ln + n]

	def ns_persist(self, index):
		self.ns.target(self.line[1][index][0])
		return False
	
	def ns_save(self):
		self.ns.release()
		return False
	
	def ns_copy(self, key, index):
		self.ns.copy(self.line[1][key][0], self.line[1][index][0])
		return False

	def new_name(self, index):
		self.new_name_token(self.line[1][index])
		return False

	def new_name_token(self, token):
		f = lambda y, x: y(y, x[0]) if type(x) is list else x

		self.ns.name_dec(f(f, token))

	def push_scope(self):
		self.ns.push()
		return False
	
	def pop_scope(self):
		self.ns.pop()
		return False

	def inc_scope(self):
		self.ns.inc_scope()
		return False

	def dec_scope(self):
		self.ns.dec_scope()
		return False

	def push_directives(self):
		self.directives.append(self.cur_directives)
		self.cur_directives = []
		return False

	def pop_directives(self):
		t = self.directives.pop()
		for x in t:
			if x.cond(self):
				self.cur_directives.append(x)
			else:
				r = x.action(self)
				for i in r:
					if i != False:
						self.line[2].append(i)

		return False

	def add_directive(self, directive, cond=(lambda x: False)):
		d = Directive(directive, cond)
		self.cur_directives.append(d)
		return False

	def op(self, opcode):
		return(Opcode(opcode))

	def eval_label(self, index):
		return(Label(self, self.line[1][index]))

	def eval_args(self, index):
		return(Arguements(self, self.line[1][index]))

	def eval_type(self, index):
		return(Type(self, self.line[1][index]))

	def eval_param(self, index):
		return(Parameters(self, self.line[1][index]))

	def eval_expr(self, index):
		return(Expression(self, self.line[1][index]))

