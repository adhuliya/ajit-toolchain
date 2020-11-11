/*Header File for SD card commands*/

#ifndef _SD_H
#define _SD_H

#include<stdint.h>
#include"Sdhc.h"
/* sd card */

/*  OCR Register bit masks    */
uint32_t ocr;
#define card_pwrup_stat 0x80000000
#define card_cap_stat   0x40000000
#define switch_1_8_V    0x01000000
#define v3_5to6         0x00800000
#define v3_4to5         0x00400000
#define v3_3to4         0x00200000          
#define v3_2to3         0x00100000
#define v3_1to2         0x00080000
#define v3_0to1         0x00040000
#define v2_9to3         0x00020000
#define v2_8to9         0x00010000
#define v2_7to8         0x00008000

/*  CSD Register*/

struct csd {
	uint8_t  csd_structure;
	uint8_t  spec_vers;
	uint8_t  taac;
	uint8_t  nsac;
	uint8_t  tran_speed;
	uint16_t ccc;
	uint8_t  read_bl_len;
	uint8_t  read_bl_partial;
	uint8_t  write_blk_misalign;
	uint8_t  read_blk_misalign;
	uint8_t  dsr_imp;
	uint16_t c_size;
	uint8_t  vdd_r_curr_min;
	uint8_t  vdd_r_curr_max;
	uint8_t  vdd_w_curr_min;
	uint8_t  vdd_w_curr_max;
	uint8_t  c_size_mult;
	union {
		struct { /* MMC system specification version 3.1 */
			uint8_t  erase_grp_size;
			uint8_t  erase_grp_mult;
		} v31;
		struct { /* MMC system specification version 2.2 */
			uint8_t  sector_size;
			uint8_t  erase_grp_size;
		} v22;
	} erase;
	uint8_t  wp_grp_size;
	uint8_t  wp_grp_enable;
	uint8_t  default_ecc;
	uint8_t  r2w_factor;
	uint8_t  write_bl_len;
	uint8_t  write_bl_partial;
	uint8_t  file_format_grp;
	uint8_t  copy;
	uint8_t  perm_write_protect;
	uint8_t  tmp_write_protect;
	uint8_t  file_format;
	uint8_t  ecc;
};


/*Function prototypes for SD CARD*/
int SET_BUS_WIDTH(int enable); //corresponds to ACMD6, command required in section. 3.4
                            
int GO_IDLE_STATE(); //sets the card in idle state
#endif