#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

// 1, 5, 10, 25 cents

int greedy(int cents);

int counter;


int main ()
{

    counter = 0;

    float dollars;
    do
    {
        dollars = get_float("change owed:");
    }
    while (dollars<=0);
    int cents = round(dollars* 100);

    greedy(cents);

    printf("%i\n", counter);
}

// u have to put the counter increment in the looping function so that it can keep looping and increasing by 1
// i intend to not have to return counter as counter is a global variable, but if i cannot put it in a loop then i might have to think of smth else. rmb to change the function data types
// maybe i can habe a counter for each coin and then add all the counters together and return that value

int greedy(int cents)
{
    int *remainder = &cents;

    //i am putting the whole thing in a do while loop that keeps doing it till cents is 0
    // i chose to do a non mutally exclusive if branches but the conidtions are in a way mutually exclusive (WRONG!)
    // what u did here is use only if branches but with diff conditions, what this does is that cents will go down all of the roads if it can, and coz u used pointers it WILL change 
    // the cents value but not the counter. it will go in sequence. the only time the counter increases is if it has already gone through one path and it need to go again hence the looping
    // hence u should use else if to force it down only one path with the conditions till cents becomes 0, while increasing the counter
    // this will allow cents to chose only one path to get a remainder and keep only choosing one path till 0
    // i have to make use of pointers so as to change the value of cents
    do
    {

        counter++;

        if (cents >= 25)
        {
            *remainder = cents - 25;
        }

        else if (cents < 25 && cents >= 10)
        {
            *remainder = cents - 10;
        }

        else if (cents < 10 && cents >= 5)
        {
            *remainder = cents - 5;
        }

        else if (cents < 5 && cents > 0)
        {
            *remainder = cents - 1;
        }
    }
    while (cents > 0);

    return 0;
}
