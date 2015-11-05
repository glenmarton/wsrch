#include <stdio.h>
#include "answer.h"
#include "direction.h"
#include "point.h"
#include "Seq.h"
#include "solution.h"
#include "verbose.h"

/*
 * local
 * prototypes
 */
static void free_answers( Seq_T seq );

/*
 * global
 * functions
 */
Seq_T answer_create( void )
{
	Seq_T answer = Seq_new( 5 );

	CDPRINT( " %p", answer );

	return answer;
}

void answer_destroy( Seq_T* answerPtr )
{
	CDPRINT( " count = %d", Seq_length( *answerPtr ));
	free_answers( *answerPtr );
	Seq_free( answerPtr );
}

void answer_add( Seq_T answer, solution_t solution )
{
	Seq_addhi( answer, (void*)solution );

	GSPRINT( " - count = %zu\n", Seq_length( answer ));
}

solution_t answer_get( Seq_T answer, size_t index )
{
	return Seq_get( answer, index );
}

size_t answer_count( Seq_T answer )
{
	return Seq_length( answer );
}

solution_t answer_remove( Seq_T answer )
{
	return Seq_remlo( answer );
}

/*
 * local
 * functions
 */
static void free_answers( Seq_T seq )
{
	size_t stop = Seq_length( seq );
	size_t i = 0;

	while (i < stop) {
		solution_t s = Seq_remhi( seq );
		solution_destroy( &s );
		i++;
	}
}
