/* str_util.h				DATE: 2014-01-13
 */
#ifndef __STR_UTIL_H__
#define __STR_UTIL_H__

/* Global count = 11 */
size_t strlcpy(char *dst, const char *src, size_t siz);
size_t strlcat(char *dst, const char *src, size_t siz);
char* chop(char* str);
char* chomp(char* str);
char *ltrim(char *s);
char* rtrim_spaces(char *str);
char *rtrim(char *s);
char *trim(char *s);
char* strutil_escapeChars(char* dest,size_t dest_sz,const char*src,const char* escape_chars);
size_t count_conversion_specifiers(const char* fmt);
size_t fmtlen_minus_conversion_specifiers (const char*fmt);
#endif /* __STR_UTIL_H__ */
