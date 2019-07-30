// RUN: find-type -config=%S/conf_double.json %s -- | FileCheck %s -check-prefix=CHECK-DOUBLE
#pragma clang diagnostic ignored "-Wnull-character"

typedef double scalar;

class container {
  // CHECK-DOUBLE: [[@LINE+1]]:3: [UnionMatcher]
  union standard_union {
    double a;
  };
  
  // CHECK-DOUBLE: [[@LINE+1]]:3: [UnionMatcher]
  union { 
    double a;
  };

  // CHECK-DOUBLE: [[@LINE+1]]:3: [UnionMatcher]
  union named_union {
    double a;
  } nunion1;

  // CHECK-DOUBLE: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_struct {
    struct astruct {
      double a;
    };
  } nunion2;

  // CHECK-DOUBLE: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_struct_2fld {
    struct astruct {
      scalar a;
      double cc;
    };
  } nunion3;

  // CHECK-DOUBLE: [[@LINE+1]]:3: [UnionMatcher]
  union standard_union_struct_2fld {
    struct astruct {
      scalar a;
      double cc;
    };
  };

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union standard_union_1 {
    scalar a;
  };

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union {
    scalar b;
  };

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_1 {
    scalar a;
  } nunion_1;

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_2 {
    struct astruct {
      scalar a;
    };
  } nunion_2;

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union named_union_3 {
    struct astruct {
      scalar a;
      scalar cc;
    };
  } nunion_3;

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:3: [UnionMatcher]
  union standard_union_2 {
    struct astruct {
      scalar a;
      scalar cc;
    };
  };
};
