/* wordsearch.h				DATE: 2015-11-12
 * PURPOSE: Load the actual word search table from input file.
 */
#ifndef __WORDSEARCH_H__
#define __WORDSEARCH_H__

/* Global count = 8 */
int wordsearch_load( const char* fname );
wstable_t wordsearch_create( void );
void wordsearch_destroy( wstable_t* wstablePtr );
char* wordsearch_getFilename( void );
void wordsearch_setFilename( const char* fname );
void wordsearch_read( void );
size_t wordsearch_getHeight( void );
size_t wordsearch_getWidth( void );
#endif /* __WORDSEARCH_H__ */
