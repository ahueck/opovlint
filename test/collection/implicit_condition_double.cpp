// RUN: find-type -config=%S/conf_double.json %s -- | FileCheck %s --check-prefix=CHECK-DOUBLE
typedef double scalar;

double a = 1, f = 10;
scalar b = 0.5, bb = 1.0;

void simple_test_double(){
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a * a) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a * a * a) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  if (!(!a)) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  if (!(!(a))) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a - 1) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (double(1)) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if ((double)1) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (static_cast<double>(1)) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (double(1 + 2)) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (f * scalar(a)) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (!(f * scalar(a))) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  for (;a;) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:10: [ImplicitConditionMatcher]
  while (a) {
  }
  // CHECK-DOUBLE: [[@LINE+3]]:9: [ImplicitConditionMatcher]
  do {
  }
  while(a);
  // CHECK-DOUBLE: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  bb = a ? b: bb;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  for (;!a;) {
  }
  // CHECK-DOUBLE: [[@LINE+1]]:10: [ImplicitConditionMatcher]
  while (!a) {
  }
  // CHECK-DOUBLE: [[@LINE+3]]:9: [ImplicitConditionMatcher]
  do {
  }
  while(!a);
  // CHECK-DOUBLE: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  bb = !a ? b: bb;

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a == 0){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a == 0.0){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a && a > 1.9){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a - 1 == 0.0f){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (static_cast<double>(1) == 0.0f){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (double(1) == 0.0f){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (scalar(a)){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (!(scalar(a) * scalar(f))){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  for (;a == 0.0;){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:10: [ImplicitConditionMatcher]
  while (a == 0.0){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+3]]:10: [ImplicitConditionMatcher]
  do{    
  }
  while (a == 0.0);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  bb = a == 0.0 ? b : bb;
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  for (;a && a > 1.9;){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:10: [ImplicitConditionMatcher]
  while (a && a > 1.9){
  }
  // CHECK-DOUBLE-NOT: [[@LINE+3]]:10: [ImplicitConditionMatcher]
  do{    
  }
  while (a && a > 1.9);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  bb = a == a && a > 1.9 ? b : bb;
}
