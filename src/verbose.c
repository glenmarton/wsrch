#include <stdio.h>
#include "verbose.h"

/*
 * local
 * variables
 */
static enum verbose_t verbose = VERBOSE_OFF;

/*
 * global
 * functions
 */
void verbose_set( int v )
{
	verbose = v;
}

int verbose_get( void )
{
	return verbose;
}

void verbose_print( enum verbose_t bitmap, const char* func, const char* fmt, ... )
{
	if ((verbose & bitmap) != bitmap) {
		return;
	}

	char buf[250];
	va_list ap;

	size_t index = (size_t) sprintf( buf, "\t- %s()", func );

	va_start(ap, fmt);
	vsnprintf(&buf[index], sizeof(buf) - index, fmt, ap);	/* safe */
	fprintf( stderr, "%s\n", buf );
	va_end(ap);
}
