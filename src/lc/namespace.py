
class Namespace():
	# Namespace data structure:
	# {
	#  "<name>"   : [ <index, int>, None ],
	#  "<object>" : [ <index, int>, {"property" : [ <index, int>, None ]}
	# }
	def __init__(self):
		self.sc = 0
		self.ns = [{}]
		self.scopes = [self.ns]
		self.stack  = []

		self.t = None
		self.tShared = []

	def name_dec(self, name):
		if name in self.ns[self.sc].keys():
			print("Declaring name that already exists!")
		else:
			self.ns[self.sc][name] = [len(self.ns[self.sc].keys()) + 1, None]

	def inc_scope(self):
		self.ns.append({})
		self.sc += 1

	def dec_scope(self):
		self.ns.pop()
		self.sc -= 1
	
	def push(self):
		self.stack.append([self.sc, self.ns])
		self.sc = 0
		self.ns = [{}]

	def pop(self):
		tmp = self.stack.pop()
		self.sc = tmp[0]
		self.ns = tmp[1]

	# New namespace
	def target(self, name):
		self.t = name
		self.push()

		self.sc = 0
		self.ns = [{}]

	# Releases target
	def release(self):
		tmp = self.ns[0]
		for name in self.tShared:
			self.ns[self.sc][name][1] = tmp

		self.pop()
		self.ns[0][self.t][1] = tmp
		self.t = None
		self.tShared = []
	
	def copy(self, new_name, name):
		if self.t == name:
			self.ns[self.sc][new_name][1] = self.ns[0]
		else:
			self.ns[self.sc][new_name][1] = self.obj_resolve(name)

	def is_obj(self, name):
		return False	

	# Resolves name into object
	def obj_resolve(self, name):
		rv = None
		if name in self.ns[0].keys():
			rv = self.ns[0][name][1]
		else:
			for namespace in self.scopes:
				for names in namespace:
					if name in names.keys() and rv == None:
						rv = names[name][1]
					elif rv != None:
						print("{} was found, but found again".format(name))

		return rv

	def resolve_with_obj(self, parent, name):
		rv = None

		if parent.is_property == True:
			obj = self.resolve_with_obj(parent.parent, parent.name)
		else:
			obj = self.obj_resolve(parent.name)

		if type(obj) == dict:
			if name in obj:
				rv = obj[name]
		elif type(obj) == list and obj[1] != None:
			if name in obj[1]:
				rv = obj[1][name]
		elif type(obj) == type(None):
			print("Object referenced before definition: {}.{}".format(
				parent.name, name)
			)

		return rv

	# Resolves name into scope and address
	def resolve(self, name):
		rv = None
		if name in self.ns[0].keys():
			rv = [1, self.ns[0][name][0]]
		elif name in self.ns[-1].keys():
			rv = [0, self.ns[-1][name][0]]
		else:
			for x, names in enumerate(self.scopes):
				if name in names[0].keys():
					rv = [((x + 1) << 1) + 1, names[0][name][0]]
				elif name in names[-1].keys():
					rv = [((x + 1) << 1) + 0, names[-1][name][0]]
		return rv
