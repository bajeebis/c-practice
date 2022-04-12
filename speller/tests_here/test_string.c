#include <stdio.h>
#include <strings.h>
#include <string.h>

int main(void)
{
    char name[5] = "Mia's";
    printf("%lu\n", strlen(name));
    int i = name[5-2];
    if (i == 39)
    {
        printf("Match\n");
    }
    else
    {
        printf("No match\n");
    }

    char name2[4] = "Mia";4
    int beef = (int) strlen(name2);
    if (name[4-1] == 39)
    {
        printf("Match on %d\n", beef);
    }
    else
    {
        printf("No match\n");
    }
}