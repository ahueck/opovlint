// RUN: find-type -config=%S/conf_double.json %s -- | FileCheck %s -check-prefix=CHECK-DOUBLE
typedef double scalar;

void container_double(){
  double a = 10.0, b = 10.5, c = 11.0, d = 11.0;
  int ai = 0.0, bi = 0.0, ci = 0.0, di = 0.0; 
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  a = b > 0 ? c: d;
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  a = ai > 0 ? a: b;
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  a = ai > 0 ? ai: b;
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  a = ai > 0 ? a: bi;

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ConditionalAssgnMatcher]
  ai = bi > 0 ? ci: di;
}
