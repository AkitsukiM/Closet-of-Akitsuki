import datetime
import math

isEND = False

n = int(input("No.n Prime Number, n:\n"))
sup = int(n * math.log2(n))

t1 = datetime.datetime.now()

a = [True] * sup
a[0] = False
a[1] = False
a[2] = True
count = 1 # 素数个数计数
k = 3 # 素数列素数指示器
i = 3 # 素数倍乘筛法指示器

while True:
	j = 3
	while j < sup / i:
		a[i * j] = False # 素数倍乘筛法
		j += 2
	while k < (i + 2) * (i + 2):
		if a[k] == True:
			count += 1
		if count == n:
			print(k)
			isEND = True
			break
		k += 2
	if isEND == True: break

	i += 2
	while a[i] == False: i += 2 # 步长为2判断下一个素数

t2 = datetime.datetime.now()
print(t2 - t1)

