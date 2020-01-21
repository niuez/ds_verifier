#ifndef VERIFIER_HPP
#define VERIFIER_HPP

#include <utility>
#include <verify_status.hpp>
#include <json11/json11.h>

#define VERIFY_START() \
  int main() { \
    std::vector<json11::Json> status; \


#define VERIFY(st) (st).detail(std::cerr), status.push_back((st))

#define VERIFY_END() \
    std::cout << json11::Json(status).dump() << std::endl; \
    return 0; \
  }

namespace ds {

 template<
    class Target,
    class Checker,
    class Gen,
    const std::size_t Seed,
    class Query
  >
  class verifier {

  public:

    using size_type = std::size_t;
    using target_type = Target;
    using checker_type = Checker;
    using status_type = verify_status<Target, Checker, Gen, Seed, Query>;
    using query_type = Query;

    verifier() {}

    status_type operator()(const std::string& test_case) const {
      Gen gen(Seed);
      try {
        query_type query;
        target_type target;
        checker_type checker;
        query.check(gen, target, checker);
      }
      catch(const fail_at& f) {
        return status_type::failure(test_case, f);
      }
      return status_type::success(test_case);
    }
  };
}

#endif
