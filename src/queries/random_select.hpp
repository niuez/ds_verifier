#include <utility>
#include <cassert>
#include <random>
#include <string>
#include <algorithm>
#include <json11/json11.h>

namespace ds {

  template<class Q, class... Qs>
  class random_select {
  public:
    using size_type = std::size_t;
    using query_type = Q;
    using qs_type = random_select<Qs...>;

    const static size_type query_size = sizeof...(Qs) + 1;

  private:
    query_type query;
    qs_type qs;

  public:

    static std::vector<json11::Json> json_rec() {
      std::vector<json11::Json> vec = qs_type::json_rec();
      vec.push_back(query_type::json());
      return vec;
    }

    static json11::Json json() {
      std::vector<json11::Json> queries_json = json_rec();
      std::reverse(begin(queries_json), end(queries_json));
      return json11::Json::object({
          { "name", "random_select" },
          { "queries", queries_json  }
          });
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
  class random_select<Q> {
  public:
    using size_type = std::size_t;
    using query_type = Q;

    const static size_type query_size = 1;

  private:
    query_type query;

  public:

    static std::vector<json11::Json> json_rec() {
      std::vector<json11::Json> vec;
      vec.push_back(query_type::json());
      return vec;
    }

    static json11::Json json() {
      std::vector<json11::Json> queries_json = json_rec();
      std::reverse(begin(queries_json), end(queries_json));
      return json11::Json::object({
          { "name", "query_process" },
          { "process", queries_json  }
          });
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
