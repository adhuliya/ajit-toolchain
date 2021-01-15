//
//
//Constants used to enumerate various types of 
//requests.
//
//NOTE : These definitions are used in cpu. caches and mmu.


#ifndef __REQUEST_TYPE_VALUES_H__
#define __REQUEST_TYPE_VALUES_H__

// TOP bit is 1 to indicate new-thread to Caches.
// In Icache, the top bit of ASI (asi[7]) is used,
// and for Dcache, the top bit of request_type is used.
#define IS_NEW_THREAD                   0x80

//
// For SWAP/LDSTUB, the first read operation
// will lock the bus so that no other operation
// can intervene between the read and the following write.
#define SET_LOCK_FLAG                   0x40



#define REQUEST_TYPE_IFETCH    			0
#define REQUEST_TYPE_READ      			1
#define REQUEST_TYPE_WRITE     			2
#define REQUEST_TYPE_STBAR     			3
#define REQUEST_TYPE_WRFSRFAR  			4
#define REQUEST_TYPE_CCU_CACHE_READ     	5
#define REQUEST_TYPE_CCU_CACHE_WRITE     	6
#define REQUEST_TYPE_NOP                        7 // used for untrapping!




#endif
