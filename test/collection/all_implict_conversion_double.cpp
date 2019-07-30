// RUN: find-type -config=%S/conf_double.json %s -- | FileCheck %s --check-prefix=CHECK-DOUBLE
// XFAIL: *
#pragma clang diagnostic ignored "-Wunused-comparison"

typedef double scalar;

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
		return versionNumber(versionNumber_ * vn.versionNumber_);
	}
};

void container() {
  double ad = 1.0; float af = 1.0f; scalar as = 10.0; scalar bs = 1.5;
  versionNumber vn(1.0);
  // CHECK-DOUBLE: [[@LINE+1]]:9: [AllImplicitConversion]
  vn == 2;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [AllImplicitConversion]
  vn == 2 * 10;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [AllImplicitConversion]
  vn == ad;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [AllImplicitConversion]
  vn == af;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [AllImplicitConversion]
  vn == af * ad;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [AllImplicitConversion]
  vn == !ad;
  // CHECK-DOUBLE: [[@LINE+1]]:9: [AllImplicitConversion]
  vn == !(af * ad);
}
