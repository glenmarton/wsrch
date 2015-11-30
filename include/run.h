/* run.h				DATE: 2015-11-20
 * PURPOSE: Run the word search.
 */
#ifndef __RUN_H__
#define __RUN_H__

/* Global count = 3 */
void run( wstable_t wstable, FILE* fin );
void run_searchWord( wstable_t wstable, const char *word );
Seq_T run_findWord( wstable_t puzzle, const char* word );
#endif /* __RUN_H__ */
