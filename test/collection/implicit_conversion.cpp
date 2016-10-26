// RUN: find-typeDebug %s -- | FileCheck-3.6 %s
typedef double scalar;

class X {
 public:
  X(scalar a);
  bool operator==(const X& other);
};

void f() {
  X a(1.0);
  // CHECK: [[@LINE+1]]:12: [ImplicitConversion]
  if (a == 1.0) {
  }
  // CHECK: [[@LINE+1]]:12: [ImplicitConversion]
  if (a == 2 * 2) {
  }
}

int main() {
  return 1;
}
