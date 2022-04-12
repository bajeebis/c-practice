#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string text = get_string("Text: ");
    float word_c = 1, letter_c = 0, sntnce_c = 0;   // Assign all in float to circumvent truncation

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letter_c += 1;
        }
        if (isspace(text[i]))
        {
            word_c += 1;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') // This part checks for sentences
        {                                                       //  via punctuation marks
            sntnce_c += 1;
        }
    }

    float L = (letter_c / word_c) * 100, S = (sntnce_c / word_c) * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;    // Here is the algorithm called Coleman-Liau Index
    printf("%i, %i, %f, %f\n", letter_c, word_c, sntence_c, index);
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", index);
    }
}