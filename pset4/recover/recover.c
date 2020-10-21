#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // TODO check file =======================================================

    // accept command line argument, file name

    // if CLA != 1, error message & return 1
    if (argc != 2)
    {
        printf("Requires 1 file\n");
        return 1;
    }

    // open memory card
    FILE *file = fopen(argv[1], "r");

    // if file cannot be opened, return 1
    if (!file)
    {
        printf("Cannot open file\n");
        return 1;
    }



    // repeat until end of card:
    // look through memory card for beginning of JPEG
    // read file
    // fread(data, size, number, inptr)

    unsigned char buffer[512];
    int jpgCnt = -1;
    char *filename = malloc(8);
    FILE *img;

    while (fread(buffer, 512, 1, file) == 1)
    {
        // check if jpeg
        // starts 0xff 0xd8 0xff 0xe?
        // if buffer[0] = 0xff, .., .., (buffer[3] & 0xf0) == 0xe0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            jpgCnt++;

            // first file, open and start writing
            if (jpgCnt == 0)
            {
                sprintf(filename, "%03i.jpg", jpgCnt);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }
            // if second or more, close the previous file and start writing a new one
            else
            {
                fclose(img);

                sprintf(filename, "%03i.jpg", jpgCnt);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }
        }
        // if not a new jpeg, just write to current existing file
        else
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(file);

    // if using malloc, free memory.
    free(filename);
}
