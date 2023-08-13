# Initialize the global variables
MOD = 10**9+7
MX = 10**5+5

N = 0  # number of nodes
sub = [0]*MX  # sub-tree sizes
adj = [[] for _ in range(MX)]  # adjacency list representation of the graph
num = [[] for _ in range(MX)]  # stores sizes of sub-trees connected to each node
bad = False
cur = [0]*MX  # current count of each remainder when the subtree size is divided by K

# Depth-first search function to compute sizes of sub-trees
def dfs(a, b):
    global sub, adj, num, N
    sub[a] = 1
    for t in adj[a]:
        if t != b:
            dfs(t, a)
            sub[a] += sub[t] #calculate the size of the subtree rooted at a 
            num[a].append(sub[t]) #add subtree t as a chain 
    if sub[a] != N:
        num[a].append(N-sub[a])

# Function to check whether it is possible to divide the tree into paths of length K
def ok(K):
    global cur, num, N
    # if N-1 is not divisible by K, return False
    if (N-1) % K != 0:
        return False
    for i in range(K):
        cur[i] = 0
    for i in range(1, N+1):
        cnt = 0
        for t in num[i]:
            z = t % K
            if z == 0: 
                continue
            if cur[K-z]:  # if a complement to z is found, decrement its count and decrement the total unpaired paths
                cur[K-z] -= 1
                cnt -= 1
            else:  # if a complement to z is not found, increment its count and increment the total unpaired paths
                cur[z] += 1
                cnt += 1 #cnt wil neutralize to 0 once it meets its pair
        if cnt:  # if there are unpaired paths, return False
            return False
    return True  # return True if all paths could be paired

def main():
    global N, adj, cur
    N = int(input())
    # read the edges of the tree and build the adjacency list
    for _ in range(1, N):
        a, b = map(int, input().split())
        adj[a].append(b)
        adj[b].append(a)
    dfs(1, 0)  # compute the sizes of all sub-trees
    # for each possible length of path from 1 to N-1, check whether it is possible to divide the tree into paths of that length
    for i in range(1, N):
        if ok(i):
            print(1, end="")  # print 1 if it is possible
        else:
            print(0, end="")  # print 0 if it is not possible
    print()  # print a newline at the end
main()