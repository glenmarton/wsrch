#include <stdbool.h>
#include <stdio.h>
#include "direction.h"
#include "point.h"
#include "wstable.h"
#include "Seq.h"
#include "run.h"
#include "try.h"
#include "verbose.h"
#include "wordsearch.h"

/*
 * global
 * functions
 */
void run( wstable_t wstable, FILE* fin )
{
	char word[80] = "";

	while (fgets( word, sizeof( word ), fin )) {
		run_searchWord( wstable, word );
	}
}

void run_searchWord( wstable_t wstable, const char *word )
{
	wstable_t puzzle = wstable_duplicate( wstable );

	Seq_T answers = run_findWord( puzzle, word );

#ifdef NOT_YET //gmj20151120
	process_answer( puzzle, answers );
#else
	if (answers) {
	}
#endif /* NOT_YET */

	wstable_destroy( &puzzle );
}

Seq_T run_findWord( wstable_t puzzle, const char* word )
{
	Seq_T answer = NULL;
	point_t start = point_create();
	size_t height = wstable_getHeight( puzzle );
	size_t width  = wstable_getWidth( puzzle );

	try_create( puzzle );
	while (start->row < height) {
		RSPRINT( " - check row: %d\n", start->row );
		start->col = 0;
		while (start->col < width) {
			RSPRINT( " - check col: %d\n", start->col );
			answer = try_this_location( word, start );
			start->col++;
		}
		start->row++;
	}

	point_destroy( &start );
	try_destroy();

	return answer;
}
