N, K = map(int, input().split())

# Constructing the 2D prefix sums for unfamiliarity
P = [[0 for _ in range(N + 1)] for _ in range(N + 1)]
for i in range(1, N + 1):
    row = list(map(int, input().split()))
    for j in range(1, N + 1):
        P[i][j] = row[j - 1] + P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1]

dp = [[1 << 30 for _ in range(N + 1)] for _ in range(K + 1)]

def dnq(k, l, r, p, q):
    if r < l:
        return 
    if p == q:
        for i in range(l, r + 1):
            dp[k][i] = dp[k - 1][p - 1] + P[i][i] - P[i][p - 1] - P[p - 1][i] + P[p - 1][p - 1]
        return 
    m = (l + r) // 2
    pos = -1
    for i in range(p, q + 1):
        val = dp[k - 1][i - 1] + P[m][m] - P[m][i - 1] - P[i - 1][m] + P[i - 1][i - 1]
        if dp[k][m] > val:
            dp[k][m] = val
            pos = i

    dnq(k, l, m - 1, p, pos)
    dnq(k, m + 1, r, pos, q)

dp[0][0] = 0
for k in range(1, K + 1):
    dnq(k, 1, N, 1, N)

print(dp[K][N])
