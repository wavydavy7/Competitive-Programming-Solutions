def dnc(i, l, r, optl, optr, dp, psum):
    if l > r:
        return

    mid = (l + r) // 2
    best = [float('inf'), l]

    for j in range(optl, min(mid, optr + 1)):
        sum_val = psum[mid] - psum[j] #mid element minus jth element gives you range from [j, mid]
        best = min(best, [sum_val * sum_val + dp[i - 1][j], j])

    dp[i][mid] = best[0]
    opt = best[1]

    dnc(i, l, mid - 1, optl, opt, dp, psum)
    dnc(i, mid + 1, r, opt, optr, dp, psum)

def main():
    N, K = map(int, input().split())
    nums = list(map(int, input().split()))
    psum = [0] * (N + 1)
    dp = [[float('inf')] * (N + 1) for _ in range(K + 1)]

    for i in range(N):
        psum[i + 1] = psum[i] + nums[i]

    dp[0][0] = 0

    for i in range(1, K + 1): 
        dnc(i, 1, N, 0, N - 1, dp, psum) #1 based indexing for psum

    print(dp[K][N])

main()
