#range DP not working

# def main():
#     def ckmax(a, b):
#         if a < b:
#             a = b
#             return True 
#         return False

#     N, M = map(int, input().split())
#     w, l, r = [], [], []

#     #MX = 300
#     mx = [[[0] * N for _ in range(N)] for _ in range(N)]

#     for _ in range(M):
#         wi, li, ri = map(int, input().split())
#         l.append(li - 1)
#         r.append(ri - 1)
#         w.append(wi)
#         for j in range(li - 1, ri):
#             mx[j][li - 1][ri - 1] = max(mx[j][li - 1][ri - 1], wi)

#     dp = [[0] * N for _ in range(N)]

#     for i in range(N):
#         for j in range(i, -1, -1):
#             for k in range(i, N):
#                 if j:
#                     ckmax(mx[i][j - 1][k], mx[i][j][k])
#                 if k < N - 1:
#                     ckmax(mx[i][j][k + 1], mx[i][j][k])

#     for a in range(N - 1, -1, -1):
#         for b in range(a, N):
#             for c in range(a, b):
#                 ckmax(dp[a][b], dp[a][c] + dp[c + 1][b])
#             for c in range(a, b + 1):
#                 if mx[c][a][b]:
#                     res = mx[c][a][b]
#                     if c > a:
#                         res += dp[a][c - 1]
#                     if c < b:
#                         res += dp[c + 1][b]
#                     ckmax(dp[a][b], res)

#     print(dp[0][N - 1])

# main()

N, M = map(int, input().split())

maxWeight = [[0] * 301 for _ in range(301)]
maxCover = [[[0] * 301 for _ in range(301)] for _ in range(301)]
dp = [[0] * 301 for _ in range(301)]

for _ in range(M):
    w, l, r = map(int, input().split())
    maxWeight[l][r] = max(maxWeight[l][r], w)

for i in range(N, -1, -1):
    for j in range(i, N+1):
        for k in range(i, j+1):
            maxCover[i][j][k] = max(max(maxCover[i+1][j][k], maxCover[i][j-1][k]), maxWeight[i][j])

for i in range(N, -1, -1):
    for j in range(i, N+1):
        for k in range(i, j+1):
            dp[i][j] = max(dp[i][j], dp[i][k-1] + dp[k+1][j] + maxCover[i][j][k])

print(dp[1][N])


