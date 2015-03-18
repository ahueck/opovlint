SIMPLE_TEST1("A simple union."
			, UNION(_TYPE_ " a;")
			, UNION_S(_TYPE_ " a;"));
SIMPLE_TEST1("A anonymous union."
			, AUNION(_TYPE_ " a;")
			, AUNION_S(_TYPE_ " a;"));
SIMPLE_TEST1("A named union."
			, NUNION(_TYPE_ " a;")
			, NUNION_S(_TYPE_ " a;"));
SIMPLE_TEST1("A named union with a struct."
			, NUNION("struct astruct { " _TYPE_ " a; };")
			, NUNION_S("struct astruct { " _TYPE_ " a; };"));
SIMPLE_TEST1("A named union with a struct with two fields."
			, NUNION("struct astruct { " _NTYPE_ " a;" _TYPE_ " cc; };")
			, NUNION_S("struct astruct { " _NTYPE_ " a;" _TYPE_ " cc; };"));
SIMPLE_TEST1("A union with a struct with two fields."
			, UNION("struct astruct { " _NTYPE_ " a; " _TYPE_ " cc; };")
			, UNION_S("struct astruct { " _NTYPE_ " a; " _TYPE_ " cc; };"));