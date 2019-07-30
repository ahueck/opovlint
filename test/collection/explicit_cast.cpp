// RUN: find-type -config=%S/conf.json %s -- | FileCheck %s
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
  // CHECK: [[@LINE+1]]:7: [ExplicitCast]
  i = static_cast<unsigned long long>(a);

  int xx = int(reCast<int, scalar>(a));
}

void container(){
  scalar a = 10.0; scalar aa = 10.5; scalar ab = 11.0; scalar* ptr = &a;
  int res = 0.0;
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a);
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * ab);
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * ab * aa);
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(static_cast<scalar>(res));
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * static_cast<scalar>(res));
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * 1);
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * (res * 2));
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>((a * 2));
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * (a * 2));
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(((a)));
  // CHECK: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * ((static_cast<scalar>(res))));
   
  //ExplicitCastNoMatchSet
  // CHECK-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res);
  // CHECK-NOT: [[@LINE+1]]:17: [ExplicitCast]
  scalar cres = static_cast<scalar>(a);
  // CHECK-NOT: [[@LINE+1]]:10: [ExplicitCast]
  cres = static_cast<scalar>(res);
  // CHECK-NOT: [[@LINE+1]]:10: [ExplicitCast]
  cres = static_cast<scalar>(a * res);
  // CHECK-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!a);
  // CHECK-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!!a);
  // CHECK-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!!(a * a));
  // CHECK-NOT: [[@LINE+1]]:19: [ExplicitCast]
  scalar *cres2 = static_cast<scalar*>(&a);
  // CHECK-NOT: [[@LINE+1]]:19: [ExplicitCast]
  scalar *cres3 = static_cast<scalar*>(ptr);
  // CHECK-NOT: [[@LINE+1]]:19: [ExplicitCast]
  scalar cres4 = static_cast<scalar>(*ptr);
}
