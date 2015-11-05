#include <assert.h>
#include <stdio.h>		//gmj20151102 DEBUG Take out!!!
#include <stdlib.h>
#include "direction.h"
#include "mem.h"
#include "point.h"
#include "solution.h"
#include "verbose.h"

/*
 * typedefs
 */
typedef struct solutionStruct {
	char* word;
	point_t start_point;
	direction_t direction;
} solutionStruct;

/*
 * local
 * prototypes
 */

/*
 * global
 * functions
 */
solution_t solution_create( void )
{
	solution_t s = (solution_t) ALLOC( sizeof( solutionStruct ));

	s->word = NULL;
	s->start_point = NULL;
	s->direction = NONE;

	return s;
}

solution_t solution_init( char* w, point_t p, direction_t d )
{
	CDPRINT( " %s, %p, %s", w, p, direction_tostring( d ));

	solution_t s = solution_create();
	solution_setWord( s, w );
	solution_setDirection( s, d );
	solution_setPoint( s, p );

	return s;
}

void solution_destroy( solution_t* solutionPtr )
{
	solution_t s = *solutionPtr;

	CDPRINT( " word:%s, point:%p, direction:%s", s->word, s->start_point, direction_tostring( s->direction ));
	FREE( s->word );
	point_destroy( &s->start_point );
	assert( s->word == NULL );
	assert( s->start_point == NULL );
	FREE( s );
	assert( s == NULL );
	*solutionPtr = NULL;
}

direction_t solution_getDirection( solution_t s )
{
	return s->direction;
}

void solution_setDirection( solution_t s, direction_t d )
{
	s->direction = d;
}

point_t solution_getPoint( solution_t s )
{
	return s->start_point;
}

void solution_setPoint( solution_t s, point_t p )
{
	assert( s );
	assert( p );

	if (s->start_point != NULL) {
		point_destroy( &s->start_point );
	}

	GSPRINT( " ( %d, %d )", p->row, p->col );
	s->start_point = point_duplicate( p );
}

char* solution_getWord( solution_t s )
{
	return s->word;
}

void solution_setWord( solution_t s, char* word )
{
	if (s->word != NULL) {
		FREE( s->word );
	}

	if (word && *word != '\0') {
		s->word = mem_stringDuplicate( word );
	}
}

char* solution_tostring( solution_t s )
{
	static char str[128];

	if (s->start_point) {
		point_t p = s->start_point;
		//if (p != 0xcdcdcdcd) {
			sprintf( str, "  - word:%s, point:(%d,%d), direction:%s", s->word, p->row, p->col,
					direction_tostring( s->direction ));
		//}
	} else {
		sprintf( str, "  - word:%s, point:%p, direction:%s", s->word, s->start_point,
				direction_tostring( s->direction ));
	}
	return str;
}
