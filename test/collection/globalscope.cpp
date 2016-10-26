// RUN: find-typeDebug %s -- | FileCheck-3.6 %s
// XFAIL: *
#pragma clang diagnostic ignored "-Wunused-value"

#include <vector>
#include <cmath>

typedef double scalar;

class X;
int a = 1;
scalar b = 1.0;
double c = 2.0;

void f(const X& x);

class X {
 public:
  friend void f(const X& x) {
  }
};

void g(scalar a);
void h(double b);

namespace ns {
void f(const X& x);
void g(scalar z);
void f();
void call() {
  ::f(X());
  ns::f(X());
  f();
  ::a;
  ::b;
  ::g(scalar(1.0));
  ::g(::b);
  ::g(::b * scalar(1));
  ::h(::b);
  ::g(b);
  g(scalar(1.0));
  ns::g(scalar(1.0));
  ::ns::g(scalar(1.0));

  std::vector<scalar> v;
  v.push_back(::b);
  ::sqrt(::b);
}
}
