// RUN: find-typeDebug %s -- | FileCheck-3.6 %s
#pragma clang diagnostic ignored "-Wnull-character"

typedef double scalar;

struct test {
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union {
    scalar a;
  };
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union {
    scalar b;
    int c;
  };
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union {
    scalar d;
    int e;
    double f;
  };
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union {
    scalar g;
    scalar gg;
    scalar ggg;
    int h;
    double i;
  };
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union XX {
    scalar a;
  };
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union YY {
    scalar b;
    int c;
  };
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union ZZ {
    scalar d;
    int e;
    double f;
  };
};
