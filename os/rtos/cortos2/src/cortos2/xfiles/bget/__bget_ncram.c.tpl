/*
Author: Anshuman Dhuliya (AD).
This file is a selected copy of bget.c source file.
It contains three functions bpool, bget, brel only.

Note: The complete bget.c was not compiling with uclibc.
Probable cause: assert statements.
*/

#define NULL 0   /*AD : added since #include<memory.h> removed */

//    BGET CONFIGURATION
//    ==================

//AD #define TestProg    /*20000	      Generate built-in test program
//AD 					 if defined.  The value specifies
//AD 					 how many buffer allocation attempts
//AD 					 the test program should make. */

#define SizeQuant   16		      /* Buffer allocation size quantum:
					 all buffers allocated are a
					 multiple of this size.  This
					 MUST be a power of two. */

//AD #define BufDump     0		      /* Define this symbol to enable the
//AD 					 bpoold() function which dumps the
//AD 					 buffers in a buffer pool. */
//AD
//AD #define BufValid    0		      /* Define this symbol to enable the
//AD 					 bpoolv() function for validating
//AD 					 a buffer pool. */
//AD
//AD #define DumpData    0		      /* Define this symbol to enable the
//AD 					 bufdump() function which allows
//AD 					 dumping the contents of an allocated
//AD 					 or free buffer. */

//AD #define BufStats    0		      /* Define this symbol to enable the
//AD 					 bstats() function which calculates
//AD 					 the total free space in the buffer
//AD 					 pool, the largest available
//AD					 buffer, and the total space
//AD					 currently allocated. */

//AD #define FreeWipe    0		      /* Wipe free buffers to a guaranteed
//AD 					 pattern of garbage to trip up
//AD 					 miscreants who attempt to use
//AD 					 pointers into released buffers. */

//AD #define BestFit     0		      /* Use a best fit algorithm when
//AD 					 searching for space for an
//AD 					 allocation request.  This uses
//AD 					 memory more efficiently, but
//AD					 allocation will be much slower. */

//AD #define BECtl	    1		      /* Define this symbol to enable the
//AD					 bectl() function for automatic
//AD					 pool space control.  */

//AD #include <stdio.h>

//AD #ifdef lint
//AD #define NDEBUG			      /* Exits in asserts confuse lint */
//AD /* LINTLIBRARY */                     /* Don't complain about def, no ref */
//AD extern char *sprintf();               /* Sun includes don't define sprintf */
//AD #endif

//AD #include <assert.h>
//AD #include <memory.h>

#ifdef BufDump			      /* BufDump implies DumpData */
#ifndef DumpData
#define DumpData    1
#endif
#endif

#ifdef DumpData
#include <ctype.h>
#endif

/*  Declare the interface, including the requested buffer size type,
    bufsize.  */

#include "__bget_ncram.h"

#define MemSize     int 	      /* Type for size arguments to memxxx()
					 functions such as memcmp(). */

/* Queue links */

struct qlinks {
    struct bfhead *flink;	      /* Forward link */
    struct bfhead *blink;	      /* Backward link */
};

/* Header in allocated and free buffers */

struct bhead {
    bufsize prevfree;		      /* Relative link back to previous
					 free buffer in memory or 0 if
					 previous buffer is allocated.	*/
    bufsize bsize;		      /* Buffer size: positive if free,
					 negative if allocated. */
};
#define BH(p)	((struct bhead *) (p))

/*  Header in directly allocated buffers (by acqfcn_ncram) */

struct bdhead {
    bufsize tsize;		      /* Total size, including overhead */
    struct bhead bh;		      /* Common header */
};
#define BDH(p)	((struct bdhead *) (p))

/* Header in free buffers */

struct bfhead {
    struct bhead bh;		      /* Common allocated/free header */
    struct qlinks ql;		      /* Links on free list */
};
#define BFH(p)	((struct bfhead *) (p))

static struct bfhead freelist_ncram = {     /* List of free buffers */
    {0, 0},
    {&freelist_ncram, &freelist_ncram}
};


#ifdef BufStats
static bufsize totalloc_ncram = 0;	      /* Total space currently allocated */
static long numget_ncram = 0, numrel_ncram = 0;   /* Number of bget() and brel() calls */
#ifdef BECtl
static long numpblk_ncram = 0;	      /* Number of pool blocks */
static long numpget_ncram = 0, numprel_ncram = 0; /* Number of block gets and rels */
static long numdget_ncram = 0, numdrel_ncram = 0; /* Number of direct gets and rels */
#endif /* BECtl */
#endif /* BufStats */

#ifdef BECtl

/* Automatic expansion block management functions */

static int (*compfcn_ncram) _((bufsize sizereq, int sequence)) = NULL;
static void *(*acqfcn_ncram) _((bufsize size)) = NULL;
static void (*relfcn_ncram) _((void *buf)) = NULL;

static bufsize exp_incr_ncram = 0;	      /* Expansion block size */
static bufsize pool_len_ncram = 0;	      /* 0: no bpool calls have been made
					 -1: not all pool blocks are
					     the same size
					 >0: (common) block size for all
					     bpool calls made so far
				      */
#endif

/*  Minimum allocation quantum: */

#define QLSize	(sizeof(struct qlinks))
#define SizeQ	((SizeQuant > QLSize) ? SizeQuant : QLSize)

#define V   (void)		      /* To denote unwanted returned values */

/* End sentinel: value placed in bsize field of dummy block delimiting
   end of pool block.  The most negative number which will  fit  in  a
   bufsize, defined in a way that the compiler will accept. */

#define ESent	((bufsize) (-(((1L << (sizeof(bufsize) * 8 - 2)) - 1) * 2) - 2))

/*  BGET  --  Allocate a buffer.  */

void *bget_ncram(requested_size)
  bufsize requested_size;
{
    bufsize size = requested_size + (requested_size % SizeQuant);
    struct bfhead *b;
#ifdef BestFit
    struct bfhead *best;
#endif
    void *buf;
#ifdef BECtl
    int compactseq_ncram = 0;
#endif

    //AD assert(size > 0);

    if (size < SizeQ) { 	      /* Need at least room for the */
	size = SizeQ;		      /*    queue links.  */
    }
#ifdef SizeQuant
#if SizeQuant > 1
    size = (size + (SizeQuant - 1)) & (~(SizeQuant - 1));
#endif
#endif

    size += sizeof(struct bhead);     /* Add overhead in allocated buffer
					 to size required. */

#ifdef BECtl
    /* If a compact function was provided in the call to bectl(), wrap
       a loop around the allocation process  to  allow	compaction  to
       intervene in case we don't find a suitable buffer in the chain. */

    while (1) {
#endif
	b = freelist_ncram.ql.flink;
#ifdef BestFit
	best = &freelist_ncram;
#endif


	/* Scan the free list searching for the first buffer big enough
	   to hold the requested size buffer. */

#ifdef BestFit
	while (b != &freelist_ncram) {
	    if (b->bh.bsize >= size) {
		if ((best == &freelist_ncram) || (b->bh.bsize < best->bh.bsize)) {
		    best = b;
		}
	    }
	    b = b->ql.flink;		  /* Link to next buffer */
	}
	b = best;
#endif /* BestFit */

	while (b != &freelist_ncram) {
	    if ((bufsize) b->bh.bsize >= size) {

		/* Buffer  is big enough to satisfy  the request.  Allocate it
		   to the caller.  We must decide whether the buffer is  large
		   enough  to  split  into  the part given to the caller and a
		   free buffer that remains on the free list, or  whether  the
		   entire  buffer  should  be  removed	from the free list and
		   given to the caller in its entirety.   We  only  split  the
		   buffer if enough room remains for a header plus the minimum
		   quantum of allocation. */

		if ((b->bh.bsize - size) > (SizeQ + (sizeof(struct bhead)))) {
		    struct bhead *ba, *bn;

		    ba = BH(((char *) b) + (b->bh.bsize - size));
		    bn = BH(((char *) ba) + size);
		    //AD assert(bn->prevfree == b->bh.bsize);
		    /* Subtract size from length of free block. */
		    b->bh.bsize -= size;
		    /* Link allocated buffer to the previous free buffer. */
		    ba->prevfree = b->bh.bsize;
		    /* Plug negative size into user buffer. */
		    ba->bsize = -(bufsize) size;
		    /* Mark buffer after this one not preceded by free block. */
		    bn->prevfree = 0;

#ifdef BufStats
		    totalloc_ncram += size;
		    numget_ncram++;		  /* Increment number of bget() calls */
#endif
		    buf = (void *) ((((char *) ba) + sizeof(struct bhead)));
		    return buf;
		} else {
		    struct bhead *ba;

		    ba = BH(((char *) b) + b->bh.bsize);
		    //AD assert(ba->prevfree == b->bh.bsize);

                    /* The buffer isn't big enough to split.  Give  the  whole
		       shebang to the caller and remove it from the free list. */

		    //AD assert(b->ql.blink->ql.flink == b);
		    //AD assert(b->ql.flink->ql.blink == b);
		    b->ql.blink->ql.flink = b->ql.flink;
		    b->ql.flink->ql.blink = b->ql.blink;

#ifdef BufStats
		    totalloc_ncram += b->bh.bsize;
		    numget_ncram++;		  /* Increment number of bget() calls */
#endif
		    /* Negate size to mark buffer allocated. */
		    b->bh.bsize = -(b->bh.bsize);

		    /* Zero the back pointer in the next buffer in memory
		       to indicate that this buffer is allocated. */
		    ba->prevfree = 0;

		    /* Give user buffer starting at queue links. */
		    buf =  (void *) &(b->ql);
		    return buf;
		}
	    }
	    b = b->ql.flink;		  /* Link to next buffer */
	}
#ifdef BECtl

        /* We failed to find a buffer.  If there's a compact  function
	   defined,  notify  it  of the size requested.  If it returns
	   TRUE, try the allocation again. */

	if ((compfcn_ncram == NULL) || (!(*compfcn_ncram)(size, ++compactseq_ncram))) {
	    break;
	}
    }

    /* No buffer available with requested size free. */

    /* Don't give up yet -- look in the reserve supply. */

    if (acqfcn_ncram != NULL) {
	if (size > exp_incr - sizeof(struct bhead)) {

	    /* Request	is  too  large	to  fit in a single expansion
	       block.  Try to satisy it by a direct buffer acquisition. */

	    struct bdhead *bdh;

	    size += sizeof(struct bdhead) - sizeof(struct bhead);
	    if ((bdh = BDH((*acqfcn_ncram)((bufsize) size))) != NULL) {

		/*  Mark the buffer special by setting the size field
		    of its header to zero.  */
		bdh->bh.bsize = 0;
		bdh->bh.prevfree = 0;
		bdh->tsize = size;
#ifdef BufStats
		totalloc_ncram += size;
		numget_ncram++;	      /* Increment number of bget() calls */
		numdget_ncram++;	      /* Direct bget() call count */
#endif
		buf =  (void *) (bdh + 1);
		return buf;
	    }

	} else {

	    /*	Try to obtain a new expansion block */

	    void *newpool;

	    if ((newpool = (*acqfcn_ncram)((bufsize) exp_incr)) != NULL) {
		bpool(newpool, exp_incr);
                buf =  bget(requested_size);  /* This can't, I say, can't
						 get into a loop. */
		return buf;
	    }
	}
    }

    /*	Still no buffer available */

#endif /* BECtl */

    return NULL;
}


/*  BPOOL  --  Add a region of memory to the buffer pool.  */

void bpool_ncram(buf, len)
  void *buf;
  bufsize len;
{
    struct bfhead *b = BFH(buf);
    struct bhead *bn;

#ifdef SizeQuant
    len &= ~(SizeQuant - 1);
#endif
#ifdef BECtl
    if (pool_len_ncram == 0) {
	pool_len_ncram = len;
    } else if (len != pool_len_ncram) {
	pool_len_ncram = -1;
    }
#ifdef BufStats
    numpget_ncram++;			      /* Number of block acquisitions */
    numpblk_ncram++;			      /* Number of blocks total */
    //AD assert(numpblk == numpget - numprel);
#endif /* BufStats */
#endif /* BECtl */

    /* Since the block is initially occupied by a single free  buffer,
       it  had	better	not  be  (much) larger than the largest buffer
       whose size we can store in bhead.bsize. */

    //AD assert(len - sizeof(struct bhead) <= -((bufsize) ESent + 1));

    /* Clear  the  backpointer at  the start of the block to indicate that
       there  is  no  free  block  prior  to  this   one.    That   blocks
       recombination when the first block in memory is released. */

    b->bh.prevfree = 0;

    /* Chain the new block to the free list. */

    //AD assert(freelist.ql.blink->ql.flink == &freelist);
    //AD assert(freelist.ql.flink->ql.blink == &freelist);
    b->ql.flink = &freelist_ncram;
    b->ql.blink = freelist_ncram.ql.blink;
    freelist_ncram.ql.blink = b;
    b->ql.blink->ql.flink = b;

    /* Create a dummy allocated buffer at the end of the pool.	This dummy
       buffer is seen when a buffer at the end of the pool is released and
       blocks  recombination  of  the last buffer with the dummy buffer at
       the end.  The length in the dummy buffer  is  set  to  the  largest
       negative  number  to  denote  the  end  of  the pool for diagnostic
       routines (this specific value is  not  counted  on  by  the  actual
       allocation and release functions). */

    len -= sizeof(struct bhead);
    b->bh.bsize = (bufsize) len;
#ifdef FreeWipe
    V memset(((char *) b) + sizeof(struct bfhead), 0x55,
	     (MemSize) (len - sizeof(struct bfhead)));
#endif
    bn = BH(((char *) b) + len);
    bn->prevfree = (bufsize) len;
    /* Definition of ESent assumes two's complement! */
    //AD assert((~0) == -1);
    bn->bsize = ESent;
}


/*  BREL  --  Release a buffer.  */

void brel_ncram(buf)
  void *buf;
{
    struct bfhead *b, *bn;

    b = BFH(((char *) buf) - sizeof(struct bhead));
#ifdef BufStats
    numrel++;			      /* Increment number of brel() calls */
#endif
    //AD assert(buf != NULL);

#ifdef BECtl
    if (b->bh.bsize == 0) {	      /* Directly-acquired buffer? */
	struct bdhead *bdh;

	bdh = BDH(((char *) buf) - sizeof(struct bdhead));
	//AD assert(b->bh.prevfree == 0);
#ifdef BufStats
	totalloc_ncram -= bdh->tsize;
	//AD assert(totalloc >= 0);
	numdrel_ncram++;		      /* Number of direct releases */
#endif /* BufStats */
#ifdef FreeWipe
	V memset((char *) buf, 0x55,
		 (MemSize) (bdh->tsize - sizeof(struct bdhead)));
#endif /* FreeWipe */
	//AD assert(relfcn != NULL);
	(*relfcn_ncram)((void *) bdh);      /* Release it directly. */
	return;
    }
#endif /* BECtl */

    /* Buffer size must be negative, indicating that the buffer is
       allocated. */

    if (b->bh.bsize >= 0) {
	bn = NULL;
    }
    //AD assert(b->bh.bsize < 0);

    /*	Back pointer in next buffer must be zero, indicating the
	same thing: */

    //AD assert(BH((char *) b - b->bh.bsize)->prevfree == 0);

#ifdef BufStats
    totalloc_ncram += b->bh.bsize;
    //AD assert(totalloc >= 0);
#endif

    /* If the back link is nonzero, the previous buffer is free.  */

    if (b->bh.prevfree != 0) {

	/* The previous buffer is free.  Consolidate this buffer  with	it
	   by  adding  the  length  of	this  buffer  to the previous free
	   buffer.  Note that we subtract the size  in	the  buffer  being
           released,  since  it's  negative to indicate that the buffer is
	   allocated. */

	register bufsize size = b->bh.bsize;

        /* Make the previous buffer the one we're working on. */
	//AD assert(BH((char *) b - b->bh.prevfree)->bsize == b->bh.prevfree);
	b = BFH(((char *) b) - b->bh.prevfree);
	b->bh.bsize -= size;
    } else {

        /* The previous buffer isn't allocated.  Insert this buffer
	   on the free list as an isolated free block. */

	//AD assert(freelist.ql.blink->ql.flink == &freelist);
	//AD assert(freelist.ql.flink->ql.blink == &freelist);
	b->ql.flink = &freelist_ncram;
	b->ql.blink = freelist_ncram.ql.blink;
	freelist_ncram.ql.blink = b;
	b->ql.blink->ql.flink = b;
	b->bh.bsize = -b->bh.bsize;
    }

    /* Now we look at the next buffer in memory, located by advancing from
       the  start  of  this  buffer  by its size, to see if that buffer is
       free.  If it is, we combine  this  buffer  with	the  next  one	in
       memory, dechaining the second buffer from the free list. */

    bn =  BFH(((char *) b) + b->bh.bsize);
    if (bn->bh.bsize > 0) {

	/* The buffer is free.	Remove it from the free list and add
	   its size to that of our buffer. */

	//AD assert(BH((char *) bn + bn->bh.bsize)->prevfree == bn->bh.bsize);
	//AD assert(bn->ql.blink->ql.flink == bn);
	//AD assert(bn->ql.flink->ql.blink == bn);
	bn->ql.blink->ql.flink = bn->ql.flink;
	bn->ql.flink->ql.blink = bn->ql.blink;
	b->bh.bsize += bn->bh.bsize;

	/* Finally,  advance  to   the	buffer	that   follows	the  newly
	   consolidated free block.  We must set its  backpointer  to  the
	   head  of  the  consolidated free block.  We know the next block
	   must be an allocated block because the process of recombination
	   guarantees  that  two  free	blocks will never be contiguous in
	   memory.  */

	bn = BFH(((char *) b) + b->bh.bsize);
    }
#ifdef FreeWipe
    V memset(((char *) b) + sizeof(struct bfhead), 0x55,
	    (MemSize) (b->bh.bsize - sizeof(struct bfhead)));
#endif
    //AD assert(bn->bh.bsize < 0);

    /* The next buffer is allocated.  Set the backpointer in it  to  point
       to this buffer; the previous free buffer in memory. */

    bn->bh.prevfree = b->bh.bsize;

#ifdef BECtl

    /*	If  a  block-release function is defined, and this free buffer
	constitutes the entire block, release it.  Note that  pool_len_ncram
	is  defined  in  such a way that the test will fail unless all
	pool blocks are the same size.	*/

    if (relfcn_ncram != NULL &&
	((bufsize) b->bh.bsize) == (pool_len_ncram - sizeof(struct bhead))) {

	//AD assert(b->bh.prevfree == 0);
	//AD assert(BH((char *) b + b->bh.bsize)->bsize == ESent);
	//AD assert(BH((char *) b + b->bh.bsize)->prevfree == b->bh.bsize);
	/*  Unlink the buffer from the free list  */
	b->ql.blink->ql.flink = b->ql.flink;
	b->ql.flink->ql.blink = b->ql.blink;

	(*relfcn_ncram)(b);
#ifdef BufStats
	numprel++;		      /* Nr of expansion block releases */
	numpblk--;		      /* Total number of blocks */
	//AD assert(numpblk == numpget - numprel);
#endif /* BufStats */
    }
#endif /* BECtl */
}

