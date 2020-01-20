#ifndef ARRAY_WRAPPER_ACCUM_HPP
#define ARRAY_WRAPPER_ACCUM_HPP

#include <vector>
#include <data_structures/accumulation.hpp>
#include <array_wrapper.hpp>
#include <queries/foldl_from0.hpp>

namespace ds {

  template<class T>
  class array_wrapper<T, accumulation<T>> {
    

  public:
    using size_type = std::size_t;
    using value_type = T;
    using ds_type = accumulation<value_type>;

  private:
    accumulation<value_type> accum;

  public:

    static constexpr const char* name() { return "accumulation"; }

  public:
    array_wrapper() {};
    array_wrapper(const std::vector<T>& init) : accum(init) {}

    size_type size() const {
      return accum.size();
    }

    template<class Query, class = void> struct QueryFunc {};

    template<class V> struct QueryFunc<foldl_from0<value_type>, V> {
      typename foldl_from0<value_type>::result_type
      static query(ds_type& accum, const typename foldl_from0<value_type>::arg_type& r) {
        return accum.foldl_from0(r);
      }
    };

    template<class Query>
    typename Query::result_type query(const typename Query::arg_type& arg) {
      return QueryFunc<Query>::query(accum, arg);
    }
  };


}

#endif
