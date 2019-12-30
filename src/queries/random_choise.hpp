#include <utility>
#include <cassert>
#include <random>

namespace ds {

  template<class... Queries>
  class random_choise {
  public:
    using size_type = std::size_t;

    const static size_type query_size = sizeof...(Queries);

  private:

    template<class Q, class... Qs>
    struct Checker {
      template<class Gen, class Target, class Checker>
      static void checker(size_type n, Gen& gen, Target& target, Checker& checker) {
        if(sizeof...(Qs) == n) Q::check(gen, target, checker);
        else Checker<Qs...>::checker(n, gen, target, checker);
      }
    };

    template<class Q>
    struct Checker<Q> {
      template<class Gen, class Target, class Checker>
      static void checker(size_type n, Gen& gen, Target& target, Checker& checker) {
        assert(n == 0);
        Q::check(gen, target, checker);
      }
    };

  public:

    template<class Gen, class Target, class Checker>
    static void check(Gen& gen, Target& target, Checker& checker) {
      size_type qn = std::uniform_int_distribution<size_type>(0, query_size - 1)(gen);
      random_choise::Checker<Queries...>::checker(qn, gen, target, checker);
    }
  };
}
