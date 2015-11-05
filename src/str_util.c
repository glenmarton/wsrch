/*	$OpenBSD: strlcpy.c,v 1.11 2006/05/05 15:27:38 millert Exp $	*/

/*
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

#include "str_util.h"

/*
 * local
 * prototoypes
 */
static int add_char_to_dest(const char*, char**, size_t, char);
static int is_possible(const char* fmt);
static size_t specifier_len (const char* fmt);

/*
 * global
 * functions
 */

/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
size_t strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++);

	}

	long dstLen = s - src;

	if (dstLen > (long)siz)
		fprintf(stderr, "%s truncation warning, need %ld byte buffer, only given %zu bytes",
				__func__, dstLen, siz);

	return (size_t)(dstLen - 1);	/* count does not include NUL */
}

/*
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
 * Returns strlen(src) + MIN(siz, strlen(initial dst)).
 * If retval >= siz, truncation occurred.
 */
size_t strlcat(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (n-- != 0 && *d != '\0')
		d++;
	dlen = (size_t) (d - dst);
	n = siz - dlen;

	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return  (dlen + (size_t)(s - src));	/* count does not include NUL */
}

/****************************************************************
 * chop()
 * PURPOSE:
 *	Removes the last character from the end of str.
 * ARGS:
 *	str - string to remove last char from
 * RETURN:
 *	str - string passed in
 */
char* chop(char* str)
{
	size_t n;

	for(n=0; str[n]!='\0'; n++);

	if (n > 1)
		str[--n] = '\0';

	return str;
}

/*================================================================
 * chomp()
 * PURPOSE:
 *		Remove newline (<CR>, \n) from end of string.
 * ARGS:
 *		str - string to remove newline from
 * RETURN:
 * 		str - Original string without the newline.
 */
char* chomp(char* str)
{
	size_t n;

	for(n=0; str[n]!='\0'; n++);
	n--;

	if (n > 1 && str[n] == '\n')
		str[n] = '\0';

	return str;
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}


char* strutil_escapeChars(char* dest, size_t dest_sz, const char*src, const char* escape_chars)
{
	char *dst = dest;
	size_t src_sz = strlen(src);
	size_t n;

	for (n=0; n < src_sz; n++) {
		if (strchr(escape_chars, src[n])) {
			if ( ! add_char_to_dest(dest, &dst, dest_sz, '\\'))
				break;
		}
		if ( ! add_char_to_dest(dest, &dst, dest_sz, src[n]))
			break;
	}
	return dest;
}

size_t count_conversion_specifiers(const char* fmt)
{
	size_t count = 0;

	if (fmt == NULL)
		return 0;

	while (*fmt != '\0') {
		int status = is_possible (fmt);
		if (status == 1) {
			size_t sz = specifier_len(fmt);
			count += sz;
			fmt += sz;
			if (sz > 0)
				continue;
		} else if (status == 2) /* found 2 % chars, skip them */
			fmt++;
		fmt++;
	}
	return count;
}

/*---------------------------------------------------------------
 * fmtlen_minus_conversion_specifiers()
 * PURPOSE:
 *     Find the length of a fmt string, used by printf,
 *     excluding the conversion specifiers.
 *     Example:
 *     fmt[] = "Hello %s.\n" is 8 characters long.
 * ARGS:
 *    fmt - format string
 * RETURNS:
 *    len - length of string minus specifiers.
 */
size_t fmtlen_minus_conversion_specifiers (const char*fmt)
{
	size_t len = strlen (fmt);

	len -= count_conversion_specifiers (fmt);

	return len;
}

/*
 * local
 * functions
 */
static int add_char_to_dest(const char* start, char** end, size_t size, char add_c)
{
	int status = (*end - start < (long)size);
	char* cp = *end;

	if (status)
		*cp++ = add_c;

	*cp = '\0';

	(*end)++;

	return status;
}

static int is_possible(const char* fmt)
{
	int flag = 1;

	if (fmt == NULL) {
		flag = 0;
	}
	else if (fmt[0] == '\0' || fmt[0] != '%') {
		flag = 0;
	}

	else if (fmt[1] == '\0') {
		flag = 0;
	}
	else if (fmt[1] == '%') {
		flag = 2;
	}
	return flag;
}
static int is_specifier(int ch)
{
	char conversion_specifiers[] = "diouxXfFeEgGaAbcs";

	char* cp = strchr (conversion_specifiers, ch);

	return (cp != NULL);
}

static size_t specifier_len (const char* fmt)
{
	size_t count = 0;

	if (fmt == NULL || fmt[0] == '\0' || fmt[1] == '\0' || fmt[1] == '%')
		return count;
	else
		count++;

	while (fmt[count] != '\0') {
		if (is_specifier( fmt[count++] ))
			break;
	}
	return count;
}
