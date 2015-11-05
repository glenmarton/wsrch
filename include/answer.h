/* answer.h				DATE: 2015-11-02
 * PURPOSE: Handle all solutions for a given word in wstable.
 */
#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "Seq.h"
#include "solution.h"

/* Global count = 6 */
Seq_T answer_create( void );
void answer_destroy( Seq_T* answerPtr );
void answer_add( Seq_T answer, solution_t solution );
solution_t answer_get( Seq_T answer, size_t index );
size_t answer_count( Seq_T answer );
solution_t answer_remove( Seq_T answer );
#endif /* __ANSWER_H__ */
