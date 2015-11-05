#ifdef NOT_YET	//gmj20151023
#include "Seq.h"
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
		Seq_T solutions = Seq_new( 5 );

		if (wstable_hasWord( word, solutions )) {
			process_solutions( solutions );
		}

		Seq_free( &solutions );
	}

	return 0;
}

int main( int argc, char* argv[] )
{
	wstable_create( argv[1] );
	wstable_setHightlight( uppercase/star/color_blue );

	run( stdin );
	return 0;
}
#endif /* NOT_YET */
