typedef double scalar;
inline void test(scalar a) {
}

inline scalar test_ret(scalar a) {
  return 1.0;
}

inline void broken() {
  scalar a,b,c,d=1.0;
  int ii = 0;
  if(b > 0) {
    a = c;
  } else {
    ii = 10;
  }
  if(b > 0) {
    a = b;
  } else {
    a = c;
  }
  if(b > 0) {
    a = d;
  }
  if(d == 0)
    a = c;
  if(a == 0) 
    b = c;
  else
    b = d; 
}
