/* testtable.h				DATE: 2015-11-20
 */
#ifndef __TESTTABLE_H__
#define __TESTTABLE_H__

/* Global count = 5 */
void testtable_init( void );
size_t testtable_getHeight( void );
size_t testtable_getWidth( void );
void testtable_addline( const char* cp );
const char* testtable_getline( size_t i );
#endif /* __TESTTABLE_H__ */
