def main():
    n, m = map(int, input().split())
    mod = 10**9 + 7
    dp = [[0 for i in range (1 << n + 1)] for j in range (m + 1)]
    dp[0][0] = 1

    def fill(col, idx, curr, next):
        if idx == n:
            dp[col + 1][next] += dp[col][curr] % mod
            return
        else:
            if curr & (1 << idx) == 0:
                fill(col, idx + 1, curr, next | (1 << idx))
                if idx + 1 < n and not curr & (1 << idx + 1):
                    fill(col, idx + 2, curr, next)
            else:
                fill(col, idx + 1, curr, next)


    for i in range(m): #the layer 
        for v in range(1 << n): #the block status 
            if dp[i][v] > 0:
                fill(i, 0, v, 0)
    
    print(dp[m][0] % mod)


    
















main()