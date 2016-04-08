from interpreter import *
if __name__ == "__main__":
	import sys

	t = Interpreter(sys.argv[1])
	for l in t.program:
		for e in l[2]:
			#print("{} : {}".format(e, e.expr))
			pass
