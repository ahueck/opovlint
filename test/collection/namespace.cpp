// RUN: find-typeDebug %s -- | FileCheck-3.6 %s
// XFAIL: *
#include <cmath>

struct adouble;
adouble sin(const adouble& a);
struct adouble {
  double v;
  adouble(double a) : v(a) {
  }
  adouble(const adouble& other) : v(other.v) {
  }
  friend adouble sin(const adouble& a) {
    return adouble(sin(a.v));
  }
};

namespace Foam {
typedef double scalar;

scalar mag(scalar c) {
  return c;
}
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

class edge {
 public:
  scalar ns_test(scalar c);
  // scalar mag(const edge&);
};

class vec {
 public:
  scalar mag(const vec&);
};

scalar vec::mag(const vec& a) {
  return 0.0;
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
  edge e;
  e.ns_test(10.0);
}
}  // Foam

Foam::scalar Foam::edge::ns_test(Foam::scalar c) {
  return mag(c);
}

int main() {
  Foam::caller();
  return 0;
}
