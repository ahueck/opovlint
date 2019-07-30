// RUN: find-type -config=%S/conf_double.json %s -- | FileCheck %s -check-prefix=CHECK-DOUBLE
#pragma clang diagnostic ignored "-Wunused-comparison"

typedef double ascalar;
#define scalar double

class versionNumber {
private:	
  scalar versionNumber_;
  int index_;
public:
	versionNumber(const scalar num) : versionNumber_(num), index_(1) {}
	versionNumber(const char* a, const scalar num=10.0f) : versionNumber_(num),	index_(1) {}
	
  bool operator==(const versionNumber& vn) {
		return index_ == vn.index_;
	}
	
  versionNumber operator*(const versionNumber& vn) {
		return versionNumber(versionNumber_*vn.versionNumber_);
	}
};

class X {
 public:
  X(scalar a);
  bool operator==(const X& other);
};

ascalar ad = 1.0; float af = 1.0f; double as = 10.0; double bs = 1.5;
void container_double() {  
  versionNumber vn(1.0);
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConversion]
  vn == 2;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConversion]
  vn == 2 * 10;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConversion]
  vn == ad;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConversion]
  vn == af;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConversion]
  vn == af * ad;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConversion]
  vn == !ad;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [ImplicitConversion]
  vn == !(af * ad);

  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConversion]
  vn == double(2);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConversion]
  vn == double(af);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConversion]
  vn == double(af * af);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConversion]
  vn == as;
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConversion]
  vn == as * bs;
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConversion]
  vn == (as * as * as / as);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConversion]
  vn == (as * (as * as)/as);
  // CHECK-DOUBLE-NOT: [[@LINE+1]]:9: [ImplicitConversion]
  vn == (af * (af * as)/af);
}

int main() {
  return 1;
}
