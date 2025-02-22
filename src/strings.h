//
// Created by Laurentiu Turcu on 05/02/25.
//

#ifndef STRINGS_H
#define STRINGS_H


typedef struct {
    char *data;
    unsigned int length;
} string_t;

string_t string_new(char *data, unsigned int length);
string_t string_new_from_literal(char *literal);

void string_free(string_t *s);

char string_equals(string_t *s1, string_t *s2);

string_t *string_slice(unsigned int start, unsigned int length, string_t *s);

void string_to_c_string_copy(char *dest, string_t *s, unsigned int max_length);

#endif // STRINGS_H
