#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "set.h"

/* linked list node */
typedef struct Node
{
    SetElement data;
    struct Node *next;
} Node;

/* set */
typedef struct SetObj
{
    struct Node *head;
    size_t length;
} SetObj;

/**
  * allocates and returns a pointer to a new Node
  * @param data character data
  * @return pointer to new node if successful, NULL otherwise
  */
Node *newnode(SetElement data)
{
    Node *node;

    node = malloc(sizeof(Node));
    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}

Set newset(void)
{
    Set s;

    s = malloc(sizeof(SetObj));
    if (!s)
        return NULL;

    s->head = NULL;
    s->length = 0;

    return s;
}

void freeset(Set *setptr)
{
    Node *temp;

    if (!setptr || !*setptr)
        return;

    while ((*setptr)->head)
    {
        temp = (*setptr)->head;
        (*setptr)->head = (*setptr)->head->next;
        free(temp);
    }

    free(*setptr);
    *setptr = NULL;
}

size_t lengthofset(Set s)
{
    return s->length;
}

bool unpopulated(Set s)
{
    return lengthofset(s) == 0;
}

int getnth(Set s, unsigned n)
{
    Node *curr;

    if (unpopulated(s))
        return EOF;

    n %= lengthofset(s);

    for (curr = s->head; n-- > 0; curr = curr->next)
        ;

    return delfromset(s, curr->data);
}

int peeknth(Set s, unsigned n)
{
    Node *curr;

    if (unpopulated(s))
        return EOF;

    n %= lengthofset(s);

    for (curr = s->head; n-- > 0; curr = curr->next)
        ;

    return curr->data;
}

bool digitinset(Set s, SetElement digit)
{
    for (Node *curr = s->head; curr; curr = curr->next)
        if (curr->data == digit)
            return true;

    return false;
}

int addtoset(Set s, SetElement data)
{
    Node *curr, *prev;

    if (s->head == NULL)
    {
        if ((s->head = newnode(data)) == NULL)
            return EOF;
        ++s->length;
        return data;
    }

    prev = NULL;
    for (curr = s->head; curr; prev = curr, curr = curr->next)
        if (curr->data == data)
            return EOF;     /* element is already in set */

    if ((prev->next = newnode(data)) == NULL)
        return EOF;
    ++s->length;
    return data;
}

int delfromset(Set s, SetElement data)
{
    Node *curr, *prev;

    if (unpopulated(s))
        return EOF;

    if (s->head->data == data)
    {
        curr = s->head;
        s->head = s->head->next;
        --s->length;
        free(curr);
        return data;
    }

    prev = s->head;
    for (curr = s->head->next; curr; prev = curr, curr = curr->next)
        if (curr->data == data)
            break;

    if (curr != NULL)
    {
        prev->next = curr->next;
        --s->length;
        free(curr);
        return data;
    }

    return EOF;
}

int clearset(Set s)
{
    int data;

    while (!unpopulated(s))
    {
        data = s->head->data;
        if (delfromset(s, data) != data)
            return EOF;
    }

    return 0;
}

void _printset(Set s, FILE *stream)
{
    for (Node *curr = s->head; curr; curr = curr->next)
    {
        fprintf(stream, "[%c]", curr->data);
        if (curr->next)
            fprintf(stream, " -> ");
    }

    putc('\n', stream);
}
