/* wstable.h				DATE: 2015-10-16
 * PURPOSE: Handle processing word search table.
 */
#ifndef __WSTABLE_H__
#define __WSTABLE_H__

#include "point.h"

typedef struct wstableStruct* wstable_t;

/* Global count = 11 */
void wstable_init( const char* fname );
wstable_t wstable_create( void );
void wstable_destroy( wstable_t* wstablePtr );
char* wstable_getFilename( void );
void wstable_setFilename( const char* fname );
void wstable_read( void );
size_t wstable_getHeight( void );
size_t wstable_getWidth( void );
char wstable_at( size_t row, size_t col );
int wstable_atPoint( point_t point );
char* wstable_getLine( size_t row );
#endif /* __WSTABLE_H__ */
