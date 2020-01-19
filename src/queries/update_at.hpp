#ifndef UPDATE_AT_HPP
#define UPDATE_AT_HPP

#include <utility>
#include <random>
#include <sstream>
#include <verify_status.hpp>
#include <queries/access_at.hpp>
#include <queries/same_size.hpp>

namespace ds {

  template<class T>
  class update_at {
  private:
    same_size<T> size_checker;
  public:
    
    static json11::Json json() {
      return json11::Json::object({
          { "name", "update_at"  }
          });
    }

  public:


    using size_type = std::size_t;
    using value_type = T;

    struct update_at_arg {
      size_type idx;
      value_type new_value;
    };

    using arg_type = update_at_arg;
    using result_type = int;
    using query_type = update_at<value_type>;

  public: 

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      size_checker.template check<Gen, Target, Checker>(gen, target, checker);

      const size_type idx = std::uniform_int_distribution<size_type>(0, target.size())(gen);
      const value_type new_value = value_type::generate(gen);
      target.template query<query_type>(update_at_arg { idx, new_value });
      checker.template query<query_type>(update_at_arg { idx, new_value });
    }
  };
}

#endif
