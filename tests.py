from functools import reduce
lst = [1,2,3,4,5]
print(reduce(lambda a,b : a/b, lst, 1)) # sums up the elements (15)