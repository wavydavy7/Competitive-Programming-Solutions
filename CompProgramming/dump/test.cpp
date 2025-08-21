#include <iostream>
#include <vector>
#include <algorithm>
 
int valid(long long n, long long k, long long m, long long x) {
  long long g = 0;
  while(k > 0 && g < n) {
    long long y = (n - g) / x;
    if(y < m) {
      long long leftover = (n-g + m-1) / m;
      return leftover <= k;
    }
    long long maxmatch = n - x*y;
    long long numdays = (maxmatch - g ) / y + 1;
    if(numdays > k) numdays = k;
    g += y * numdays;
    k -= numdays;
  }
  return g >= n;
}
 
int main() {
  freopen("loan.in", "r", stdin);
  freopen("loan.out", "w", stdout);
  long long n, k, m;
  scanf("%lld %lld %lld", &n, &k, &m);
  long long lhs = 1;
  long long rhs = 1e12;
  while(lhs < rhs) {
    long long mid = (lhs + rhs + 1) / 2;
    if(valid(n, k, m, mid)) {
      lhs = mid;
    }
    else {
      rhs = mid - 1;
    }
  }
  printf("%lld\n", lhs);
}