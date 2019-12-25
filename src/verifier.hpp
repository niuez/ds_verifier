#ifndef VERIFIER_HPP
#define VERIFIER_HPP

#include <utility>
#include <verify_status.hpp>

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
          Query query(gen, target);
          query.check(checker);
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
