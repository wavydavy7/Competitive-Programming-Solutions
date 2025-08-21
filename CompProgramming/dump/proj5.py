import numpy as np
from scipy import stats
#H0 is that the difference in mean hitting is 0(mu1 - mu2 = 0 where mu_i is the average hitting distance of the ith golf design)
#Ha is that there are difference in mean hitting(mu1 - mu2 not equal to 0)
#If 2*P(X < Z crit) < 0.5, we accept the alternate hypothesis

#We use a difference in means independent t-test since the 2 designs are independent/not related, and we are trying
#to find any differences in driving distances 

#
t1 = np.array([239.4, 232.2, 234.6, 224.7, 227.1, 229.9, 229.9, 237.7, 223.1, 239.6, 235.5])
t2 = np.array([226.4, 226.9, 211.7, 231.9, 230.0, 224.7, 233.3, 215.0, 227.1])
n1 = len(t1)
n2 = len(t2)
mean1 = np.mean(t1)
mean2 = np.mean(t2)
var1 = np.sum((t1 - mean1)**2) / (n1 - 1)
var2 = np.sum((t2 - mean2)**2) / (n2 - 1)
sp2 = ((n1-1)*var1 + (n2 - 1)*var2)/(n1 + n2 - 2)
t_stat = (mean1 - mean2) / (np.sqrt(sp2*(1/n1 + 1/n2)))
print(t_stat)
df = n1 + n2 - 2
print(df)
p_val3 = 1 - stats.t.cdf(t_stat, df)
print(p_val3)

#.014 * 2 < .05, we reject the null hypothesis in favor of the alternate hypothesis that states there is a difference in mean hitting distance 
#Because there is a noticeable difference in between the difference golfball designs, manufacturing more of design 2 and selling it at a higher price
#could generate more revenue for the company

#H0 is that there is no difference in proportion of spending between the genders(p1 - p2 = 0 where p1 is the proportion of men who shop regularly, and p2 is that for women)
#Ha is that there are more men who regularly make purchases online compared to women proportionally(p1 - p2 > 0)

x1 = 5400
x2 = 8600
n1 = 6000
n2 = 10000
p1 = x1 / n1 
p2 = x2 / n2

phat = (x1 + x2) / (n1 + n2)
print(phat)
se = np.sqrt(phat*(1 - phat)*((1/n1 + 1/n2)))
print(se)
z = (p1 - p2) / se
print(z)

#P(Z > 7.41) is almost 0, so we reject H0 for Ha, thus concluding that men shop more regularly online 
#Type 2 error would be failing to reject H0 when Ha is true, namely, there are actually more men than shop regularly online, but we wrongfully state that there is no difference

interval = [(p1 - p2) - 1.96*se, (p1 - p2) + 1.96*se]
print(interval)
#[np.float64(0.02941479019260053), np.float64(0.05058520980739954)]


