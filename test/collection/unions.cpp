typedef double scalar;

struct test {
  scalar a;
  union {
    ;
    int c;
  };  
scalar b;
  union {
    ;
    int e;
    double f;
  };  
scalar d;
  struct XX {
    scalar a;
  };
  struct YY {
    scalar b;
    int c;
  };
  struct ZZ {
    scalar d;
    int e;
    double f;
  };
};