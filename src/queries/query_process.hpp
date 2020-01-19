#include <utility>
#include <cassert>
#include <random>
#include <string>
#include <algorithm>
#include <json11/json11.h>

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

    static std::vector<json11::Json> json_rec() {
      std::vector<json11::Json> vec = qs_type::json_rec();
      vec.push_back(query_type::json());
      return vec;
    }

    static json11::Json json() {
      std::vector<json11::Json> queries_json = json_rec();
      std::reverse(begin(queries_json), end(queries_json));
      return json11::Json::object({
          { "name", "query_process" },
          { "query_count", (int)(Q_count) },
          { "process", queries_json  }
          });
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
          { "query_count", (int)(Q_count) },
          { "process", queries_json  }
          });
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
