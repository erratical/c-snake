#include <stdlib.h>
#include "../lib/buffer.h"
#include <string.h>

void abAppend(struct abuf *ab, const char *s, int len)
{
    // Reallocate memory to fit both ab->b and s
    char* new = realloc(ab->b, ab->len + len);

    if (new == NULL) return;

    // Copy string `s` into end of new
    memcpy(&new[ab->len], s, len);

    // Update `ab->b` and `ab->len`
    ab->b = new;
    ab->len += len;
}

void abFree(struct abuf *ab)
{
    free(ab->b);
}