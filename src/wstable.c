#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "direction.h"
#include "go.h"
#include "wstable.h"
#include "mem.h"
#include "point.h"
#include "Seq.h"
#include "solution.h"
#include "str_util.h"
#include "verbose.h"

/*
 * typedefs
 */
typedef struct wstableStruct {
	char* wstable[80];
	size_t width, height;
} wstableStruct;

/*
 * local
 * variables
 */
static int v = 0;	// verbose flag

/*
 * local
 * prototypes
 */
#ifdef NOT_YET	//gmj20151113
static bool try_this_location( const char* word, point_t start, Seq_T solutions );
static bool try_every_direction( const char* word, point_t start, Seq_T answer );
static bool try_this_direction( const char*word, point_t start, direction_t direction );
static void add_solution( Seq_T answer, const char* word, point_t start, direction_t direction );
static void set_filename( const char* fname );
#endif /* NOT_YET */

/*
 * global
 * functions
 */
wstable_t wstable_create( void )
{
	wstable_t puzzle = (wstableStruct*) ALLOC( sizeof( wstableStruct ));

	memset( puzzle->wstable, 0, sizeof( puzzle->wstable ));
	puzzle->width = 0;
	puzzle->height = 0;

	return puzzle;
}

void wstable_destroy( wstable_t* wstablePtr )
{
	wstable_t puzzle = *wstablePtr;
	size_t i, stop = puzzle->height;

	for (i = 0; i < stop; i++) {
		FREE( puzzle->wstable[i]);
	}

	FREE( wstablePtr );
}

size_t wstable_getHeight( wstable_t puzzle )
{
	return puzzle->height;
}

size_t wstable_getWidth( wstable_t puzzle )
{
	return puzzle->width;
}

char wstable_at( wstable_t puzzle, size_t row, size_t col )
{
	size_t width = puzzle->width;
	size_t height= puzzle->height;
	size_t no_table_loaded = 0;

	assert( height != no_table_loaded && width != no_table_loaded );

	if(v&0x10)fprintf( stderr, "%s:%d - height = %zu, row = %zu\n", __FILE__, __LINE__, height, row );
	assert( row < height );
	assert( col < width );

	return puzzle->wstable[ row ][ col ];
}

int wstable_atPoint( wstable_t puzzle, point_t point )
{
	size_t r = (size_t) point->row;
	size_t c = (size_t) point->col;

	return wstable_at( puzzle, r, c );
}

char* wstable_getLine( wstable_t puzzle, size_t row )
{
	size_t y = row - 1;

	assert( y < puzzle->height );

	return puzzle->wstable[ y ];
}


size_t wstable_addLine( wstable_t puzzle, const char* line )
{
	assert( puzzle );

	if (line) {
		size_t row = puzzle->height++;

		puzzle->wstable[ row ] = mem_stringDuplicate ( line );

		if (puzzle->width == 0) {
			puzzle->width = strlen( line );
		}
	}

	return puzzle->height;
}

/*
 * local
 * functions
 */
#ifdef NOT_YET	//gmj20151113
static bool try_this_location( const char* word, point_t start, Seq_T solutions )
{
	bool flag = false;
	int first_char_of_word = *word;
	int char_at_start_point = wstable_atPoint( puzzle, start );

if(v&8)fprintf( stderr, "%s() - First letter %c == %c at (%d, %d)? %d\n", __func__, *word, char_at_start_point, start->row, start->col, *word == char_at_start_point);
	if (first_char_of_word == char_at_start_point) {
		flag = try_every_direction( word, start, solutions );
	}

	return flag;
}

static bool try_every_direction( const char* word, point_t start, Seq_T answer)
{
	bool flag = false;
	direction_t direction = NORTH_WEST;
	point_t p = point_create();

	go_create( (int)height, (int)width );

	while (direction != NONE) {
		p->row = start->row;
		p->col = start->col;
if(v&4)fprintf( stderr, "\n\t%s:%d - First letter of '%s' at (%d, %d) direction: '%s'\n", __FILE__, __LINE__, word, start->row, start->col, direction_tostring( direction ));
		if (try_this_direction( word, p, direction )) {
			add_solution( answer, word, start, direction );
			flag = true;
		}
		direction--;
	}

	go_destroy();

	point_destroy( &p );

	return flag;
}

static bool try_this_direction( const char*word, point_t start, direction_t direction )
{
	const char* cp = word + 1;
	const char* stop = word + strlen( word ) - 1;
	goFunctPtr_t go_direction = go_getFunctionPtr( direction );

if(v&2)fprintf( stderr, "%s:%d - Second letter of '%s' %c at (%d, %d) direction: '%s', last char '%c'\n", __FILE__, __LINE__, word, *cp, start->row, start->col, direction_tostring( direction ), *stop );
	while (cp != stop ) {
		if (!go_direction( start )) {
if(v&2)fprintf( stderr, "%s:%d - Can't go %s any further than (%d, %d)\n", __FILE__, __LINE__, direction_tostring( direction ), start->row, start->col );
			break;
		} else if (*cp != wstable_atPoint( start )) {
if(v&2)fprintf( stderr, "%s:%d - %c != %c at (%d, %d)\n", __FILE__, __LINE__, *cp, wstable_atPoint( start ), start->row, start->col );
			break;
		} else {
			cp++;
		}
	}

if(v&1 && cp == stop)fprintf( stderr, "%s(\"%s\", %s) - Found at (%d, %d).\n", __func__, word, direction_tostring( direction ), start->row, start->col );
	return cp == stop;
}

static void add_solution( Seq_T answer, const char* word, point_t start, direction_t direction )
{
	solution_t solution = solution_init( (char*)word, start, direction );
	if(v&0x1)fprintf( stderr, "%s:%d - Found word: %s\n", __FILE__, __LINE__, solution_tostring( solution ));
	Seq_addhi( answer, (void*)solution );
}

static void set_filename( const char* fname )
{
	FREE( filename );

	if (fname) {
		filename = mem_stringDuplicate( fname );
	}
}
#endif /* NOT_YET */
