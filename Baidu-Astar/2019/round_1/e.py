
A = 1
for i in range(100):
	A = (i + 3) * A % (i + 2)
	print(A)
