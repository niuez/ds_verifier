#ifndef ARRAY_WRAPPER_ACCUM_HPP
#define ARRAY_WRAPPER_ACCUM_HPP

#include <vector>
#include <data_structures/accumulation.hpp>
#include <array_wrapper.hpp>

namespace ds {

  template<class T>
  class array_wrapper<T, accumulation<T>> {
    

  public:
    using size_type = std::size_t;
    using value_type = T;

  private:
    accumulation<value_type> accum;

  public:

    static constexpr const char* name() { return "accumulation"; }

  public:
    array_wrapper() {};
    array_wrapper(const std::vector<T>& init) : accum(init) {}

    value_type accum_from0(size_type r) const {
      return accum.accum_from0(r);
    }
    size_type size() const {
      return accum.size();
    }
  };
}

#endif
