// RUN: find-type -config=%S/conf_double.json %s -- | FileCheck %s -check-prefix=CHECK-DOUBLE
#include "reCast.h"
#pragma clang diagnostic ignored "-Wunused-value"

typedef double scalar;

void container(){
  scalar a = 10.0; scalar aa = 10.5; scalar ab = 11.0; scalar* ptr = &a;
  int res = 0.0;
   
  //ExplictCastNoMatchDouble
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * ab);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * ab * aa);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(static_cast<scalar>(res));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * static_cast<scalar>(res));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * 1);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * (res * 2));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>((a * 2));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * (a * 2));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(static_cast<int>(a));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(static_cast<int>(res * (a * 2)));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(((a)));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * ((static_cast<scalar>(res))));
  // mixed int/bool/scalar casts
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<scalar>(a);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<scalar>(res);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<scalar>(a * res);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!a);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!!a);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!!(a * a));
}


//ExplictCastMatchSetDouble
void container_double(){
  double a = 10.0; double aa = 10.5; double ab = 11.0; double* ptr = &a;
  int res = 0.0;  

  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a);
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * ab);
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * ab * aa);
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(static_cast<double>(res));
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * static_cast<double>(res));
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * 1);
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a * (res * 2));
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>((a * 2));
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * (a * 2));
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(a);
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * (a * 2));
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(((a)));
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res * ((static_cast<double>(res))));

  //ExplicitCastNoMatchSet
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(res);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:17: [ExplicitCast]
  double cres = static_cast<double>(a);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:10: [ExplicitCast]
  cres = static_cast<double>(res);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:10: [ExplicitCast]
  cres = static_cast<double>(a * res);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!a);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!!a);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ExplicitCast]
  res = static_cast<int>(!!(a * a));
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:19: [ExplicitCast]
  double *cres2 = static_cast<double*>(&a);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:19: [ExplicitCast]
  double *cres3 = static_cast<double*>(ptr);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:19: [ExplicitCast]
  double cres4 = static_cast<double>(*ptr);
  
}
