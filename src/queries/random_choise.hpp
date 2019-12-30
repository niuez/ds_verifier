#include <utility>
#include <cassert>
#include <random>
#include <string>

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
        else random_choise::Checker<Qs...>::template checker<Gen, Target, Checker>(n, gen, target, checker);
      }
      static std::string name() {
        return "[" + std::string(Q::name()) + "], " + Checker<Qs...>::name();
      }
    };

    template<class Q>
    struct Checker<Q> {
      template<class Gen, class Target, class Checker>
      static void checker(size_type n, Gen& gen, Target& target, Checker& checker) {
        assert(n == 0);
        Q::check(gen, target, checker);
      }
      static std::string name() {
        return "[" + std::string(Q::name()) + "]";
      }
    };


  public:

    static std::string name() {
      return std::string("random_choise from ") + Checker<Queries...>::name();
    }

    template<class Gen, class Target, class Checker>
    static void check(Gen& gen, Target& target, Checker& checker) {
      size_type qn = std::uniform_int_distribution<size_type>(0, query_size - 1)(gen);
      random_choise::Checker<Queries...>::checker(qn, gen, target, checker);
    }
  };
}
