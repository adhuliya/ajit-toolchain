#ifndef ENV_SYSMEM_H__
#define ENV_SYSMEM_H__

#include <stdint.h>

void startSysmemThreads ();
void setSysmemSocketFlag (uint8_t v);
void setSysmemVerboseFlag (uint8_t v);
void setSysmemUseSimplifiedAhbPipes (uint8_t v);
void setSysmemMemAddressMask (uint32_t v);

#endif
