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
 * global
 * functions
 */
wstable_t wstable_createEmpty( void )
{
	wstable_t puzzle = (wstableStruct*) ALLOC( sizeof( wstableStruct ));

	memset( puzzle->wstable, 0, sizeof( puzzle->wstable ));
	puzzle->width = 0;
	puzzle->height = 0;

	return puzzle;
}

wstable_t wstable_create( size_t height, size_t width, getlineFp_t getline )
{
	size_t h;

	wstable_t puzzle = wstable_createEmpty();

	for (h = 0; h < height; h++) {
		wstable_addLine( puzzle, getline( h ));
	}

	return puzzle;
}

void wstable_destroy( wstable_t* wstablePtr )
{
	wstable_t puzzle = *wstablePtr;
	size_t i, stop = 0;

	if (puzzle) {
		stop = puzzle->height;
	}

	for (i = 0; i < stop; i++) {
		FREE( puzzle->wstable[i]);
	}

	FREE( *wstablePtr );
}

wstable_t wstable_duplicate( wstable_t orig )
{
	wstable_t dup = NULL;
	size_t height;
	size_t width;
	size_t h;

	assert( orig );

	height = wstable_getHeight( orig );
	width = wstable_getWidth( orig );

	dup = wstable_createEmpty();
	dup->width = width;

	for (h = 0; h < height; h++) {
		wstable_addLine( dup, wstable_getLine( orig, h ));
	}

	return dup;
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
	if(v&0x10)fprintf( stderr, "%s:%d - width  = %zu, col = %zu\n", __FILE__, __LINE__, width,  col );
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
	assert( row < puzzle->height );

	return puzzle->wstable[ row ];
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

void wstable_show( wstable_t puzzle, void* vp )
{
	FILE* fp = (FILE*)vp;
	size_t i;
	//size_t stop = puzzle->height;
	size_t stop = sizeof( puzzle->wstable ) / sizeof( puzzle->wstable[0] );

	fprintf( fp, "%p => (%zu, %zu)\n", puzzle->wstable, puzzle->height, puzzle->width );
	for (i = 0; i < stop; i++) {
		fprintf( fp, "%s\n", puzzle->wstable[i] );
	}
	fputs( "\n", fp );
}
