#winning gene

from collections import defaultdict
length = int(input())
string = input()
P = defaultdict(set) #map a pair to a set
res = [0] * length

def findLeft(i, j, substring):
    mn = 0
    mx = i
    while mn < mx:  # Change <= to < to ensure the loop can exit, find leftmost 
        mid = (mn + mx) // 2  # Corrected max to mx
        if string[mid:mid + (j - i)] > substring:  # Check bounds
            mx = mid 
        else:
            mn = mid + 1
    return mn  # Return the lower bound as the left boundary

def findRight(i, j, substring):
    mn = j
    mx = length  # Correct the initialization to use the actual upper bound
    while mn < mx:  # Change <= to < for correct looping
        mid = (mn + mx + 1) // 2  # Adjust calculation to bias towards the right
        if substring <= string[mid - (j - i):mid]:  # Adjust slicing
            mn = mid# Move right
        else:
            mx = mid - 1
    return mx   # Adjust return to reflect the upper boundary



for i in range(length):
    for j in range(i + 1, length + 1):
        substring = string[i:j]
        # print(substring)
        sub_length = j - i 

        # l = i
        # r = j
        # while l - 1 >= 0 and string[l - 1:r - (i - l + 1)] > substring:
        #     l -= 1
        l = findLeft(i, j, substring)
        
        # while r + 1 <= length and substring <= string[i + (r - j + 1):r + 1]:
        #     r += 1
        r = findRight(i, j, substring)
        
        dist = r - l
        # print(dist)

        for k in range(sub_length, dist + 1):
            P[(k, sub_length)].add(i)
            # print(P[(k, sub_length)])

#now that we have bounds

for key in P.keys():
    s = len(P[key])
    # if s == 7:
        # print(key)
        # print(P[key])
    res[s - 1] += 1

for index in range(length):
    print(res[index])














