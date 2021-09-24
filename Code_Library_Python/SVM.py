import sys
import numpy
import random
import datetime
import time
import matplotlib.pyplot as plt

# 初始化平面散点及其标签 ----- ----- ----- ----- ----- #
N = 25
X_origin = numpy.zeros(N, dtype = int)
for i in range(N):
    while True:
        temp = random.randint(1, 100) # 随机生成[1, 100]的数
        if temp not in X_origin:
            X_origin[i] = temp
            break

X = numpy.vstack(((X_origin - 1) % 10 + 1, (X_origin - 1) // 10 + 1)) # 转换成平面散点
Y = X[0, ...] * X[1, ...] # 计算乘积
for i in range(N): # 计算标签
    if Y[i] < 25:
        Y[i] = -1
    else:
        Y[i] = 1

# print(X)
# print(Y)

t1 = datetime.datetime.now()

# 初始化A ----- ----- ----- ----- ----- #
A = numpy.ones(N)
S = numpy.dot(A, Y)
if N == S or N == -S:
    sys.exit()
for i in range(N):
    if Y[i] == -1: A[i] = 2 / (N - S) # (N - S) / 2 * (-1)
    else: A[i] = 2 / (N + S) # (N + S) / 2 * (1)

print(A)

# 初始化其他 ----- ----- ----- ----- ----- #
C = 25
W = X[..., 0] * 0
B = 0
s = 0
t = 1
plt.ion()
fig1 = plt.figure(1)

def K(x, y):
    return numpy.dot(x, y)

def refdot(para_A, para_B, para_C, x_min, x_max, y_min, y_max): # para_A * x + para_B * y + para_C = 0
    x1 = x_min
    y1 = (-para_C - x1 * para_A) / para_B
    if y1 < y_min:
        y1 = y_min
        x1 = (-para_C - y1 * para_B) / para_A
    elif y1 > y_max:
        y1 = y_max
        x1 = (-para_C - y1 * para_B) / para_A
    x2 = x_max
    y2 = (-para_C - x2 * para_A) / para_B
    if y2 < y_min:
        y2 = y_min
        x2 = (-para_C - y2 * para_B) / para_A
    elif y2 > y_max:
        y2 = y_max
        x2 = (-para_C - y2 * para_B) / para_A
    return [x1, x2, y1, y2]

def pltdraw(isfinished):
    plt.clf()

    temp1 = fig1.add_subplot(1, 1, 1)
    temp1.scatter([0, 0, 11, 11], [0, 11, 0, 11], c = "#000000", marker = "+", alpha = 0.5)
    for i in range(N):
        if i == s or i == t:
            if Y[i] == -1:
                temp1.scatter(X[0, i], X[1, i], c = "#FF0000", marker = "x")
            else:
                temp1.scatter(X[0, i], X[1, i], c = "#000000", marker = "x")
        elif Y[i] == -1:
            temp1.scatter(X[0, i], X[1, i], c = "#FF0000")
        else:
            temp1.scatter(X[0, i], X[1, i], c = "#000000")
    line_refdot = refdot(W[0], W[1], B, 0, 11, 0, 11)
    temp1.plot([line_refdot[0], line_refdot[1]], [line_refdot[2], line_refdot[3]], c = "#0000FF")

    if isfinished == 0:
        plt.pause(0.01)
    else:
        plt.ioff()
        plt.show()

# 更新A ----- ----- ----- ----- ----- #
count = 0

while True:
    # 更新W
    W = W * 0.0
    for i in range(N):
        W = W + A[i] * Y[i] * X[..., i]
    # 更新B
    Bs = Y[s] - K(W, X[..., s])
    Bt = Y[t] - K(W, X[..., t])
    B = (Bs + Bt) / 2
    pltdraw(0)
    # 更新判断
    needupdate_s = -1;
    needupdate_t = [];
    E_max = 0;
    for i in range(N):
        # 1.001和0.999是为了解决精度误差的问题
        KB = K(W, X[..., i]) + B
        if (A[i] > 0 and Y[i] * KB > 1.001) or (A[i] < C and Y[i] * KB < 0.999) \
            or ((A[i] == 0 or A[i] == C) and (Y[i] * KB < 1.001 and Y[i] * KB > 0.999)):
                if abs(KB - Y[i]) >= E_max:
                    needupdate_s = i
                    E_max = abs(KB - Y[i])
        if A[i] != 0 and A[i] != C:
            needupdate_t.append(i)

    if needupdate_s == -1:
        break
    else:
        s = int(needupdate_s)
        if s in needupdate_t: needupdate_t.remove(s);
        t = needupdate_t[random.randint(0, len(needupdate_t) - 1)] # 随机选一项

    # 更新A[s], A[t]
    L = 0
    H = C
    if Y[s] != Y[t]:
        if A[t] - A[s] > L: L = A[t] - A[s]
        if C + A[t] - A[s] < H: H = C + A[t] - A[s]
    else:
        if A[t] + A[s] - C > L: L = A[t] + A[s] - C
        if A[t] + A[s] < H: H = A[t] + A[s]
    Es = K(W, X[..., s]) + B - Y[s]
    Et = K(W, X[..., t]) + B - Y[t]
    eta = K(X[..., s], X[..., s]) + K(X[..., t], X[..., t]) - 2 * K(X[..., s], X[..., t])
    At_new = A[t] + Y[t] * (Es - Et) / eta
    if At_new > H: At_new = H
    if At_new < L: At_new = L
    As_new = A[s] + Y[s] * Y[t] * (A[t] - At_new)
    A[s] = As_new
    A[t] = At_new

    # 计数更新次数
    count = count + 1
    print("No.", count, sep = "")
    print(A)

t2 = datetime.datetime.now()
print(t2 - t1)

# 输出 ----- ----- ----- ----- ----- #
print(X)
print(Y)
print(W)
print(B)

pltdraw(1)
