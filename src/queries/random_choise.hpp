#include <utility>
#include <cassert>
#include <random>
#include <string>

namespace ds {

  template<class Q, class... Qs>
  class random_choise {
  public:
    using size_type = std::size_t;
    using query_type = Q;
    using qs_type = random_choise<Qs...>;

    const static size_type query_size = sizeof...(Qs) + 1;

  private:
    query_type query;
    qs_type qs;

  public:

    static std::string name_rec() {
      return std::string("[") + query_type::name() + "], " + qs_type::name_rec();
    }

    static std::string name() {
      return std::string("random_choise from ") + name_rec();
    }

    template<class Gen, class Target, class Checker>
    void check_rec(size_type n, Gen& gen, Target& target, Checker& checker) {
      if(sizeof...(Qs) == n) query.check(gen, target, checker);
      else qs.template check_rec<Gen, Target, Checker>(n, gen, target, checker);
    }

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      size_type qn = std::uniform_int_distribution<size_type>(0, query_size - 1)(gen);
      this->template check_rec<Gen, Target, Checker>(qn, gen, target, checker);
    }
  };

  template<class Q>
  class random_choise<Q> {
  public:
    using size_type = std::size_t;
    using query_type = Q;

    const static size_type query_size = 1;

  private:
    query_type query;

  public:

    static std::string name_rec() {
      return std::string("[") + query_type::name() + "]";
    }

    static std::string name() {
      return std::string("random_choise from ") + name_rec();
    }

    template<class Gen, class Target, class Checker>
    void check_rec(size_type n, Gen& gen, Target& target, Checker& checker) {
      query.check(gen, target, checker);
    }

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      size_type qn = std::uniform_int_distribution<size_type>(0, query_size - 1)(gen);
      this->template check_rec<Gen, Target, Checker>(qn, gen, target, checker);
    }
  };
}
