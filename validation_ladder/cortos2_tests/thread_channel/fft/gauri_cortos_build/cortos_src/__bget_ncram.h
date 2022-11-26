/*

    Interface definitions for bget.c, the memory management package.

*/

#ifndef _
#ifdef PROTOTYPES
#define  _(x)  x		      /* If compiler knows prototypes */
#else
#define  _(x)  ()                     /* It it doesn't */
#endif /* PROTOTYPES */
#endif

typedef long bufsize;
void	bpool_ncram	    _((void *buffer, bufsize len));
void   *bget_ncram	    _((bufsize size));
void	brel_ncram	    _((void *buf));
