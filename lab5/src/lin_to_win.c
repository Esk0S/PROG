#include "lin_to_win.h"
#include "strings.h"

char **input()
{
#if (DEBUG == 1)
	FILE *input = fopen("input_debug.txt", "r");
#else
    FILE *input = fopen("input.txt", "r");
#endif
    char **a = malloc(4 * sizeof(a));
    for (int i = 0; i < 4; i++) {
        a[i] = malloc(1000);
    }
    for (int i = 0; i < 4; i++)
    {
        fscanf(input, "%s", a[i]);
    }
    return a;
}

int IpOrDomain(char *split_ip_domain[], int ip_domain_l)
{
	int isip = 0;
	for (int i = 0; i < ip_domain_l; i++) {
		for (int j = 0; split_ip_domain[i][j] != '\0'; j++) {
			if (!my_isdigit(split_ip_domain[i][j])) {
				isip = 1;
			}
		}
	}
	
	int isdomain = 2;
	for (int i = 0; i < ip_domain_l; i++) {
		for (int j = 0; split_ip_domain[i][j] != '\0'; j++) {
			if (!my_isalpha(split_ip_domain[i][j])) {
				isdomain = 3;
			}
		}
	}
	if (isdomain == 2)
		return 2;
	if (isip == 0)
		return 0;

	return 5;
}

int DomainCheck(char *domain)
{
	if (scmp(domain, "com") == 0 || scmp(domain, "ru") == 0 || scmp(domain, "org") == 0){
		return 1;
	}
	return 0;
}

int IpCheck(char *ip[MAX_PATH], int ip_domain_l)
{
	for (int i = 0; i < ip_domain_l; i++) {
		if (atoi(ip[i]) > 255 || atoi(ip[i]) < 0) {
			return 0;
		}
	}
	return 1;
}

int *check(char *source_string)
{
	int *a = malloc(4 * 15);
	int err_c = 1;
	for (int i = 0; i < 15; i++) {
		a[i] = -1;
	}
	char forbidden_chars[] = "/\\:*?«<>|";
	char *str[MAX_PATH];
	char string[MAX_PATH];
	scpy(string, source_string);
	int str_l = split_string(string, ":/", str);
#if (DEBUG == 1)
	for (int i = 0; i < str_l; i++) {
		printf("token %d: %s\n", i + 1, str[i]);
	}
#endif
	
	char *split_ip_domain[MAX_PATH];
	char ip_domain[MAX_PATH];
	scpy(ip_domain, str[1]);
	int ip_domain_l = split_string(ip_domain, ".", split_ip_domain);

	int IpDom = IpOrDomain(split_ip_domain, ip_domain_l);

	int w = 0;
	if (IpDom == 0 || IpDom == 2) {
		if (scmp("smb", str[0]) != 0 && scmp("http", str[0]) != 0) {
			a[err_c] = 10;
			err_c++;
		} else w++;
		int i;
		for (i = 2; i < str_l; i++) {
			if (sspn(str[i], forbidden_chars) == 0) {
				a[err_c] = 11;
				err_c++;
				break;
			}
		}
		if (i == str_l) {  w++; }
		if (slen(source_string) > MAX_PATH) {
#if (DEBUG == 1)
			printf("PATH_SIZE: %ld\n", slen(source_string));
#endif
			a[err_c] = 9;
			err_c++;
		} else w++;
	}

	if (IpDom == 0) {
		if (!IpCheck(split_ip_domain, ip_domain_l)) {
			a[err_c] = 6;
			err_c++;
		} else w++;
		if (ip_domain_l != 4) {
			a[err_c] = 8;
			err_c++;
		} else w++;
		if (w == 5) {
			a[0] = IpDom;
		}
	}
	
	if (IpDom == 2) {
		if (!DomainCheck(split_ip_domain[ip_domain_l - 1])) {
			a[err_c] = 4;
			err_c++;
		} else w++;
		if (ip_domain_l > 4) {
			a[err_c] = 7;
			err_c++;
		} else w++;
		if (w == 5) {
			a[0] = IpDom;
		}
	}
	if (IpDom != 0 && IpDom != 2) {
		a[err_c] = 5;
		err_c++;
	}
	return a;
}

char *process(char source_strings[][MAX_PATH], int str_c)
{
	char *splited_strings[MAX_PATH];
	int num_toks;
	char *dest_str = malloc(1000);
	int g = 0;
	int q;

	for (int j = 0; j < str_c; j++) {
		q = 1;
		num_toks = split_string(source_strings[j], ":/", splited_strings);
		dest_str[g] = '\\';
		g++;
		dest_str[g] = '\\';
		g++;
		dest_str[g] = '\0';
		g--;
		for (int i = 0; i < num_toks - 1; i++) {
			scat(dest_str, splited_strings[q]);
			g += slen(splited_strings[q]);
			scat(dest_str, "\\");
			g++;
			q++;
		}
		if (j != str_c - 1) {
			scat(dest_str, "+");
			g += 2;
		}
	}

	return dest_str;
}