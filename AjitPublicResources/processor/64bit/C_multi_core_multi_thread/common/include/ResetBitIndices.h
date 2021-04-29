#ifndef _ResetBitIndices_h___
#define _ResetBitIndices_h___
#include <stdint.h>

//
// The soft-reset to the processor is
// an 8-bit signal whose bits have
// the following meanings
// 7-3     2              1  		0
// zeros  single-step   debug-mode   hard-reset
#define HARD_RESET_MASK 	0x1
#define DEBUG_MODE_MASK 	0x2
#define SINGLE_STEP_MASK	0x4

#define _isHardReset_(x) (x & HARD_RESET_MASK)
#define _isDebugMode_(x) (x & DEBUG_MODE_MASK)
#define _isSingleStepMode(x) (x & SINGLE_STEP_MASK)

#endif
