// RUN: find-type %s -config=%S/conf.json %s -- | FileCheck %s
// XFAIL: *
typedef double scalar;

// CHECK: [[@LINE+5]]:5: [ExplicitConstructor]
class versionNumber{
private:
    scalar versionNumber_;
public:
    versionNumber(const scalar num): versionNumber_(num){}
};

// CHECK: [[@LINE+6]]:5: [ExplicitConstructor]
template<typename T>
class templateVersionNumber{
private:
    T versionNumber_;
public:
    templateVersionNumber<T>(const T num): versionNumber_(num){}
};

// CHECK-NOT: [[@LINE+6]]:5: [ExplicitConstructor]
template<typename T>
class templateVersionNumber2{
private:
    T versionNumber_;
public:
    templateVersionNumber2<T>(const T num): versionNumber_(num){}
};
