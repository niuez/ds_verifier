#ifndef ACCUMS_FROM0_HPP
#define ACCUMS_FROM0_HPP

#include <utility>
#include <random>
#include <sstream>
#include <verify_status.hpp>

namespace ds {

  template<class T>
  class accum_from0 {
  public:
    
    static constexpr const char* name() { return "accumlation from 0 index"; }

  public:

    using size_type = std::size_t;
    using value_type = T;

    using arg_type = size_type;
    using result_type = value_type;
    using query_type = accum_from0<value_type>;

  public: 

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {

      if(target.size() != checker.size()) {
        std::stringstream ss;
        ss << "target size is " << target.size() << " but checker size is" << checker.size();
        throw fail_at(query_type::name(), ss.str());
      }

      const arg_type r = std::uniform_int_distribution<size_type>(0, target.size())(gen);
      const result_type tres = target.template query<query_type>(r);
      const result_type cres = checker.template query<query_type>(r);

      if(tres != cres) {
        std::stringstream ss;
        ss << "target results " << tres << " but checker results" << cres;
        throw fail_at(query_type::name(), ss.str());
      }
    }
  };
}

#endif
