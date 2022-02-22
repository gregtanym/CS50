#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// ci = (pi + k) % 26
// Lowercase letters remain lowercase, and uppercase letters remain uppercase.
// Notice that neither the comma nor the space were “shifted” by the cipher. Only rotate alphabetical characters!
// Your program must accept a single command-line argument, a non-negative integer. Let’s call it k for the sake of discussion.

// first im gonna try to fix and solve the command line argument part

int i = 0;

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    while (argv[1][i] != '\0')
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        i++;
    }

    // now that the command line argument is all set i need to convert the arvg[1] string to int data type, and print out the int value
    // k is the key value

    int k = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    // i need to +1 to all the characters in the stirng individually without affecting the spaces and punctuations
    // and i also need to settle the wraparound from integers over 26
    i = 0;

    // this allows for k to always be within range of 26. eg 46, remainder is 20, so instead of adding 46 to the char, it will add 20 instead
    if (k >= 26)
    {
        k = k % 26;
    }
    while (plaintext[i] != '\0')
    {
        if (isalpha(plaintext[i]) != 0)
        {
            int ctext = plaintext[i] + k;

            // if k equal to 23, the value might exceed 127 and hence give some garbage letter
            // what if the value is below 97 before but then u add in a key and it becomes greater than 97
            if (91 <= ctext && ctext <= 96)
            {
                int a = 90 - plaintext[i];
                printf("%c", 64 + k - a);
            }
            else if (123 <= ctext && ctext <= 127)
            {
                int a = 122 - plaintext[i];
                printf("%c", 96 + k - a);
            }
            else if (65 <= ctext && ctext <= 90)
            {
                printf("%c", ctext);
            }
            else if (97 <= ctext && ctext <= 122)
            {
                printf("%c", ctext);
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
        i++;
    }
    printf("\n");

}
