import numpy as np
from scipy.stats import t
before = [158, 189, 202, 353, 416, 426, 441]
after = [284, 214, 101, 227, 290, 176, 290]
diff = [a - b for a, b in zip(before, after)]

#a)
mu = sum(diff) / 7
print(mu)
sde = (np.sum([(d - mu) ** 2 for d in diff]) / 6) ** 0.5
tval = mu / (sde / 7**0.5)
print(tval)
prob = 1 - t.cdf(tval, 6)
print(prob)
#0.057 > 0.05, we fail to reject the null hypothesis

#b)
interval = [mu - 2.447*(sde / 7**0.5), mu + 2.447*(sde / 7**0.5)]
print(interval)
#c)we must assume that the before and after values are normally distributed, resulting in the fact the differences are also normally distributed

#2
new = [1.47, 2.59, 5.21, 3.49, 3.99, 3.10, 5.75]
old = [1.68, 2.99, 5.68, 3.70, 4.20, 2.99, 6.10]
diff2 = [a - b for a, b in zip(new, old)]
mu2 = sum(diff2) / 7
sde2 = (np.sum([(d - mu2) ** 2 for d in diff2]) / 6) ** 0.5
tval2 = mu2 / (sde2 / 7**0.5)
prob = t.cdf(tval2, 6)
print(prob)
#.006 < 0.01. There is sufficient evidence to conclude that the average required for the new processor is less than the average required for the old processor
#b
interval2 = [mu2 - 3.707*(sde2 / 7**0.5), mu2 + 3.707*(sde2 / 7**0.5)]
print(interval2)
#we must assume that the before and after values are normally distributed, resulting in the fact the differences are also normally distributed
#we can conclude that the new processor is faster than the old processor since there is sufficient evidence that the time required is less (difference is less than 0)



