SIMPLE_TEST1("A conditional assignment."
			, COND
			, COND_S);
SIMPLE_TEST1("A conditional assignment with integer condition."
			, MAKE_CODE("a = ai > 0 ? a : b")
			, "ai > 0 ? a : b");
SIMPLE_TEST1("A conditional assignment with integer condition and integer true expr."
			, MAKE_CODE("a = ai > 0 ? ai : b")
			, "ai > 0 ? ai : b");
SIMPLE_TEST1("A conditional assignment with integer condition and integer false expr."
			, MAKE_CODE("a = ai > 0 ? a : bi")
			, "ai > 0 ? a : bi");