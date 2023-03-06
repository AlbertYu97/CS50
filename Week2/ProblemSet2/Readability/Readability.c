#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Prompt a string input
    string text = get_string("Text: ");
    int letter = 0;
    // Number of words equal to number of spaces + 1
    int words = 1;
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letter ++;
        }
        else if (isspace(text[i]))
        {
            words ++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences ++;
        }
    }

    // Calculate Coleman-Liau index
    float result = (float)letter / (float)words * 100 * 0.0588 - (float)sentences / (float)words * 100 * 0.296 - 15.8;
    int grade = round(result);


    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
