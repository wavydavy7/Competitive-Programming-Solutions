from collections import deque

class Rect:
    def __init__(self, x, y, a):
        self.x = x
        self.y = y
        self.a = a
    
    def lt(self, other):
        return self.x < other.x
    
def slope(rects, dp, i, j):
    return (dp[i] - dp[j]) / (rects[i].x - rects[j].x)

def max_area(n, rects):
    rects.sort()
    dp = [0] * (n + 1)
    q = deque()
    q.append(0)

    for i in range(n + 1):
        while len(q) > 1 and slope(rects, dp, q[0], q[1]) >= rects[i].y: #if x value is greater, forms upside down convex hull, def not included
            q.popleft()
        
        j = q[0]
        dp[i] = max(dp[i - 1], rects[i].x * rects[i].y - rects[i].a + dp[j] - rects[j].x * rects[i].y)

        while len(q) > 1 and slope(rects, dp, q[-2], q[-1]) <= slope(rects, dp, q[-1], i): # you can also replace rightmost line with one with better slope and righter intersection
            q.pop()
        
        q.append(i)

    return dp[n]

n = int(input())
rects = [Rect(0, 0, 0)]
for _ in range(n):
    x, y, a = map(int, input().split())
    rects.append(Rect(x, y, a))

print(max_area(n, rects))

