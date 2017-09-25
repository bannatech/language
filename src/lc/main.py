#!/usr/bin/python3

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

	return(ba)

def printb(l):
	if type(l) is list:
		for i in l:
			printb(i)
	else:
		print(" "+hex(l), end="")

def write_out(output_file):
	out = open(output_file, "wb")

	print("\nTO BYTES\n")

	rv = []

	for n, l in enumerate(itr.program):
		print("{}: {} <= ".format(str(n).rjust(4),
		                          l[0].name.rjust(15),
		                          l[1]),
		                          end="")

		for e in l[2]:
			t = e.action()
			printb(t)
			rv.append(t)

		print()

	program = bytearray()
	program = tobytearray(rv, 0, program)

	out.write(program)
	out.close()

if __name__ == "__main__":
	import sys

	if len(sys.argv) != 3:
		print("useage: {} input_file output_file".format(sys.argv[0]))
		sys.exit(1)

	itr = Interpreter(sys.argv[1])

	if itr.success:
		write_out(sys.argv[2])

