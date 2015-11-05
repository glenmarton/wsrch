/* solution.h				DATE: 2015-10-23
 * PURPOSE: Handle manipulation of a solution.
 */
#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "direction.h"
#include "point.h"

typedef struct solutionStruct* solution_t;

/* Global count = 10 */
solution_t solution_create( void );
solution_t solution_init( char* w, point_t p, direction_t d );
void solution_destroy( solution_t* solutionPtr );
direction_t solution_getDirection( solution_t s );
void solution_setDirection( solution_t s, direction_t d );
point_t solution_getPoint( solution_t s );
void solution_setPoint( solution_t s, point_t p );
char* solution_getWord( solution_t s );
void solution_setWord( solution_t s, char* word );
char* solution_tostring( solution_t s );
#endif /* __SOLUTION_H__ */
