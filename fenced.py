import random

def main():
    def nd(r, c):
        return r * M + c

    def find(x):
        return x if P[x] == x else find(P[x])

    def merge(x, y):
        X = find(x)
        Y = find(y)
        if X == Y:
            return False
        P[X] = P[Y] = P[x] = P[y] = X if random.random() < 0.5 else Y
        return True

    A, B, N, M = map(int, input().split())

    VA = [0] * (N + 1)
    HA = [0] * (M + 1)

    for i in range(N):
        VA[i] = int(input())
    
    for j in range(M):
        HA[j] = int(input())

    VA.sort()
    for i in range(N):
        VA[i] = VA[i + 1] - VA[i]
    VA[N] = B - VA[N]

    HA.sort()
    for i in range(M):
        HA[i] = HA[i + 1] - HA[i]
    HA[M] = A - HA[M]

    VA.sort()
    HA.sort()
    N += 1
    M += 1

    P = [0] * (N * M)
    for i in range(N * M):
        P[i] = i
    
    result = 0
    vi = 0
    hi = 0
    while vi < N or hi < M:
        if hi == M or (vi < N and VA[vi] < HA[hi]):
            for i in range(M - 1):
                if merge(nd(vi, i), nd(vi, i + 1)):
                    result += VA[vi]
            vi += 1
        else:
            for i in range(N - 1):
                if merge(nd(i, hi), nd(i + 1, hi)):
                    result += HA[hi]
            hi += 1
    
    print(result)

main()
