#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool correct_arg_num(int x);
bool correct_key_len(string array[2]);
bool check_non_alphabetic(string array[2]);
bool check_repitition(string array[2]);
string encrypt(string user_input, string array[2]);

int main(int argc, string argv[])
{
    // Check the command line arg exist
    if (correct_arg_num(argc))
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    // Check valid key
    if (correct_key_len(argv))
    {
        printf("Key must contain 26 characters.");
        return 1;
    }

    // Check non-alphabetic element
    if (check_non_alphabetic(argv))
    {
        printf("Key must not contain non alphabetic elements.");
        return 1;
    }

    // Check repetition of alphabetic elements
    if (check_repitition(argv))
        {
            printf("Key must not contain duplicated alphabets");
            return 1;
        }

    // Prompt user for input string
    string user_input = get_string("plaintext: ");

    // Encrypt
    string ciphertext = encrypt(user_input, argv);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}



bool correct_arg_num(int x)
{
    return x != 2;
}

bool correct_key_len(string array[2])
{
    return strlen(array[1]) != 26;
}

bool check_non_alphabetic(string array[2])
{
    for (int i = 0, n = strlen(array[1]); i < n; i++)
    {
        if (!isalpha(array[1][i]))
        {
            return true;
        }
    }
    return false;
}

bool check_repitition(string array[2])
{
    for (int i = 0, n = strlen(array[1]); i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[1][i] == array[1][j])
            {
                return true;
            }
        }
    }
    return false;
}

string encrypt(string user_input, string array[2])
{
    for (int i = 0, n = strlen(user_input); i < n; i++)
    {
        // lowercase
        if (user_input[i] >= 'a' && user_input[i] <= 'z')
        {
            user_input[i] = tolower(array[1][user_input[i] - 97]);
        }

        // uppercase
        else if (user_input[i] >= 'A' && user_input[i] <= 'Z')
        {
            user_input[i] = toupper(array[1][user_input[i] - 65]);
        }
    }
    return user_input;
}
