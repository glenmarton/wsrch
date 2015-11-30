#include <stdio.h>
#include <stdbool.h>
#include "direction.h"
#include "go.h"
#include "point.h"
#include "verbose.h"

/*
 * local
 * variables
 */
static int v = 0x0;
static int height = 0;
static int width = 0;
static 	goFunctPtr_t table[] = { NULL,
		go_north, go_northeast, go_east, go_southeast,
		go_south, go_southwest, go_west, go_northwest };

/*
 * local
 * prototypes
 */
static bool adjust_heightLimit( point_t p );
static bool adjust_widthLimit( point_t p );

/*
 * global
 * functions
 */
void go_init( int r, int c )
{
	height = r;
	width = c;
}

bool go_north( point_t p )
{
	bool flag = false;

	if (adjust_widthLimit( p ) || adjust_heightLimit( p )) {
		GOPRINT( " can not go any further than %s.", point_toStr( p ));
	} else if (p->row > 0) {
		p->row--;
		flag = true;
	}
	return flag;
}

bool go_south( point_t p )
{
	bool flag = false;
	int max = height - 1;

	if (adjust_widthLimit( p ) || adjust_heightLimit( p )) {
		GOPRINT( " can not go any further than %s.", point_toStr( p ));
	} else if (p->row < max) {
		p->row++;
		flag = true;
	}
	return flag;
}

bool go_east( point_t p )
{
	bool flag = false;
	int max = width - 1;

if(v&1)fprintf( stderr, "%s(%d, %d) table(%d, %d)\n", __func__, p->row, p->col, height, width);
	if (adjust_widthLimit( p ) || adjust_heightLimit( p )) {
		GOPRINT( " can not go any further than %s.", point_toStr( p ));
	} else if (p->col < max) {
		p->col++;
		flag = true;
	}
	return flag;
}

bool go_west( point_t p )
{
	bool flag = false;

	if (adjust_widthLimit( p ) || adjust_heightLimit( p )) {
		/* do nothing */
	} else if (p->col > 0) {
		p->col--;
		flag = true;
	}

	return flag;
}

bool go_northeast( point_t p )
{
	return go_north( p ) && go_east( p );
}

bool go_southeast( point_t p )
{
	return go_south( p ) && go_east( p );
}

bool go_northwest( point_t p )
{
	return go_north( p ) && go_west( p );
}

bool go_southwest( point_t p )
{
	return go_south( p ) && go_west( p );
}

goFunctPtr_t go_getFunctionPtr( direction_t direction )
{
	goFunctPtr_t fptr = NULL;

	if (direction > NONE && direction <= NORTH_WEST) {
		fptr = table[ direction ];
	} else {
#ifndef CPPUTEST_COMPILATION
		fprintf( stderr, "%s() passed invalid direction %d.\n", __func__, direction);
#endif /* CPPUTEST_COMPILATION */
	}

	return fptr;
}

void go_print_fptrs( void )
{
	direction_t d = NONE;

	while (d <= NORTH_WEST) {
		printf( "%s = %p\n", direction_tostring( d ), table[ d ] );
		d++;
	}
}

/*
 * local
 * functions
 */
static bool adjust_heightLimit( point_t p )
{
	bool flag = true;

	if (p->row < 0) {
		p->row = 0;
	} else if (p->row >= height) {
		p->row = height - 1;
	} else {
		flag = false;
	}

	return flag;
}

static bool adjust_widthLimit( point_t p )
{
	bool flag = true;

	if (p->col < 0) {
		p->col = 0;
	} else if (p->col >= width) {
		p->col = width - 1;
	} else {
		flag = false;
	}

	return flag;
}
