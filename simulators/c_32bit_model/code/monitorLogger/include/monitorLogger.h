#ifndef monitorLogger_h__
#define monitorLogger_h__


// logger daemon.
void monitorLogger();

// returns 32-bit signature based on input values.
// Register-write signature.
// bits are as follows
//  31  	flag to indicate that psr-has-been-updated.
//  30  	S
//  29  	PS
//  28  	ET 
//  27:24	PIL
//  23:20	CWP (4-bits)
//  19          wim-updated
//  18		tbr-updated
//  17		y-updated
//  16          GPR-updated
//  15		0
//  14		0
//  13		double-word GPR update
//  12:8        write-register-id
//  7:0         register signature  calculated as xor of
//		  all written bytes from GPR, WIM, TBR, Y
//  Note: if no register is updated, the signature will be 0.
uint32_t assembleRegisterWriteSignature( uint8_t psr_updated, uint32_t psr_value,
		uint8_t wim_updated, uint32_t wim_value,
		uint8_t tbr_updated, uint32_t tbr_value,
		uint8_t y_updated, uint32_t y_value,
		uint8_t gpr_write, uint8_t double_word_write,
		uint8_t reg_id, uint32_t reg_val_high, uint32_t reg_val_low);

// splits 32-bit register write signature into specified values.
void splitRegisterWriteSignature(uint32_t reg_write_signature,
		uint8_t* psr_updated,
		uint8_t* S,
		uint8_t* PS,
		uint8_t* ET,
		uint8_t* PIL,
		uint8_t* CWP,
		uint8_t* wim_write,
		uint8_t* tbr_write,
		uint8_t* y_write,
		uint8_t* gpr_write,
		uint8_t* double_word_write,
		uint8_t* reg_id,
		uint8_t* reg_val_signature);

// returns 32-bit signature for store, based on supplied info.
//  Store signature
//  bits are as follows
//  31		store-is-completed
//  30		double-word-store
//  29:24	asi (6 bits used).
//  23:16	byte-mask
//  15:8	address-signature
//		  xor of all bytes in address.
//  7:0		data-signature
//                xor of all bytes written.
//  Note: if no store-is-completed, then the signature will be 0.
uint32_t assembleStoreSignature( uint8_t store_active,
		uint8_t  asi,
		uint8_t  byte_mask,
		uint8_t  double_word_write,
		uint32_t addr,
		uint32_t word_high,
		uint32_t word_low);

// split 32-bit store signature into constituents.
void splitStoreSignature(uint32_t store_signature,
		uint8_t* store_active,
		uint8_t* double_word,
		uint8_t* asi,
		uint8_t* byte_mask,
		uint8_t* addr_signature,
		uint8_t* data_signature);
#endif
