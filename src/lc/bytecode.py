from memonic import *
from helper import *

class PropertyAssignment():
	def __init__(self, ovar, plabel, expression):
		self.ovar = VariableGet(ovar)
		self.label = plabel
		self.expr = expression
	
	def action(self):
		return([
		        self.expr.action(),
		        self.ovar.action(),
		        OP_SETN,
		        self.label.action()
		       ])

class PropertyGet():
	def __init__(self, ovar, plabel):
		self.ovar = VariableGet(ovar)
		self.label = plabel
	
	def action(self):
		return([
		        self.ovar.action(),
		        OP_GETN,
		        self.label.action()
		       ])

class MethodCall():
	def __init__(self, ovar, label, arguements):
		self.ovar  = VariableGet(ovar)
		self.label = label
		self.args  = arguements
	
	def action(self):
		return([
		        self.args.action(),
		        self.ovar.action(),
		        OP_CALLM,
		        self.label.action()
		       ])

class ClassDef():
	def __init__(self, label, args):
		self.label = label
		self.args  = args
	
	def action(self):
		tmp = self.args.action() if self.args != None else 0x0
		return([
		        OP_DECLASS,
		        self.label.action(),
		        tmp
		       ])

class NewClass():
	def __init__(self, toset, label, args):
		self.toset = toset
		self.label = label
		self.args  = args
	
	def action(self):
		return([
		        self.args.action(),
		        OP_NEW,
		        self.label.action(s=True),
		        self.label.action(),
		        OP_DEC,
		        self.label.action(s=True),
		        0x06,
		        self.toset.action(),
		        OP_STV,
		        self.toset.action(s=True),
		        self.toset.action()
		       ])

class VariableNew():
	def __init__(self, label, typed):
		self.label = label
		self.typed = typed
	
	def action(self):
		return([
		        OP_DEC,
		        self.label.action(s=True),
		        self.typed.action(),
		        self.label.action()
		       ])

class VariableAssignment():
	def __init__(self, label, expression):
		self.label = label
		self.expr  = expression
	
	def action(self):
		if self.label.is_property:
			return(PropertyAssignment(self.label.obj,
			                          self.label,
			                          self.expr).action())
		else:
			return([
			        self.expr.action(),
			        OP_STV,
			        self.label.action(s=True),
			        self.label.action()
			       ])

class VariableGet():
	def __init__(self, label):
		self.label = label
	
	def action(self):
		if self.label.is_property:
			return(PropertyGet(self.label.obj, self.label).action())
		else:
			return([
			        OP_LOV,
			        self.label.action(s=True),
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
		if self.label.is_property:
			return(MethodCall(self.label.obj,
			                  self.label,
			                  self.arguements).action())
		else:
			return([
			        self.arguements.action(),
			        OP_CALL,
			        self.label.action(s=True),
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
		        0x0A,
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
		        0x07,
		        self.value
		       ])

class BinaryOp():
	def __init__(self, expr1, op):
		self.vals = [expr1]
		self.op = op
	
	def action(self):
		return([
		        self.vals[1].action(),
		        self.vals[0].action(),
		        self.op.action()
		       ])

class Opcode():
	def __init__(self, opcode):
		self.opcode = opcode
	
	def action(self):
		return(self.opcode)
