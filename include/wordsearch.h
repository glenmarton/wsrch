/* wordsearch.h				DATE: 2015-11-12
 * PURPOSE: Load the actual word search table from input file.
 */
#ifndef __WORDSEARCH_H__
#define __WORDSEARCH_H__

/* Global count = 7 */
wstable_t wordsearch_create( const char* fname );
void wordsearch_destroy( void );
int wordsearch_load( const char* fname );
char* wordsearch_getFilename( void );
size_t wordsearch_getHeight( void );
size_t wordsearch_getWidth( void );
const char* wordsearch_getLine( size_t index );
#endif /* __WORDSEARCH_H__ */
