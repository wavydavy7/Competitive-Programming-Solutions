N = int(input())

dp = [[[[[0] for _ in range(2)] for _ in range(210)] for _ in range(210)] for _ in range(210)]
structure = [0]
pts = []
for i in range(N):
    x, y = map(int, input().split())
    pts.append((x, y))

for i in range(N):
    curx, cury = pts[i + 1 % N]
    nextx, nexty = pts[i + 2 % N]
    distance = abs(curx - pts[i][0]) + abs(cury - pts[i][1])
    structure.append(distance)
    #need two line segments
    direction = ((pts[i][0] - curx) * (nexty - cury)) - ((pts[i][1] - cury) * (nextx - curx)) #take the cross product
    if direction > 0:
        #were turning clockwise to the right
        structure.append(-1)
    elif direction < 0:
        structure.append(-2)

structure[-1] = 0 #might be left or right, but set to 0 saying that if you take this turn then you're out 



#we want the min(max(best strategy|f_on  - f_out |) ... we subtract optimal from on with the dp of finding out where you are to heading to the exit

psum = [0] * (N + 1)
opt = [0] * (N + 1)
for i in range(N):
    #0, then first distance on odds, then corners on evens
    psum[i + 1] = opt[i + 1] = psum[i] + structure[2 * i] 

opt[N] = 0

for i in range(N - 1, -1, -1):
    #go counter clockwise
    opt[i] = min(opt[i], structure[2*i + 1] + opt[i + 1])

canon = [[[0] * 410] for _ in range(410)]
#calculate the canonical ones(earliest occurence of the string)... if 2 strings are the same, then the one that differs is either an edge or a vertex
for ln in range(1, len(structure) + 1):
    for i in range(len(structure) + 1 - ln):
        j = canon[i][ln]
        for j in range(i):
            if canon[j][ln - 1] == canon[i][ln - 1] and structure[j + ln - 1] == structure[i + ln - 1]:
                canon[i][ln - 1] = j #this is an earlier option
                break


#let's extend left and right
lpar = [[[0] * 210] for _ in range(210)]  
rpar= [[[0] * 210] for _ in range(210)]
for i in range(0, len(structure), 2): #starting at a corner
    #question is, how do you play optimally
    for ln in range(3, len(structure) - i + 1, 2):
        if i != canon[i][ln]: #(i to side to next one), only considering corners to corners
            continue
        lpar[canon[i + 2][ln - 2] / 2][ln / 2].append(i / 2) 
        rpar[canon[i][ln - 2] / 2][ln / 2].append(i / 2)

result = 0
for ln in range(N, 0, -1):#really stands for how many edges
    for i in range(N + 2 - ln): #you are allowed to stumble onto N + 1
        if canon[2 * i][2 * ln - 1] != 2 * i: #from point to another vertex
            continue
        dist = psum[i + ln - 1] - psum[i]
        for strt in range(ln):
            for side in range(2):
                if i == 0 or i + ln == N + 1:
                    dp[i][ln][strt][side] = -opt[i + strt] #you've finished, need to subtract from optional to get difference
                    continue
        left = -float('inf')
        for l in lpar[i][ln]:
            left = max(left, structure[2*l + 1] + dp[l][ln + 1][strt + 1][0])
        
        right = -float('inf')
        for r in rpar[i][ln]:
            right = max(right, structure[2 * (r + ln) - 1] + dp[r][ln + 1][strt][1])

        if side: #which is 1
            left += dist
        else:
            right += dist
        
        dp[i][ln][strt][side] = min(left, right)

        if ln == 1:
            result = max(result, dp[i][ln][strt][side]) #we only consider those where ln = 1

print(result)
        







        



    



    

