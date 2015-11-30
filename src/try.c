#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "direction.h"
#include "go.h"
#include "mem.h"
#include "point.h"
#include "Seq.h"
#include "wstable.h"
#include "solution.h"
#include "try.h"
#include "verbose.h"

/*
 * local
 * variables
 */
static int v = 0x0;
static wstable_t puzzle = NULL;
static Seq_T answer = NULL;

/*
 * local
 * prototypes
 */
static bool get_next_point_this_direction( direction_t direction, point_t point );
static bool does_char_match_point( const char ch, point_t p );
static void add_solution( Seq_T answer, const char* word, point_t start, direction_t direction );

/*
 * global
 * functions
 */
void try_create( wstable_t wstable )
{
	puzzle = wstable;
	go_init( (int)wstable_getHeight( puzzle ), (int)wstable_getWidth( puzzle ) );
	answer = Seq_new( 5 );
}

void try_destroy( void )
{
	//	This destroys data before program can results.
//	Seq_free( &answer );
}

Seq_T try_this_location( const char* word, point_t start )
{
	int first_char_of_word = *word;
	int char_at_start_point = wstable_atPoint( puzzle, start );

	int test = (first_char_of_word == char_at_start_point);

	if(v&8)TYPRINT( " - First letter %c at %s? %s\n", *word, point_toStr( start ),
			test? "true" : "false" );

	if (test) {
		answer = try_every_direction( word, start );
TYPRINT( " - Found %zu answer.", Seq_length( answer ));
	}
	return answer;
}

Seq_T try_every_direction( const char* word, point_t start )
{
	TYPRINT( " -Got here %d.", __LINE__ );
	direction_t direction = NORTH_WEST;
	point_t p = point_create();

	while (direction != NONE) {
		p->row = start->row;
		p->col = start->col;

		if(v&4)TYPRINT( " - First letter of '%s' at %s direction: '%s'\n", word,
				point_toStr( start ), direction_tostring( direction ));

		if (try_this_direction( word, p, direction )) {
			add_solution( answer, word, start, direction );
		}
		direction--;
	}

	point_destroy( &p );

TYPRINT( " - Found %zu solutions.", Seq_length( answer ));
	return answer;
}

bool try_this_direction( const char*word, point_t start, direction_t direction )
{
	const char* cp = word + 1;
	const char* stop = word + strlen( word ) - 1;
	point_t point = point_duplicate( start );

	while (cp != stop ) {
		bool flag = get_next_point_this_direction( direction, point );

		if(v&4)TYPRINT( " Next letter of '%s' headed %s at %s is %c.", word, direction_tostring( direction ), point_toStr( point ), wstable_atPoint( puzzle, point ));

		if (flag && does_char_match_point( *cp, point )) {
			cp++;	/* try next char in word */
		} else {
			break;
		}
	}

	point_destroy( &point );

	if (cp == stop) {
		TYPRINT( " Found \"%s\", headed %s at %s.", word, direction_tostring(
					direction ), point_toStr( start ));
	}
	return cp == stop;
}
void try_free_answers( void )
{
	size_t stop = Seq_length( answer );
	size_t n = 0;

	for (n = 0; n < stop; n++) {
		void* vp = Seq_get( answer, n );
		FREE( vp );
	}

	Seq_free( &answer );
}

/*
 * local
 * functions
 */
static bool get_next_point_this_direction( direction_t direction, point_t point)
{
	goFunctPtr_t go_direction = go_getFunctionPtr( direction );
	bool flag =  go_direction( point );

	if (!flag && v & 0x2) {
		TYPRINT( " Can't go %s any further than %s",
				direction_tostring( direction ), point_toStr( point ) );
	}

	return flag;
}

static bool does_char_match_point( const char ch, point_t p )
{
	const char char_at_point = (const char)wstable_atPoint( puzzle, p );
	bool flag = (ch == char_at_point);

	if (!flag) {
		TYPRINT( " %c != %c at %s\n", ch, char_at_point, point_toStr( p ));
	}
	return flag;
}

static void add_solution( Seq_T answer, const char* word, point_t start, direction_t direction )
{
	solution_t solution = solution_init( (char*)word, start, direction );
	if(v&0x1)fprintf( stderr, "%s:%d - Found word: %s\n", __FILE__, __LINE__, solution_tostring( solution ));
	Seq_addhi( answer, (void*)solution );
}
