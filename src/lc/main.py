from interpreter import *
def tobytearray(l, n, ba):
	for i in l:
		if type(i) is list:
			n += 1
			ba = tobytearray(i, n, ba)
		else:
			print((" "*n)+hex(i))
			ba.append(i)

	return(ba)

	
if __name__ == "__main__":
	import sys

	if len(sys.argv) != 3:
		print("useage: {} input_file output_file".format(sys.argv[0]))
		sys.exit(1)

	itr = Interpreter(sys.argv[1])
	
	out = file(sys.argv[2], "w")

	rv = []
	for l in itr.program:
		for e in l[2]:
			rv.append(e.action())

	program = bytearray()
	program = tobytearray(rv, 0, program)

	out.write(program)
