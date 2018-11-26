#ifndef STRING_H
#define STRING_H

#include "../../include/string.h"

hidden void *__memrchr(const void *, int, size_t);
hidden char *__stpcpy(char *, const char *);
hidden char *__stpncpy(char *, const char *, size_t);
hidden char *__strchrnul(const char *, int);
hidden size_t __strscpy(const char *, char *, size_t);

#endif
