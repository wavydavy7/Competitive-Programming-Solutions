#Davy Wang STAT401

conf90 = 1.65
conf95 = 1.96
conf99 = 2.58
def interval(m, sig, n, conf):
    if sig != 0:
        return [m - (conf*sig/n**(1/2)), m + (conf*sig/n**(1/2))]

ans1a = interval(37, 5, 15, conf90)
ans1b = interval(37, 5, 15, conf95)
ans1c = interval(37, 5, 15, conf99)
#for part d, the width of the interval increases as you increase the confidence level
print([ans1a, ans1b, ans1c])

ans2a = interval(270, 40, 25, conf95)
ans2b = interval(270, 40, 50, conf95)
ans2c = interval(270, 40, 100, conf95)
#for part d, the confidence interval shrinks in width with a larger sample size
print([ans2a, ans2b, ans2c])

ans3a = interval(850, 50, 100, conf95)
ans3b = interval(850, 100, 100, conf95)
ans3c = interval(850, 200, 100, conf95)
#for part d, the confidence interval increases with a larger sigma 
print([ans3a, ans3b, ans3c])

ans4a = interval(270, 20, 10, 2.262)
ans4b = interval(270, 20, 20, 2.086)
ans4c = interval(270, 20, 40, 2.021)
#for part d, the confidence interval decreases with a larger n value
print([ans4a, ans4b, ans4c])

ans5a = interval(850, 15, 25, 2.064)
ans5b = interval(850, 30, 25, 2.064)
ans5c = interval(850, 60, 25, 2.064)
#for part d, the confidence interval increases with a larger s
print([ans5a, ans5b, ans5c])

nums = [21,22,22,17,21,17,23,20,20,24,9,22,16,21,22,21]
avg = sum(nums) / 16
ese = 0
for num in nums:
    ese += (num - avg)**2
ese /= 15
ese = ese**(1/2)
#we have our sigma
ans6 = interval(avg, ese, 16, 1.753)
print(ans6)

# the actual confidence intervals outputted with each line containing the confidence intervals for one of the six questions in order
# [[34.86985915958592, 39.13014084041408], [34.46965088047782, 39.53034911952218], [33.66923432226162, 40.33076567773838]]
# [[254.32, 285.68], [258.9125656709949, 281.0874343290051], [262.16, 277.84]]
# [[840.2, 859.8], [830.4, 869.6], [810.8, 889.2]]
# [[255.69385586539826, 284.30614413460177], [260.67112439787087, 279.32887560212913], [263.6090368487997, 276.3909631512003]]
# [[843.808, 856.192], [837.616, 862.384], [825.232, 874.768]]
# [18.27573773811433, 21.47426226188567]
