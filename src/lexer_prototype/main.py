from parser import *
if __name__ == "__main__":
	import sys

	thing = Parser(sys.argv[1])
	for i in thing.get_statements():
		print(i)
