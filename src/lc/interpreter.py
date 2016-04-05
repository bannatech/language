from parser import *

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
		pass
	
	def action(self):
		pass

class Arguements(AbstractToken):
	def update(self):
		tokens = []
		tmp = []
		capturing = False
		esc_chars = [["[", "("], ["]", ")"]]
		for x in self.data[1:-1]:
			if x in esc_chars[0]:
				capturing = esc_chars[0].index(x)
				tmp.append(x)
			elif x in esc_chars[1]:
				if esc_chars[1][capturing] == x:
					capturing = False
					tmp.append(x)
			elif x != ",":
				tmp.append(x)
			
			if x == "," and not capturing:
				tokens.append(tmp)
				tmp = []
		tokens.append(tmp)

		for t in tokens:
			self.expr.append(Expression(self.i, t))

	def action(self):
		for i in self.expr:
			i.action()

class Type(AbstractToken):
	def update(self):
		pass
	
	def action(self):
		pass

class Parameters(AbstractToken):
	def update(self):
		tmp = []
		for x in self.data:
			if x != "(" and x != ")" and x != ",":
				tmp.append(x)
			elif x == "," or x == ")":
				t = Type(self.i, tmp[0])
				l = Label(self.i, tmp[1])
				self.expr.append([t, l])
				tmp = []

	def action(self):
		pass

class Expression(AbstractToken):
	def update(self):
		pass
	
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

	def loop_until_ready(self):
		for self.line in self.program:
			self.line[2].action()

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

