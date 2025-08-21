N = int(input())


def solve(p1, p2, p3):
    sol = -1
    for d12 in range(min(p1, p2) + 1):
        for d13 in range(min(p1, p3) + 1):
            for d23 in range(min(p2, p3) + 1):
                if (p1 - d12 - d13) % 2 != 0 or d12 + d13 > p1:
                    continue
                if (p2 - d12 - d23) % 2 != 0 or d12 + d23 > p2:
                    continue
                if (p3 - d13 - d23) % 2 != 0 or d13 + d23 > p3:
                    continue
                sol = max(sol, d12 + d13 + d23)
    print(sol)


while N > 0:
    N -= 1
    p1, p2, p3 = map(int, input().split())
    if (p1 + p2 + p3) % 2:
        print(-1)
    else:
        solve(p1, p2, p3)



