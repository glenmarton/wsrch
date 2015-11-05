#include <stdio.h>		//gmj20151102 DEBUG Take out soon!!
#include <string.h>
#include "mem.h"
#include "point.h"
#include "verbose.h"


point_t point_create( void )
{
	CDPRINT( " => (0,0)" );
	point_t p = (point_t)ALLOC( sizeof( pointStruct ));

	memset( p, 0, sizeof( pointStruct ));

	return p;
}

point_t point_new( int r, int c )
{
	CDPRINT( " => (%d, %d)", r, c );
	point_t p = point_create();

	p->row = r;
	p->col = c;

	return p;
}

void point_destroy( point_t* ptr )
{
	point_t p = *ptr;
	CDPRINT( " %p", *ptr );
	//CDPRINT( " (%d,%d)", p->row, p->col );

	FREE( p );
	*ptr = NULL;
}

point_t point_duplicate( point_t src )
{
	point_t dup = (point_t)ALLOC( sizeof( pointStruct ));

	dup->row = src->row;
	dup->col = src->col;

	return dup;
}
