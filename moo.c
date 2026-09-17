#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "set.h"

#define MAXCODELEN 10
#define DEFAULTCODELEN 4

char code[MAXCODELEN + 1];          /* stores the current secret code */
size_t codelen = DEFAULTCODELEN;    /* stores the amount of digits in the code */

/**
  * handles errors when using input to determine codelen
  * @param digits integer conversion of input; (inf, inf)
  * @return length of code in range [1, MAXCODELEN]
  */
size_t normalizecodelen(int digits);

/**
  * run a game of Bulls and Cows
  * https://en.wikipedia.org/wiki/Bulls_and_cows
  * @return negative if error, zero if user wins, positive if user loses
  */
int bullscows(void);

int main(int argc, char **argv)
{
    srand(time(NULL));

    if (argc > 1)
    {
        while (*++argv)
        {
            codelen = normalizecodelen(atoi(*argv));
            if (bullscows() != 0)
                return 1;
        }
    }
    else if (bullscows() != 0)
        return 1;

    return 0;
}

size_t normalizecodelen(int digits)
{
    if (digits <= 0)
        return DEFAULTCODELEN;
    else if (digits > MAXCODELEN)
        return MAXCODELEN;

    return digits;
}

int gencode(void)
{
    Set space;
    char *ptr;
    char picked;
    size_t digits;

    if ((space = newset()) == NULL)
    {
        fprintf(stderr, "gencode: failed to allocated memory for sample space\n");
        return -1;
    }

    for (char d = '0'; d <= '9'; ++d)
        if ((addtoset(space, d)) != d)
        {
            fprintf(stderr, "gencode: failed to populate sample space\n");
            freeset(&space);
            return -1;
        }

    ptr = code;
    digits = codelen;
    while (digits-- > 0)
    {
        picked = getnth(space, rand());
        *ptr++ = picked;
    }
    *ptr = '\0';

    freeset(&space);
    return 0;
}

int bullscows(void)
{
    Set guessed;
    int ch;
    unsigned int bulls, cows;

    if (gencode() != 0)
        return -1;

    if ((guessed = newset()) == NULL)
    {
        fprintf(stderr, "bullscows: failed to allocate memory for guessed digits\n");
        return -1;
    }

    for (bulls = cows = 0; bulls < codelen; )
    {
        bulls = cows = 0;

        /* get a set of unique digits, representing the guess */
        clearset(guessed);
        while (lengthofset(guessed) < codelen)
        {
            while ((ch = getchar()) != EOF && (isspace(ch) || !isdigit(ch)))
                ;
            if (ch == EOF)
                return -1;
            addtoset(guessed, ch);
        }

        /* compare the set of unique digits against the code */
        for (size_t i = 0; i < codelen; ++i)
            if (code[i] == peeknth(guessed, i))
                ++bulls;
            else if (digitinset(guessed, code[i]))
                ++cows;

        /* inform the user of the result */
        printf("%u bull", bulls);
        if (bulls != 1)
            putchar('s');
        printf(" and %u cow", cows);
        if (cows != 1)
            putchar('s');
        putchar('\n');
    }

    freeset(&guessed);
    return 0;
}
