SIMPLE_TEST0("A simple union."
			, UNION(_NTYPE_ " a;"));
SIMPLE_TEST0("A anonymous union."
			, AUNION(_NTYPE_ " a;"));
SIMPLE_TEST0("A named union."
			, NUNION(_NTYPE_ " a;"));
SIMPLE_TEST0("A named union with a struct."
			, NUNION("struct astruct { " _NTYPE_ " a; };"));
SIMPLE_TEST0("A named union with a struct with two fields."
			, NUNION("struct astruct { " _NTYPE_ " a; " _NTYPE_ " cc; };"));
SIMPLE_TEST0("A union with a struct with two fields."
			, UNION("struct astruct { " _NTYPE_ " a; " _NTYPE_ " cc; };"));