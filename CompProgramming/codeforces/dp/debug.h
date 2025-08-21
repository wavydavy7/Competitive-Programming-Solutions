#undef _GLIBCXX_DEBUG
 
#include <bits/stdc++.h>
using namespace std;
 
template <typename A, typename B>
string to_string(pair<A, B> p);
 
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);
 
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);
 
string to_string(const string& s) {
  return '"' + s + '"';
}
 
string to_string(const char* s) {
  return to_string((string) s);
}
 
string to_string(bool b) {
  return (b ? "true" : "false");
}
 
string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
string to_string(vector<char> v) {
    string res = "\n{";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) res += " ";
        res += "'";
        res += v[i]; // Treat each char as a single character
        res += "'";
    }
    res += "}\n";
    return res;
}

string to_string(vector<int> v) {
    string res = "\n{";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) res += " ";
        res += "'";
        res += to_string(v[i]); // Treat each char as a single character
        res += "'";
    }
    res += "}\n";
    return res;
}
 
template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename T>
string to_string(queue<T> q) {
    string res = "{";
    bool first = true;
    while (!q.empty()) {
        if (!first) res += ", ";
        first = false;
        res += to_string(q.front());
        q.pop();
    }
    res += "}";
    return res;
}
template <size_t X, size_t Y>
void debug_array(int (&dp)[X][Y]) {
    cerr << "2D Array Debugging: " << X << "x" << Y << "\n";
    for (size_t i = 0; i < X; ++i) {
        for (size_t j = 0; j < Y; ++j) {
            cerr << dp[i][j] << " ";
        }
        cerr << "\n";
    }
    cerr << "------------------------------------\n";
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
 
template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
 
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}
 
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

template<size_t N, typename... T>
typename enable_if<N == sizeof...(T), string>::type
to_string(const tuple<T...>& t) {
    return "";
}

template<size_t N = 0, typename... T>
typename enable_if<N < sizeof...(T), string>::type
to_string(const tuple<T...>& t) {
    return (N ? ", " : "") + to_string(get<N>(t)) + to_string<N + 1, T...>(t);
}


 
void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)