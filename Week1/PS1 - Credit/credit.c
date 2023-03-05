#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long number = get_long("Number: ");
    int sum = 0;
    int length = 0;
    int first_two_digits = 0;

    while (number > 1)
    {
        length++;
        number = number / 10;
        int last = number % 10;

        if ((length % 2) == 0)
        {
            last = last * 2;
            if (last > 10)
            {
                sum = last / 10 + last % 10;
            }
            sum += last;
        }
        else
        {
            sum += last;
        }

        if (number >= 10 && number <= 100)
        {
            first_two_digits = number;
        }
    }

    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 || first_two_digits == 54|| first_two_digits == 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && ((first_two_digits / 10) == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}





