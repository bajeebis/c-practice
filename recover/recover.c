#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    typedef uint8_t BYTE;
    BYTE header[512];
    int x = 0, y = 0;
    char jpegname[8];

    while (fread(&header, sizeof(header), 1, file) != 0)
    {
        if (header[0] == 0xff && header[1] == 0xd8 && header[2] == 0xff && (header[3] & 0xf0) == 0xe0)
        {
            sprintf(jpegname, "%03i.jpg", x);
            FILE *test = fopen(jpegname, "r");
            if (test == NULL)
            {
                FILE *img = fopen(jpegname, "w");
                fwrite(&header, sizeof(header), 1, img);
                x += 1;
                fclose(img);
                y = 1;
            }
            else
            {
                fclose(test);
            }
        }
        else if (y == 1)
        {
            FILE *img = fopen(jpegname, "a");
            fwrite(&header, sizeof(header), 1, img);
            fclose(img);
        }
        else
        {
            y = 0;
            continue;
        }

    }
    fclose(file);
}