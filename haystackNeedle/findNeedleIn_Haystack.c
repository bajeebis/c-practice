#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char *find_needle(const char **haystack, size_t count)
{
  int x;
  x = (int) count;
  for (int i = 0; i < x; i++) {
    int chck = strcmp(haystack[i], "needle");
    if (chck == 0) {
      char a[30] = "found the needle at position ";
      int length = snprintf(NULL, 0, "%d", i);
      printf("%d\n", length);
      char* str = malloc(length + 1);
      snprintf(str, length + 1, "%d", i);

      //printf("%s", strcat(a, str));
      printf("%s\n", str);

      static char buffer[32];
      snprintf(buffer, sizeof(a) + length + 1, "%s%s", a, str);
      free(str);
      printf("%s\n", buffer);
      return buffer;
    }
  }
  return 0;
}

