#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "set.h"

#define MAXCODELEN 10
#define DEFAULTCODELEN 4
#define MAXPLAYERS 8
#define DEFAULTPLAYERS 2

char code[MAXCODELEN + 1];          /* stores the current secret code */

/**
  * handles errors when using input to determine playercount
  * @param count integer conversion of player count; (inf, inf)
  * @return player count in range [1, MAXPLAYERS]
  */
unsigned short normalizeplayercount(int count);

/**
  * handles errors when using input to determine codelen
  * @param digits integer conversion of input; (inf, inf)
  * @return length of code in range [1, MAXCODELEN]
  */
size_t normalizecodelen(int digits);

/**
  * run a game of Bulls and Cows
  * https://en.wikipedia.org/wiki/Bulls_and_cows
  * @param players player count
  * @param codelen normalized code length in [1, MAXCODELEN]
  * @return negative if error, or nonzero otherwise
  */
int bullscows(unsigned short players, size_t codelen);

int main(int argc, char **argv)
{
    unsigned short players;

    srand(time(NULL));

    players = DEFAULTPLAYERS;
    if (argc > 1)
    {
        while (*++argv)
        {
            if (**argv == '+')
                players = normalizeplayercount(atoi((*argv) + 1));
            else if (bullscows(players, normalizecodelen(atoi(*argv))) < 0)
                return 1;
        }
    }
    else if (bullscows(players, DEFAULTCODELEN) < 0)
        return 1;

    return 0;
}

unsigned short normalizeplayercount(int count)
{
    if (count <= 0)
        return 1;
    else if (count > MAXCODELEN)
        return DEFAULTPLAYERS;

    return count;
}

size_t normalizecodelen(int digits)
{
    if (digits <= 0)
        return DEFAULTCODELEN;
    else if (digits > MAXCODELEN)
        return MAXCODELEN;

    return digits;
}

int gencode(size_t codelen)
{
    Set space;
    char *ptr;
    char picked;

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
    while (codelen-- > 0)
    {
        picked = getnth(space, rand());
        *ptr++ = picked;
    }
    *ptr = '\0';

    freeset(&space);
    return 0;
}

int bullscows(unsigned short players, size_t codelen)
{
    Set guessed;
    int ch;
    unsigned short currentplayer, winningplayer;
    unsigned int numguesses, minguesses;
    unsigned int bulls, cows;
    const char line[] = "============";

    printf("%s ", line);
    printf("BULLS AND COWS ");
    printf("(CODE LENGTH: %lu) ", codelen);
    printf("%s\n", line);

    if ((guessed = newset()) == NULL)
    {
        fprintf(stderr, "bullscows: failed to allocate memory for guessed digits\n");
        return -1;
    }

    minguesses = UINT_MAX;
    for (currentplayer = 1; currentplayer <= players; ++currentplayer)
    {
        if (gencode(codelen) != 0)
        {
            freeset(&guessed);
            return -1;
        }

        printf("PLAYER %hu:\n", currentplayer);

        numguesses = 0;
        for (bulls = cows = 0; bulls < codelen; ++numguesses)
        {
            bulls = cows = 0;

            printf(" > ");

            /* get a set of unique digits, representing the guess */
            clearset(guessed);
            while (lengthofset(guessed) < codelen)
            {
                while ((ch = getchar()) != EOF && (isspace(ch) || !isdigit(ch)))
                    ;
                if (ch == EOF)
                {
                    freeset(&guessed);
                    return -1;
                }
                addtoset(guessed, ch);
            }

            /* compare the set of unique digits against the code */
            for (size_t i = 0; i < codelen; ++i)
                if (code[i] == peeknth(guessed, i))
                    ++bulls;
                else if (digitinset(guessed, code[i]))
                    ++cows;

            /* inform the user of the result */
            printf(" >> ");
            printf("%u bull", bulls);
            if (bulls != 1)
                putchar('s');
            printf(" and %u cow", cows);
            if (cows != 1)
                putchar('s');
            putchar('\n');
        }

        if (numguesses < minguesses)
        {
            minguesses = numguesses;
            winningplayer = currentplayer;
        }
    }

    if (players > 1)
        printf("PLAYER %hu WON IN %u GUESS", winningplayer, minguesses);
    else
        printf("CODE FOUND IN %u GUESS", minguesses);
    if (minguesses != 1)
    {
        putchar('E');
        putchar('S');
    }
    putchar('\n');

    freeset(&guessed);
    return winningplayer;
}
