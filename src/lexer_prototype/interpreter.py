from parser import *

class Interpreter():
	def __init__(self, filename):
		self.p = Parser(filename)

		self.program = self.p.get_statements()

		self.line = (None, None)

		for self.line in self.program:
			self.line[0].action(self)

	def eval_label(self, index):
		return(self.line)

	def eval_args(self, index):
		return(self.line)

	def eval_type(self, index):
		return(self.line)

	def eval_param(self, index):
		return(self.line)

	def eval_expr(self, index):
		return(self.line)

