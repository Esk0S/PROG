#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MAX_PATH 260

size_t slen(char*);
int scmp(char*, char*);
char *stok(char *str, const char *delim);
char *scpy(char dest[], const char source[]);
int sspn(char *source, char *symbs);
const char *schr(const char*, int);
int split_string(char *string, char *delim, char **buf);
int my_isdigit(char character);
int my_isalpha(char character);
char *sstr(char *string1, const char *string2);
char *scat(char *des, char *src);