#include <cmath>

struct adouble;
adouble sin(const adouble& a);
struct adouble {
  double v;
  adouble(double a) : v(a) {}
  adouble(const adouble& other) : v(other.v) {}
  friend adouble sin(const adouble& a) {
    return adouble(sin(a.v));
  }
};

namespace Foam {
typedef double scalar;
scalar sin(double a) {
  return ::sin(a);
}

scalar cos(scalar a) {
  return ::cos(a);
}

double tan(scalar a) {
  return ::tan(a);
}

double cotan(double a) {
  return ::tan(a);
}

namespace lower {
scalar cos(scalar a) {
  return ::cos(a);
}
}

void caller() {
  scalar a(10.0);
  Foam::sin(10.0);
  Foam::sin(a);
  Foam::cos(10.0);
  Foam::cos(a);
  Foam::tan(a);
  Foam::tan(10.0);
  Foam::cotan(a);
  Foam::cotan(10.0);
  ::Foam::lower::cos(10.0);
  ::sin(a);
  sin(a);
}
} // Foam

int main() {
  Foam::caller();
  return 0;
}
