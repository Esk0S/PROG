#include "strings.h"
#include "lin_to_win.h"

size_t slen(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
    }
    return i;
}

int scmp(char *str1, char *str2)
{
    for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
    {
        if (str1[i] != str2[i])
        {
            if (str1[i] > str2[i])
                return 1;
            else if (str1[i] < str2[i])
                return -1;
        }
        
    }
    return 0;
}

int sspn(char *source, char *symbs)
{
    for (int i = 0; source[i] != '\0'; i++) {
        for (int j = 0; symbs[j] != '\0'; j++)
            if (symbs[j] == source[i]) 
                return 0;
    }
    return -1;
}

char *scpy(char dest[], const char source[])
{
    int i = 0;
    while (1)
    {
        dest[i] = source[i];
        if (dest[i] == '\0')
            break;
        i++;
    } 
    return dest;
}

const char *schr(const char *str, int symbol)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == symbol)
            return str + i;
    }
    return NULL;
}

char *stok(char *str, const char *delim)
{
	static char *last = 0;
	if (str)
		last = str;
	if ((last == 0) || (*last == 0))
		return 0;
	char *c = last;
	while (schr(delim, *c)) {
		++c;
	}
	if (*c == 0)
		return 0;
	char *start = c;
	while (*c && (schr(delim, *c) == 0))
		++c;
	if (*c == 0)
	{
		last = c;
		return start;
	}
	*c = 0;
	last = c + 1;
	return start;
}

int split_string(char *string, char *delim, char **buf)
{
	int i = 0;
    buf[i] = stok(string, delim);
    while (buf[i] != NULL) {
		i++;
        buf[i] = stok(NULL, delim);
    }
	return i;
}

int my_isdigit(char character)
{
    int f = 0;
    if (character >= '0' && character <= '9')
        f = 1;
    return f; 
}

int my_isalpha(char character)
{
    int f = 0;
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
        f = 1;
    return f;
}

char *scat(char *des, char *src)
{
	int j = slen(des);
	for (int i = 0; src[i] != 0; i++) {
		des[j] = src[i];
		j++;
	}
	des[j] = '\0';
	return des;
}
