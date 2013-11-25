/*
 * gqic.c
 * Reference:
 * http://gprolog.univ-paris1.fr/manual/html_node/gprolog072.html
 * Nov 22, 2013
 * daveti@cs.uoregon.edu
 * http://davejingtian.org
 */
#include <stdio.h>
#include <gprolog.h>

/* Check if n1 is the ancestor of n2 */
static int query2_gprolog(char *n1, char *n2)
{
	int func;
	PlTerm arg[10];
	char *sol[100];
	int i, nb_sol = 0;
	PlBool res;

	func = Pl_Find_Atom("anc");
	Pl_Query_Begin(PL_TRUE);
	arg[0] = Pl_Mk_String(n1);
	arg[1] = Pl_Mk_String(n2);
	nb_sol = 0;

	res = Pl_Query_Call(func, 2, arg);
	Pl_Query_End(PL_RECOVER);

	printf("query_gprolog: Is [%s] ancestor of [%s]: [%d]\n", n1, n2, res);
}


/* find the ancestors of n2 */
static int query_gprolog(char *n2)
{
	int func;
	PlTerm arg[10];
	char *sol[100];
	int i, nb_sol = 0;
	PlBool res;

	func = Pl_Find_Atom("anc");
	Pl_Query_Begin(PL_TRUE);
	arg[0] = Pl_Mk_Variable();
	arg[1] = Pl_Mk_String(n2);
	nb_sol = 0;

	res = Pl_Query_Call(func, 2, arg);
	while (res)
	{
		sol[nb_sol++] = Pl_Rd_String(arg[0]);
		res = Pl_Query_Next_Solution();
	}
	Pl_Query_End(PL_RECOVER);

	printf("query_gprolog: The ancestors of [%s]:\n", n2);
	for (i = 0; i < nb_sol; i++)
		printf("  solution: %s\n", sol[i]);
	printf("%d solution(s)\n", nb_sol);
}

static int
Main_Wrapper(int argc, char *argv[])
{
	Pl_Start_Prolog(argc, argv);

	///////////////////////////
	query_gprolog("john");
	query2_gprolog("bob", "john");
	query2_gprolog("john", "bob");
	///////////////////////////
	
	Pl_Stop_Prolog();

	return 0;
}

int
main(int argc, char *argv[])
{
	printf("I know - it's weird...\n");
	return Main_Wrapper(argc, argv);
}
