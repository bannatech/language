from memonic import *
from helper import *

class VariableNew():
	def __init__(self, label, typed):
		self.label = label
		self.typed = typed
	
	def action(self):
		return([
		        OP_DEC,
		        self.label.action(scope=True),
		        self.typed.action(),
		        self.label.action()
		       ])

class VariableAssignment():
	def __init__(self, label, expression):
		self.label = label
		self.expr  = expression
	
	def action(self):
		return([
		        self.expr.action(),
		        OP_STV,
		        self.label.action(scope=True),
		        self.label.action()
		       ])

class VariableGet():
	def __init__(self, label):
		self.label = label
	
	def action(self):
		return([
		        OP_LOV,
		        self.label.action(scope=True),
		        self.label.action()
		       ])

class FunctionDef():
	def __init__(self, label, args, typed):
		self.label = label
		self.args  = args
		self.typed = typed
	
	def action(self):
		tmp = self.args.action() if self.args != None else 0x0
		return([
		        OP_DEFUN,
		        self.label.action(),
		        self.typed.action(),
		        tmp
		       ])

class FunctionCall():
	def __init__(self, label, arguements):
		self.label = label
		self.arguements = arguements
	
	def action(self):
		return([
		        self.arguements.action(),
		        OP_CALL,
		        self.label.action()
		       ])

#TODO: Implement this
class ForLoop():
	def __init__(self, expression):
		self.expr = expression
	
	def action(self):
		return([0])

class SerializeableType():
	def __init__(self, value):
		pass

class StringConstant(SerializeableType):
	def __init__(self, value):
		self.value = []
		for i in value:
			self.value.append(ord(i))

	def action(self):
		return([
		        OP_CTS,
		        int_to_bytes(len(self.value) + 1),
		        0x00,
		        0x09,
		        self.value
		       ])

class IntegerConstant(SerializeableType):
	def __init__(self, value):
		t = int(value[0])
		self.raw = t
		self.value = int_to_bytes(t)
	
	def action(self):
		return([
		        OP_CTS,
		        int_to_bytes(len(self.value) + 1),
		        0x00,
		        0x06,
		        self.value
		       ])

class BinaryOp():
	def __init__(self, expr1, op):
		self.vals = [expr1]
		self.op = op
	
	def action(self):
		return([
		        self.vals[0].action(),
		        self.vals[1].action(),
		        self.op.action()
		       ])

class Opcode():
	def __init__(self, opcode):
		self.opcode = opcode
	
	def action(self):
		return(self.opcode)


