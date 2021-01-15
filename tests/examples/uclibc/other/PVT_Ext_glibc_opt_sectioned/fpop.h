#include <stdint.h>
#include <stdio.h>

#ifdef AJIT
#include "core_portme.h"
#endif

inline void sqrt_ajit_asm_double (uint32_t a, uint32_t b);
inline void sqrt_ajit_asm_single (uint32_t a, uint32_t b);
