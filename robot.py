# def solve():
#     n = int(input()) #converts input to int
#     finalx, finaly = (int(z) for z in input().split()) #converts to int for z in input
#     possibilities = [(0, 0, 0)] #final x, final y, and instructions used
#     for _ in range(n):
#         movex, movey = (int(m) for m in input().split())
#         for i in range(len(possibilities)):
#             possibilities.append((possibilities[i][0] + movex, possibilities[i][1] + movey, possibilities[i][2] + 1))
#     ret = [0] * n
#     for destx, desty, moves in possibilities:
#         if (destx, desty) == (finalx, finaly):
#             ret[moves - 1] += 1
#     for x in ret:
#         print(x)

# solve()

#solution 2
def all_subsets(dirs):
    v = [((0, 0), 0)]
    for d in dirs:
        now = len(v)
        for i in range(now):
            v.append(((v[i][0][0] + d[0], v[i][0][1] + d[1]), v[i][1] + 1))
    v.sort()
    return v

def main():
    N = int(input())
    goal = tuple(map(int, input().split()))
    dirs = []
    for _ in range(N):
        d = tuple(map(int, input().split()))
        dirs.append(d)
    a = all_subsets(dirs[:N // 2])
    b = all_subsets(dirs[N // 2:])[::-1]
    ans = [0] * (N + 1)
    with_num = []
    rest_prev = (10**18, 10**18)
    ib = 0
    for offset, num in a:
        rest = tuple(goal[i] - offset[i] for i in range(2))
        if rest != rest_prev:
            rest_prev = rest
            with_num = [0] * (N - N // 2 + 1)
            while ib < len(b) and b[ib][0] > rest:
                ib += 1
            while ib < len(b) and b[ib][0] == rest:
                with_num[b[ib][1]] += 1
                ib += 1
        for i in range(len(with_num)):
            ans[i + num] += with_num[i]
    for i in range(1, N + 1):
        print(ans[i])

main()
