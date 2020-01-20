#ifndef ARRAY_WRAPPER_SEGMENT_TREE_HPP
#define ARRAY_WRAPPER_SEGMENT_TREE_HPP

#include <vector>
#include <string>
#include <array_wrapper.hpp>
#include <queries/foldl_from0.hpp>
#include <queries/foldl_range.hpp>
#include <queries/access_at.hpp>
#include <queries/update_at.hpp>
#include <data_structures/segment_tree.hpp>

namespace ds {

  template<class T>
  class array_wrapper<T, niu::segment_tree<T>> {

  public:

    static constexpr const char* name() { return "segment_tree";  }


  public:
    using size_type = std::size_t;
    using value_type = T;
    using ds_type = niu::segment_tree<value_type>;

  private:

    niu::segment_tree<value_type> seg;

  public:

    array_wrapper() {};
    array_wrapper(const std::vector<T>& init) : seg(init) {}

    size_type size() const {
      return seg.size();
    }

    template<class Query, class = void> struct QueryFunc {};

    template<class V> struct QueryFunc<foldl_from0<value_type>, V> {
      typename foldl_from0<value_type>::result_type
      static query(ds_type& seg, const typename foldl_from0<value_type>::arg_type& r) {
        return seg.sum(0, r);
      }
    };

    template<class V> struct QueryFunc<foldl_range<value_type>, V> {
      typename foldl_range<value_type>::result_type
      static query(ds_type& seg, const typename foldl_range<value_type>::arg_type& range) {
        return seg.sum(range.l, range.r);
      }
    };

    template<class V> struct QueryFunc<access_at<value_type>, V> {
      typename access_at<value_type>::result_type
      static query(ds_type& seg, const typename access_at<value_type>::arg_type& arg) {
        return seg.at(arg);
      }
    };

    template<class V> struct QueryFunc<update_at<value_type>, V> {
      typename update_at<value_type>::result_type
      static query(ds_type& seg, const typename update_at<value_type>::arg_type& arg) {
        seg.update(arg.idx, arg.new_value);
        return 0;
      }
    };

    template<class Query>
    typename Query::result_type query(const typename Query::arg_type& arg) {
      return QueryFunc<Query>::query(seg, arg);
    }
  };
}

#endif
