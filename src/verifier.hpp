#ifndef VERIFIER_HPP
#define VERIFIER_HPP

#include <utility>
#include <verify_status.hpp>
#include <json11/json11.h>

#define VERIFY_START() \
  int main() { \
    std::vector<json11::Json> status; \


#define VERIFY(st) status.push_back((st))

#define VERIFY_END() \
    std::cout << json11::Json(status).dump() << std::endl; \
    return 0; \
  }

namespace ds {

 template<
    class Target,
    class Checker,
    class Gen,
    class InitMethod,
    const std::size_t Q,
    class Query
  >
  class verifier {

  public:

    using size_type = std::size_t;
    using target_type = Target;
    using checker_type = Checker;
    using init_method = InitMethod;
    using status_type = verify_status<Target, Checker, Gen, InitMethod, Q, Query>;

    verifier() {}

    status_type operator()(Gen& gen, const std::string& test_case) const {
      try {
        init_method init(gen);
        target_type target = init.template initialize<target_type>();
        checker_type checker = init.template initialize<checker_type>();
        for(size_type i = 0; i < Q; i++) {
          Query::check(gen, target, checker);
        }
      }
      catch(const fail_at& f) {
        return status_type::failure(test_case, f);
      }
      return status_type::success(test_case);
    }
  };
}

#endif
