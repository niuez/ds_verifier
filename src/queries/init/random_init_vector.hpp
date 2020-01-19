#ifndef INIT_RANDOM_INIT_VECTOR_HPP
#define INIT_RANDOM_INIT_VECTOR_HPP

#include <vector>
#include <string>
#include <json11/json11.h>

namespace ds {
  template<class T, const size_t N>
  class random_init_vector {

  public:
    using size_type = std::size_t;
    using value_type = T;

  public:

    static json11::Json json() {
      return json11::Json::object({
            { "name", "random_init_vector" },
            { "type", value_type::name() },
            { "size", (int)N }
          });
    }
  public:

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) const {
      std::vector<value_type> init(N);
      for(size_type i = 0;i < N;i++) {
        init[i] = value_type::generate(gen);
      }
      target = Target(init);
      checker = Checker(init);
    }
  };
}

#endif
