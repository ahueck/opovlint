SIMPLE_TEST0("A static cast of an int."
		, SCAST("res"));
SIMPLE_TEST0("A static cast"
		, SCAST_TYPE(_TYPE_, "a"));
SIMPLE_TEST0("A static cast of an int."
		, SCAST_TYPE(_TYPE_, "res"));
SIMPLE_TEST0("A static cast of a binary op"
		, SCAST_TYPE(_TYPE_, "a*res"));
SIMPLE_TEST0("A static cast of an unary."
		, SCAST("!a"));
SIMPLE_TEST0("A static cast of a nested unary."
		, SCAST("!!a"));
SIMPLE_TEST0("A static cast of a nested unary of a binary."
		, SCAST("!!(a*a)"));