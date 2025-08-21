N = int(input()) #cows

adj = [0 for i in range(N)]
for i in range(N):
    #find what they would rather have before it 
    arr = list(map(int, input().split()))
    for g in arr:
        g -= 1
        adj[i] |= 1 << g
        if g == i:
            break


# ans = [0] * (1 << (N + 1))
# ans[0] = 1
# #I want to return dp[mask][which one I'm on]
# dp = [[0] * N for j in range(1 << N)] #only some configs are valid

# for i in range(N):
#     dp[1 << i][i] = 1 # 1 means it's taken, start here

# for cow in range(N): #the highest cow
#     for mask in range(1 << cow, 1 << (cow + 1), 1): #mix up the bits 
#         for prev in range(cow + 1): #end with the highest

#             if mask & (1 << prev): #before the current cow
#                 val = dp[mask][prev] #if that one's taken, and default doesn't involve cow in cycle
                
                
#                 #we connect to the prev
#                 for k in range(cow): #the one we trade with
#                     if not (mask & (1 << k)): #if there isn't a 1 and 1 at ith position
#                         if pref[prev] & (1 << k):
#                             dp[mask ^ (1 << k)][k] += val
                
#                 if pref[prev] & (1 << cow):
#                     ans[mask] += val
    
#         for k in range(cow + 1, N, 1):
#             dp[mask ^ (1 << k)][k] += ans[mask]


ans = [0] * (1 << N)
ans[0] = 1
dp = [[0] * N for _ in range(1 << N)]
for k in range(N):
    dp[1 << k][k] = 1

for i in range(N):
    for mask in range(1 << i, 1 << (i + 1)):
        for last in range(i + 1):
            if mask & (1 << last):
                val = dp[mask][last]
                for k in range(i):
                    if not (mask & (1 << k)) and (adj[last] & (1 << k)):
                        dp[mask ^ (1 << k)][k] += val
                if adj[last] & (1 << i):
                    ans[mask] += val
        for k in range(i + 1, N):
            dp[mask ^ (1 << k)][k] += ans[mask]


Q = int(input())
results = []
for _ in range(Q):
    breeds = input()
    g = 0
    h = 0
    for i in range(N):
        if breeds[i] == 'G':
            g ^= 1 << i
        else:
            h ^= 1 << i
    results.append(ans[g] * ans[h])

for result in results:
    print(result)


# def main():
#     N = int(input())  # Get the number of items
#     assert N <= 20  # Ensure N does not exceed the maximum allowed
    
#     adj = [0] * N  # Adjacency list initialization
#     for i in range(N):
#         pref = list(map(int, input().split()))
#         for g in pref:
#             g -= 1
#             adj[i] |= 1 << g
#             if g == i:
#                 break
    
#     # Initialize DP and answer arrays
#     ans = [0] * (1 << N)
#     dp = [[0] * N for _ in range(1 << N)]
    
#     ans[0] = 1  # Base case for answers
#     for k in range(N):  # Initialize starting positions for DP
#         dp[1 << k][k] = 1
    
#     # Process all possible configurations
#     for cow in range(N): #the highest cow
#         for mask in range(1 << cow, 1 << (cow + 1), 1): #mix up the bits 
#             for prev in range(cow + 1): #end with the highest

#                 if mask & (1 << prev): #before the current cow
#                     val = dp[mask][prev] #if that one's taken, and default doesn't involve cow in cycle
                    
                    
#                     #we connect to the prev
#                     for k in range(cow): #the one we trade with
#                         if not (mask & (1 << k)): #if there isn't a 1 and 1 at ith position
#                             if adj[prev] & (1 << k):
#                                 dp[mask ^ (1 << k)][k] += val
                    
#                     if adj[prev] & (1 << cow):
#                         ans[mask] += val
        
#             for k in range(cow + 1, N, 1):
#                 dp[mask ^ (1 << k)][k] += ans[mask]

    
#     # Handle queries
#     Q = int(input())
#     results = []
#     for _ in range(Q):
#         breeds = input()
#         g = 0
#         h = 0
#         for i in range(N):
#             if breeds[i] == 'G':
#                 g ^= 1 << i
#             else:
#                 h ^= 1 << i
#         results.append(ans[g] * ans[h])
    
#     for result in results:
#         print(result)


# main()
