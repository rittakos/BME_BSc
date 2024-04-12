import math


# I(p/(p+n), n/(p+n))

P = 242
N = 394

if P == 0 or N == 0:
	I = 0
else:
	p = P / (P + N)
	n = N / (P + N)

	I = -1 * p * math.log2(p) - n * math.log2(n)

print("I = ", I)