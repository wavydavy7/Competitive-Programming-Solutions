# def solution(n):
#     # Your code here
#     n = int(n)
#     res = 0
#     while n > 3:
#         if n % 2 == 1:
#             if n & 2:
#                 n = (n + 1) >> 2
#                 res += 3
#             else:
#                 n = (n - 1) >> 2
#                 res += 3
#         else:
#             n >>= 1
#             res += 1
#     if n == 3:
#         res += 2
#     if n == 2:
#         n -= 1
#         res += 1
#     return res
        
    

# print(solution('15'))


# def solution(l):
#     # Your code here
#     res = 0
#     dp = [0] * (len(l))
#     for i in range(len(l)):
#         for j in range(i):
#             if l[i] % l[j] == 0:
#                 res += dp[j]
#                 dp[i] += (dp[j] + 1)
                
#     return res

# print(solution([1, 1, 1]))

# from heapq import heappush, heappop

# def solution(times, times_limit):
    
#     n = len(times)
#     for k in range(n):
#         for i in range(n):
#             for j in range(n):
#                 if times[i][k] + times[k][j] < times[i][j]:
#                     times[i][j] = times[i][k] + times[k][j]
                    

#     for i in range(n):
#         if times[i][i] < 0:
#             return list(range(n - 2))

    
#     best_bunnies = []
#     pq = [(-len(best_bunnies), 0, times_limit, set())]  # Using a priority queue with -len to prioritize paths with more bunnies.

#     while pq:
#         num_bunnies, curr, curr_time, rescued = heappop(pq)
#         if curr == n - 1:  # If we reach the end
#             if -num_bunnies > len(best_bunnies):
#                 best_bunnies = rescued
#             continue

#         for next_node in range(n):
#             if curr != next_node and next_node - 1 not in rescued:
#                 time_needed = times[curr][next_node]
#                 new_rescued = rescued.copy()

#                 if 0 < next_node < n - 1:  # If it's a bunny node
#                     new_rescued.add(next_node - 1)

#                 if curr_time - time_needed >= times[next_node][-1]:  # Can reach the exit after rescuing
#                     heappush(pq, (-len(new_rescued), next_node, curr_time - time_needed, new_rescued))

#     return sorted(list(best_bunnies))



# def solution(banana_list):
#     #Your code here
#     n = len(banana_list)
#     d = {}
#     cnt = {}
#     banana_list.sort()
    
#     def loop(x, y):
#         n = x + y

#         while n % 2 == 0:
#             n >>= 1
        
#         return x % n != 0
    

#     for i in range(n - 1):
#         for j in range(i + 1, n):
#             if loop(banana_list[i], banana_list[j]):
#                 if i not in d:
#                     d[i] = []
#                 if j not in d:
#                     d[j] = []

#                 d[i].append(j)
#                 d[j].append(i)

#                 cnt[i] = cnt.get(i, 0) + 1
#                 cnt[j] = cnt.get(j, 0) + 1
                
#     #greedily search through cnts(least -> most)
    
#     lst = [(value, key) for key, value in cnt.items()]
#     lst.sort(key= lambda x: x[0], reverse = True)
    
#     res = n
#     while lst:
#         val, i = lst.pop()
#         if val > 0:
#             to_remove = d[i].pop()
#             lst = [item for item in lst if item[1] != to_remove]
#             for key in d:
#                 if to_remove in d[key]:
#                     d[key].remove(to_remove)
#                     cnt[key] -= 1

#             res -= 2
        
#         lst.sort(key= lambda x: x[0], reverse = True)
        
#     return res
    
# print(solution([1,1]))

class Graph:
    def __init__(self,banana_list):
        self.length = len(banana_list)
        self.graph = list([0]*self.length for i in range(self.length))
        for i in range(self.length):
            for j in range(self.length):
                if i < j: 
                    self.graph[i][j] = self.loop(banana_list[i], banana_list[j])
                    self.graph[j][i] = self.graph[i][j]  

    def loop(self, x, y):
        n = x + y

        while n % 2 == 0:
            n >>= 1
        
        if x % n != 0:
            return 1
        else:
            return 0

    def augment(self, u, match, seen):
        for v in range(self.length):
            if self.graph[u][v] and seen[v] == False:
                seen[v] = True
 
                if match[v] == -1 or self.augment(match[v], match, seen):
                    match[v] = u
                    return True
        return False

    def maxPair(self):
        matchR = [-1] * self.length
        result = 0
        for i in range(self.length):
            seen = [False] * self.length
            if self.augment(i, matchR, seen):
                result += 1
        return self.length- 2*(result/2)


def solution(l):
    return Graph(l).maxPair()