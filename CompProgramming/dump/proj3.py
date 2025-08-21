import numpy as np
from scipy import stats
#1
#a
p_test = .1835
z_val = (.24 - .1835) / np.sqrt(p_test*(1 - p_test) / 100)
p_val = 1 - stats.norm.cdf(z_val)
print(p_val)

#b
#we must have np_0 >= 10 and n(1 - p_0) >= 10 to have approximately normal distribution. 100(.1835) >= 10, 100(.8165) >= 10, satisfying conditions

#c
z_val2 = (.24 - .1835) / np.sqrt(p_test*(1 - p_test) / 400)
p_val2 = 1 - stats.norm.cdf(z_val2)
print(p_val2)

#d 
# if you have a larger sample size, then it is easier to reject the null hypothesis for the same alpha value as seen between part a 
#and part c. In other words, our hypothesis test has higher power with a larger sample size

#e 
# with a sample size of 20, it will be very difficult to reject the null hypothesis. As we discussed in part d, the size of the sample
#correlates with the power of the test to reject values that are greater than the mean. With such a small sample, it will be difficult to 
#reject the null hypothesis

#2
t1 = np.array([7.8, 7.4, 5.4, 6.1, 5.5, 4.5, 3.3])
t2 = np.array([7.4, 4.3, 4.2, 5.2, 6.4, 7.1, 5.2, 6.1, 3.7, 2.3])
n1 = len(t1)
n2 = len(t2)
mean1 = np.mean(t1)
mean2 = np.mean(t2)
var1 = np.sum((t1 - mean1)**2) / (n1 - 1)
var2 = np.sum((t2 - mean2)**2) / (n2 - 1)
se = np.sqrt(var1 / n1 + var2 / n2)
t_stat = (mean1 - mean2) / se
print(t_stat)
df = (var1/n1 + var2/n2)**2 / ((var1**2)/((n1**2)*(n1-1)) + (var2**2)/((n2**2)*(n2-1)))
print(df)
p_val3 = 1 - stats.t.cdf(t_stat, df)
print(p_val3)
#0.26 > 0.01, we fail to reject H_0 and conclude that there is not sufficient evidence to establish a difference in levels

#b
t_crit = stats.t.ppf(0.995, df)
print(t_crit)
moe = t_crit * se
c_lo = (mean1 - mean2) - moe
c_hi = (mean1 - mean2) + moe
print([c_lo, c_hi])
#[-1.8199423616369055, 2.8685137902083335]. We are 99% confident that the true difference in true benzene concentrations is in this interval


