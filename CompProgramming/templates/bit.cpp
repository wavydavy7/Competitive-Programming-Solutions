// -------------------- fenwick template -------------------- //
template <typename T>
class fenwick {
 public:
  vector<T> fenw;
  int n;
 
  fenwick(int _n) : n(_n) {
    fenw.resize(n);
  }
 
  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }

  void modify(int x, int y, T v){
    modify(x, v);
    modify(y + 1, -v);
  }
 
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }

  T getr(int x, int y){
    return get(y) - get(x - 1);
  }
};
//fenwick<long long> fenw(n);