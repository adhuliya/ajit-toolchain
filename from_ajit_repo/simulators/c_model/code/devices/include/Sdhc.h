#ifndef _Sdhc_h_____
#define _Sdhc_h_____

typedef struct SdcardState {
	// registers
	
	// storage array.

} SdcardState;
void initSdcardState();

// return 0 if read ok, else 1.
int readBlock(SdcardState* s, int block_size_in_bytes, int block_start_byte_index, uint8_t* barray);
int writeBlock(SdcardState* s, int block_size_in_bytes, int block_start_byte_index, uint8_t* barray);
// etc...




// data structures
typedef struct SdhcState__ {

	// registers


	SdcardState sd_card_state;
} SdhcState;
//
// a loop
// while(1) {
//    get command from processor bus
//    execute command 
//    return response
//}
//
void SdhcDaemon();



#endif
