#include <cstddef>
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
  std::size_t i = reinterpret_cast<std::size_t>(ptr);
  i = static_cast<std::size_t>(a);

  int xx = int(reCast<int, scalar>(a));
}
