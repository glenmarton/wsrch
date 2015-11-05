/* wstable.h				DATE: 2015-10-16
 * PURPOSE: Handle processing word search table.
 */
#ifndef __WSTABLE_H__
#define __WSTABLE_H__

#include "point.h"
#include "Seq.h"

/* Global count = 11 */
void wstable_create( const char* fname );
void wstable_destroy( void );
char* wstable_getFilename( void );
void wstable_setFilename( const char* fname );
void wstable_read( void );
size_t wstable_getHeight( void );
size_t wstable_getWidth( void );
char wstable_at( size_t row, size_t col );
int wstable_atPoint( point_t point );
char* wstable_getLine( size_t row );
bool wstable_findWord( const char* word, Seq_T solutions );
#endif /* __WSTABLE_H__ */
