# https://oi.edu.pl/en/archive/pa/2011/plo
# Link is dead, this is only tested on the sample input

N, M = map(int, input().split())

X = [0] * (N + 1)
Y = [0] * (N + 1)
R = [0] * (N + 1)
T = [0] * (N + 1)
L = [0] * (N + 1)
B = [0] * (N + 1)

X[1] = 1
Y[1] = 1
R[1] = 1
T[1] = 1

for i in range(2, N + 1):
    X[i] = X[i - 1] - Y[i - 1]
    Y[i] = X[i - 1] + Y[i - 1]
    R[i] = max(R[i - 1], X[i] + T[i - 1])
    T[i] = max(T[i - 1], Y[i] - L[i - 1])
    L[i] = min(L[i - 1], X[i] + B[i - 1])
    B[i] = min(B[i - 1], Y[i] - R[i - 1])


def d(x, y, n):
    if x < L[n] or x > R[n]:
        return []
    if y < B[n] or y > T[n]:
        return []
    if n == 1:
        if y <= x:
            return [x + y]
        else:
            return []
    return d(x, y, n - 1) + [2**n - k for k in d(Y[n] - y, x - X[n], n - 1)]


for j in range(M):
    x, y = map(int, input().split())
    res = []
    if (x + y) % 2 == 0:
        x, y = (x + y) // 2, (y - x) // 2

        res = d(x, y, N)
    print(' '.join(map(str, [len(res)] + res)))
