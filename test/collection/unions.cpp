#pragma clang diagnostic ignored "-Wnull-character"

typedef double scalar;

struct test {
  union {
    scalar a;
  };
  union {
    scalar b;
    int c;
  };
  union {
    scalar d;
    int e;
    double f;
  };
  union {
    scalar g;
    scalar gg;
    scalar ggg;
    int h;
    double i;
  };
  union XX {
    scalar a;
  };
  union YY {
    scalar b;
    int c;
  };
  union ZZ {
    scalar d;
    int e;
    double f;
  };
};
