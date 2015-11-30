/* try.h				DATE: 2015-11-21
 * PURPOSE: Try to match word with this location/direction.
 */
#ifndef __TRY_H__
#define __TRY_H__

/* Global count = 7 */
void try_create( wstable_t wstable );
void try_destroy( void );
Seq_T try_this_location( const char* word, point_t start );
Seq_T try_every_direction( const char* word, point_t start );
bool try_this_direction( const char*word, point_t start, direction_t direction );
bool try_this_directionImpl( const char*word, point_t start, direction_t direction );
void try_free_answers( void );
#endif /* __TRY_H__ */
