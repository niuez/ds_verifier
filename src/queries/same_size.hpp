#ifndef SAME_SIZE_HPP
#define SAME_SIZE_HPP

#include <utility>
#include <random>
#include <sstream>
#include <verify_status.hpp>

namespace ds {

  template<class T>
  class same_size {
  public:
    
    static constexpr const char* name() { return "check same size"; }

  public:

    using size_type = std::size_t;
    using value_type = T;

    using arg_type = size_type;
    using result_type = value_type;
    using query_type = same_size<value_type>;

  public: 

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      if(target.size() != checker.size()) {
        std::stringstream ss;
        ss << "target size is " << target.size() << " but checker size is" << checker.size();
        throw fail_at(query_type::name(), ss.str());
      }
    }
  };
}

#endif
