#include <stdio.h>
#include "strings.h"
#include "lin_to_win.h"

void output(char **a)
{
    char *delim = a[1];
    char str_to_process[20][MAX_PATH];
    int t = 0;

    char *source_string = a[3];
    char *strings[10];
	int numb_str = split_string(source_string, delim, strings);

    for (int j = 0; j < numb_str; j++) {
        char strtotest[MAX_PATH];
        scpy(strtotest, strings[j]);
        int *b = check(strtotest);
        if (b[0] == 0) {
#if (DEBUG == 1)
            printf("ip good\n%s\n", strings[j]);
#endif
            scpy(str_to_process[t], strings[j]);
            t++;
        } else if (b[0] == 2) {
#if (DEBUG == 1)
            printf("domain good\n%s\n", strings[j]);
#endif
            scpy(str_to_process[t], strings[j]);
            t++;
        }
#if (DEBUG == 1)
        for (int i = 1; b[i] != -1; i++) {
            if (b[i] == 9)
                printf("Превышено максимальное количество символов в пути:\n%s\n", strings[j]);
            if (b[i] == 10)
                printf("Должен использоваться протокол URL:\n%s\n", strings[j]);
            if (b[i] == 11)
                printf("В пути используются запрещённые символы:\n%s\n", strings[j]);
            if (b[i] == 5)
                printf("Неверный формат адреса:\n%s\n", strings[j]);
            if (b[i] == 4)
                printf("Доменное имя должно оканчиваться на .com, .ru, .org:\n%s\n", strings[j]);
            if (b[i] == 6)
                printf("Неверный диапазон ip:\n%s\n", strings[j]);
            if (b[i] == 7)
                printf("Глубина вложения доменного имени должна быть не больше четырёх:\n%s\n", strings[j]);
            if (b[i] == 8)
                printf("Ip должен содержать четыре десятичных числа:\n%s\n", strings[j]);
        }
        printf("\n");
#endif
    }
    char *out = process(str_to_process, t);

    printf("new path: %s\n", out);
}
