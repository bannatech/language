from interpreter import *

def tobytearray(l, n, ba):
	for i in l:
		if type(i) is list:
			ba = tobytearray(i, n, ba)
			n += 1
		else:
			if type(i) is bytes:
				i = int.from_bytes(i, byteorder='big')
			if type(i) is int:
				ba.append(i)

			print((" "*n)+hex(i))

	return(ba)


if __name__ == "__main__":
	import sys

	if len(sys.argv) != 3:
		print("useage: {} input_file output_file".format(sys.argv[0]))
		sys.exit(1)

	itr = Interpreter(sys.argv[1])
	
	out = open(sys.argv[2], "wb")

	rv = []
	for l in itr.program:
		for e in l[2]:
			rv.append(e.action())

	program = bytearray()
	program = tobytearray(rv, 0, program)

	out.write(program)
	out.close()
