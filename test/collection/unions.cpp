// RUN: find-type -config=%S/conf.json %s -- | FileCheck %s
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

class container {
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union standard_union {
    scalar a;
  };
  
  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union { 
    scalar a;
  };

  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union named_union {
    scalar a;
  } nunion1;

  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_struct {
    struct astruct {
      scalar a;
    };
  } nunion2;

  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_struct_2fld {
    struct astruct {
      double a;
      scalar cc;
    };
  } nunion3;

  // CHECK: [[@LINE+1]]:3: [UnionMatcher]
  union standard_union_struct_2fld {
    struct astruct {
      double a;
      scalar cc;
    };
  };

  // CHECK-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union standard_union_1 {
    double a;
  };

  // CHECK-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union {
    double b;
  };

  // CHECK-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_1 {
    double a;
  } nunion_1;

  // CHECK-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_2 {
    struct astruct {
      double a;
    };
  } nunion_2;

  // CHECK-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_3 {
    struct astruct {
      double a;
      double cc;
    };
  } nunion_3;

  // CHECK-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union standard_union_2 {
    struct astruct {
      double a;
      double cc;
    };
  };
};
