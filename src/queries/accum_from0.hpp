#ifndef ACCUMS_FROM0_HPP
#define ACCUMS_FROM0_HPP

#include <utility>
#include <random>
#include <sstream>
#include <verify_status.hpp>

namespace ds {

  template<class T>
  class accum_from0_query {


  public:
    
    static constexpr const char* name() { return "accumlate from 0 index"; }

  public:

    using size_type = std::size_t;
    using value_type = T;

  private:

    const size_type r;
    const value_type result;

  public: 

    template<class Gen, class Target>
    accum_from0_query(Gen& gen, Target& target)
      : r(std::uniform_int_distribution<size_type>(0, target.size())(gen)), result(target.accum_from0(r)) {}
    

    template<class Checker>
    void check(Checker& checker) const {
      const value_type checker_result = checker.accum_from0(r);
      if(result != checker_result) {
        std::stringstream ss;
        ss << "target results " << result << " but checker results" << checker_result;
        throw fail_at(accum_from0_query<T>::name(), ss.str());
      }
    }
  };
}

#endif
