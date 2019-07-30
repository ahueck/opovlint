// RUN: find-type -config=%S/conf.json %s -- | FileCheck %s
typedef double scalar;

scalar a = 1, f = 10;
double b = 0.5, bb = 1.0;

void simple_test(){  
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a * a) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a * a * a) {
  }
  // CHECK: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  if (!(!a)) {
  }
  // CHECK: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  if (!(!(a))) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a - 1) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (scalar(1)) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if ((scalar)1) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (static_cast<scalar>(1)) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (scalar(1 + 2)) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (f * double(a)) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (!(f * double(a))) {
  }
  // CHECK: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  for (;a;) {
  }
  // CHECK: [[@LINE+1]]:10: [ImplicitConditionMatcher]
  while (a) {
  }
  // CHECK: [[@LINE+3]]:9: [ImplicitConditionMatcher]
  do {
  }
  while(a);
  // CHECK: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  bb = a ? b: bb;
  // CHECK: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  for (;!a;) {
  }
  // CHECK: [[@LINE+1]]:10: [ImplicitConditionMatcher]
  while (!a) {
  }
  // CHECK: [[@LINE+3]]:9: [ImplicitConditionMatcher]
  do {
  }
  while(!a);
  // CHECK: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  bb = !a ? b: bb;

  // CHECK-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a == 0){
  }
  // CHECK-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a == 0.0){
  }
  // CHECK-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a && a > 1.9){
  }
  // CHECK-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a - 1 == 0.0f){
  }
  // CHECK-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (static_cast<scalar>(1) == 0.0f){
  }
  // CHECK-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (scalar(1) == 0.0f){
  }
  // CHECK-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (double(a)){
  }
  // CHECK-NOT: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (!(double(a) * double(f))){
  }
  // CHECK-NOT: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  for (;a == 0.0;){
  }
  // CHECK-NOT: [[@LINE+1]]:10: [ImplicitConditionMatcher]
  while (a == 0.0){
  }
  // CHECK-NOT: [[@LINE+3]]:10: [ImplicitConditionMatcher]
  do{    
  }
  while (a == 0.0);
  // CHECK-NOT: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  bb = a == 0.0 ? b : bb;
  // CHECK-NOT: [[@LINE+1]]:9: [ImplicitConditionMatcher]
  for (;a && a > 1.9;){
  }
  // CHECK-NOT: [[@LINE+1]]:10: [ImplicitConditionMatcher]
  while (a && a > 1.9){
  }
  // CHECK-NOT: [[@LINE+3]]:10: [ImplicitConditionMatcher]
  do{    
  }
  while (a && a > 1.9);
  // CHECK-NOT: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  bb = a == a && a > 1.9 ? b : bb;
}

void fn() {
  scalar a;
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (a) {
  }
  // CHECK: [[@LINE+1]]:7: [ImplicitConditionMatcher]
  if (!a) {
  }
  // CHECK: [[@LINE+1]]:8: [ImplicitConditionMatcher]
  if (!!a) {
  }
}

int main() {
  return 1;
}
