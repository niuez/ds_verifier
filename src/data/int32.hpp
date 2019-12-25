#include <random>

namespace ds {

  class int32 {
    
    int i;
  public:
    int32() : i(0) {}
    int32(int i) : i(i) {}
    
    template<class Gen>
    int32(Gen& gen) : i(std::uniform_int_distribution<int>(0, 100)(gen)) {}


    operator int() const { return i; }
  };
}
