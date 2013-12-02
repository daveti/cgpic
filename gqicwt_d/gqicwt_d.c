/*
 * gqicwt_d.c
 * Reference:
 * http://gprolog.univ-paris1.fr/manual/html_node/gprolog072.html
 * Nov 26, 2013
 * daveti@cs.uoregon.edu
 * http://davejingtian.org
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <gprolog.h>
#include <pthread.h>

/* My thread id */
static pthread_t my_thread_id;

/* Thread main method */
static void thread_main(void *data)
{
	/* Let's do the boring factorial function */
	int i;
	int fac = 1;
	for (i = 1; i < 6; i++)
		fac *= i;
	printf("thread compute !5 = [%d]\n", fac);
}

/* Add new bindings into the system */
static int asserta_gprolog(char *n1, char *n2)
{
	int func;
	PlTerm arg[10];
	PlTerm arg2[10];
	PlBool res;

	func = Pl_Find_Atom("parent");
	printf("debug: func(parent)=[%d]\n", func);
	Pl_Query_Begin(PL_TRUE);
	arg[0] = Pl_Mk_String(n1);
	arg[1] = Pl_Mk_String(n2);
	arg2[0] = Pl_Mk_Callable(func, 2, arg);
	func = Pl_Find_Atom("asserta");
	res = Pl_Query_Call(func, 1, arg2);

	Pl_Query_End(PL_RECOVER);

	printf("asserta_gprolog: parent(%s, %s) binding added [%d]\n", n1, n2, res);
}

/* Check if n1 is the ancestor of n2 */
static int query2_gprolog(char *n1, char *n2)
{
	int func;
	PlTerm arg[10];
	PlBool res;

	func = Pl_Find_Atom("anc");
	printf("debug: func(anc)=[%d]\n", func);
	Pl_Query_Begin(PL_TRUE);
	arg[0] = Pl_Mk_String(n1);
	arg[1] = Pl_Mk_String(n2);

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
	printf("debug: func(anc)=[%d]\n", func);
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
	asserta_gprolog("daveti", "john");
	query_gprolog("john");
	///////////////////////////
	
	Pl_Stop_Prolog();

	return 0;
}

int
main(int argc, char *argv[])
{
	int ret;
	printf("I know - it's weird...\n");
	/* Start the working thread */
	ret = pthread_create(&my_thread_id, NULL, thread_main, NULL);
	if (ret != 0)
		printf("threat creation failure - [%s]\n", strerror(errno));
	/* Run the damn prolog */
	Main_Wrapper(argc, argv);
	/* Join the thread */
	pthread_join(my_thread_id, NULL);

	return 0;
}
