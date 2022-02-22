#include <stdio.h>
#include <cs50.h>

void repeat(char c, int num);

int main()
{
    int h, w;
    do
    {
        h = get_int("Height:");
    }
    while (h < 1 || h > 8);
    w = h;

    int num_hash, num_space;
    for (int i = 0; i < h; i++)
    {
        // i starts from 0, so u have to account for this by adding 1 to i to get the correct number of hashes
        num_hash = i + 1;
        num_space = w - (num_hash);

        repeat(' ', num_space);
        repeat('#', num_hash);

        printf("  ");

        repeat('#', num_hash);
        printf("\n");
    }

}

void repeat(char c, int num)
{
    while (num-- > 0)
    {
        printf("%c", c);
    }
}