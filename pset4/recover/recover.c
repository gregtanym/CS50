#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open inputted file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error 1\n");
        return 1;
    }
    else
    {
        printf("File opened successfully\n");
    }

    // read file into buffer
    BYTE *buffer = malloc(3.57 * 100000000);
    if (buffer == NULL)
    {
        printf("Error 2\n");
        return 1;
    }
    int r = fread(buffer, 512, 7314, fp);
    printf("%i\n", r);

    // find start of jpeg file
    int i = 0;
    while (1 < 2)
    {
        if (buffer[0 + 512 * i] != 0xff && buffer[1 + 512 * i] != 0xd8 && buffer[2 + 512 * i] != 0xff && (buffer[3 + 512 * i] & 0xf0) != 0xe0)
        {
            i++;
        }
        else if (buffer[0 + 512 * i] == 0xff && buffer[1 + 512 * i] == 0xd8 && buffer[2 + 512 * i] == 0xff && (buffer[3 + 512 * i] & 0xf0) == 0xe0)
        {
            break;
        }
    }

    // create new jpeg file
    int j = 0;
    char *array = malloc(8);
    sprintf(array, "%03i.jpg", j);
    FILE *img = fopen(array, "w");

    // write first 512 chunk of data from buffer into new jpeg file
    BYTE *ptr = &buffer[0 + 512 * i];
    fwrite(ptr, 512, 1, img);

    // subsequent if conditions
    for (i = i + 1; i < r + 1; i++)
    {
        ptr = &buffer[0 + 512 * i];

        if (buffer[0 + 512 * i] == 0xff && buffer[1 + 512 * i] == 0xd8 && buffer[2 + 512 * i] == 0xff && (buffer[3 + 512 * i] & 0xf0) == 0xe0)
        {
            // close previous jpg file
            fclose(img);
            j++;

            // create new jpg file and write the first 512 chunk of data into it
            sprintf(array, "%03i.jpg", j);
            fopen(array, "w");

            fwrite(ptr, 512, 1, img);
        }

        
        else
        {
            // keep writing
            fwrite(ptr, 512, 1, img);
        }
    }
    return 0;
    fclose(img);
    fclose(fp);
    free(buffer);
    free(array);

}