#include<string.h>
#include<stdio.h>

int b;
void main() {
  char *s1 = "hello";
  char *s2 = "Hello";

  b = strcmp(s1, s2);
}
