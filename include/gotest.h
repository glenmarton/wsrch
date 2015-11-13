#ifndef __GOTEST_H__
#define __GOTEST_H__

#include "point.h"

typedef bool(*goFunctPtr_t)( point_t );

/* Global count = 12 */
void go_init( int r, int c );
bool go_north( point_t p );
bool go_south( point_t p );
bool go_east( point_t p );
bool go_west( point_t p );
bool go_northeast( point_t p );
bool go_southeast( point_t p );
bool go_northwest( point_t p );
bool go_southwest( point_t p );
goFunctPtr_t go_getFunctionPtr( direction_t direction );
void go_print_fptrs( void );
#endif /* __GOTEST_H__ */