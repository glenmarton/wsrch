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
static int read_file( const char* fname );

/*
 * global
 * functions
 */
int wordsearch_load( const char* fname )
{
	CDPRINT( " %s", fname );
	strlcpy( filename, fname, sizeof( filename ));

	memset( wordsearch, 0, sizeof( wordsearch ));

	width  = 0;
	height = 0;

	return read_file( fname );
}

char* wordsearch_getFilename( void )
{
	return filename;
}

void wordsearch_setFilename( const char* fname )
{
	GSPRINT( "old: %s, new: %s", filename, fname );
	strlcpy( filename, fname, sizeof( filename ));
}

void wordsearch_read( void )
{
	FILE* fp = fopen( filename, "r" );
	char line[MAX_WIDTH + 1];

	if (!fp) {
		perror( "ERROR: Can not open word search table" );
		exit( 2 );
	}

	while (fgets( line, sizeof( line ), fp ) != NULL) {
		width = strlen( line );
		strlcpy( wordsearch[ height ], line, width + 1 );
		height++;
	}
	fclose( fp );

	assert( width <= MAX_WIDTH );
	assert( height <= MAX_HEIGHT );
}

size_t wordsearch_getHeight( void )
{
	return height;
}

size_t wordsearch_getWidth( void )
{
	return width;
}

/*
 * local
 * functions
 */
static int read_file( const char* fname )
{
	FILE* fp = fopen( fname, "r" );

	if (!fp) {
		perror( "Fatal can't open word search input table" );
		return 0;
	}

	while (fgets( wordsearch[ height ], MAX_WIDTH, fp )) {
		height++;
	}

	return fclose( fp ) != 0;
}
