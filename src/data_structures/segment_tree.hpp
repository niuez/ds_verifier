#ifndef DATA_STRUCTURES_SEGMENT_TREE_HPP
#define DATA_STRUCTURES_SEGMENT_TREE_HPP

#include <vector>

namespace niu {

  using namespace std;
  using i64 = long long;

  template<class T>
  struct segment_tree {
    static T ope(const T& a, const T& b) {
      return a + b;
    }
    static T ide() { return T(); }

    std::size_t len;
    i64 n;
    vector<T> node;

    segment_tree() {}
    segment_tree(const vector<T>& init) : len(init.size()) {
      n = 1;
      while(n < init.size()) n *= 2;
      node.resize(2 * n, ide());
      for(int i = 0;i < init.size();i++) node[i + n] = init[i];
      for(int i = n - 1; i >= 1;i--) node[i] = ope(node[i * 2], node[i * 2 + 1]);
    }

    std::size_t size() const { return len; }


    void update(i64 i, T x) {
      i += n;
      node[i] = x;
      while(i > 1) {
        i = i / 2;
        node[i] = ope(node[i * 2], node[i * 2 + 1]);
      }
    }

    T at(i64 i) {
      return node[i + n];
    }

    /* [l, r) */
    T sum(i64 l, i64 r) {
      T lx = ide();
      T rx = ide();
      l += n;
      r += n - 1;
      while(l < r) {
        if(l & 1) { lx = ope(lx, node[l]); }
        if(!(r & 1)) { rx = ope(node[r], rx); }
        l = (l + 1) >> 1;
        r = (r - 1) >> 1;
      }
      if(l == r) { lx = ope(lx, node[l]); }
      return ope(lx, rx);
    }
  };
}

#endif
