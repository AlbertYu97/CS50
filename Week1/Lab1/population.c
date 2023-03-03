#include<stdio.h>
#include<cs50.h>

int main(void)
{
    // prompt for starting # of lamas
    int start;
    do
    {
        start = get_int("Starting number: ");
    }
    while (start < 9);

    // prompt end # of lamas
    int end;
    do
    {
        end = get_int("Ending number: ");
    }
    while (end < start);

    // calculate number of years to get to the goal
    int years = 0;
    while (start < end)
    {
        start = start + start / 3 - start / 4;
        years ++;
    }
    printf("Years: %i\n", years);

}
