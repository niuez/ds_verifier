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
      target_type target = init_method::template generate<target_type>(gen);
      checker_type checker = init_method::template generate<checker_type>(gen);

      for(size_type i = 0; i < Q; i++) {
        Query query;
        if(query(gen, target) != query(gen, target)) {
          return false;
        }
      }
      return true;
    }
  };
}
