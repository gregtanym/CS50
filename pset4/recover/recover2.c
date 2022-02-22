#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // programme should only take one command line argument
    if (argc != 2)
    {
        printf("invalid input\n");
        return 1;
    }

    // open file given to READ only
    FILE *fp = fopen(argv[1], "r");

    // if file not found or cannot be opened, user should be informed
    if (fp == NULL)
    {
        printf("file could not be opened\n");
        return 1;
    }

    else
    {
        printf("file opened successfully\n");
    }

    // why do i need to guess and check the malloc size and the fread element number?????
    BYTE* buffer = malloc(3.57 * 1000000000);
    int r = fread(buffer, 512, 9000, fp);
    printf("%i\n", r);


    int i = 0;
    int j = 0;
    while(1<2)
    {
        if (buffer[0 + 512 * i] != 0xff && buffer[1 + 512 * i] != 0xd8 && buffer[2 + 512 * i] != 0xff && (buffer[3 + 512 * i] & 0xf0) != 0xe0)
        {
        printf("start not found\n");
        i++;
        }
        else if(buffer[0 + 512 * i] == 0xff && buffer[1 + 512 * i] == 0xd8 && buffer[2 + 512 * i] == 0xff && (buffer[3 + 512 * i] & 0xf0) == 0xe0)
        {
            printf("start found\n");
            break;
        }
    }

    // creating an array to hold the name of the jpg files in sequence
    char* array = malloc(7 * sizeof(char) + 1);
    if (array == NULL)
    {
        printf("Error 1\n");
        return 1;
    }
    sprintf(array, "%03i.jpg", j);

    // create new file
    FILE* img = fopen(array, "w");
    if(img == NULL)
    {
        printf("Error 2\n");
        return 1;
    }

    BYTE* ptr = &buffer[0 + 512 * i];

    fwrite(ptr, 512, 1, img);


    for (i = i + 1; i < r; i++)
    {
        ptr = &buffer[0 + 512 * i];
        // if new header is detected, close the current file, create a new one and write the data in it
        if (buffer[0 + 512 * i] == 0xff && buffer[1 + 512 * i] == 0xd8 && buffer[2 + 512 * i] == 0xff && (buffer[3 + 512 * i] & 0xf0) == 0xe0)
        {
            //seg fault also occurs here
            fclose(img);
            j++;
            sprintf(array, "%03i.jpg", j);
            img = fopen(array, "w");

            fwrite(ptr, 512, 1, img);

        }

        // else continue writing the data in it
        else
        {
            fwrite(ptr, 512, 1, img);
        }
    }
    free(buffer);
    free(array);
    fclose(img);
    fclose(fp);

}