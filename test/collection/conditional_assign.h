typedef double scalar;

scalar ret(scalar a) {
        scalar _oolint_t_441226;
condassign(_oolint_t_441226, a > 0, a, 0.);
return _oolint_t_441226;
}

scalar ret2(scalar b) {
        scalar _oolint_t_881630;
condassign(_oolint_t_881630, b > 0, b, 0.);
return ret(_oolint_t_881630);
}


inline void test(scalar a) {
}


inline void func(scalar a) {
}

inline scalar test_ret(scalar a) {
  return 1.0;
}

bool test_bool(bool a, scalar b) {
	return a;
}

inline void broken() {
  scalar a,b,c,d=1.0;
  int j;
  bool tt;
  bool bt = j == 0 ? true : test_bool(tt, c);
//  a = b > 0 ? c : d;
    scalar _oolint_t_33331225;
condassign(_oolint_t_33331225, b > 0, c, d);
func(a = _oolint_t_33331225);
    scalar _oolint_t_3434821;
condassign(_oolint_t_3434821, b > 0, c, d);
func(_oolint_t_3434821);
    scalar _oolint_t_35351629;
condassign(_oolint_t_35351629, b > 0, c, d);
scalar _oolint_t_3535734;
condassign(_oolint_t_3535734, b > 0, _oolint_t_35351629, d);
a = _oolint_t_3535734;
    scalar _oolint_t_36361730;
condassign(_oolint_t_36361730, b > 0, c, d);
test(test_ret(_oolint_t_36361730));
  if(a > 0) {
    if(b > 0) {
                scalar _oolint_t_39391326;
condassign(_oolint_t_39391326, b > 0, c, d);
a = _oolint_t_39391326;
    }
  }

  if(a > 0) {
        scalar _oolint_t_45451326;
condassign(_oolint_t_45451326, b > 0, c, d);
if(b > 0)
        a = _oolint_t_45451326;
  }
}
