def main():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    dp = [(25, 0)] * (1 << n)
    dp[0] = (0, k + 1)

    for s in range(1, 1 << n):
        dp[s] = (25, 0)
        for i in range(n):
            if s >> i & 1:
                c, w = dp[s ^ (1 << i)]
                if w + a[i] > k:
                    c += 1
                    w = min(a[i], w)
                else:
                    w += a[i]
                dp[s] = min(dp[s], (c, w))

    print(dp[(1 << n) - 1][0])

main()