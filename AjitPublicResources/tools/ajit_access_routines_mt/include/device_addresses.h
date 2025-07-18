#ifndef __device_addresses_h
#define __device_addresses_h

//
// The currently supported device address mappings
// can be one of the following:
//    - default 
//        addresses are mapped to the range 
//        0xffff0000 to 0xffffffff.
//    - alternate
//        addresses are mapped to the
//        range 0x80000000 to 0x8000ffff.
//
#ifdef USE_ALTERNATE_DEVICE_ADDRESSES
#include "alternate_device_addresses.h"
#else
#include "default_device_addresses.h"
#endif

#endif
