#include <random>
#include <iostream>

namespace ds {

  class int32 {
    
    int i;

  public:

    static constexpr const char* name() { return "int32"; }
    template<class Gen>
    static int32 generate(Gen& gen) {
      return int32(std::uniform_int_distribution<int>(0, 100)(gen));
    }

  public:
    int32() : i(0) {}
    int32(int i) : i(i) {}

    operator int() const { return i; }

    friend std::ostream& operator<<(std::ostream&, const int32&);
  };

  std::ostream& operator<<(std::ostream& os, const ds::int32& i) {
    return os << (int)(i);
  }

}

