#ifndef ACCESS_AT_HPP
#define ACCESS_AT_HPP

#include <utility>
#include <random>
#include <sstream>
#include <verify_status.hpp>

namespace ds {

  template<class T>
  class access_at {
  public:
    
    static constexpr const char* name() { return "access at"; }

  public:

    using size_type = std::size_t;
    using value_type = T;

    using arg_type = size_type;
    using result_type = value_type;
    using query_type = access_at<value_type>;

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
        ss << "[access_at] target results " << tres << " but checker results" << cres;
        throw fail_at(query_type::name(), ss.str());
      }
    }
  };
}

#endif
