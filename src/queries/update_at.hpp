#ifndef UPDATE_AT_HPP
#define UPDATE_AT_HPP

#include <utility>
#include <random>
#include <sstream>
#include <verify_status.hpp>
#include <queries/access_at.hpp>

namespace ds {

  template<class T>
  class update_at {
  public:
    
    static constexpr const char* name() { return "update at"; }

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

      if(target.size() != checker.size()) {
        std::stringstream ss;
        ss << "target size is " << target.size() << " but checker size is" << checker.size();
        throw fail_at(query_type::name(), ss.str());
      }

      const size_type idx = std::uniform_int_distribution<size_type>(0, target.size())(gen);
      const value_type new_value = value_type::generate(gen);
      target.template query<query_type>(update_at_arg { idx, new_value });
      checker.template query<query_type>(update_at_arg { idx, new_value });


      // update check
      const value_type tres = target.template query<access_at<value_type>>(idx);
      const value_type cres = checker.template query<access_at<value_type>>(idx);
      if(tres != new_value || cres != new_value) {
        std::stringstream ss;
        ss << "[access_at] new_value is " << new_value << " but target results " << tres << "and checker results" << cres;
        throw fail_at(query_type::name(), ss.str());
      }
    }
  };
}

#endif
