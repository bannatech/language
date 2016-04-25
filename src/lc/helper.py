
# This function splits a tokenstring by split characters, along with providing
# a way to preserve capturing groups via esc_chars
# An example call would be as follows:
#
# token_split( ["Hello", " ", "(", "Wonderful", " ", "World", ")"],
#              [ ["("], [")"] ],
#              [" "] )
#
#  Would return:
#    [ [ "Hello" ], ["(", "Wonderful", " ", "World", ")" ] ]
def token_split(tokenstring, esc_chars, split_chars, include_splitter=True):
	tokens = []
	tmp = []
	capturing = False
	for x in tokenstring:
		if x in esc_chars[0]:
			capturing = esc_chars[0].index(x)
			tmp.append(x)
		elif x in esc_chars[1]:
			if esc_chars[1][capturing] == x:
				capturing = False
				tmp.append(x)
		elif include_splitter or not x in split_chars or capturing:
			tmp.append(x)

		if x in split_chars and not capturing:
			tokens.append(tmp)
			tmp = []
	if len(tmp) > 0:
		tokens.append(tmp)

	return tokens

def int_to_bytes(number):
	rv = []
	c = 0
	while (number / (0xFF << (8*c))) > 1:
		rv.insert(0, (number & (0xFF << (8*c))) >> (8*c))
		c += 1

	rv.insert(0, (number & (0xFF << (8*c))) >> (8*c))

	return rv

def int_to_word(number):
	rv = [0, 0]

	rv[0] = (number & 0xFF00) >> 8
	rv[1] = number & 0x00FF

	return rv
