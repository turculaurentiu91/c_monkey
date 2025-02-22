//
// Created by Laurentiu Turcu on 05/02/25.
//

#include <stdlib.h>
#include <string.h>

#include "strings.h"

string_t string_new(char *data, unsigned int length) {
    string_t str = {data, length};
    return str;
}

string_t string_new_from_literal(char *literal) {
    unsigned int length = strlen(literal);

    string_t str = {NULL, length};
    if (length == 0) {
        return str;
    }

    str.data = malloc(sizeof(char) * length);
    memcpy(str.data, literal, length);
    return str;
}

void string_free(string_t *s) {
    free(s->data);
    free(s);
}

char string_equals(string_t *s1, string_t *s2) {
    if (s1 == NULL && s2 == NULL) {
        return 1;
    }

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    char result = 1;

    if (s1->length != s2->length) {
        return 0;
    }

    for (unsigned int i = 0; i < s1->length; i++) {
        char ch1 = s1->data[i];
        char ch2 = s2->data[i];

        if (ch1 != ch2) {
            result = 0;
            break;
        }
    }

    return result;
}

string_t *string_slice(unsigned int start, unsigned int length, string_t *s) {
    if (start == 0 && length == s->length) {
        return s;
    }

    unsigned int new_length = length;
    if (start + length > s->length) {
        new_length = s->length - start;
    }

    string_t *str = malloc(sizeof(string_t));
    str->length = new_length;
    str->data = &s->data[start];
    return str;
}

void string_to_c_string_copy(char *dest, string_t *s, unsigned int max_length) {
    unsigned int length = s->length;
    if (length > max_length) {
        length = max_length;
    }

    memcpy(dest, s->data, length);
    dest[length] = '\0';
}
