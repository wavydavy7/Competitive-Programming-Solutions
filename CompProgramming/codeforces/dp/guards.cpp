#include <bits/stdc++.h>
// #include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 251;
int N, M;


template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }

  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }

  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular& operator+=(const Modular& other) { value += other.value; value -= (value >= mod()) * mod(); return *this; }
  Modular& operator-=(const Modular& other) { value -= other.value; value += (value < 0) * mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
    int64_t q = int64_t(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

  friend const Type& abs(const Modular& x) { return x.value; }

  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename V, typename U>
  friend V& operator>>(V& stream, Modular<U>& number);

 private:
  Type value;
};

template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
  return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
  return stream << number();
}

// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, int64_t>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

// using ModType = int;

// struct VarMod { static ModType value; };
// ModType VarMod::value;
// ModType& md = VarMod::value;
// using Mint = Modular<VarMod>;

constexpr int md = int(1e9) + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;
int gr[MX][MX];
Mint dp[MX][1 << 16][2][2]; 
int main(){
    cin >> N >> M;
    
    memset(gr, 0, sizeof(gr));
    for (int i = 0; i < N; i++){
        string s;
        cin >> s;
        for (int j = 0; j < M; j++){
            if (s[j] == 'x') {
                if (N > M) gr[j][i] = 1;
                else gr[i][j] = 1;
            }
            
        }
    }
    // debug(N);
    if (N > M){
        swap(N, M);
    }
    vector<int> bl(M, 0);
    for (int c = 0; c < M; c++){
        int num = 0;
        for (int r = 0; r < N; r++){
            if (gr[r][c]) num |= (1 << r);
        }
        bl[c] = num;
    }
    //debug(bl);
    memset(dp, 0, sizeof(dp));
    
    
    if (!gr[0][0]) {
        dp[0][1][0][1] = 1; //put one here 
        dp[0][0][1][0] = 1; //don't
    } 
    else {
        dp[0][0][0][0] = 1;
    }
    

    //N is the smaller one 
    for (int c = 0; c < M; c++){
        for (int r = 0; r < N; r++){
            int idx = (c * N) + r;
            if (idx == 0) continue;
            for (int msk = 0; msk < (1<<N); msk++){
                for (int m = 0; m < 2; m++){ //missing
                    for (int ab = 0; ab < 2; ab++){

                        //overcounting somehow
                        
                        if (gr[r][c]) {
                        
                            dp[idx][msk & (~0 ^ (1 << r))][m][0] += dp[idx - 1][msk][m][ab]; //we have to reduce rays   
                            
                        }
                        else{
                            int cannot = !(msk & (1 << r)) && (ab == 0 || r == 0); //there is nothing to help it 
                            dp[idx][msk | (1 << r)][m][1] += dp[idx - 1][msk][m][ab]; //choose to 
                            //don't choose 
                            if (cannot + m < 2){ //the min
                                dp[idx][msk][m + cannot][ab && (r > 0)] += dp[idx - 1][msk][m][ab];
                            }
                            // if (gr[r][c]) { //blocked
                            //     dp[idx][msk][m][0] += dp[idx - 1][msk][m][0]; 
                            //     dp[idx][msk][m][0] += dp[idx - 1][msk][m][1]; //one above gets negated
                            // }
                            // else if (msk & (1 << r)) { //empty space, hit
                            //     dp[idx][msk][m][1] += dp[idx - 1][msk][m][1]; 
                            //     dp[idx][msk][m][1] += dp[idx - 1][msk][m][0]; //by placing it here
                            //     dp[idx][msk][m][0] += dp[idx - 1][msk][m][0]; 
                            // }
                            // else { //not place, not hit
                            //     dp[idx][msk | (1 << r)][m][1] += dp[idx - 1][msk][m][0]; //you must put one here   
                                
                            //     dp[idx][msk | (1 << r)][m][1] += dp[idx - 1][msk][m][1]; 
                            //     dp[idx][msk][m][1] += dp[idx - 1][msk][m][1]; 
                            //     if (m == 0) dp[idx][msk][1][0] += dp[idx - 1][msk][0][0];
                            // }
                        }
                    }
                }
            }
        }
    }

    // for (int idx = 0; idx <M*N; idx++){
    //     for (int msk = 0; msk < (1 << 2); msk++){
    //         for (int mis = 0; mis < 2; mis++){
    //             for (int ab = 0; ab < 2; ab++){
    //                 auto x = {idx, msk, mis, ab};
    //                 debug(x);
    //                 debug(dp[idx][msk][mis][ab]);
    //             }
    //         }
    //     }
    // }
    // debug(dp[0][1][0][1]);
    // debug(dp[1][3][0][1]);
    // debug(dp[1][1][0][1]);
    // debug(dp[1][2][0][1]);
    // debug(dp[2][3][0][1]); 
    // debug(dp[2][3][1][1]);  
    Mint ans = 0;
    for (int msk = 0; msk < (1 << 16); msk++){
        for (int m = 0; m < 2; m++){
            for (int p = 0; p < 2; p++){
                ans += dp[M*N - 1][msk][m][p];
            }
        }
    }
    cout << ans;

    
}