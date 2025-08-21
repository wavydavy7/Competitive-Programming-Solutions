import math
from collections import defaultdict

def solve(n, hay):
    res = set()
    for i, num in enumerate(hay):
        if i + 1 < n and num == hay[i + 1]:
            res.add(num)
        elif i + 2 < n and num == hay[i + 2]:
            res.add(num)

    if not res:
        return "-1"
    else:
        return " ".join(map(str, sorted(res)))



final = []
T = int(input())
for k in range(T):
    N = int(input().strip())
    arr = list(map(int, input().split()))
    final.append(solve(N, arr))

for f in final:
    print(f)


