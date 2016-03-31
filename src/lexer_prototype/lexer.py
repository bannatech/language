import re

class AtomicSymbol():
	def __init__(self, symbol):
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
		rv = []
		r = self.symbols[0].match(tokenstring, index)
		if r[0]:
			rv.extend(r[1])
			index = r[0]
			while index < len(tokenstring):
				r = self.symbols[1].match(tokenstring, index)
				if r[0]:
					index = r[0]
					rv.extend(r[1])
					break
				else:
					rv.append(tokenstring[index])
					index += 1

		return [index, rv] if len(rv) > 0 else [False, None]

class Statement():
	def __init__(self, name, expression=[]):
		self.name = name
		self.expr = expression
	
	def match(self, tokenstring):
		rv = []
		index = 0
		for e in self.expr:
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

	def generate_statements(self):
		rv = []
		tmp = []
		for i in self.symbols:
			t = i.strip()
			if len(t) > 0:
				tmp.append(t)
	
			for x in self.statement_delim:
				if x == i:
					rv.append(tmp)
					tmp = []

		return rv

def lex(file_name):
	splitters = [
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
	end_statements = [
		":",
		";",
		"{",
		"}"
	]

	known_tokens = [
		"if",
		"for",
		"func"
	]

	defined_types = [
		"int",
		"float",
		"array"
	]

	number_def    = AtomicSymbol("[0-9]+")

	type_def      = InclusiveSymbol(defined_types)
	label_def     = ExclusiveSymbol(defined_types + known_tokens)

	paramlist_def = GroupingSymbol( [
	                                 AtomicSymbol("\("),
	                                 AtomicSymbol("\)")
	                                ] )

	expr_def = PolySymbol( [
	                        label_def,
	                        number_def,
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

	active_tokens = [
		Statement(
			"codeblock_begin",
			expression=[
				AtomicSymbol("{")
			]
		),
		Statement(
			"codeblock_end",
			expression=[
				AtomicSymbol("}")
			]
		),
		Statement(
			"if",
			expression=[
				AtomicSymbol("if"),
				expr_def,
				AtomicSymbol(":")
			]
		),
		Statement(
			"for",
			expression=[
				AtomicSymbol("for"),
				expr_def,
				AtomicSymbol(":")
			]
		),
		Statement(
			"function",
			expression=[
				AtomicSymbol("func"),
				label_def,
				paramlist_def,
				AtomicSymbol("->"),
				type_def,
				AtomicSymbol(":")
			]
		),
		Statement(
			"instantiation",
			expression=[
				type_def,
				label_def,
				AtomicSymbol("="),
				expr_def,
				AtomicSymbol(";")
			]
		),
		Statement(
			"assignment",
			expression=[
				label_def,
				AtomicSymbol("="),
				expr_def,
				AtomicSymbol(";")
			]
		),
		Statement(
			"expression",
			expression=[
				expr_def,
				AtomicSymbol(";")
			]
		)
	]
	data=""
	with open(file_name, 'r') as program:
	    data=program.read().replace('\n', '')

	symbols = Tokenizer(splitters, end_statements)

	symbols.generate_symbols(data)

	lines = symbols.generate_statements()
	rv = []
	for l in lines:
		for a in active_tokens:
			r = a.match(l)
			if r:
				rv.append((a.name,r))
				break
	
	return rv

if __name__ == "__main__":
	import sys
	for i in lex(sys.argv[1]):
		print(i)
