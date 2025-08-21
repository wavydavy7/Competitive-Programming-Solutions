#include <bits/stdc++.h>
using namespace std;
//------------------Euler's Phi Function-------------------//
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

//----------------Find Primes with Sieve-----------------//
constexpr int MAXC = 1e6 + 2;
vector<int>primes(MAXC, 0);
vector<int> cmp(MAXC, 0);
vector<int> kmp(MAXC, 0);
auto factors = [&](int x, int boo){
    while (x > 1){
        int p = primes[x];
        int cnt = 0;
        while (x % p == 0){
            x /= p;
            cnt++;
        }
        if (boo){
            cmp[p] = max(cmp[p], cnt);
        }
        else{
            kmp[p] = cnt;
        }
    
    }
};
//--------------------Sieve------------------//
void find(){
    constexpr int MAXC = 1e6 + 2;
    vector<int>primes(MAXC, 0);
    for (int i = 2; i < MAXC; i++){
        if (primes[i] == 0){
            //ps.insert(i);
            for (int j = i; j < MAXC; j += i){
                primes[j] = i; //the primes should have themselves in the primes vector
            }
        }
    }
}
//--------------MOD Inverse--------------------------------//
int gcd(int a, int m, int& x, int& y) { //mod inverse, remember to add m after
    if (m == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(m, a % m, x1, y1);
    x = y1;
    y = x1 - y1 * (a / m);
    return d;
}
//---------------Pollard Rho/Miller Rabin-----------------//
using ull = unsigned long long;
ull mul_mod(ull a, ull b, ull mod) {
    return (unsigned __int128)a * b % mod;
}
ull pow_mod(ull a, ull d, ull mod) {
    ull res = 1;
    while (d) {
        if (d & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return res;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    for (ull p : {2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull, 19ull, 23ull, 29ull, 31ull, 37ull}) {
        if (n % p == 0) return n == p;
    }
    ull d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    for (ull a : {2ull, 325ull, 9375ull, 28178ull, 450775ull, 9780504ull, 1795265022ull}) {
        if (a % n == 0) continue;
        ull x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (ull r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ull pollards_rho(ull n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    ull c = uniform_int_distribution<ull>(1, n - 1)(rng);
    ull x = uniform_int_distribution<ull>(0, n - 1)(rng);
    ull y = x, d = 1;
    auto f = [&](ull v){ return (mul_mod(v, v, n) + c) % n; };
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd<ull>(x > y ? x - y : y - x, n);
    }
    return d == n ? pollards_rho(n) : d;
}

void factor(ull n, vector<ull>& fac) {
    if (n == 1) return;
    if (isPrime(n)) {
        fac.push_back(n);
    } else {
        ull d = pollards_rho(n);
        factor(d, fac);
        factor(n / d, fac);
    }
}

//-----------------diophantine----------------------//
template<typename T>
T extgcd(T a, T b, T &x, T &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  T p = b / a;
  T g = extgcd(b - p * a, a, y, x);
  x -= p * y;
  return g;
}
 
template<typename T>
bool diophantine(T a, T b, T c, T &x, T &y, T &g) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      x = y = g = 0;
      return true;
    }
    return false;
  }
  if (a == 0) {
    if (c % b == 0) {
      x = 0;
      y = c / b;
      g = abs(b);
      return true;
    }
    return false;
  }
  if (b == 0) {
    if (c % a == 0) {
      x = c / a;
      y = 0;
      g = abs(a);
      return true;
    }
    return false;
  }
  g = extgcd(a, b, x, y);
  if (c % g != 0) {
    return false;
  }
  T dx = c / a;
  c -= dx * a;
  T dy = c / b;
  c -= dy * b;
  x = dx + (T) ((__int128) x * (c / g) % b);
  y = dy + (T) ((__int128) y * (c / g) % a);
  g = abs(g);
  return true;
}
 
bool crt(int64_t k1, int64_t m1, int64_t k2, int64_t m2, int64_t &k, int64_t &m) {
  k1 %= m1;
  if (k1 < 0) k1 += m1;
  k2 %= m2;
  if (k2 < 0) k2 += m2;
  int64_t x, y, g;
  if (!diophantine(m1, -m2, k2 - k1, x, y, g)) {
    return false;
  }
  int64_t dx = m2 / g;
  int64_t delta = x / dx - (x % dx < 0); //the floor x/dx, and if x is negative, then we subtract 1 
  k = m1 * (x - dx * delta) + k1;
  m = m1 / g * m2;
  assert(0 <= k && k < m);
  return true;
}

