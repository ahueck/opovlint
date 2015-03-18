SIMPLE_TEST0("An if condition with a legal binary comparison (integer literal)."
			, IF("a == 0"));
SIMPLE_TEST0("An if condition with a legal binary comparison (float literal)."
			, IF("a == 0.0"));
SIMPLE_TEST0("An if condition with a legal nested binary comparison."
			, IF("a && a > 1.9"));
SIMPLE_TEST0("An if condition with a legal binary comparison (including binary op)."
			, IF("a-1 == 0.0f"));
SIMPLE_TEST0("An if condition with a legal binary comparison (static cast of literal)."
			, IF("static_cast<" _TYPE_ ">(1) == 0.0f"));
SIMPLE_TEST0("An if condition with a legal binary comparison (constructor cast literal)."
			, IF( _TYPE_ "(1) == 0.0f"));
SIMPLE_TEST0("An if condition with a cast away from scalar."
			, IF( _NTYPE_ "(a)"));
SIMPLE_TEST0("An if condition with a cast away from scalar including a binary operation."
			, IF( _NTYPE_ "(a)*b"));
SIMPLE_TEST0("An if condition with a cast away from scalar including a binary operation inside a unary."
			, IF("!(" _NTYPE_ "(a)*" _NTYPE_ "(f))"));
SIMPLE_TEST0("A for condition with a legal binary comparison (integer literal)."
			, FOR("a == 0.0"));
SIMPLE_TEST0("A while condition with a legal binary comparison (integer literal)."
			, WHILE("a == 0.0"));
SIMPLE_TEST0("A do-while condition with a legal binary comparison (integer literal)."
			, DO("a == 0.0"));
SIMPLE_TEST0("A conditional assign condition with a legal binary comparison (integer literal)."
			, COND("a == 0.0"));
SIMPLE_TEST0("A for condition with a legal nested binary comparison."
			, FOR("a && a > 1.9"));
SIMPLE_TEST0("A while condition with a legal nested binary comparison."
			, WHILE("a && a > 1.9"));
SIMPLE_TEST0("A do-while condition with a legal nested binary comparison."
			, DO("a && a > 1.9"));
SIMPLE_TEST0("A conditional assign condition with a legal nested binary comparison."
			, COND("a && a > 1.9"));
