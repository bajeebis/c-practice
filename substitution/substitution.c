#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

int checker(string alci);

int main(int argc, string argv[])
{
    int array[26];
    string ciph = argv[1];

    /* Checking the cipher if it is valid */
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    /* ------------ALPHABET CIPHER CONVERTER 3000 ------------*/
    for (int i = 0; i < strlen(ciph); i++)
    {                                       // Gets difference between
        if (islower(ciph[i]))
        {             //  alphabet and cipher-bet.
            array[i] = ALPHA[i] - (ciph[i] - 32);
        }
        else
        {
            array[i] = ALPHA[i] - ciph[i];
        }
    }

    // Reason why this is below from the first check is because
    //  of sequence of argc and argv.
    //  * argc must be first
    if (checker(ciph) == 2 || checker(ciph) == 1)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (checker(ciph) == 3)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string inpt = get_string("plaintext: "); // gets string_input here.
    int plnArray[strlen(inpt)];

    printf("ciphertext: "); // Ciphering below
    for (int i = 0; inpt[i] != '\0'; i++)
    {
        for (int ii = 0; ii < strlen(ciph); ii++)
        {
            if (inpt[i] == ALPHA[ii] && isupper(inpt[i]))
            {
                plnArray[i] = ALPHA[ii] - array[ii];
            }
            if (inpt[i] == (ALPHA[ii] + 32) && islower(inpt[i]))
            {
                plnArray[i] = (ALPHA[ii] + 32) - array[ii];
            }
            if (inpt[i] >= '!' && inpt[i] <= '@')
            {
                plnArray[i] = inpt[i];
            }
            if (inpt[i] >= '[' && inpt[i] <= '`')
            {
                plnArray[i] = inpt[i];
            }
            if (inpt[i] >= '{' && inpt[i] <= '~')
            {
                plnArray[i] = inpt[i];
            }
            if (inpt[i] == ' ')
            {
                plnArray[i] = inpt[i];
            }
        }
        printf("%c", plnArray[i]); // Prints ciphered message by character.
    }
    printf("\n");
    return 0;
}

int checker(string alci)
{
    int array_c[26], count = 0;

    // This function serves to initialized 0 to each value in the array
    for (int i = 0; i < 26; i++)
    {
        array_c[i] = 0;
    }

    for (int i = 0; i < strlen(alci); i++)
    {
        for (int z = 0; z < strlen(ALPHA); z++)
        {
            if (alci[i] == ALPHA[z])
            {
                array_c[z] += 1;
                if (array_c[z] > 1)
                {
                    // If there is a double error, it will return 1.
                    return 1;
                }
            }
            if (alci[i] >=  '!' && alci[i] <= '@')
            {
                return 3;
            }
            if (alci[i] >= '[' && alci[i] <= '`')
            {
                return 3;
            }
            if (alci[i] >= '{' && alci[i] <= '~')
            {
                return 3;
            }
        }
        if (isalpha(alci[i]))
        {
            count += 1;
        }
        if (isdigit(alci[i]) || isspace(alci[i]))
        {
            return 3;
        }
    }
    if (count != 26)
    {
        return 2;
    }
    return 0;
}