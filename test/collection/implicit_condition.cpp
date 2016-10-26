// RUN: find-typeDebug %s -- | FileCheck-3.6 %s
typedef double scalar;

void f() {
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
