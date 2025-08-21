N = int(input())
arr = list(map(int, input().split()))
cnt = 0

for i, num in enumerate(arr):
    temp = num * - 1 if num < 0 else num
    cnt += temp
    for j in range(i + 1, N):
        arr[j] += ((j - i + 1) * -num)

print(cnt)