/* wstable.h				DATE: 2015-10-16
 * PURPOSE: Handle processing word search table.
 */
#ifndef __WSTABLE_H__
#define __WSTABLE_H__

#include "point.h"

typedef struct wstableStruct* wstable_t;
typedef const char*(*getlineFp_t)(size_t);

/* Global count = 11 */
wstable_t wstable_createEmpty( void );
wstable_t wstable_create( size_t height, size_t width, getlineFp_t getline );
void wstable_destroy( wstable_t* wstablePtr );
wstable_t wstable_duplicate( wstable_t orig );
size_t wstable_getHeight( wstable_t puzzle );
size_t wstable_getWidth( wstable_t puzzle );
char wstable_at( wstable_t puzzle, size_t row, size_t col );
int wstable_atPoint( wstable_t puzzle, point_t point );
char* wstable_getLine( wstable_t puzzle, size_t row );
size_t wstable_addLine( wstable_t puzzle, const char* line );
void wstable_show( wstable_t puzzle, void* vp );
#endif /* __WSTABLE_H__ */
