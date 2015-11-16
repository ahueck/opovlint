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
    scalar _oolint_t_34341225;
condassign(_oolint_t_34341225, b > 0, c, d);
func(a = _oolint_t_34341225);
    scalar _oolint_t_3535821;
condassign(_oolint_t_3535821, b > 0, c, d);
func(_oolint_t_3535821);
    scalar _oolint_t_36361629;
condassign(_oolint_t_36361629, b > 0, c, d);
scalar _oolint_t_3636734;
condassign(_oolint_t_3636734, b > 0, _oolint_t_36361629, d);
a = _oolint_t_3636734;
    scalar _oolint_t_37371730;
condassign(_oolint_t_37371730, b > 0, c, d);
test(test_ret(_oolint_t_37371730));
  if(a > 0) {
    if(b > 0) {
                scalar _oolint_t_40401326;
condassign(_oolint_t_40401326, b > 0, c, d);
a = _oolint_t_40401326;
    }
  }

  if(a > 0) {
        scalar _oolint_t_46461326;
condassign(_oolint_t_46461326, b > 0, c, d);
if(b > 0)
        a = _oolint_t_46461326;
  }

}
