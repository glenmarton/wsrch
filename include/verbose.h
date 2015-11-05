/* verbose.h				DATE: 2015-11-02
 * PURPOSE: Verbose print controls.
 */
#ifndef __VERBOSE_H__
#define __VERBOSE_H__

enum verbose_t { VERBOSE_OFF, CONSTRUCTOR_DESTRUCTOR, GET_SET };

#define CDPRINT(fmt, args...) verbose_print( CONSTRUCTOR_DESTRUCTOR, __func__, (fmt), ## args)
#define GSPRINT(fmt, args...) verbose_print( GET_SET, __func__, (fmt), ## args)

/* Global count = 4 */
void verbose_set( int v );
int verbose_get( void );
void verbose_print( enum verbose_t bitmap, const char* func, const char* fmt, ... );
#endif /* __VERBOSE_H__ */
