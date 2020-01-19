#ifndef INIT_INITONCE_HPP
#define INIT_INITONCE_HPP

#include <vector>
#include <string>

namespace ds {
  template<class Init, class Q>
  class init_once {

  public:
    using init_query = Init;
    using query_type = Q;

  private:

    init_query init;
    query_type query;

  public:

    static std::string name() {
      return std::string("init once by { ")
           + std::string(init_query::name())
           + std::string(" }, and query { ")
           + query_type::name()
           + std::string(" }");
    }

  public:

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      init.template check<Gen, Target, Checker>(gen, target, checker);
      query.template check<Gen, Target, Checker>(gen, target, checker);
    }
  };
}

#endif
