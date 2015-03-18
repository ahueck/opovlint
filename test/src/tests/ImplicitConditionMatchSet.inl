SIMPLE_TEST1("An if condition with a unary operation."
			, IF("!a")
			, "!a");
SIMPLE_TEST1("An if condition with a binary operation."
			, IF("a*a")
			, "a*a");
SIMPLE_TEST1("An if condition with a nested binary operation."
			, IF("a*a*a")
			, "a*a*a");
SIMPLE_TEST1("An if condition with a nested unary operation."
			, IF("!(!a)")
			, "!a");
SIMPLE_TEST1("An if condition with a nested unary operation including brackets."
			, IF("!(!(a))")
			, "!(a)");
SIMPLE_TEST1("An if condition with a binary operation including a constant."
			, IF("a - 1")
			, "a - 1");
SIMPLE_TEST1("An if condition with constructor style cast."
			, IF( _TYPE_ "(1)")
			, _TYPE_ "(1)");
SIMPLE_TEST1("An if condition with c-style cast."
			, IF("(" _TYPE_ ") 1")
			, "(" _TYPE_ ") 1");
SIMPLE_TEST1("An if condition with static cast."
			, IF("static_cast<" _TYPE_ ">(1)")
			, "static_cast<" _TYPE_ ">(1)");
SIMPLE_TEST1("An if condition with constructor style cast of aa binary op."
			, IF(_TYPE_"(1+2)")
			, _TYPE_"(1+2)");
SIMPLE_TEST1("An if condition with with binary operation, including a cast away from scalar."
			, IF("f*" _NTYPE_ "(a)")
			, "f*" _NTYPE_ "(a)");
SIMPLE_TEST1("An if condition with binary operation inside a unary, including a cast away from scalar."
			, IF("!(f*" _NTYPE_ "(a))")
			, "!(f*" _NTYPE_ "(a))");
SIMPLE_TEST1("A for condition ."
			, FOR("a")
			, "a");
SIMPLE_TEST1("A while condition."
			, WHILE("a")
			, "a");
SIMPLE_TEST1("A do-while condition."
			, DO("a")
			, "a");
SIMPLE_TEST1("A do-while condition."
			, COND("a")
			, "a");
SIMPLE_TEST1("A for condition with a unary operation."
			, FOR("!a")
			, "!a");
SIMPLE_TEST1("A while condition with a unary operation."
			, WHILE("!a")
			, "!a");
SIMPLE_TEST1("A do-while condition with a unary operation."
			, DO("!a")
			, "!a");
SIMPLE_TEST1("A do-while condition with a unary operation."
			, COND("!a")
			, "!a");