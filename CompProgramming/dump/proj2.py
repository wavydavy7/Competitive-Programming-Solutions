import math
from math import sqrt
import numpy as np
from scipy import stats
#1
#a. Type 1 happens when you accidentally reject that the drug is unsafe(think it's safe), when it really is unsafe
#Type 2 happens when you think it's unsafe, but it's actually safe
#b. Consumers don't want Type 1 - they don't want a drug to be declared safe, but it really is unsafe 
#c. Lobbyists don't want type 2 - they want drugs to be approved quicker, so they wouldn't want people to mistake safe drugs for unsafe drugs. 
#d. You can decrease both errors by increasing the sample size. 

#2
#a. 
#p = 2*P(Z < -2) = .0456 => the p value is low so we reject the null hypothesis
#b. 
sd = 100 / math.sqrt(64)
stat = (350 - 375) / sd
#c. 
interval = [350 - 1.96*sd, 350 + 1.96*sd]
print(interval)
#d. the interval does not contain 375, which agrees with what we said in part a about not being sure that the null hypothesis is true

#3
#a. 
nums = np.array([7.42, 6.29, 5.83, 6.5, 8.34, 9.51, 7.1, 6.8, 5.9, 4.89, 6.5, 5.52, 7.9, 8.3, 9.6])
tot = 0
for x in nums:
    tot += x
avg = tot / 15
ssd = 0
for x in nums:
    ssd += (x - avg)**2
ssd /= 14
ssd = math.sqrt(ssd)
#we need to run t test
mu = 6.5
t_stat, p_value = stats.ttest_1samp(nums, mu)
print((t_stat, p_value))
#based on a p_value of 2*.124, we cannot conclude that the mean amount of money spent is different from 6.5
#b. we must assume that the underlying distribution of how much one spends for lunch is normally distributed
#c. 
tstd = (ssd / math.sqrt(15)) 
tstat = (avg - 6.5) / tstd
print(tstat)
#d.
tinterval = [avg - 2.131*tstd, avg + 2.131*tstd]
print(tinterval)

