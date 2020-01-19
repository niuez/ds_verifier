#include <cstdint>
#include <random>
#include <string>
#include <iostream>

namespace ds {
  template<const std::uint32_t M>
  class modint {
    using i64 = std::int64_t;
    i64 a;
  public:

    static std::string name() { return std::string("modint<") + std::to_string(M) + std::string(">"); }
    template<class Gen>
    static modint<M> generate(Gen& gen) {
      return modint<M>(std::uniform_int_distribution<i64>(0,M - 1)(gen));
    }

    constexpr modint(const i64 x = 0) noexcept: a((x % M + M) % M) {}
    constexpr i64 value() const noexcept { return a; }
    constexpr modint pow(i64 r) const noexcept {
      modint ans(1);
      modint aa = *this;
      while(r) {
        if(r & 1) {
          ans *= aa;
        }
        aa *= aa;
        r >>= 1;
      }
      return ans;
    }
    constexpr modint& operator+=(const modint r) noexcept {
      a += r.a;
      if(a >= M) a -= M;
      return *this;
    }
    constexpr modint& operator=(const i64 r) {
      a = (r % M + M) % M;
      return *this;
    }
    constexpr modint& operator-=(const modint r) noexcept {
      a -= r.a;
      if(a < 0) a += M;
      return *this;
    }
    constexpr modint& operator*=(const modint r) noexcept {
      a = a * r.a % M;
      return *this;
    }
    constexpr modint& operator/=(modint r) noexcept {
      i64 ex = M - 2;
      while(ex) {
        if(ex & 1) {
          *this *= r;
        }
        r *= r;
        ex >>= 1;
      }
      return *this;
    }

    constexpr modint operator+(const modint r) const {
      return modint(*this) += r;
    }
    constexpr modint operator-(const modint r) const {
      return modint(*this) -= r;
    }
    constexpr modint operator*(const modint r) const {
      return modint(*this) *= r;
    }
    constexpr modint operator/(const modint r) const {
      return modint(*this) /= r;
    }
    constexpr bool operator==(const modint r) const {
      return a == r.a;
    }
    constexpr bool operator!=(const modint r) const {
      return a != r.a;
    }
    template<const std::uint32_t N>
    friend std::ostream& operator<<(std::ostream&, const modint<N>&);
  };

  using modint998244353 = modint<998244353>;

  template<const std::uint32_t M>
  std::ostream& operator<<(std::ostream& os, const modint<M>& m) {
    os << "(" << m.value() << " [mod" << M << "])";
    return os;
  }
}
