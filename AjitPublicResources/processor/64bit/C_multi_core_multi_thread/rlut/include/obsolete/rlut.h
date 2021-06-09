#ifndef  __rlut_h___
#define  __rlut_h___

// base page size is 4kB
#define BASE_PAGE_SIZE 		4096  // bytes
#define LOG_BASE_PAGE_SIZE 	  12  // bytes

#define PA_VA_OVERLAP_IDX_MASK    0x3f // bottom 6 bits of index for 512 line cache.

// these two should be consistent
// with each other.
#define LOG_CACHE_LINE_SIZE    6    // bytes.
#define CACHE_LINE_SIZE       64    // bytes.

// these three should be consistent
// with each other.
#define CACHE_SIZE       512	// lines
#define LOG_CACHE_SIZE   9	// lines
#define CACHE_LINE_INDEX_MASK 0x1ff

//
// The RLUT needs to maintain the reverse translation
// state of exactly 512 virtual addresses.
//
// The va->pa mapping is many-to-one.  Thus, given
// a pa, the problem is to find the distinct va's
// which can be mapped to it.  
//
// We do this as follows:  first, we maintain a table
// of virtual address tags (this table will have 512
// entries, and each va tag will be 17 bits long).
//
// Now we maintain a table of physical address tags (this
// table will have 512 entries,with each tag having
// 21 bits in it).  For each pa tag, we also maintain
// a list of va indices corresponding to this pa.
// 
// The PA line index is obtained as PA[14:6] and the VA
// line index is VA[14:6].  Since bits [11:0] of the VA
// and PA must coincide, this implies that for a PA index,
// the corresponding VA index has at most 8 possibilities
// determined by VA[14:12].  For each PA in the table, 
// we use a single byte to remember the VA's in the table
// which correspond to this PA (all this for 512 entry CACHE).
//
// (The converse is also true:  for each VA, there are at
//  most 8 possible PA's corresponding to it in the cache).
//
// Then, everytime a new translation occurs in the
// mmu, 
//    the va and pa tag arrays are updated.
//    the pa->va list is updated.
//
// On a flush, both tags arrays are cleared.
//
// To do a lookup (for invalidation), we are given
// a pa.   Use the _pa_va_bitmap to identify the
// indices of the matching va's for the pa, 
// and invalidate the corresponding lines in the cache.
//
//

typedef struct __Rlut {
	// new scheme..  top 17 bits of VA form the tag,
	//   which is stored in the lower bits of the  word.
	uint32_t  __va_tags		[ CACHE_SIZE ];


	// new scheme..  top 21 bits of the pa form the tag
	//   which is stored in the bottom 21 bits of the word.
	//   top bit keeps valid flag.
	uint32_t  __pa_tags		[ CACHE_SIZE ];

	// list of va's in caches that are
	// mapped to this pa.  Note that,
	// for caches with 512 entries, this
	// list can contain at most 8 entries,
	//
	// single byte is enough to keep track of all
	// va's that can be mapped to a pa.. But we
	// we will use 2x16 = 32 bits.  Top half-word
	// is va->pa and bottom half-word is pa->va
	// 
	// The top-half is currently unused because the
	// caches are always flushed on a context switch.
	//
	uint32_t   __pa_va_bit_map [ CACHE_SIZE ];

	pthread_mutex_t rlut_mutex;
} Rlut;

void initRlut(Rlut* r);
uint16_t getLink (Rlut* r);
void releaseLink (Rlut* r, uint16_t r_link);
void initFreeList(Rlut* r);
void initBitMaps (Rlut* r);
void clear_free_list(Rlut* r, uint16_t head_index);
void insertEntryIntoRlut (Rlut* r, uint32_t pa_line_addr, uint32_t va_line_addr);
int lookupEntryAndInvalidateFromRlut (Rlut* rs, uint32_t pa_line_addr, char* pipe_name);
void flushRlut (Rlut* r);


typedef struct __RlutState {
	int 	  cpu_id;

	Rlut      icache_rlut;
	Rlut      dcache_rlut;

	char rlut_to_icache_pipe_name[256];
	char rlut_to_dcache_pipe_name[256];

	char biu_to_rlut_pipe_name[256];
	

	uint64_t number_of_requests_from_biu;
	uint64_t number_of_requests_forwarded_to_icache;
	uint64_t number_of_requests_forwarded_to_dcache;


} RlutState;
RlutState* makeRlutState (int cpu_id);

uint32_t update_va_tag (uint32_t va_tag, uint8_t asi);
void  parseMmuCommand(uint64_t mmu_cmd, 
		uint8_t *valid,
		uint8_t *insert, 
		uint8_t *flush, 
		uint8_t *asi,
		uint32_t *pa_line_addr, 
		uint32_t *va_line_addr);
uint64_t constructMmuCommand (uint8_t insert, uint8_t flush, uint8_t asi, uint32_t pa_line_addr,
		uint32_t va_line_addr);


void insertEntry(RlutState* rs, uint32_t pa_line_addr, uint32_t va_line_addr, uint8_t asi);

void lookupEntryAndInvalidate (RlutState* rs, uint32_t pa_line_addr);
void RlutDaemon(void* vrs);

void registerRlutPipes (RlutState* rs);
void startRlutDaemon(RlutState* rs);

void printStatistics(RlutState* rs);

uint16_t list_length (RlutState* rs, uint16_t head_index);

#endif
