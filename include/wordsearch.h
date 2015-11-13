/* wordsearch.h				DATE: 2015-11-12
 * PURPOSE: Load the actual word search table from input file.
 */
#ifndef __WORDSEARCH_H__
#define __WORDSEARCH_H__

/* Global count = 6 */
int wordsearch_load( const char* fname );
char* wordsearch_getFilename( void );
void wordsearch_setFilename( const char* fname );
void wordsearch_read( void );
size_t wordsearch_getHeight( void );
size_t wordsearch_getWidth( void );
#endif /* __WORDSEARCH_H__ */
