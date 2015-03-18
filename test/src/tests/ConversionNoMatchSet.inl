SIMPLE_TEST0("A comparison with a constant casted to " _TYPE_
			, CMP( _TYPE_ "(2)"));
SIMPLE_TEST0("A comparison with a float casted to " _TYPE_
			, CMP( _TYPE_ "(af)"));
SIMPLE_TEST0("A comparison with a binary op. casted to " _TYPE_
			, CMP( _TYPE_ "(af*af)"));
SIMPLE_TEST0("A comparison with the type."
			, CMP("as"));
SIMPLE_TEST0("A comparison with a binary op."
			, CMP("as*bs"));
SIMPLE_TEST0("A comparison with a nested binary op."
			, CMP("as*as*as/as"));
SIMPLE_TEST0("A comparison with a nested binary op. inside parens."
			, CMP("((as*(as*as)/as))"));
SIMPLE_TEST0("A comparison with a nested binary op. inside parens."
			, CMP("((af*(af*as)/af))"));