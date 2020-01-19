#ifndef ARRAY_WRAPPER_FENWICK_TREE_HPP
#define ARRAY_WRAPPER_FENWICK_TREE_HPP

#include <vector>
#include <string>
#include <array_wrapper.hpp>
#include <queries/accum_from0.hpp>
#include <queries/access_at.hpp>
#include <queries/update_at.hpp>
#include <queries/modify_at.hpp>
#include <data_structures/fenwick_tree.hpp>

namespace ds {

  template<class T>
  class array_wrapper<T, niu::fenwick_tree<T, std::plus<T>>> {

  public:

    static constexpr const char* name() { return "segment_tree";  }


  public:
    using size_type = std::size_t;
    using value_type = T;
    using ds_type = niu::fenwick_tree<value_type, std::plus<value_type>>;

  private:

    niu::fenwick_tree<value_type, std::plus<value_type>> fen;

  public:

    array_wrapper() {};
    array_wrapper(const std::vector<T>& init) : fen(init) {}

    size_type size() const {
      return fen.size();
    }

    template<class Query, class = void> struct QueryFunc {};

    template<class V> struct QueryFunc<accum_from0<value_type>, V> {
      typename accum_from0<value_type>::result_type
      static query(ds_type& fen, const typename accum_from0<value_type>::arg_type& r) {
        return fen.sum(r);
      }
    };

    template<class V> struct QueryFunc<update_at<value_type>, V> {
      typename modify_at<value_type>::result_type
      static query(ds_type& fen, const typename modify_at<value_type>::arg_type& arg) {
        fen.modify(arg.idx, arg.modify_value);
        return 0;
      }
    };

    template<class Query>
    typename Query::result_type query(const typename Query::arg_type& arg) {
      return QueryFunc<Query>::query(fen, arg);
    }
  };
}

#endif
