#ifndef ARRAY_WRAPPER_VECTOR_HPP
#define ARRAY_WRAPPER_VECTOR_HPP

#include <vector>
#include <array_wrapper.hpp>
#include <string>

namespace ds {

  template<class T>
  class array_wrapper<T, std::vector<T>> {
    std::vector<T> arr;

  public:

    static constexpr const char* name() { return "std::vector";  }

  public:
    using size_type = std::size_t;
    using value_type = T;

    array_wrapper() {};
    array_wrapper(const std::vector<T>& init) : arr(init) {}

    value_type access_index(size_type i) const {
      return arr[i];
    }
    value_type accum_from0(size_type r) const {
      T ans = T();
      for(size_type i = 0;i < r;i++) {
        ans = ans + arr[i];
      }
      return ans;
    }
    size_type size() const {
      return arr.size();
    }
  };
}

#endif
