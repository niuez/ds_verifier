#ifndef VERIFIER_HPP
#define VERIFIER_HPP

#include <utility>

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

    verifier() {}

    bool operator()(Gen& gen) const {
      init_method init(gen);
      target_type target = init.template initialize<target_type>();
      checker_type checker = init.template initialize<checker_type>();

      for(size_type i = 0; i < Q; i++) {
        Query query;
        Gen checker_gen = gen;
        if(query(gen, target) != query(checker_gen, checker)) {
          return false;
        }
      }
      return true;
    }
  };
}

#endif
