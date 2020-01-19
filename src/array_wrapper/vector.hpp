#ifndef ARRAY_WRAPPER_VECTOR_HPP
#define ARRAY_WRAPPER_VECTOR_HPP

#include <vector>
#include <string>
#include <array_wrapper.hpp>
#include <queries/accum_from0.hpp>
#include <queries/access_at.hpp>
#include <queries/update_at.hpp>
#include <queries/modify_at.hpp>

namespace ds {

  template<class T>
  class array_wrapper<T, std::vector<T>> {

  public:

    static constexpr const char* name() { return "std::vector";  }


  public:
    using size_type = std::size_t;
    using value_type = T;
    using ds_type = std::vector<value_type>;

  private:

    std::vector<value_type> arr;

  public:

    array_wrapper() {};
    array_wrapper(const std::vector<T>& init) : arr(init) {}

    size_type size() const {
      return arr.size();
    }

    template<class Query, class = void> struct QueryFunc {};

    template<class V> struct QueryFunc<accum_from0<value_type>, V> {
      typename accum_from0<value_type>::result_type
      static query(ds_type& arr, const typename accum_from0<value_type>::arg_type& r) {
        T ans = T();
        for(size_type i = 0;i < r;i++) {
          ans = ans + arr[i];
        }
        return ans;
      }
    };

    template<class V> struct QueryFunc<access_at<value_type>, V> {
      typename access_at<value_type>::result_type
      static query(ds_type& arr, const typename access_at<value_type>::arg_type& arg) {
        return arr[arg];
      }
    };

    template<class V> struct QueryFunc<update_at<value_type>, V> {
      typename update_at<value_type>::result_type
      static query(ds_type& arr, const typename update_at<value_type>::arg_type& arg) {
        arr[arg.idx] = arg.new_value;
        return 0;
      }
    };

    template<class V> struct QueryFunc<modify_at<value_type>, V> {
      typename modify_at<value_type>::result_type
      static query(ds_type& arr, const typename modify_at<value_type>::arg_type& arg) {
        arr[arg.idx] = arr[arg.idx] + arg.modify_value;
        return 0;
      }
    };

    template<class Query>
    typename Query::result_type query(const typename Query::arg_type& arg) {
      return QueryFunc<Query>::query(arr, arg);
    }
  };
}

#endif
