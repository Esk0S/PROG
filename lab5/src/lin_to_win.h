#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MAX_PATH 260
#define DEBUG 1

char **input();
void output(char **a);
int *check(char *path);
int IpOrDomain(char *split_ip_domain[], int ip_domain_l);
int IpCheck(char *ip[], int);
int DomainCheck(char *domain);
char *process(char source_string[][MAX_PATH], int t);