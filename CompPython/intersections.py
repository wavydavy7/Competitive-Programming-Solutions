class BIT:
    def __init__(self, len):
        self.bit = [0] * (len + 1)
        self.l = len
    
    def query(self, i):
        res = 0
        while i >= 1:
            res += self.bit[i]
            i -= i & -i
        return res

    def update(self, i, amt):
        while i <= self.l:
            self.bit[i] += amt
            i += i & -i

bit = BIT(2000005)
n = int(input())
coordinates = [] * n
for i in range(n):
    x1, y1, x2, y2 = map(int, input().split())
    if x1 == x2:
        coordinates.append([x1, 2, y1, y2])
    else:
        coordinates.append([x1, 1, y1, 1])
        coordinates.append([x2, 3, y2, 1])
coordinates.sort()

res = 0

for c in coordinates:
    c[2] += 1000001
    c[3] += 1000001
    if c[1] == 1:
        bit.update(c[2], 1)
    elif c[1] == 2:
        res += bit.query(c[3]) - bit.query(c[2] - 1)
    else:
        bit.update(c[2], -1)

print(res)
        





