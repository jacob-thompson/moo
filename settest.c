#include <stdlib.h>
#include <time.h>

#include "set.h"

int main(void)
{
    Set A, B, C;

    if ((A = newset()) == NULL)
    {
        fprintf(stderr, "failed to allocated A\n");
        return 1;
    }
    if (!unpopulated(A))
    {
        fprintf(stderr, "unexpected values in A\n");
        return 1;
    }

    if (addtoset(A, '5') != '5')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '5') != EOF)
    {
        fprintf(stderr, "expected error adding duplicate\n");
        return 1;
    }
    if (lengthofset(A) != 1)
    {
        fprintf(stderr, "unexpected values in A\n");
        return 1;
    }

    if (addtoset(A, '0') != '0')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '8') != '8')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (lengthofset(A) != 3)
    {
        fprintf(stderr, "unexpected length of A\n");
        return 1;
    }

    _printset(A, stdout);

    if (delfromset(A, '0') != '0')
    {
        fprintf(stderr, "failed to delete from A\n");
        return 1;
    }
    if (lengthofset(A) != 2)
    {
        fprintf(stderr, "unexpected length of A\n");
        return 1;
    }
    _printset(A, stdout);

    if (delfromset(A, '5') != '5')
    {
        fprintf(stderr, "failed to delete from A\n");
        return 1;
    }
    if (lengthofset(A) != 1)
    {
        fprintf(stderr, "unexpected length of A\n");
        return 1;
    }
    _printset(A, stdout);

    if (delfromset(A, '8') != '8')
    {
        fprintf(stderr, "failed to delete from A\n");
        return 1;
    }
    if (!unpopulated(A))
    {
        fprintf(stderr, "unexpected values in A\n");
        return 1;
    }

    if (delfromset(A, 'f') != EOF)
    {
        fprintf(stderr, "expected error adding non-digit character\n");
        return 1;
    }
    if (!unpopulated(A))
    {
        fprintf(stderr, "unexpected values in A\n");
        return 1;
    }

    if (addtoset(A, '0') != '0')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '1') != '1')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '2') != '2')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '3') != '3')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '4') != '4')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (lengthofset(A) != 5)
    {
        fprintf(stderr, "unexpected length of A\n");
        return 1;
    }
    _printset(A, stdout);

    if (clearset(A) != 0)
    {
        fprintf(stderr, "failed to clear A\n");
        return 1;
    }
    if (!unpopulated(A))
    {
        fprintf(stderr, "unexpected values in A\n");
        return 1;
    }

    if (addtoset(A, '5') != '5')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '6') != '6')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '7') != '7')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '8') != '8')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (addtoset(A, '9') != '9')
    {
        fprintf(stderr, "failed to add to A\n");
        return 1;
    }
    if (lengthofset(A) != 5)
    {
        fprintf(stderr, "unexpected length of A\n");
        return 1;
    }
    _printset(A, stdout);

    /* passing a position >= the set length causes wraparound */
    if (getnth(A, lengthofset(A)) != '5')
    {
        fprintf(stderr, "failed to get first element in A\n");
        return 1;
    }

    /* first element */
    if (getnth(A, lengthofset(A)) != '6')
    {
        fprintf(stderr, "failed to get first element in A\n");
        return 1;
    }

    /* last element */
    if (getnth(A, lengthofset(A) - 1) != '9')
    {
        fprintf(stderr, "failed to get last element in A\n");
        return 1;
    }

    if (clearset(A) != 0)
    {
        fprintf(stderr, "failed to clear A\n");
        return 1;
    }

    for (char c = '0'; c <= '9'; ++c)
        if (addtoset(A, c) == EOF)
        {
            fprintf(stderr, "failed to add to A\n");
            return 1;
        }
    _printset(A, stdout);

    if (peeknth(A, 0) != '0')
    {
        fprintf(stderr, "failed to peek at first element of A\n");
        return 1;
    }
    if (peeknth(A, 10) != '0')
    {
        fprintf(stderr, "failed to peek at first element of A\n");
        return 1;
    }
    if (peeknth(A, 9) != '9')
    {
        fprintf(stderr, "failed to peek at last element of A\n");
        return 1;
    }

    if (!digitinset(A, '0'))
    {
        fprintf(stderr, "expected to find digit in A\n");
        return 1;
    }
    if (!digitinset(A, '9'))
    {
        fprintf(stderr, "expected to find digit in A\n");
        return 1;
    }
    if (digitinset(A, 'a'))
    {
        fprintf(stderr, "did not expect to find digit in A\n");
        return 1;
    }

    srand(time(NULL));

    if ((B = newset()) == NULL)
    {
        fprintf(stderr, "failed to allocate B\n");
        return 1;
    }

    while (!unpopulated(A))
        if (addtoset(B, getnth(A, rand())) == EOF)
        {
            fprintf(stderr, "failed to add to B\n");
            return 1;
        }
    _printset(B, stdout);

    if ((C = newset()) == NULL)
    {
        fprintf(stderr, "failed to allocate C\n");
        return 1;
    }
    if (addtoset(C, getnth(B, rand())) == EOF)
    {
        fprintf(stderr, "failed to add to C\n");
        return 1;
    }
    if (lengthofset(C) != 1 || lengthofset(B) != 9)
    {
        fprintf(stderr, "unexpected length of C or B\n");
        return 1;
    }
    _printset(C, stdout);

    if (clearset(B) != 0)
    {
        fprintf(stderr, "failed to clear B\n");
        return 1;
    }
    if (delfromset(B, '0') != EOF)
    {
        fprintf(stderr, "expected error deleting from empty set\n");
        return 1;
    }
    if (getnth(B, 0) != EOF)
    {
        fprintf(stderr, "expected error getting element from empty set\n");
        return 1;
    }
    if (peeknth(B, 0) != EOF)
    {
        fprintf(stderr, "expected error peeking into empty set\n");
        return 1;
    }

    freeset(&A);
    if (A != NULL)
    {
        fprintf(stderr, "expected A to be null after free \n");
        return 1;
    }
    freeset(&B);
    if (B != NULL)
    {
        fprintf(stderr, "expected B to be null after free \n");
        return 1;
    }
    freeset(&C);
    if (C != NULL)
    {
        fprintf(stderr, "expected C to be null after free \n");
        return 1;
    }

    return 0;
}
