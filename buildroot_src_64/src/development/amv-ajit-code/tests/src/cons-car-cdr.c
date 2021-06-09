/*
 * List of natural numbers using  cons, car and cdr primitives that we
 * implement.
 *
 * List of numbers is given on the command line.
 */
#include <stdio.h>
#include <stdlib.h>

#define   E_OK                     0
#define   E_INSUFFICIENT_INPUT    -1

typedef struct list {
  int member;
  struct list *next;
} LIST;

LIST  *head = NULL;
int  counter = 0;
int  lst_len = 0;

LIST   *cons  (int, LIST  *);
int     car   (LIST  *);
LIST   *cdr   (LIST  *);
int     ll    (LIST  *);                /* List length */
int     llrec (LIST  *);		/* List length */

int
main (int argc, char *argv[])
{
  int ec = E_OK;
  int i  = 1; /* Argument list traverse, skip first element, i.e. i = 0 */
  LIST  *scan = NULL;

  if (argc > 1) {		/* List elements exist on command line */
    while (i < argc) {		/* Build the list */
      int the_num = atoi (argv[i]);
      head = cons (the_num, head);
      i++;
    }

    /* lst_len = ll (head); */
    lst_len = llrec (head);
    printf ("List as %d members.\n", lst_len);

    /* Print the list, and an additional counter for demo sake. */
    scan = head;
    while ((scan != NULL) &&
	   (counter < lst_len)) {
      int the_num = car (scan);

      printf ("Element %02d : %d\n", (counter + 1), the_num);
      scan = cdr (scan);
      counter++;
    }
  } else
    ec = E_INSUFFICIENT_INPUT;

  return ec;
}

LIST   *
cons  (int num, LIST  *lst)
{
  LIST  *scan = NULL;

  scan = calloc (1, sizeof (LIST));
  if (scan != NULL) {
    scan->member = num;
    scan->next   = lst;
  } else
    scan = NULL;

  return scan;
}

int   car   (LIST  *lst)
{
  return ((lst != NULL) ? lst->member : -1);
}

LIST   *cdr   (LIST  *lst)
{
  return ((lst != NULL) ? lst->next : NULL);
}

int
ll    (LIST  *lst)		/* List length */
{
  LIST  *scan = lst;
  int  cnt  = 0;

  while (scan != NULL) {
    cnt++;
    scan = cdr (scan);
  }

  return cnt;
}

int
llrec (LIST *lst)		/* List length */
{
  LIST *scan = lst;

  if (scan == NULL) 
    return 0;
  else
    return (1  + llrec (cdr (scan)));
}

