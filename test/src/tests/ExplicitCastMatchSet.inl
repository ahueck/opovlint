SIMPLE_TEST1("A static cast."
			, SCAST("a")
			, SCAST_S("a"));
SIMPLE_TEST1("A static cast of a binary op."
			, SCAST("a*ab")
			, SCAST_S("a*ab"));
SIMPLE_TEST1("A static cast of a nested binary op."
		, SCAST("a*ab*aa")
		, SCAST_S("a*ab*aa"));
SIMPLE_TEST1("A static cast of a casted variable."
			, SCAST(SCAST_T(_TYPE_, "res"))
			, SCAST_S(SCAST_T(_TYPE_, "res")));
SIMPLE_TEST1("A static cast of a binary op. with a cast."
			, SCAST("res*" SCAST_T(_TYPE_, "res"))
			, SCAST_S("res*" SCAST_T(_TYPE_, "res")));
SIMPLE_TEST1("A static cast of a binary op. with constant."
			, SCAST("a*1")
			, SCAST_S("a*1"));
SIMPLE_TEST1("A static cast of a binary op. with paren expression."
			, SCAST("a*(res*2)")
			, SCAST_S("a*(res*2)"));
SIMPLE_TEST1("A static cast of a paren expression with binary op."
			, SCAST("(a*2)")
			, SCAST_S("(a*2)"));
SIMPLE_TEST1("A static cast of a binary op with paren expression."
			, SCAST("res*(a*2)")
			, SCAST_S("res*(a*2)"));
SIMPLE_TEST1("A static cast of a nested cast expression."
			, SCAST(SCAST_S("a"))
			, SCAST_S("a"));
SIMPLE_TEST1("A static cast of a nested cast expression of a binary op."
			, SCAST(SCAST_S("res*(a*2)"))
			, SCAST_S("res*(a*2)"));
SIMPLE_TEST1("A static cast with parens."
			, SCAST("((a))")
			, SCAST_S("((a))"));
SIMPLE_TEST1("A static cast of a binary op. with a cast inside parens."
			, SCAST("res*((" SCAST_T(_TYPE_, "res") "))")
			, SCAST_S("res*((" SCAST_T(_TYPE_, "res") "))"));
