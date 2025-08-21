class TreeMatching:
    def dfs(v, p, adj, dp):
        for nei in adj[v]:
            if nei != p:
                TreeMatching.dfs(nei, v, adj, dp)
                dp[v][0] += max(dp[nei][0], dp[nei][1])
        for nei in adj[v]:
            if nei != p:
                dp[v][1] = max(dp[v][1], dp[nei][0] + 1 + dp[v][0] - max(dp[nei][0], dp[nei][1]))

    def main():
        N = int(input())
        adj = [[] for _ in range(N)]
        dp = [[0] * 2 for _ in range(N)]
        for i in range(N - 1):
            st = tuple(map(int, input().split()))
            st = (st[0] - 1, st[1] - 1)
            adj[st[0]].append(st[1])
            adj[st[1]].append(st[0])
        
        TreeMatching.dfs(0, -1, adj, dp)
        print(max(dp[0][0], dp[0][1]))

TreeMatching.main()
