import re

class AtomicSymbol():
	def __init__(self, symbol):
		self.raw = symbol
		self.symbol = re.compile(symbol)
	
	def match(self, tokenstring, index):
		return [index + 1, [tokenstring[index]]]                          \
		       if self.symbol.match(tokenstring[index]) else [False, None]

class CompoundSymbol():
	def __init__(self, symbols):
		for x, i in enumerate(symbols):
			if type(i) is str:
				symbols[x] = AtomicSymbol(i)

		self.symbols = symbols

	def match(self, tokenstring, index):
		rv = []
		for i in self.symbols:
			r = i.match(tokenstring, index)
			if r[0]:
				rv = r[1]
				index = r[0]
				break

		return [index, rv] if len(rv) > 0 else [False, None]

class InclusiveSymbol(CompoundSymbol):
	def match(self, tokenstring, index):
		rv = []
		for i in self.symbols:
			r = i.match(tokenstring, index)
			if r[0]:
				rv = r[1]
				index = r[0]
				break

		return [index, rv] if len(rv) > 0 else [False, None]

class ExclusiveSymbol(CompoundSymbol):
	def match(self, tokenstring, index):
		rv = [tokenstring[index]]
		for i in self.symbols:
			r = i.match(tokenstring, index)
			if r[0]:
				rv = []

		return [index + 1, rv] if len(rv) > 0 else [False, None]

class PolySymbol():
	def __init__(self, symbols, terminator=[]):
		self.symbols = symbols
		self.terminator = terminator
	
	def match(self, tokenstring, index):
		rv = []
		while index+1 < len(tokenstring):
			for t in self.terminator:
				r = t.match(tokenstring, index)
				if r[0]:
					break
			v = False
			for s in self.symbols:
				r = s.match(tokenstring, index)
				if r[0]:
					rv.extend(r[1])
					index = r[0]
					v = True
					break
			if not v:
				break
			
		return [index, rv] if len(rv) > 0 else [False, None]

class GroupingSymbol(PolySymbol):
	def match(self, tokenstring, index):
		found = False
		rv = []
		r = self.symbols[0].match(tokenstring, index)
		if r[0]:
			index = r[0]
			ignore = 0
			while index < len(tokenstring):
				r = self.symbols[0].match(tokenstring, index)
				if r[0]:
					ignore += 1
					rv.extend(r[1])
					index = r[0]
				else:
					r = self.symbols[1].match(tokenstring, index)
					if r[0]:
						if ignore > 0:
							ignore -= 1
							rv.extend(r[1])
							index = r[0]
						else:
							index = r[0]
							found = True
							break
					else:
						rv.append(tokenstring[index])
						index += 1

		return [index, rv] if found else [False, None]

class Statement():
	def __init__(self, name, expression=[], init=None):
		self.name   = name
		self.expr   = expression
		self.action = init
	
	def match(self, tokenstring):
		rv = []
		index = 0
		for e in self.expr:
			if index >= len(tokenstring):
				return False
			r = e.match(tokenstring, index)
			if r[0]:
				rv.append(r[1])
				index = r[0]
			else:
				break

		return rv if index == len(tokenstring) else False

class Tokenizer():
	def __init__(self, symbol_delim, statement_delim):
		self.symbol_delim    = symbol_delim
		self.statement_delim = statement_delim

		self.symbols = []

	# Based off of self.symbol_delim, and string literals, break code into bits
	def generate_symbols(self, raw_string):
		tmp = ""

		#Thing that keeps string literals in tact.
		in_string = False
		no_escape = True
		for char in raw_string:
			if char == "\\":
				no_escape = False
			if char == "\"" and no_escape:
				if in_string:
					tmp = tmp + char
					self.symbols.append(tmp)
					tmp = ""
					in_string = False
				else:
					self.symbols.append(tmp)
					tmp = ""
					tmp = "\0" + tmp + char
					in_string = True
			else:
				tmp = tmp + char
				if char != "\\" and no_escape == False:
					no_escape = True

		self.symbols.append(tmp)

		# Go and split them codes into symbols!
		for i in self.symbol_delim:
			tmp = []
			for x in self.symbols:
				if len(x) > 0:
					# This checks for the work the above code did
					# It prevents string literals from being subdivided
					if x[0] != "\0":
						tmp.extend(re.split("({})".format(i), x))
					else:
						tmp.append(x)
			self.symbols = tmp

	def generate_statements(self, raw):
		rv = []
		tmp = []

		self.generate_symbols(raw)

		for i in self.symbols:
			t = i.strip()
			if len(t) > 0:
				tmp.append(t)
	
			for x in self.statement_delim:
				if x == i:
					rv.append(tmp)
					tmp = []

		return rv

