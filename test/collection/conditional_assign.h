typedef double scalar;
inline void test(scalar a) {
}

inline scalar test_ret(scalar a) {
  return 1.0;
}

inline void broken() {
  scalar a,b,c,d=1.0;
  int j;
  if(b > 0) {
    a = c;
  } else {
    int i  = b;
    }
  if(b > 0) {
    a = c;
  } else {
    j  = b;
    }
/*
  a = b > 0 ? c : d;
  func(b > 0 ? c : d);
  a = b > 0 ? (b > 0 ? c : d) : d;
  test(test_ret(b > 0 ? c : d));
*/
}
