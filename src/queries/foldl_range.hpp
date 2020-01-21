#ifndef FOLDL_RANGE_HPP
#define FOLDL_RANGE_HPP

#include <utility>
#include <random>
#include <sstream>
#include <verify_status.hpp>
#include <queries/same_size.hpp>

namespace ds {

  template<class T>
  class foldl_range {
  private:
    same_size<T> size_checker;
  public:
    
    static json11::Json json() {
      return json11::Json::object({
          { "name", "foldl_range"  }
          });
    }

  public:

    using size_type = std::size_t;
    using value_type = T;

    struct arg_t {
      size_type l;
      size_type r;
    };

    using arg_type = arg_t;
    using result_type = value_type;
    using query_type = foldl_range<value_type>;

  public: 

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      size_checker.template check<Gen, Target, Checker>(gen, target, checker);
      size_type l, r;
      do {
        l = std::uniform_int_distribution<size_type>(0, target.size())(gen);
        r = std::uniform_int_distribution<size_type>(0, target.size())(gen);
        if(r < l) std::swap(l, r);
      } while(l == r);
      const result_type tres = target.template query<query_type>(arg_type { l, r });
      const result_type cres = checker.template query<query_type>(arg_type { l, r });

      if(tres != cres) {
        std::stringstream ss;
        ss << "[" << l << ", " << r << ")" << "target results " << tres << " but checker results" << cres;
        throw fail_at("foldl_from0", ss.str());
      }
    }
  };
}

#endif
