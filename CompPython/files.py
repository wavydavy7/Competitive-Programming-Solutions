from collections import defaultdict
MAX = 10 ** 5 + 5
s = [""] * max
adj = defaultdict(list)
sub = [0] * MAX
res = [0] * MAX
up = [0] * MAX
mn = float('inf')

def main():
    stdin = open("dirtraverse.in", "r")
    stdout = open("dirtraverse.out", "w")

    n = int(input())
    for i in range(1, n + 1):
        s[i] = input().strip()
        k = int(input())
        for _ in range(k):
            a = int(input())
            adj[i].append(a)
    

    def dfs(v):
        global adj, s, sub, res
        for u in adj[v]:
            if not adj[u]:
                res[v] += len(s[u])
                sub[v] += 1
                continue
            dfs(u)
            res[v] += res[u] + sub[u] * len((s[u]) + 1) # adds leaves
            sub[v] += sub[u]
    
    def dfs2(v):
        global adj, s, sub, res, up, mn
        mn = min(mn, res[v] + up[v])
        for u in adj[v]:
            if not adj[u]:
                continue
            up[u] = up[v] + res[v] - res[u] - sub[u] * len(s[u] + 1) + 3 * sub[1] - sub[u]
            dfs2(u)

    dfs(1)
    dfs2(1)
    
    print(mn, file = stdout)

main()