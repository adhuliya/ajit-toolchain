#ifndef __device_addresses_h
#define __device_addresses_h

// Change this to 0 if you wish to use
// alternate device address.
#define USE_DEFAULT_DEVICE_ADDRESSES        1


#if USE_DEFAULT_DEVICE_ADDRESSES

#include "default_device_addresses.h"

#else

#include "alternate_device_addresses.h"

#endif

#endif
