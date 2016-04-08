class FunctionCall():
	def __init__(self, label, arguements):
		self.label = label
		self.arguements = arguements

class IntegerConstant():
	def __init__(self, value):
		self.value = int(value[0][0])
