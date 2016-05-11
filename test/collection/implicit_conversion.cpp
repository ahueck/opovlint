typedef double scalar;

class X {
 public:
  X(scalar a);
  bool operator==(const X& other);
};

void f() {
  X a(1.0);
  if (a == 1.0) {
  }
  if (a == 2 * 2) {
  }
}

int main() {
  return 1;
}
