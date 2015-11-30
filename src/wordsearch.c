#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "str_util.h"
#include "verbose.h"

/*
 * constants
 */
#define MAX_WIDTH 80
#define MAX_HEIGHT 80

/*
 * local
 * variables
 */
static char filename[128] = "";
static char wordsearch[MAX_HEIGHT][MAX_WIDTH];
static size_t width  = 0;
static size_t height = 0;

/*
 * local
 * prototypes
 */
static void init( const char* fname );
static int read_file( FILE* fp );

/*
 * global
 * functions
 */
/*---------------------------------------------------------------
 * wordsearch_load()
 * PURPOSE:
 * Read word search puzzle into memory.
 *
 * ARGS:
 *	fname - file name of word search puzzle
 *
 * RETURNS:
 *	0 - false file failed to load
 *	1 - true file was loaded
 */
int wordsearch_load( const char* fname )
{
	int flag = 0;
	FILE *fp = NULL;

	if (fname == NULL || *fname == '\0') {
		return 0;
	}

	CDPRINT( " %s", fname );
	init( fname );

	fp = fopen( fname, "r" );

	if (fp) {
		flag = read_file( fp );
		fclose( fp );
	} else {
		perror( "Fatal can't open word search input table" );
	}

	return flag;
}

char* wordsearch_getFilename( void )
{
	return filename;
}

size_t wordsearch_getHeight( void )
{
	return height;
}

size_t wordsearch_getWidth( void )
{
	return width;
}

const char* wordsearch_getLine( size_t index )
{
	const char* cp = NULL;

	if (index < height) {
		cp = wordsearch[ index ];
	}

	return cp;
}

/*
 * local
 * functions
 */
static void init( const char* fname )
{
	strlcpy( filename, fname, sizeof( filename ));

	memset( wordsearch, 0, sizeof( wordsearch ));

	width  = 0;
	height = 0;
}

static int read_file( FILE* fp )
{
	while (fgets( wordsearch[ height ], MAX_WIDTH, fp )) {
		rtrim( wordsearch[ height ] );
		height++;
		assert( height <= MAX_HEIGHT );		// Word search has to many rows.
	}

	width = strlen( wordsearch[ 0 ] );
	assert( width < MAX_WIDTH );			// Word search has to many cols.

	return width > 0;
}
