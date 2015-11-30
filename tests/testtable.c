#include "testtable.h"

/*
 * constants
 */
#define MAX_HEIGHT 4
#define MAX_WIDTH 80

/*
 * local
 * variables
 */
static char table[MAX_HEIGHT][MAX_WIDTH];
static size_t height = MAX_HEIGHT;
static size_t width  = 0;

void testtable_init( void )
{
	size_t h, w;

	for (h = 0; h < MAX_HEIGHT; h++) {
		for (w = 0; w < MAX_WIDTH; w++) {
			table[h][w] = 0;
		}
	}
	height = 0;
	width = 0;
}

size_t testtable_getHeight( void )
{ return height; }

size_t testtable_getWidth( void )
{ return width; }

void testtable_addline( const char* cp )
{
	size_t w;

	if (height < MAX_HEIGHT) {

		for (w = 0; cp[w] != '\0'; w++) {
			table[height][w] = cp[w];
		}
		table[height][w] = '\0';

		height++;
		width = w;
	}
}

const char* testtable_getline( size_t i )
{
	const char* cp = NULL;

	if (i < height) {
		cp = table[i];
	}

	return cp;
}
