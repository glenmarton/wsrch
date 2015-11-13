#ifdef NOT_YET	//gmj20151023
#include "Seq.h"
#include "wstable.h"

/*
 * local
 * prototypes
 */
static void process_answer( wstable_t puzzle, Seq_T answers );

/*
 * global
 * functions
 */
void process_solutions( solutions_t solutions )
{
	size_t stop = solutions_getCount();

	for (size_t num = 0; num < stop; num++) {
		solution_t solution = solutions_get( num );
		char* output = wstable_solutionToString( solution );

		printf( output );
		free( output );
	}
}

int run( FILE* fin )
{
	char word[64];
	size_t wsize = sizeof( word );

	while (fgets( word, wsize, fin )) {
		Seq_T answers = Seq_new( 5 );

		if (wstable_findWord( word, answers )) {
			wstable_t puzzle = wstable_create();

			result_record( puzzle, answers );
			printf( "%s\n", wstable_tostring( puzzle ));

			wstable_destroy( &puzzle );
		}

		free_solutions( answers );
		Seq_free( &answers );
	}

	return 0;
}

int run2( FILE* fin )
{
	char word[65];
	size_t wsize = sizeof( word );

	while (fgets( word, wsize, fin )) {
		wstable_t puzzle = wstable_create();
		Seq_T answers = go_findWord( puzzle, word );

		if (answers) {
			process_answer( puzzle, answers );
		}
		wstable_destroy( &puzzle );
	}

	return 0;
}
#ifdef CPPUTEST_COMPILATION
int wsrch_main( int argc, char* argv[] )
#else
int main( int argc, char* argv[] )
#endif /* CPPUTEST_COMPILATION */
{
	wstable_init( argv[1] );
	wstable_setHightlight( uppercase/star/color_blue );

	run( stdin );
	return 0;
}

/*
 * local
 * functions
 */
static void process_answer( wstable_t puzzle, Seq_T answers )
{
			result_record( puzzle, answers );

			printf( "%s\n", wstable_tostring( puzzle ));

			free_solutions( answers );
			Seq_free( &answers );
}
#endif /* NOT_YET */
