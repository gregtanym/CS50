#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

// index = 0.0588 * L - 0.296 * S - 15.8
// L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
// how many lengthy the words are. how long the sentences are
// key pointers: find out the number of letters, numbers of words and number of sentences in a given text

// number of words can be determined by number of spaces in a sentence and +1
// number of sentences can be determined by number of .!?
// number of letters can be used by array? (done)
int letters(string str);
int space(string str);
int sentence(string str);

int i;
int a_counter = 0;
int w_counter = 0;
int s_counter = 0;

int main()
{
    string str = get_string("Text:");
    letters(str);
    space(str);
    sentence(str);
    w_counter = w_counter + 1;
    
    //calculating L 
    float L;
    L = ((float)a_counter / (float)w_counter * 100);
    
    //calculating S
    float S;
    S = ((float)s_counter / (float)w_counter * 100);
    
    int grade = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}






int letters(string str)
{
    i = 0;
    while (str[i] != '\0')
    {
        if (isalpha(str[i]) != 0)
        {
            a_counter++;
        }
        i++;
    }
    return 0;
}

int space(string str)
{
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            w_counter++;
        }
        i++;
    }
    return w_counter;
}

int sentence(string str)
{
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '.')
        {
            s_counter++;
        }
        if (str[i] == '?')
        {
            s_counter++;
        }
        if (str[i] == '!')
        {
            s_counter++;
        }
        i++;
    }
    return 0;
}