SIMPLE_TEST1("A comparison with a constant."
			, CMP("2")
			, "2");
SIMPLE_TEST1("A comparison with a binary op of constants."
			, CMP("2*10")
			, "2*10");
SIMPLE_TEST1("A comparison with a double var."
			, CMP("ad")
			, "ad");
SIMPLE_TEST1("A comparison with a float var."
			, CMP("af")
			, "af");
SIMPLE_TEST1("A comparison with a binary op between double and float var."
			, CMP("af*ad")
			, "af*ad");
SIMPLE_TEST1("A comparison with an unary op."
			, CMP("!ad")
			, "!ad");
SIMPLE_TEST1("A comparison with a binary op inside an unary op."
			, CMP("!(af*ad)")
			, "!(af*ad)");
	
