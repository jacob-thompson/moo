/// a Set represents an ordered linked list consisting of unique values
/// this Set ADT is unoptimized and intended for relatively small sample spaces

#ifndef _SET_H
#define _SET_H

#include <stdio.h>
#include <stdbool.h>

typedef char SetElement;        /* char keeps the sample space small */
typedef struct SetObj * Set;    /* exported Set type */

/* ----- constructor, destructor ----- */

/**
  * allocates and returns a new Set
  * @return pointer to new set if successful, NULL otherwise
  */
Set newset(void);

/**
  * frees all memory associated with a set
  * @param setptr pointer to a Set
  */
void freeset(Set *setptr);

/* ----- access ----- */

/**
  * get the length of the set
  * @param s set
  * @return length of set
  */
size_t lengthofset(Set s);

/**
  * is the set empty?
  * @param s set
  * @return true if empty, false otherwise
  */
bool unpopulated(Set s);

/**
  * get the data stored in the nth element in the set,
  * and remove the node from the set
  * @param s set
  * @param n a position in the set's linked list in [0, inf]
  * @return character that was stored in nth element if successful, EOF otherwise
  */
int getnth(Set s, unsigned n);

/**
  * look at the data stored in the nth element in the set,
  * without removing the node from the set
  * @param s set
  * @param n a position in the set's linked list in [0, inf]
  * @return character that was stored in nth element if successful, EOF otherwise
  */
int peeknth(Set s, unsigned n);

/**
  * checks the set for the given digit
  * @param s set
  * @param digit a digit character
  * @return true if the digit is in the set, false otherwise
  */
bool digitinset(Set s, SetElement digit);

/* ----- manipulation ----- */

/**
  * add a node to the set that holds the given data
  * @param s set
  * @param data character data for the new node to hold
  * @return the data of the new node if successful, EOF otherwise
  */
int addtoset(Set s, SetElement data);

/**
  * delete the node containing the given data value from the set,
  * and frees all memory associated with the node
  * @param s set
  * @param data character data to search for in set
  * @return the deleted data value if successful, EOF otherwise
  */
int delfromset(Set s, SetElement data);

/**
  * delete all existing nodes from the set
  * @param s set
  * @return zero on success, EOF on error
  */
int clearset(Set s);

/* ----- other ----- */

/**
  * print the character data of each node in the set
  * for debugging purposes
  * @param s set
  * @param stream pointer to output stream
  */
void _printset(Set s, FILE *stream);

#endif
