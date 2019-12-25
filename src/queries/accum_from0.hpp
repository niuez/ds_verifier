#ifndef ACCUMS_FROM0_HPP
#define ACCUMS_FROM0_HPP

#include <utility>
#include <random>
#include <iostream>

namespace ds {

  template<class T>
  class accum_from0_query {

  public:

    using size_type = std::size_t;


    accum_from0_query() {}

    template<class Gen, class Target>
    T operator()(Gen& gen, Target& target) const {
      const size_type r = std::uniform_int_distribution<size_type>(0, target.size())(gen);
      return target.accum_from0(r);
    }

  };
}

#endif
