// RUN: find-type -config=%S/conf.json %s -- | FileCheck %s
// XFAIL: *
typedef double scalar;

scalar ret(scalar a) {
  // CHECK: [[@LINE+1]]:10: [ConditionalAssgnMatcher]
  return a > 0 ? a : 0.0;
}

scalar ret2(scalar b) {
  // CHECK: [[@LINE+1]]:14: [ConditionalAssgnMatcher]
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

  // CHECK: [[@LINE+1]]:12: [ConditionalAssgnMatcher]
  func(a = b > 0 ? c : d);
  // CHECK: [[@LINE+1]]:8: [ConditionalAssgnMatcher]
  func(b > 0 ? c : d);
  // CHECK: [[@LINE+2]]:16: [ConditionalAssgnMatcher]
  // CHECK: [[@LINE+1]]:7: [ConditionalAssgnMatcher]  
  a = b > 0 ? (b > 0 ? c : d) : d;
  // CHECK: [[@LINE+1]]:17: [ConditionalAssgnMatcher]
  test(test_ret(b > 0 ? c : d));
  // CHECK: [[@LINE+3]]:11: [ConditionalAssgnMatcher]
  if (a > 0) {
    if (b > 0) {
      a = b > 0 ? c : d;
    }
  }

  // CHECK: [[@LINE+3]]:11: [ConditionalAssgnMatcher]
  if (a > 0) {
    if (b > 0)
      a = b > 0 ? c : d;
  }
}

void container(){
  scalar a = 10.0, b = 10.5, c = 11.0, d = 11.0;
  int ai = 0.0, bi = 0.0, ci = 0.0, di = 0.0;  
  // CHECK: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  a = b > 0 ? c: d;
  // CHECK: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  a = ai > 0 ? a: b;
  // CHECK: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  a = ai > 0 ? ai: b;
  // CHECK: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  a = ai > 0 ? a: bi;

  // CHECK-NOT: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  ai = bi > 0 ? ci: di;
}
