#ifndef INIT_INITONCE_HPP
#define INIT_INITONCE_HPP

#include <vector>
#include <string>
#include <json11/json11.h>

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

    static json11::Json json() {
      return json11::Json::object({
            { "name", "init_once" },
            { "init_method", init_query::json() },
            { "query", query_type::json() }
          });
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
