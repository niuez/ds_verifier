#ifndef FOLDL_FROM0_ALL_HPP
#define FOLDL_FROM0_ALL_HPP

#include <utility>
#include <random>
#include <sstream>
#include <verify_status.hpp>
#include <queries/foldl_from0.hpp>

namespace ds {

  template<class T>
  class foldl_from0_all {
  public:
    
    static json11::Json json() {
      return json11::Json::object({
          { "name", "foldl_from0_all"  }
          });
    }

  public:

    using size_type = std::size_t;
    using value_type = T;

    using arg_type = typename foldl_from0<value_type>::arg_type;
    using result_type = typename foldl_from0<value_type>::result_type;
    using query_type = foldl_from0<value_type>;

  public: 

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      for(size_type i = 0; i < target.size(); i++) {
        const arg_type r = i;
        const result_type tres = target.template query<query_type>(r);
        const result_type cres = checker.template query<query_type>(r);

        if(tres != cres) {
          std::stringstream ss;
          ss << "r = " << r << " : target results " << tres << " but checker results" << cres;
          throw fail_at("foldl_from0_all", ss.str());
        }
      }
    }
  };
}

#endif
