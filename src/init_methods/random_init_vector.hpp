#ifndef INIT_METHODS_RANDOM_INIT_VECTOR_HPP
#define INIT_METHODS_RANDOM_INIT_VECTOR_HPP

#include <vector>

namespace ds {
  template<class T, const size_t N>
  class random_init_vector {

  public:
    using size_type = std::size_t;
    using value_type = T;

  private:

    std::vector<value_type> init;

  public:

    template<class Gen>
    random_init_vector(Gen& gen) : init(N) {
      for(size_type i = 0;i < N;i++) {
        init[i] = T(gen);
      }
    }

    template<class Target>
    Target initialize() const {
      return Target(init);
    }
  };
}

#endif
