#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
// string!

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string key = argv[1];

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    /* Better way */
    /* Begin */
    // for (int i = 0; i < 26; i++)
    // {
    //     for (int j = i + 1; j < 26; j++)
    //     {
    //         if (tolower(key[i]) == tolower(key[j]))
    //         {
    //             printf("Key must contain 26 characters.\n");
    //             return 1;
    //         }
    //     }
    // }
    int a[26] = {0};
    for (int i = 0; i < 26; i++) {
        a[tolower(key[i]) - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (a[i] != 1) {
            printf("error");
            return 1;
        }
    }
    /* End */

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        /* Better Way */
        /* Begin
        if (islower(plaintext[i]))
        {
            // Correspond cipher letter is lower too.
            int index = (int)(plaintext[i] - 'a');
            printf("%c", tolower(key[index]));
        }
        else if (isupper(plaintext[i]))
        {
            printf("%c", toupper(key[(int)(plaintext[i] - 'A')]));
        }
        else
        {
            // Blank space or comma
            printf("%c", plaintext[i]);
        } */
        if (isalpha(plaintext[i])) {
            printf("%c", islower(plaintext[i]) ? tolower(key[plaintext[i] - 'a']) : toupper(key[plaintext[i] - 'A']));
        } else {
            printf("%c", plaintext[i]);
        }



        // !!!!!!!!!!! 可以用三目运算符改写
    }
    printf("\n");

    return 0;
}