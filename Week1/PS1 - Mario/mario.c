#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (int i = 1; i <= n; i++)
    {
        // Print spaces on LHS
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");
        }

        // Print bricks on LHS
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // Print two spaces in the middle
        printf("  ");

        // Print bricks on RHS
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        //Change lines
        printf("\n");
    }

}
