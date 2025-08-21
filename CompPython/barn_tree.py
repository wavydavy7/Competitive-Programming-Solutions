from collections import defaultdict

N = int(input().strip())
barns = list(map(int, input().strip().split()))
edges = defaultdict(list)

for i in range(N - 1):
    x, y = list(map(int, input().strip().split()))
    edges[x - 1].append(y - 1)
    edges[y - 1].append(x - 1)

avg = sum(barns) // N
subtree_tot = [0] * N
moves = []

def dfs_fill_subtrees(i, par=-1):
    subtree_tot[i] = barns[i] - avg
    for child in edges[i]:
        if child != par:
            dfs_fill_subtrees(child, i)
            subtree_tot[i] += subtree_tot[child]

def dfs_make_orders(i, par=-1):
    for child in edges[i]:
        if child != par and subtree_tot[child] >= 0:
            dfs_make_orders(child, i)
            if subtree_tot[child] > 0:
                moves.append((child + 1, i + 1, subtree_tot[child]))
                
    for child in edges[i]:
        if child != par and subtree_tot[child] < 0:
            moves.append((i + 1, child + 1, -subtree_tot[child]))
            dfs_make_orders(child, i)

dfs_fill_subtrees(0)
dfs_make_orders(0)

print(len(moves))
for move in moves:
    print(*move)
