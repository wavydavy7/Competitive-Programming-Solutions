class Node:
    def __init__(self, covers = 0, coverables = 0, points = 0):
        self.covers = covers
        self.coverable = coverables
        self.points = points



def comb(x, y):
    ep = min(x.coverables, y.covers)
    return Node(
        covers = x.covers + y.covers - ep, 
        coverables = x.coverables + y.coverables - ep,
        points = x.points + y.points + ep
        )
MAXN = 1 << 17
H = [Node()] * (MAXN * 2)

def fix(x):
    while x != 1:
        x //= 2
        H[x] = comb(H[x * 2], H[x * 2 + 1])

def solve(A, B):
    N = len(A)
    R = [0] * (N + 1)
    global H
    H = [Node()] * (MAXN * 2)

    for i in range(N):
        H[MAXN + B[i]].covers = 1
        H[MAXN + A[i]].covers = 1
        fix(MAXN + B[i])
        fix(MAXN + A[i])
        R[i + 1] = H[1].points
    
    return R

def main():
    N = int(input())

    used = [False] * (2 * N)
    A = [int(x) - 1 for x in input().split()]
    for val in A:
        used[val] = True
    
    B = [i for i in range(2 * N - 1, -1, -1) if not used[i]]

    r0 = solve(A, B)
    A.reverse()
    B.reverse()
    A = [2 * N - 1 - x for x in A]
    B = [2 * N - 1 - x for x in B]
    r1 = solve(A, B)

    res = max([r0[i] + r1[N - i] for i in range(N + 1)])
    print(res)

main()




