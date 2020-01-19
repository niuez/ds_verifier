#include <utility>
#include <cassert>
#include <random>
#include <string>

namespace ds {

  template<const std::size_t Q_count, class Q, class... Qs>
  class query_process {
  public:
    using size_type = std::size_t;
    using query_type = Q;
    using qs_type = query_process<Q_count, Qs...>;

    const static size_type query_size = sizeof...(Qs) + 1;

  private:
    query_type query;
    qs_type qs;

  public:

    static std::string name_rec() {
      return std::string("[") + query_type::name() + "] -> " + qs_type::name_rec();
    }

    static std::string name() {
      return std::string("query_process for ")
           + std::to_string(Q_count)
           + std::string(" times { ") + name_rec() + std::string(" }");
    }

    template<class Gen, class Target, class Checker>
    void check_rec(Gen& gen, Target& target, Checker& checker) {
      query.check(gen, target, checker);
      qs.template check_rec<Gen, Target, Checker>(gen, target, checker);
    }

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      for(size_type q = 0; q < Q_count; q++) {
        this->template check_rec<Gen, Target, Checker>(gen, target, checker);
      }
    }
  };

  template<const std::size_t Q_count, class Q>
  class query_process<Q_count, Q> {
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
      return std::string("query_process for ")
           + std::to_string(Q_count)
           + std::string(" times { ") + name_rec() + std::string(" }");
    }

    template<class Gen, class Target, class Checker>
    void check_rec(Gen& gen, Target& target, Checker& checker) {
      query.check(gen, target, checker);
    }

    template<class Gen, class Target, class Checker>
    void check(Gen& gen, Target& target, Checker& checker) {
      for(size_type q = 0; q < Q_count; q++) {
        this->template check_rec<Gen, Target, Checker>(gen, target, checker);
      }
    }
  };
}
