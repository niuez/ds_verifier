#ifndef DATA_STRUCTURES_ACCUM_HPP
#define DATA_STRUCTURES_ACCUM_HPP

#include <vector>

namespace ds {
  template<class T>
  class accumulation {
  public:

    using value_type = T;
    using size_type = std::size_t;

  private:

    size_type N;
    std::vector<value_type> arr;

  public:

    accumulation(): N(0), arr(1) {}
    accumulation(const std::vector<value_type>& init)
      : N(init.size()), arr(N + 1) {
        for(size_type i = 0;i < init.size(); i++) {
          arr[i + 1] = arr[i] + init[i];
        }
      }

    value_type accum_from0(size_type r) const {
      return arr[r];
    }
    size_type size() const {
      return N;
    }
  };
}

#endif
