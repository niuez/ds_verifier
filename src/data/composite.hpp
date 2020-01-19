#include <random>
#include <iostream>
#include <string>

namespace ds {

  template<class T>
  class composite {

    using self = composite<T>;
  public:
    using value_type = T;
  private:
    value_type a, b;
  public:
    static std::string name() { return std::string("composite<") + T::name() + std::string(">"); }

    template<class Gen>
    static self generate(Gen& gen) {
      value_type a = value_type::generate(gen);
      value_type b = value_type::generate(gen);
      return composite(a, b);
    }

    composite(): a(1), b(0) {}
    composite(const value_type& a, const value_type& b): a(a), b(b) {}

    self& operator+=(const self& c) {
      b = a * c.b + b;
      a = a * c.a;
      return *this;
    }
    self& operator+(const self& c) const { return composite(*this) += c; }

    bool operator==(const self& c) const { return a == c.a && b == c.b; }
    bool operator!=(const self& c) const { return !(*this == c); }

    template<class U>
    friend std::ostream& operator<<(std::ostream&, const composite<U>&);
  };

  template<class T>
  std::ostream& operator<<(std::ostream& os, const composite<T>& c) {
    return os << "(" << c.a << ", " << c.b << ")";
  }
}
