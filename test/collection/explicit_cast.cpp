#include "reCast.h"
#pragma clang diagnostic ignored "-Wunused-value"

typedef double scalar;
inline void test(scalar a) {
}

inline scalar test_ret(scalar a) {
  return 1.0;
}

inline void broken() {
  scalar a, b, c, d = 1.0;
  scalar* ptr = &a;
  static_cast<scalar>(*ptr);
  static_cast<scalar*>(&a);
  static_cast<scalar*>(ptr);
  unsigned long long i = reinterpret_cast<unsigned long long>(ptr);
  i = static_cast<unsigned long long>(a);

  int xx = int(reCast<int, scalar>(a));
}
