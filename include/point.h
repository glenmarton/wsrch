/* point.h					DATE: 2015-10-23
 * PURPOSE: Define structure of a point.
 */
#ifndef __POINT_H__
#define __POINT_H__

typedef struct pointStruct {
	int row;
	int col;
} pointStruct;

typedef pointStruct* point_t;

/* Global count = 5 */
point_t point_create( void );
point_t point_new( int r, int c );
void point_destroy( point_t* ptr );
point_t point_duplicate( point_t src );
const char* point_toStr( point_t p );
#endif /* __POINT_H__ */
