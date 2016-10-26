// RUN: find-typeDebug %s -- | FileCheck-3.6 %s
// XFAIL: *
typedef double scalar;

scalar ret(scalar a) {
  return a > 0 ? a : 0.0;
}

scalar ret2(scalar b) {
  return ret(b > 0 ? b : 0.0);
}

inline void test(scalar a) {
}

inline void func(scalar a) {
}

inline scalar test_ret(scalar a) {
  return 1.0;
}

bool test_bool(bool a, scalar b) {
  return a;
}

inline void broken() {
  scalar a, b, c, d = 1.0;
  int j;
  bool tt;
  bool bt = j == 0 ? true : test_bool(tt, c);

  //  a = b > 0 ? c : d;
  func(a = b > 0 ? c : d);
  func(b > 0 ? c : d);
  a = b > 0 ? (b > 0 ? c : d) : d;
  test(test_ret(b > 0 ? c : d));
  if (a > 0) {
    if (b > 0) {
      a = b > 0 ? c : d;
    }
  }

  if (a > 0) {
    if (b > 0)
      a = b > 0 ? c : d;
  }
}
