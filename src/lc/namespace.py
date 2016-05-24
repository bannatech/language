
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
		self.pop()
		self.ns[0][self.t][1] = tmp
		self.t = None
	
	def copy(self, new_name, name):
		self.ns[self.sc][new_name][1] = self.obj_resolve(name)[1]
	
	# Resolves name into object
	def obj_resolve(self, name):
		rv = None
		for namespace in self.scopes:
			for names in namespace:
				if name in names.keys() and rv == None:
					rv = names[name]
				elif rv != None:
					print("{} was found, but found again".format(name))

		return rv

	def resolve_with_obj(self, obj, name):
		t = self.obj_resolve(obj)
		print(t)

	# Resolves name into scope and address
	def resolve(self, name):
		rv = None
		
		if name in self.ns[0].keys():
			rv = [1, self.ns[0][name][0]]
		elif name in self.ns[-1].keys():
			rv = [0, self.ns[-1][name][0]]
		else:
			print("Out of scope tbi")
		
		return rv
