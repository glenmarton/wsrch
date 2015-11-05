/* $Id: seq.c 6 2007-01-22 00:45:22Z drhanson $ */
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "assert.h"
#include "Seq.h"
#include "Array.h"
#include "Arrayrep.h"
#include "mem.h"
#define T Seq_T
struct seq_t {
	struct array_t array;
	size_t length;
	size_t head;
};
static void expand(T seq) {
	size_t n = seq->array.length;
	Array_resize(&seq->array, 2*n);
	if (seq->head > 0)
		{
			void **old = &((void **)seq->array.array)[seq->head];
			memcpy(old+n, old, (n - seq->head)*sizeof (void *));
			seq->head += n;
		}
}
T Seq_new(size_t hint) {
	T seq;
	assert(hint >= 0);
	NEW0(seq);
	if (hint == 0)
		hint = 16;
	ArrayRep_init(&seq->array, hint, sizeof (void *),
		ALLOC(hint*sizeof (void *)));
	return seq;
}
T Seq_seq(void *x, ...) {
	va_list ap;
	T seq = Seq_new(0);
	va_start(ap, x);
	for ( ; x; x = va_arg(ap, void *))
		Seq_addhi(seq, x);
	va_end(ap);
	return seq;
}
void Seq_free(T *seq) {
	assert(seq && *seq);
	assert((void *)*seq == (void *)&(*seq)->array);
	Array_free((Array_T *)seq);
}
size_t Seq_length(T seq) {
	assert(seq);
	return seq->length;
}
void *Seq_get(T seq, size_t i) {
	assert(seq);
	assert(i >= 0 && i < seq->length);
	return ((void **)seq->array.array)[(seq->head + i)%seq->array.length];
}
void *Seq_put(T seq, size_t i, void *x) {
	void *prev;
	assert(seq);
	assert(i >= 0 && i < seq->length);
	prev = ((void **)seq->array.array)[(seq->head + i)%seq->array.length];
	((void **)seq->array.array)[(seq->head + i)%seq->array.length] = x;
	return prev;
}
void *Seq_remhi(T seq) {
	size_t i;
	assert(seq);
	assert(seq->length > 0);
	i = --seq->length;
	return ((void **)seq->array.array)[(seq->head + i)%seq->array.length];
}
void *Seq_remlo(T seq) {
	size_t i = 0;
	void *x;
	assert(seq);
	assert(seq->length > 0);
	x = ((void **)seq->array.array)[(seq->head + i)%seq->array.length];
	seq->head = (seq->head + 1)%seq->array.length;
	--seq->length;
	return x;
}
void *Seq_addhi(T seq, void *x) {
	size_t i;
	assert(seq);
	if (seq->length == seq->array.length)
		expand(seq);
	i = seq->length++;
	return ((void **)seq->array.array)[(seq->head + i)%seq->array.length] = x;
}
void *Seq_addlo(T seq, void *x) {
	size_t i = 0;
	assert(seq);
	if (seq->length == seq->array.length)
		expand(seq);
	if (--seq->head < 0)
		seq->head = seq->array.length - 1;
	seq->length++;
	return ((void **)seq->array.array)[(seq->head + i)%seq->array.length] = x;
}
